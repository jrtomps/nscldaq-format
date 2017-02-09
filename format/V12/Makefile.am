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
                              CCompoundRingItem.cpp \
                              CRingItemParser.cpp \
                              CDataFormatItem.cpp

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
                    CCompoundRingItem.h \
                    CRingItemParser.h \
                    CDataFormatItem.h \
                    format_cast.h \
                    DataFormat.h

libdataformatv12_la_CFLAGS = -I@srcdir@/..

libdataformatv12_la_CPPFLAGS = -I@srcdir@/.. \
                               -I@top_srcdir@/Buffer

libdataformatv12_la_LDFLAGS = @top_builddir@/Buffer/libbuffer.la

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
                        compounditemtests.cpp \
                        ringparsertests.cpp \
                        dataformattest.cpp \
                        formatcasttest.cpp

unittests_LDADD	= $(CPPUNIT_LIBS) 		\
                        @builddir@/libdataformatv12.la	\
                        @top_builddir@/Buffer/libbuffer.la

unittests_CFLAGS= -I@srcdir@/..
unittests_CPPFLAGS= -I@srcdir@/.. \
                    -I@top_srcdir@/Buffer \
		    @CPPUNIT_CFLAGS@ \
                    -I@top_srcdir@/testutils

unittests_LDFLAGS	= -Wl,"-rpath-link=$(libdir)"


TESTS=./unittests
