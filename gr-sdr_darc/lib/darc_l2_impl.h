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

#ifndef INCLUDED_SDR_DARC_DARC_L2_IMPL_H
#define INCLUDED_SDR_DARC_DARC_L2_IMPL_H

#include <sdr_darc/darc_l2.h>

namespace gr {
namespace sdr_darc {

    class darc_l2_impl : public darc_l2 {
        private:
            unsigned short l2_data[18];
            void process_l3();
            bool darc_l2_crc14();

        public:
            darc_l2_impl(bool enable_crc);
            ~darc_l2_impl();

            // Where all the action really happens
            void forecast (int noutput_items, gr_vector_int &ninput_items_required);

            int general_work(int noutput_items,
                    gr_vector_int &ninput_items,
                    gr_vector_const_void_star &input_items,
                    gr_vector_void_star &output_items);
    };

} // namespace sdr_darc
} // namespace gr

#endif /* INCLUDED_SDR_DARC_DARC_L2_IMPL_H */

