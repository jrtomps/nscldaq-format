lib_LTLIBRARIES = libdataformatv11.la

libdataformatv11_la_SOURCES = CRingItem.cpp \
                           CAbnormalEndItem.cpp \
                           CRingScalerItem.cpp \
                           CRingStateChangeItem.cpp \
                           CPhysicsEventItem.cpp \
                           CRingPhysicsEventCountItem.cpp \
                           CRingTextItem.cpp \
                           CRingFragmentItem.cpp \
                           CGlomParameters.cpp \
                           CUnknownFragment.cpp \
                           CDataFormatItem.cpp \
                           CRingItemFactory.cpp \
                                                                                                        RingItemComparisons.cpp \
                                                                                                        StringsToIntegers.cpp \
													 ringitem.c 
nscldaq11dir = @includedir@/V11

nscldaq11_HEADERS = CRingItem.h \
                  CAbnormalEndItem.h \
                  CRingScalerItem.h \
                  CRingStateChangeItem.h \
                  CPhysicsEventItem.h \
                  CRingPhysicsEventCountItem.h \
                  CRingTextItem.h \
                  CRingFragmentItem.h \
                  CGlomParameters.h \
                  CUnknownFragment.h \
                  CDataFormatItem.h \
                  CRingItemFactory.h \
                  RingItemComparisons.h \
                  DataFormatV11.h \
                  StringsToIntegers.h

libdataformatv11_la_CFLAGS = -I@srcdir@/..

libdataformatv11_la_CXXFLAGS = -I@srcdir@/..

noinst_PROGRAMS = unittests

unittests_SOURCES	= TestRunner.cpp \
										ringitemtests.cpp teststate.cpp	\
										scalertests.cpp texttest.cpp physcounttests.cpp		\
                                                                                physeventtests.cpp \
										formatoutputtests.cpp dataformattests.cpp       \
                                                                                fragmenttest.cpp glomparamtests.cpp factorytests.cpp \
                                                                                stringtointstest.cpp

if FORMAT_STANDALONE
unittests_CPPFLAGS = -I@srcdir@/.. \
                    $(CPPUNIT_CFLAGS) \
                    -I@top_srcdir@/testutils
else
FORMAT_DIR=utilities/nscldaq-format
unittests_CPPFLAGS = -I@srcdir@/.. \
                    $(CPPUNIT_CFLAGS) \
                    -I@top_srcdir@/$(FORMAT_DIR)/testutils
endif

unittests_LDADD	= -L$(libdir) $(CPPUNIT_LIBS) 		\
                        @builddir@/libdataformatv11.la
unittests_CFLAGS = -I@srcdir@/..
unittests_LDFLAGS = -Wl,"-rpath-link=$(libdir)"


TESTS=./unittests
