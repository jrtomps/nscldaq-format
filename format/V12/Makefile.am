lib_LTLIBRARIES = libdataformatv12.la

libdataformatv12_la_SOURCES = CRingItem.cpp \
                              CRawRingItem.cpp \
                              CPhysicsEventItem.cpp \
                              CRingScalerItem.cpp \
                              CRingTextItem.cpp \
                              CRingStateChangeItem.cpp \
                              CRingPhysicsEventCountItem.cpp \
                              CGlomParameters.cpp \
                              CRingItemFactory.cpp \
                              CAbnormalEndItem.cpp \
                              CCompositeRingItem.cpp \
                              CRingItemParser.cpp \
                              CDataFormatItem.cpp \
                              StringsToIntegers.cpp

nscldaq12dir = @includedir@/V12

nscldaq12_HEADERS = CRingItem.h \
                    CRawRingItem.h \
                    CPhysicsEventItem.h \
                    CRingScalerItem.h \
                    CRingTextItem.h \
                    CRingStateChangeItem.h \
                    CRingPhysicsEventCountItem.h \
                    CGlomParameters.h \
                    CRingItemFactory.h \
                    CAbnormalEndItem.h \
                    CCompositeRingItem.h \
                    CRingItemParser.h \
                    CDataFormatItem.h \
                    format_cast.h \
                    DataFormat.h \
										StringsToIntegers.h

libdataformatv12_la_CFLAGS = -I@srcdir@/..

if FORMAT_STANDALONE
libdataformatv12_la_CPPFLAGS = -I@srcdir@/.. \
                               -I@top_srcdir@/Buffer \
                               -I@top_srcdir@/utils


libdataformatv12_la_LDFLAGS = @top_builddir@/Buffer/libbuffer.la
else
FORMAT_DIR=utilities/nscldaq-format
libdataformatv12_la_CPPFLAGS = -I@srcdir@/.. \
                               -I@top_srcdir@/$(FORMAT_DIR)/Buffer \
                               -I@top_srcdir@/base/headers

libdataformatv12_la_LDFLAGS = @top_builddir@/$(FORMAT_DIR)/Buffer/libbuffer.la
endif

noinst_PROGRAMS = unittests

unittests_SOURCES	= TestRunner.cpp \
                          rawringitemtests.cpp \
                          physeventtests.cpp \
                            teststate.cpp	\
                        texttest.cpp  \
                        scalertests.cpp \
                        physcounttests.cpp \
                        glomparamtests.cpp \
                        factorytests.cpp \
                        abnormalendtests.cpp \
                        compositeitemtests.cpp \
                        ringparsertests.cpp \
                        dataformattest.cpp \
                        formatcasttest.cpp \
												stringtointstest.cpp

if FORMAT_STANDALONE
unittests_LDADD	= $(CPPUNIT_LIBS) 		\
                        @builddir@/libdataformatv12.la	\
                        @top_builddir@/Buffer/libbuffer.la
unittests_CPPFLAGS= -I@srcdir@/.. \
                    -I@top_srcdir@/Buffer \
		    @CPPUNIT_CFLAGS@ \
                    -I@top_srcdir@/testutils \
                    -I@top_srcdir@/utils
else
unittests_LDADD	= $(CPPUNIT_LIBS) 		\
                        @builddir@/libdataformatv12.la	\
                        @top_builddir@/$(FORMAT_DIR)/Buffer/libbuffer.la
unittests_CPPFLAGS= -I@srcdir@/.. \
                    -I@top_srcdir@/$(FORMAT_DIR)/Buffer \
		    @CPPUNIT_CFLAGS@ \
                    -I@top_srcdir@/$(FORMAT_DIR)/testutils \
                    -I@top_srcdir@/base/headers
endif

unittests_CFLAGS= -I@srcdir@/..

unittests_LDFLAGS	= -Wl,"-rpath-link=$(libdir)"


TESTS=./unittests
