/* -*- c++ -*- */

#define SDR_DARC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "sdr_darc_swig_doc.i"

%{
#include "sdr_darc/darc_l2.h"
%}

%include "sdr_darc/darc_l2.h"
GR_SWIG_BLOCK_MAGIC2(sdr_darc, darc_l2);
