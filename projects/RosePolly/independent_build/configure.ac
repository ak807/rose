

AC_INIT([accelerate], [0.9], [ak807@doc.ic.ac.uk])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_PROG_CXX
CXXFLAGS="$CXXFLAGS -Wl,--no-as-needed"
AC_CHECK_PROG(RM,rm,rm -f)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
# AM_CONDITIONAL([LAB],[test $HOSTNAME != dark])
AC_CONFIG_SRCDIR([src])

AC_OUTPUT
