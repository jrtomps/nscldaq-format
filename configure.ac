AC_PREREQ(2.61)

AC_INIT([nscldaq-format],1.0-000,[scientificsoftware@nscl.msu.edu])

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AX_CXX_COMPILE_STDCXX_11([noext])

AM_PATH_CPPUNIT


AC_SUBST([AM_CXXFLAGS], [-fno-strict-aliasing])

AM_INIT_AUTOMAKE([foreign])

AM_CONDITIONAL([FORMAT_STANDALONE],[true])

AC_CONFIG_FILES([Makefile
                 utils/Makefile
                 Buffer/Makefile
                 FormattedIO/Makefile
                 IO/Makefile
                 conversion/Makefile
                 format/Makefile
                 format/V8/Makefile
                 format/V10/Makefile
                 format/V11/Makefile
                 format/V12/Makefile])

AC_OUTPUT
