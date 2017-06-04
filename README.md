# FM_DARC
DARC decoding with SDR

This is a GNU Radio project to decode DARC (Data Radio Channel) messages sent with radio broadcasting (FM) at a subcarrier frequency of 76kHz using a RTL-SDR R820T2 module. The decoding of the messages from Layer1 to Layer5 follows ETSI EN 300 751 V1.2.1 (2003-01) available at http://www.etsi.org/deliver/etsi_en/300700_300799/300751/01.02.01_60/en_300751v010201p.pdf

To compile and run, the following dependecies have to be met.

1. Install gnuradio-companion
    sudo apt-get install gnuradio
2. RTL-SDR
    Follow the steps in http://osmocom.org/projects/sdr/wiki/rtl-sdr

    git clone git://git.osmocom.org/rtl-sdr.git
    cd rtl-sdr/
    mkdir build
    cd build
    cmake ../
    make
    sudo make install
    sudo ldconfig

3. OSMOCOM
    Follow the steps in http://osmocom.org/projects/sdr/wiki/rtl-sdr
    git clone git://git.osmocom.org/gr-osmosdr
    cd gr-osmosdr/
        (If you are building for gnuradio 3.6 series, you have to switch to the gr3.6 branch as follows)
        git checkout gr3.6
    mkdir build
    cd build/
    cmake ../

This project was created using OOT module provided with GNU Radio. To compile, follow similar steps
    cd gr-sdr_darc/
    mkdir build
    cd build
    cmake ../
    sudo make install
    sudo ldconfig

The source code (C++) is present in directory gr-sdr_darc/lib/

To run,
    1. Run 'gnuradio-companion' on a terminal.
    2. Open file gr-sdr_darc/apps/sdr_darc.grc
    3. The decoded messages are output to the console.

The module darc_l2 in grc file is the implemented module and can be found under 'sdr_darc' subsection on the right. It decodes all the layers (almost).

