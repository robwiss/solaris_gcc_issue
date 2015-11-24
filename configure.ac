AC_PREREQ([2.63])
AC_INIT([solaris_gcc_issue], [1.0.0])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11
AC_PROG_LIBTOOL

# Checks for packages.
AM_PATH_XML2([2.9.1], [], [AC_MSG_ERROR([libxml2 not found.])])

# Checks for libraries.
AC_CHECK_LIB([xml2], [xmlParseFile], [], [AC_MSG_ERROR([Dependency libxml2 not found.])])

AC_CONFIG_FILES([
    Makefile
])

AC_OUTPUT
