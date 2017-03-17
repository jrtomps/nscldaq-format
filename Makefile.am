
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

DIST_SUBDIRS = $(SUBDIRS)
endif

# we need this so that make distclean does not try to clean out Buffer twice:
# Once from the main/utilities/Makefile level and once from this level. You can
# imagine how doing it the second time would fail...there would be no more Makefile
# to run make with.
DIST_SUBDIRS = $(SUBDIRS)

