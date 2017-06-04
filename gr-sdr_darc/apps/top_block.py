#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Sun Jun  4 19:13:52 2017
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from gnuradio import analog
from gnuradio import audio
from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from gnuradio.wxgui import fftsink2
from gnuradio.wxgui import forms
from gnuradio.wxgui import waterfallsink2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import math
import osmosdr
import sdr_darc
import time
import wx


class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.xlate_bandwidth = xlate_bandwidth = 100e3
        self.volume = volume = 25
        self.samp_rate = samp_rate = 1.024e6
        self.offset_freq = offset_freq = 250e3
        self.gain = gain = 40
        self.freq = freq = 87.90e6
        self.baseband_rate = baseband_rate = 256000
        self.audio_freq = audio_freq = 48000

        ##################################################
        # Blocks
        ##################################################
        _volume_sizer = wx.BoxSizer(wx.VERTICAL)
        self._volume_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_volume_sizer,
        	value=self.volume,
        	callback=self.set_volume,
        	label="Volume",
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._volume_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_volume_sizer,
        	value=self.volume,
        	callback=self.set_volume,
        	minimum=0,
        	maximum=100,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_volume_sizer, 0, 1, 1, 1)
        _gain_sizer = wx.BoxSizer(wx.VERTICAL)
        self._gain_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_gain_sizer,
        	value=self.gain,
        	callback=self.set_gain,
        	label="RF Gain",
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._gain_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_gain_sizer,
        	value=self.gain,
        	callback=self.set_gain,
        	minimum=0,
        	maximum=49.6,
        	num_steps=124,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_gain_sizer, 0, 0, 1, 1)
        _freq_sizer = wx.BoxSizer(wx.VERTICAL)
        self._freq_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_freq_sizer,
        	value=self.freq,
        	callback=self.set_freq,
        	label="Freq",
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._freq_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_freq_sizer,
        	value=self.freq,
        	callback=self.set_freq,
        	minimum=80e6,
        	maximum=104e6,
        	num_steps=205,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_freq_sizer, 1, 0, 1, 2)
        self.wxgui_waterfallsink2_0 = waterfallsink2.waterfall_sink_f(
        	self.GetWin(),
        	baseband_freq=0,
        	dynamic_range=100,
        	ref_level=0,
        	ref_scale=2.0,
        	sample_rate=baseband_rate,
        	fft_size=512,
        	fft_rate=15,
        	average=False,
        	avg_alpha=None,
        	title="Waterfall Plot",
        )
        self.Add(self.wxgui_waterfallsink2_0.win)
        self.wxgui_fftsink2_1 = fftsink2.fft_sink_c(
        	self.GetWin(),
        	baseband_freq=0,
        	y_per_div=10,
        	y_divs=10,
        	ref_level=0,
        	ref_scale=2.0,
        	sample_rate=baseband_rate,
        	fft_size=1024,
        	fft_rate=15,
        	average=False,
        	avg_alpha=None,
        	title="FFT Plot",
        	peak_hold=False,
        )
        self.Add(self.wxgui_fftsink2_1.win)
        self.sdr_darc_darc_l2_0 = sdr_darc.darc_l2(bool(1))
        self.rtlsdr_source_0 = osmosdr.source( args="numchan=" + str(1) + " " + "" )
        self.rtlsdr_source_0.set_time_unknown_pps(osmosdr.time_spec_t())
        self.rtlsdr_source_0.set_sample_rate(samp_rate)
        self.rtlsdr_source_0.set_center_freq(freq-offset_freq, 0)
        self.rtlsdr_source_0.set_freq_corr(0, 0)
        self.rtlsdr_source_0.set_dc_offset_mode(2, 0)
        self.rtlsdr_source_0.set_iq_balance_mode(0, 0)
        self.rtlsdr_source_0.set_gain_mode(True, 0)
        self.rtlsdr_source_0.set_gain(gain, 0)
        self.rtlsdr_source_0.set_if_gain(20, 0)
        self.rtlsdr_source_0.set_bb_gain(20, 0)
        self.rtlsdr_source_0.set_antenna("", 0)
        self.rtlsdr_source_0.set_bandwidth(0, 0)
          
        self.rational_resampler = filter.rational_resampler_fff(
                interpolation=audio_freq,
                decimation=51200,
                taps=None,
                fractional_bw=None,
        )
        self.low_pass_filter_0 = filter.fir_filter_fff(1, firdes.low_pass(
        	1, baseband_rate, 8000, 4000, firdes.WIN_HAMMING, 6.76))
        self.freq_xlating_fir_filter_xxx_2 = filter.freq_xlating_fir_filter_fcc(1, (firdes.low_pass(1,256000,16000,8000,firdes.WIN_BLACKMAN,6.76)), 76000, samp_rate/4)
        self.freq_xlating_fir_filter_xxx_0 = filter.freq_xlating_fir_filter_ccf(1, (firdes.low_pass(1, samp_rate, xlate_bandwidth, 100000)), offset_freq, samp_rate)
        self.fir_filter_xxx_1 = filter.fir_filter_fff(5, (firdes.low_pass(1.0,256e3,13e3,3e3,firdes.WIN_HAMMING)))
        self.fir_filter_xxx_1.declare_sample_delay(0)
        self.digital_clock_recovery_mm_xx_0 = digital.clock_recovery_mm_ff(int(baseband_rate/16000)*(1+0.0), 0.25*0.175*0.175, 0.5, 0.175, 0.005)
        self.digital_binary_slicer_fb_1 = digital.binary_slicer_fb()
        self.blocks_null_sink_0_0_0 = blocks.null_sink(gr.sizeof_char*24)
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vff((volume, ))
        self.audio_sink_0 = audio.sink(48000, "pulse", True)
        self.analog_wfm_rcv_0 = analog.wfm_rcv(
        	quad_rate=samp_rate,
        	audio_decimation=4,
        )
        self.analog_quadrature_demod_cf_0 = analog.quadrature_demod_cf(baseband_rate/(2*math.pi*8000/8.0))
        self.analog_fm_deemph_0_0_0 = analog.fm_deemph(fs=5, tau=75e-6)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_fm_deemph_0_0_0, 0), (self.blocks_multiply_const_vxx_0, 0))    
        self.connect((self.analog_quadrature_demod_cf_0, 0), (self.low_pass_filter_0, 0))    
        self.connect((self.analog_wfm_rcv_0, 0), (self.fir_filter_xxx_1, 0))    
        self.connect((self.analog_wfm_rcv_0, 0), (self.freq_xlating_fir_filter_xxx_2, 0))    
        self.connect((self.analog_wfm_rcv_0, 0), (self.wxgui_waterfallsink2_0, 0))    
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.rational_resampler, 0))    
        self.connect((self.digital_binary_slicer_fb_1, 0), (self.sdr_darc_darc_l2_0, 0))    
        self.connect((self.digital_clock_recovery_mm_xx_0, 0), (self.digital_binary_slicer_fb_1, 0))    
        self.connect((self.fir_filter_xxx_1, 0), (self.analog_fm_deemph_0_0_0, 0))    
        self.connect((self.freq_xlating_fir_filter_xxx_0, 0), (self.analog_wfm_rcv_0, 0))    
        self.connect((self.freq_xlating_fir_filter_xxx_2, 0), (self.analog_quadrature_demod_cf_0, 0))    
        self.connect((self.freq_xlating_fir_filter_xxx_2, 0), (self.wxgui_fftsink2_1, 0))    
        self.connect((self.low_pass_filter_0, 0), (self.digital_clock_recovery_mm_xx_0, 0))    
        self.connect((self.rational_resampler, 0), (self.audio_sink_0, 0))    
        self.connect((self.rtlsdr_source_0, 0), (self.freq_xlating_fir_filter_xxx_0, 0))    
        self.connect((self.sdr_darc_darc_l2_0, 0), (self.blocks_null_sink_0_0_0, 0))    

    def get_xlate_bandwidth(self):
        return self.xlate_bandwidth

    def set_xlate_bandwidth(self, xlate_bandwidth):
        self.xlate_bandwidth = xlate_bandwidth
        self.freq_xlating_fir_filter_xxx_0.set_taps((firdes.low_pass(1, self.samp_rate, self.xlate_bandwidth, 100000)))

    def get_volume(self):
        return self.volume

    def set_volume(self, volume):
        self.volume = volume
        self._volume_slider.set_value(self.volume)
        self._volume_text_box.set_value(self.volume)
        self.blocks_multiply_const_vxx_0.set_k((self.volume, ))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.freq_xlating_fir_filter_xxx_0.set_taps((firdes.low_pass(1, self.samp_rate, self.xlate_bandwidth, 100000)))
        self.rtlsdr_source_0.set_sample_rate(self.samp_rate)

    def get_offset_freq(self):
        return self.offset_freq

    def set_offset_freq(self, offset_freq):
        self.offset_freq = offset_freq
        self.freq_xlating_fir_filter_xxx_0.set_center_freq(self.offset_freq)
        self.rtlsdr_source_0.set_center_freq(self.freq-self.offset_freq, 0)

    def get_gain(self):
        return self.gain

    def set_gain(self, gain):
        self.gain = gain
        self._gain_slider.set_value(self.gain)
        self._gain_text_box.set_value(self.gain)
        self.rtlsdr_source_0.set_gain(self.gain, 0)

    def get_freq(self):
        return self.freq

    def set_freq(self, freq):
        self.freq = freq
        self._freq_slider.set_value(self.freq)
        self._freq_text_box.set_value(self.freq)
        self.rtlsdr_source_0.set_center_freq(self.freq-self.offset_freq, 0)

    def get_baseband_rate(self):
        return self.baseband_rate

    def set_baseband_rate(self, baseband_rate):
        self.baseband_rate = baseband_rate
        self.analog_quadrature_demod_cf_0.set_gain(self.baseband_rate/(2*math.pi*8000/8.0))
        self.digital_clock_recovery_mm_xx_0.set_omega(int(self.baseband_rate/16000)*(1+0.0))
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.baseband_rate, 8000, 4000, firdes.WIN_HAMMING, 6.76))
        self.wxgui_fftsink2_1.set_sample_rate(self.baseband_rate)
        self.wxgui_waterfallsink2_0.set_sample_rate(self.baseband_rate)

    def get_audio_freq(self):
        return self.audio_freq

    def set_audio_freq(self, audio_freq):
        self.audio_freq = audio_freq


def main(top_block_cls=top_block, options=None):

    tb = top_block_cls()
    tb.Start(True)
    tb.Wait()


if __name__ == '__main__':
    main()
