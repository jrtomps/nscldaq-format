#-------------- The library libdataformat

lib_LTLIBRARIES	=	libdaqformatio.la


if FORMAT_STANDALONE

########################################################################
#
# STANDALONE BUILD

libdaqformatio_la_SOURCES = BufferIOV8.cpp \
                            RingIOV10.cpp \
                            RingIOV11.cpp \
                            RingIOV12.cpp

include_HEADERS	= BufferIOV8.h \
                  RingIOV10.h \
                  RingIOV11.h \
                  RingIOV12.h


libdaqformatio_la_CPPFLAGS	=  \
                -I@top_srcdir@/format \
                -I@top_srcdir@/Buffer \
                -I@top_srcdir@/utils

libdaqformatio_la_LIBADD	= \
                        @top_builddir@/Buffer/libbuffer.la \
                        @top_builddir@/format/V8/libdataformatv8.la \
                        @top_builddir@/format/V10/libdataformatv10.la \
                        @top_builddir@/format/V11/libdataformatv11.la \
                        @top_builddir@/format/V12/libdataformatv12.la
else

########################################################################
#
# NSCLDAQ  Build


FORMAT_DIR=utilities/nscldaq-format

libdaqformatio_la_SOURCES = BufferIOV8.cpp \
                            RingIOV10.cpp \
                            RingIOV11.cpp \
                            RingIOV12.cpp \
                            CRingSelectPredWrapper.cpp \
                            CRingSelectionPredicate.cpp \
                            CAllButPredicate.cpp \
                            CDesiredTypesPredicate.cpp \
                            CSimpleAllButPredicate.cpp  \
                            CSimpleDesiredTypesPredicate.cpp

include_HEADERS	= BufferIOV8.h \
                  RingIOV10.h \
                  RingIOV11.h \
                  RingIOV12.h \
                  CRingSelectPredWrapper.h \
                  CRingSelectionPredicate.h \
                  CAllButPredicate.h \
                  CDesiredTypesPredicate.h \
                  CSimpleAllButPredicate.h \
                  CSimpleDesiredTypesPredicate.h \
                  CDataSourcePredicate.h


libdaqformatio_la_CPPFLAGS	=  \
                -I@top_srcdir@/$(FORMAT_DIR)/format \
                -I@top_srcdir@/$(FORMAT_DIR)/Buffer \
                -I@top_srcdir@/$(FORMAT_DIR)/utils \
                -I@top_srcdir@/utilities/IO \
                -I@top_srcdir@/base/dataflow \
                -I@top_srcdir@/base/os \
                -DNSCLDAQ_BUILD

libdaqformatio_la_LIBADD	= \
                        @top_builddir@/$(FORMAT_DIR)/Buffer/libbuffer.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V8/libdataformatv8.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V10/libdataformatv10.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V11/libdataformatv11.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V12/libdataformatv12.la \
                        @top_builddir@/utilities/IO/libdaqio.la \
                        @top_builddir@/base/os/libdaqshm.la
endif


libdaqformatio_la_LDFLAGS = -Wl,"-rpath-link=$(libdir)" -lrt



libdaqformatio_la_CXXFLAGS = $(AM_CXXFLAGS)


------------------- Tests:

noinst_PROGRAMS = unittests



if FORMAT_STANDALONE

########################################################################
#
# STANDALONE BUILD

unittests_SOURCES	= TestRunner.cpp  \
                            daq8test.cpp \
                                                                                daq10test.cpp \
                                                                                daq11test.cpp \
                                                                                daq12test.cpp
unittests_LDADD		= @builddir@/libdaqformatio.la \
                        @top_builddir@/Buffer/libbuffer.la \
                        @top_builddir@/format/V8/libdataformatv8.la \
                        @top_builddir@/format/V10/libdataformatv10.la \
                        @top_builddir@/format/V11/libdataformatv11.la \
                        @top_builddir@/format/V12/libdataformatv12.la \
                        $(CPPUNIT_LIBS)

unittests_CPPFLAGS=  -I@top_srcdir@/Buffer \
-I@top_srcdir@/format \
-I@top_srcdir@/testutils

else

########################################################################
#
# NSCLDAQ  Build

unittests_SOURCES	= TestRunner.cpp  \
                            daq8test.cpp \
                            daq10test.cpp \
                            daq11test.cpp \
                            daq12test.cpp \
                            selecttest.cpp \
                            csimpleallbutpredicatetest.cpp


unittests_LDADD		= @builddir@/libdaqformatio.la \
                        @top_builddir@/$(FORMAT_DIR)/Buffer/libbuffer.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V8/libdataformatv8.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V10/libdataformatv10.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V11/libdataformatv11.la \
                        @top_builddir@/$(FORMAT_DIR)/format/V12/libdataformatv12.la \
                        @top_builddir@/utilities/IO/libdaqio.la \
                        @top_builddir@/base/dataflow/libDataFlow.la \
                        @top_builddir@/base/os/libdaqshm.la \
                        $(CPPUNIT_LIBS)



unittests_CPPFLAGS=  -I@top_srcdir@/$(FORMAT_DIR)/Buffer \
-I@top_srcdir@/$(FORMAT_DIR)/format \
-I@top_srcdir@/$(FORMAT_DIR)/testutils \
-I@top_srcdir@/utilities/IO \
-I@top_srcdir@/base/os \
-I@top_srcdir@/base/dataflow
endif

unittests_CXXFLAGS = $(AM_CXXFLAGS)

unittests_LDFLAGS = -Wl,"-rpath-link=$(libdir)"

TESTS=./unittests


