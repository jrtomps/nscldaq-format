lib_LTLIBRARIES = libdataformatv10.la

libdataformatv10_la_SOURCES = CRingItem.cpp \
                           CRingScalerItem.cpp \
                           CRingTimestampedRunningScalerItem.cpp \
                           CRingStateChangeItem.cpp \
                           CPhysicsEventItem.cpp \
                           CRingPhysicsEventCountItem.cpp \
                           CRingTextItem.cpp \
                           CRingFragmentItem.cpp \
                           CUnknownFragment.cpp \
                           CRingItemFactory.cpp \
                           ringitem.cpp

nscldaq10dir = @includedir@/V10

nscldaq10_HEADERS = CRingItem.h \
                  CRingScalerItem.h \
                  CRingTimestampedRunningScalerItem.h \
                  CRingStateChangeItem.h \
                  CPhysicsEventItem.h \
                  CRingPhysicsEventCountItem.h \
                  CRingTextItem.h \
                  CRingFragmentItem.h \
                  CUnknownFragment.h \
                  CRingItemFactory.h \
                  CVoidItem.h \
                  DataFormat.h

if FORMAT_STANDALONE
libdataformatv10_la_CXXFLAGS = -I@srcdir@/.. \
                               -I@top_srcdir@/Buffer

libdataformatv10_la_LDFLAGS = @top_builddir@/Buffer/libbuffer.la
else 
FORMAT_DIR=utilities/nscldaq-format
libdataformatv10_la_CXXFLAGS = -I@srcdir@/.. \
                               -I@top_srcdir@/$(FORMAT_DIR)/Buffer

libdataformatv10_la_LDFLAGS = @top_builddir@/$(FORMAT_DIR)/Buffer/libbuffer.la
endif

noinst_PROGRAMS = unittests

unittests_SOURCES	= TestRunner.cpp \
                                                                                ringitemtests.cpp teststate.cpp	\
                                                                                scalertests.cpp texttest.cpp physcounttests.cpp		\
                                                                                formatoutputtests.cpp physeventtests.cpp

if FORMAT_STANDALONE
unittests_LDADD	= $(CPPUNIT_LIBS) 		\
                        @top_builddir@/Buffer/libbuffer.la \
                        @builddir@/libdataformatv10.la

unittests_CPPFLAGS= -I@srcdir@/.. \
                    $(CPPUNIT_CFLAGS) \
                    -I@top_srcdir@/Buffer \
                    -I@top_srcdir@/testutils
else
#FORMAT_DIR=utilities/nscldaq-format
unittests_LDADD	= $(CPPUNIT_LIBS) 		\
                        @top_builddir@/$(FORMAT_DIR)/Buffer/libbuffer.la \
                        @builddir@/libdataformatv10.la

unittests_CPPFLAGS= -I@srcdir@/.. \
                    $(CPPUNIT_CFLAGS) \
                    -I@top_srcdir@/$(FORMAT_DIR)/Buffer \
                    -I@top_srcdir@/$(FORMAT_DIR)/testutils
endif


unittests_LDFLAGS	= -Wl,"-rpath-link=$(libdir)"


TESTS=./unittests
