#-------------- The library libdataformat

lib_LTLIBRARIES	=	libdaqformatio.la

libdaqformatio_la_SOURCES = BufferIOV8.cpp \
                            RingIOV10.cpp \
											RingIOV11.cpp

include_HEADERS	= BufferIOV8.h \
                  RingIOV10.h \
									RingIOV11.h

if FORMAT_STANDALONE
libdaqformatio_la_CPPFLAGS	=  \
                -I@top_srcdir@/format \
                -I@top_srcdir@/Buffer \
                -I@top_srcdir@/utils

libdaqformatio_la_LIBADD	= \
                        @top_builddir@/Buffer/libbuffer.la \
                        @top_builddir@/format/V8/libdataformatv8.la \
                        @top_builddir@/format/V10/libdataformatv10.la \
                        @top_builddir@/format/V11/libdataformatv11.la
else
FORMAT_DIR=utilities/nscldaq-format
libdaqformatio_la_CPPFLAGS	=  \
                -I@top_srcdir@/$(FORMAT_DIR)/format \
                -I@top_srcdir@/$(FORMAT_DIR)/Buffer \
                -I@top_srcdir@/$(FORMAT_DIR)/utils \
								-I@top_srcdir@/utilities/IO \
								-DNSCLDAQ_BUILD

libdaqformatio_la_LIBADD	= \
                        @top_builddir@/$(FORMAT_DIR)/Buffer/libbuffer.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V8/libdataformatv8.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V10/libdataformatv10.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V11/libdataformatv11.la \
												@top_builddir@/utilities/IO/libdaqio.la
endif


libdaqformatio_la_LDFLAGS = -Wl,"-rpath-link=$(libdir)" -lrt



libdaqformatio_la_CXXFLAGS = $(AM_CXXFLAGS)


------------------- Tests:

noinst_PROGRAMS = unittests

unittests_SOURCES	= TestRunner.cpp  \
                            daq8test.cpp \
                                                                                daq10test.cpp \
                                                                                daq11test.cpp

if FORMAT_STANDALONE
unittests_LDADD		= @builddir@/libdaqformatio.la \
                        @top_builddir@/Buffer/libbuffer.la \
                        @top_builddir@/format/V8/libdataformatv8.la \
                        @top_builddir@/format/V10/libdataformatv10.la \
                        @top_builddir@/format/V11/libdataformatv11.la \
                        $(CPPUNIT_LIBS)

unittests_CPPFLAGS=  -I@top_srcdir@/Buffer \
-I@top_srcdir@/format \
-I@top_srcdir@/testutils

else

unittests_LDADD		= @builddir@/libdaqformatio.la \
                        @top_builddir@/$(FORMAT_DIR)/Buffer/libbuffer.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V8/libdataformatv8.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V10/libdataformatv10.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V11/libdataformatv11.la \
												@top_builddir@/utilities/IO/libdaqio.la \
                        $(CPPUNIT_LIBS)



unittests_CPPFLAGS=  -I@top_srcdir@/$(FORMAT_DIR)/Buffer \
-I@top_srcdir@/$(FORMAT_DIR)/format \
-I@top_srcdir@/$(FORMAT_DIR)/testutils \
-I@top_srcdir@/utilitites/IO
endif

unittests_CXXFLAGS = $(AM_CXXFLAGS)

unittests_LDFLAGS	= -Wl,"-rpath-link=$(libdir)"

TESTS=./unittests


