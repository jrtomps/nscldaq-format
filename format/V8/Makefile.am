lib_LTLIBRARIES = libdataformatv8.la

libdataformatv8_la_SOURCES = bheader.cpp \
                                CV8Buffer.cpp \
                                CRawBuffer.cpp \
                                CPhysicsEventBuffer.cpp \
                                CScalerBuffer.cpp \
                                CPhysicsEventBodyParser.cpp \
				CGenericBodyParser.cpp \
                                CControlBuffer.cpp \
                                CTextBuffer.cpp \
                                CVoidBuffer.cpp

nscldaq8dir = @includedir@/V8

nscldaq8_HEADERS = DataFormatV8.h \
                    bheader.h \
                    CV8Buffer.h \
                    CRawBuffer.h \
                    CPhysicsEventBuffer.h \
                    CScalerBuffer.h \
                    CPhysicsEventBodyParser.h \
		    CGenericBodyParser.h \
		    CControlBuffer.h \
                    CTextBuffer.h \
                    CVoidBuffer.h \
                    format_cast.h

if FORMAT_STANDALONE
libdataformatv8_la_CXXFLAGS = -I@srcdir@/.. \
                              -I@top_srcdir@/format \
                              -I@top_srcdir@/Buffer
libdataformatv8_la_LDFLAGS = @top_builddir@/Buffer/libbuffer.la
else 
FORMAT_DIR=utilities/nscldaq-format
libdataformatv8_la_CXXFLAGS = -I@srcdir@/.. \
                              -I@top_srcdir@/$(FORMAT_DIR)/format \
                              -I@top_srcdir@/$(FORMAT_DIR)/Buffer
libdataformatv8_la_LDFLAGS = @top_builddir@/$(FORMAT_DIR)/Buffer/libbuffer.la
endif



noinst_PROGRAMS = unittests

unittests_SOURCES	= TestRunner.cpp \
                            ccontrolbuffertest.cpp \
                            physicseventtest.cpp \
			    scalerbuffertest.cpp \
			    format_casttest.cpp \
                            rawbuffertest.cpp \
                            ctextbuffertest.cpp \
			    cvoidbuffertest.cpp \
			    cgenericbodyparsertest.cpp

if FORMAT_STANDALONE
unittests_LDADD	= $(CPPUNIT_LIBS) 		\
                  @builddir@/libdataformatv8.la	\
                  @top_builddir@/Buffer/libbuffer.la

unittests_CPPFLAGS= -I@top_srcdir@/format \
                    -I@top_srcdir@/Buffer \
                    @CPPUNIT_CFLAGS@ \
                    -I@top_srcdir@/testutils \
                    -I@top_srcdir@/utils
else 
unittests_LDADD	= $(CPPUNIT_LIBS) 		\
                  @builddir@/libdataformatv8.la	\
                  @top_builddir@/$(FORMAT_DIR)/Buffer/libbuffer.la

unittests_CPPFLAGS= -I@top_srcdir@/$(FORMAT_DIR)/format \
                    -I@top_srcdir@/$(FORMAT_DIR)/Buffer \
                    @CPPUNIT_CFLAGS@ \
                    -I@top_srcdir@/$(FORMAT_DIR)/testutils \
                    -I@top_srcdir@/$(FORMAT_DIR)/utils
endif

unittests_LDFLAGS = -Wl,"-rpath-link=$(libdir)"


TESTS=./unittests


EXTRA_DIST = ChangeBufferSize.h
