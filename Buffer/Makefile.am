lib_LTLIBRARIES = libbuffer.la


libbuffer_la_SOURCES = ByteOrder.cpp

include_HEADERS = ByteBuffer.h \
                  ByteOrder.h \
                  BufferPtr.h \
                  Deserializer.h \
                  Deserializer2.h

noinst_PROGRAMS = unittests


unittests_SOURCES = TestRunner.cpp \
                    translatorptrtest.cpp \
                    byteordertest.cpp\
                    bytebuffertest.cpp \
                    deserializertest.cpp

unittests_LDADD	= libbuffer.la

if FORMAT_STANDALONE
unittests_CPPFLAGS= -I@top_srcdir@/testutils \
                    $(CPPUNIT_CFLAGS)
else
unittests_CPPFLAGS= -I@top_srcdir@/base/testutils \
                    $(CPPUNIT_CFLAGS)
endif

unittests_LDFLAGS = $(CPPUNIT_LIBS) \
                -Wl,"-rpath-link=$(libdir)"

TESTS=./unittests

