# FM_DARC - dev

DARC decoding with SDR

This is a GNU Radio project to decode DARC (Data Radio Channel) messages sent with radio broadcasting (FM) at a subcarrier frequency of 76kHz. The receiver is an RTL-SDR R820T2 module. The decoding of the messages from Layer1 to Layer5 follows ETSI EN 300 751 V1.2.1 (2003-01) available at http://www.etsi.org/deliver/etsi_en/300700_300799/300751/01.02.01_60/en_300751v010201p.pdf

To compile and run, the following dependecies have to be met.

1. Install gnuradio-companion
    a. sudo apt-get install gnuradio
2. RTL-SDR
    a. Follow the steps in http://osmocom.org/projects/sdr/wiki/rtl-sdr
    b. git clone git://git.osmocom.org/rtl-sdr.git
    c. cd rtl-sdr/
    d. mkdir build
    e. cd build
    f. cmake ../
    g. make
    h. sudo make install
    i. sudo ldconfig

3. OSMOCOM
    a. Follow the steps in http://osmocom.org/projects/sdr/wiki/rtl-sdr
    b. git clone git://git.osmocom.org/gr-osmosdr
    c. cd gr-osmosdr/
    d. (If you are building for gnuradio 3.6 series, you have to switch to the gr3.6 branch as follows) git checkout gr3.6
    e. mkdir build
    f. cd build/
    g. cmake ../

This project was created using OOT module provided with GNU Radio. To compile, follow similar steps as above,
    a. cd gr-sdr_darc/
    b. mkdir build
    c. cd build
    d. cmake ../
    e. sudo make install
    f. sudo ldconfig

The source code (C++) is present in directory gr-sdr_darc/lib/

To run,
    1. Run 'gnuradio-companion' on a terminal.
    2. Open file 'gr-sdr_darc/apps/sdr_darc.grc' and run.
    3. The decoded messages are output to the console.

The module darc_l2 in grc file is the implemented module and can be found under 'sdr_darc' subsection on the right. It decodes all the layers (almost).

