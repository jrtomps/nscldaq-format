#-------------- The library libdataformat

lib_LTLIBRARIES	=	libdaqformatio.la

libdaqformatio_la_SOURCES = BufferIOV8.cpp \
                            RingIOV10.cpp \
											RingIOV11.cpp

include_HEADERS	= BufferIOV8.h \
                  RingIOV10.h \
									RingIOV11.h

libdaqformatio_la_CPPFLAGS	=  \
                -I@top_srcdir@/format \
                -I@top_srcdir@/Buffer \
                -I@top_srcdir@/utils

                #-I@top_srcdir@/utilities/IO

libdaqformatio_la_LDFLAGS = -Wl,"-rpath-link=$(libdir)" -lrt

libdaqformatio_la_LIBADD	= \
                        @top_builddir@/Buffer/libbuffer.la \
                        @top_builddir@/format/V8/libdataformatv8.la \
                        @top_builddir@/format/V10/libdataformatv10.la \
                        @top_builddir@/format/V11/libdataformatv11.la


#@top_builddir@/daq/format/libdataformat.la
                        #@top_builddir@/utilities/IO/libdaqio.la


libdaqformatio_la_CXXFLAGS = $(AM_CXXFLAGS)


------------------- Tests:

noinst_PROGRAMS = unittests

unittests_SOURCES	= TestRunner.cpp  \
                            daq8test.cpp \
                                                                                daq10test.cpp \
                                                                                daq11test.cpp

unittests_LDADD		= @builddir@/libdaqformatio.la \
                        @top_builddir@/Buffer/libbuffer.la \
                        @top_builddir@/format/V8/libdataformatv8.la \
                        @top_builddir@/format/V10/libdataformatv10.la \
                        @top_builddir@/format/V11/libdataformatv11.la \
                        $(CPPUNIT_LIBS)

                        #@top_builddir@/daq/format/libdataformat.la		\
                        #@builddir@/libdaqformatio.la \
                        #@top_builddir@/utilities/IO/libdaqio.la


unittests_CPPFLAGS=  -I@top_srcdir@/Buffer \
-I@top_srcdir@/format \
-I@top_srcdir@/testutils

                #-I@top_srcdir@/utilities/IO

unittests_CXXFLAGS = $(AM_CXXFLAGS)

unittests_LDFLAGS	= -Wl,"-rpath-link=$(libdir)"

TESTS=./unittests


