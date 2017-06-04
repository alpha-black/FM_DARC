INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_SDR_DARC sdr_darc)

FIND_PATH(
    SDR_DARC_INCLUDE_DIRS
    NAMES sdr_darc/api.h
    HINTS $ENV{SDR_DARC_DIR}/include
        ${PC_SDR_DARC_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    SDR_DARC_LIBRARIES
    NAMES gnuradio-sdr_darc
    HINTS $ENV{SDR_DARC_DIR}/lib
        ${PC_SDR_DARC_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDR_DARC DEFAULT_MSG SDR_DARC_LIBRARIES SDR_DARC_INCLUDE_DIRS)
MARK_AS_ADVANCED(SDR_DARC_LIBRARIES SDR_DARC_INCLUDE_DIRS)

