/* -*- c++ -*- */
/*
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <arpa/inet.h>
#include <bitset>
#include <gnuradio/io_signature.h>
#include "darc_l2_impl.h"
#include "darc_l2_utils.h"

namespace gr {
namespace sdr_darc {

    darc_l2::sptr darc_l2::make(bool enable_crc) {
        return gnuradio::get_initial_sptr
            (new darc_l2_impl(enable_crc));
    }

    /*
     * The private constructor
     */
    darc_l2_impl::darc_l2_impl(bool enable_crc) : gr::block("darc_l2",
            gr::io_signature::make(1, 1, sizeof(char)),
            gr::io_signature::make(1, 1, sizeof(char) * 24)) {
    }

    /*
     * Our virtual destructor.
     */
    darc_l2_impl::~darc_l2_impl() {
    }

    void darc_l2_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required) {
        ninput_items_required[0] = BLOCK_LEN * (noutput_items+1);
    }

    int darc_l2_impl::general_work (int noutput_items, gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items, gr_vector_void_star &output_items) {

        int n_out_items = 0;
        unsigned short _BIC = 0x0000;
        unsigned int n_items_done = 0;
        const char *input = (const char *) input_items[0];

        while(n_items_done < (ninput_items[0] - BLOCK_LEN)) {
            _BIC = (_BIC << 1) | input[n_items_done];

            if (_BIC == BIC1 || _BIC == BIC2 || _BIC == BIC3 || _BIC == BIC4) {
                std::cout << "BIC found " << get_BIC_string(_BIC);

                /* Unscramble data */
                for (unsigned int i = 0; i < BLOCK_DLEN; ++i) {
                    int indx = i / 16;
                    l2_data[indx] = (l2_data[indx] << 1) | input[++n_items_done];
                    if (i != 0 && i % 16 == 15) {
                        l2_data[indx] = l2_data[indx] ^ scramble_table[indx];
                    }
                }
                process_l3();

                n_out_items++;
                if(noutput_items <= n_out_items) {
                    break;
                }
            } else {
                n_items_done++;
            }
        }
        consume_each(n_items_done);
        return n_out_items;
    }

    void darc_l2_impl::process_l3() {
        std::cout << " CRC14 " << darc_l2_crc14() << "\n";

        /* Only 22 bytes of l2_data is data. Rest are CRC and parity */
        unsigned short *data = NULL;
        unsigned int remaining_bits = 0;

        if ((l2_data[0] & 0xF000) == 0x1000) {
            std::cout << "------------Service channel------------\n";
            std::cout << "---------------------------------------\n";

            printf("CID ((%#x)) ", (l2_data[0] & 0x00F0));
            printf("NID (%#x) ", (l2_data[1] & 0xF000));
            //printf("BLN (%#x) ", ((l2_data[1] & 0x0F00) >> 8));
            printf("BLN (%#x) ", (l2_data[1] & 0x0F00));
            //printf("BLN (%#x) ", ((l2_data[1] >> 8) & 0xF));

            printf("ECC (%#x) ", (l2_data[1] & 0x00FF));
            printf("TSEID (%#x) ", (l2_data[2] & 0xFE00) >> 8);
            printf("Length (%#x) ", (l2_data[2] & 0x01FF));

            std::cout << "Type - ";
            switch (l2_data[0] & 0x000F) {
                case 0x0000:
                    std::cout << "Channel Org. Table, ";
                    printf("Service Identity (%#x) ", ((l2_data[3] & 0xFFFC) >> 2));
                    printf("CA Flag (%#x) ", ((l2_data[3] & 0x0002) >> 1));
                    printf("SA Flag (%#x) ", (l2_data[3] & 0x0001));
                    if (((l2_data[3] & 0x0002) >> 1) == 0x1) {
                        printf("SCA (%#x) ", ((l2_data[4] & 0xFF00) >> 8));
                        data = (unsigned short *)(&l2_data[4] + 8);
                        remaining_bits = BLOCK_INFO_LEN - (4 * 16) - 8;
                    } else {
                        data = (unsigned short *)(&l2_data[4]);
                        remaining_bits = BLOCK_INFO_LEN - (4 * 16);
                    }
                    break;
                case 0x0008:
                    std::cout << "Alternate Freq. Table, ";
                    printf("Frame Type - (%#x) ", ((l2_data[3] & 0xC000) >> 14));
                    printf("AF Number - (%#x) ", ((l2_data[3] & 0x3F00) >> 8));
                    printf("Tuning Frequency - (%#x) ", l2_data[3] & 0x00FF);
                    data = (unsigned short *)(&l2_data[4]);
                    remaining_bits = BLOCK_INFO_LEN - (4 * 16);
                    break;
                case 0x0004:
                    std::cout << "Service Alternate Freq. Table,\n";
                    data = (unsigned short *)(&l2_data[3]);
                    remaining_bits = BLOCK_INFO_LEN - (3 * 16);
                    break;
                case 0x000C:
                    std::cout << "Time, Date, Position and Network name Table,\n";
                    data = (unsigned short *)(&l2_data[3]);
                    remaining_bits = BLOCK_INFO_LEN - (3 * 16);
                    break;
                case 0x0002:
                    std::cout << "Service Name Table,\n";
                    data = (unsigned short *)(&l2_data[3]);
                    remaining_bits = BLOCK_INFO_LEN - (3 * 16);
                    break;
                case 0x000A:
                    std::cout << "Time and Date Table , ";
                    printf("Time (4 bytes) -(%#x) (%#x) ", l2_data[3], l2_data[4]);
                    printf("Date (3 bytes) -(%#x) (%#x) ", l2_data[5],
                            ((l2_data[6] & 0xFF00) >> 8));
                    data = (unsigned short *)(&l2_data[6] + 8);
                    remaining_bits = BLOCK_INFO_LEN - (6 * 16) - 8;
                    break;
                case 0x0006:
                    std::cout << "Synchronous Channel Organization Table, ";
                    data = (unsigned short *)(&l2_data[3]);
                    remaining_bits = BLOCK_INFO_LEN - (3 * 16);
                    break;
                default:
                    std::cout << "Future use, ";
                    break;
            }
            std::cout << "\n";
        } else if ((l2_data[0] & 0xF000) == 0x9000) {
            std::cout << "------------Short Message channel------------\n";
            std::cout << "---------------------------------------------\n";
            /* Just dump */
            data = (unsigned short *)(&(l2_data[0]) + 4);
            remaining_bits = BLOCK_INFO_LEN - 4;
        } else if ((l2_data[0] & 0xF000) == 0x5000) {
            std::cout << "------------Long Message channel------------\n";
            std::cout << "--------------------------------------------\n";
            printf("L3 Header - ");
            printf("DI (%#x) ", ((l2_data[0] & 0x0800) >> 11));
            printf("LF (%#x) ", ((l2_data[0] & 0x0400) >> 10));
            printf("SC (%#x) ", ((l2_data[0] & 0x03C0) >> 6));
            printf("CRC (%#x)\n", (l2_data[0] & 0x003F));
            printf("L4 Header - ");
            printf("RI (%#x) ", ((l2_data[1] & 0xC000) >> 14));
            printf("CI (%#x) ", ((l2_data[1] & 0x3000) >> 12));
            printf("F/L %s ", (get_long_msg_FL((l2_data[1] & 0x0C00) >> 10)).c_str());

            char ext = ((l2_data[1] & 0x0200) >> 9);
            printf("Address (%#x) ", (l2_data[1] & 0x01FF));
            //printf("Printing rest of header in data");
            if (ext == 0x01) {
                data = (unsigned short *)(&l2_data[2] + 8);
                remaining_bits = BLOCK_INFO_LEN - (2 * 16) - 8;
            } else {
                data = (unsigned short *)(&l2_data[2]);
                remaining_bits = BLOCK_INFO_LEN - (2 * 16);
            }
            std::cout << "\n";
        } else if ((l2_data[0] & 0xF000) == 0xD000) {
            std::cout << "------------Block Message channel------------\n";
            std::cout << "---------------------------------------------\n";
            printf("L3 Header - ");
            printf("DI (%#x) ", ((l2_data[0] & 0x0800) >> 11));
            printf("Sch (%#x) ", ((l2_data[0] & 0x0700) >> 8));
            data = (unsigned short *)(&l2_data[0] + 8);
            remaining_bits = BLOCK_INFO_LEN - 8;
            std::cout << "\n";
        }

        if (data) {
            std::cout << "Data dump - \n";
            for (unsigned int i = 0; i < remaining_bits/16; ++i) {
                unsigned short d = ntohs(data[i]);
                printf("%#x ", ((d & 0xFF00) >> 8));
                printf("%#x ", (d & 0x00FF));
            } std::cout << "\n";

            for (unsigned int i = 0; i < remaining_bits/16; ++i) {
                /* Some CRC could get printed with this */
                unsigned short d = ntohs(data[i]);
                unsigned char byte1 = (unsigned char)(((d & 0xFF00) >> 8));
                unsigned char byte2 = (unsigned char)(d & 0x00FF);
                if (byte1 >= 0x20 && byte1 <= 0x7E) {
                    printf("%c ", byte1);
                } else {
                    printf("%#x ", byte1);
                }
                if (byte2 >= 0x20 && byte2 <= 0x7E) {
                    printf("%c ", byte2);
                } else {
                    printf("%#x ", byte2);
                }
            } std::cout << "\n";
        }
    }

    bool darc_l2_impl::darc_l2_crc14() {
        /* L2 data - 176 Info + 14 CRC + 82 Parity */
        std::bitset<190> data;
        for (unsigned int i = 0; i < 12; ++i) {
            unsigned int j_max = std::min (16, int(190 - i*16));
            for (unsigned int j = 0; j < j_max; ++j) {
                data[i*16 + j] = ((l2_data[i] << j) & 0x8000);
            }
        }

        std::bitset<15> pol(0x4805);

        for (int i = 0; i < 172; ++i) {
            if (!data[i]) {
                continue;
            }
            for (int j = 0; j < 15; ++j) {
                data[i+j] = data[i+j] ^ pol[j];
            }
        }
        for (int i = 0; i < 172; ++i) {
            if (data[i] != 0)
                return false;
        }
        return true;
    }

} /* namespace sdr_darc */
} /* namespace gr */
