
ACLOCAL_AMFLAGS=-I m4

if FORMAT_STANDALONE

SUBDIRS = utils \
          Buffer \
          format \
          FormattedIO \
					testutils

else

# the Buffer package is needed earlier than utilities/IO so the utilities/Makefile
# explicitly builds it prior to the IO package.

SUBDIRS = utils \
          format \
          FormattedIO \
                                        testutils

endif

