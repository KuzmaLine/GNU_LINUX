#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([RHASHER], [0.0.0], [1@yandex.ru])
AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_library_init], [], [AC_MSG_ERROR([Unable to find librhash])])
AC_CHECK_LIB([readline], [readline])

# Checks for header files.
AC_CHECK_HEADER([rhash.h], [], [AC_MSG_ERROR([Unable to find rhash.h])])
AC_CHECK_HEADER([readline/readline.h])
AC_CHECK_HEADER([readline/history.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp])

AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--enable-readline], [Enable use readline]),
    AC_DEFINE(ENABLE_READLINE,[],[Use readline lib])
  )

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
