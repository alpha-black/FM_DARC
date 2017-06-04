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


#ifndef INCLUDED_SDR_DARC_DARC_L2_H
#define INCLUDED_SDR_DARC_DARC_L2_H

#include <sdr_darc/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace sdr_darc {

    /*!
     * \brief <+description of block+>
     * \ingroup sdr_darc
     *
     */
    class SDR_DARC_API darc_l2 : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<darc_l2> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of sdr_darc::darc_l2.
       *
       * To avoid accidental use of raw pointers, sdr_darc::darc_l2's
       * constructor is in a private implementation
       * class. sdr_darc::darc_l2::make is the public interface for
       * creating new instances.
       */
      static sptr make(bool enable_crc);
    };

  } // namespace sdr_darc
} // namespace gr

#endif /* INCLUDED_SDR_DARC_DARC_L2_H */

