#ifndef __DARC_L2_UTILS_H__
#define __DARC_L2_UTILS_H__

#define BIC1            0x135E
#define BIC2            0x74A6
#define BIC3            0xA791
#define BIC4            0xC875

inline const std::string get_BIC_string(unsigned short _bic) {
    switch(_bic) {
        case BIC1:
            return "BIC1";
        case BIC2:
            return "BIC2";
        case BIC3:
            return "BIC3";
        case BIC4:
            return "BIC4";
        default:
            return "Wrong BIC";
    }
    return "Wrong BIC";
}

inline const std::string get_long_msg_FL(unsigned short fl) {
    switch(fl) {
        case 0x0000:
            return "Intermediate Message";
        case 0x0001:
            return "Last Message";
        case 0x0002:
            return "First Message";
        case 0x0003:
            return "The one and only message";
        default:
            return "Bad F/L value.";
    }
}

/* From windytan */
static const unsigned short scramble_table[19] =
                { 0xAFAA, 0x814A, 0xF2EE, 0x073A, 0x4F5D,
                  0x4486, 0x70BD, 0xB343, 0xBC3F, 0xE0F7,
                  0xC5CC, 0x8253, 0xB479, 0xF362, 0xA471,
                  0xB571, 0x3110, 0x0846, 0x1390};

/* From EN 300 751
 * One frame consists of 272 rows of data. Each row contains a block of 288 bits.
 * This block comprises a BIC (Block Identification Code) of 16 bits and a
 * data block of 272 bits.
 * The data blocks may be of two types:
 *      1. information blocks
 *      2. parity blocks.
 *
 * There are three specified types of frames: Frame A, Frame B and Frame C.
 * Frame A and B comprise 190 information blocks and 82 parity blocks.
 * Frame C comprises 272 information blocks and no parity block.
 * The different frames are distinguished by the BIC codes. */

#define BLOCK_LEN       288
#define BLOCK_DLEN      272
#define BIC_LEN         16
#define BLOCK_INFO_LEN  176

#define L2_BODY_LEN     BLOCK_DLEN

/* Frame A -
 * 60 information blocks with BIC3;
 * 70 information blocks with BIC2;
 * 60 information blocks with BIC1;
 * 82 parity blocks with BIC4.
 **/


/* Frame B is interleaved with parity blocks in the same frame
 **/

#endif
