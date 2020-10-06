AC_PREREQ([2.59])
AC_INIT([facts_db], [0.1], [kmx.io], [facts_db], [http://kmx.io/])
CFLAGS="$CFLAGS -W -Wall -Werror"
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])
AC_CONFIG_SRCDIR([skiplist.c])
AC_CONFIG_HEADERS([config.h:config.h.in])

AM_INIT_AUTOMAKE
AM_PROG_AR

PKG_CHECK_MODULES([CHECK], [check >= 0.9.6])
AC_PROG_CC

LT_INIT()

if test -d /usr/local/include; then
  CPPFLAGS="$CPPFLAGS -I/usr/local/include"
fi
if test -d /usr/local/lib; then
  LDFLAGS="$LDFLAGS -L/usr/local/lib"
fi

if test -d /usr/include; then
  CPPFLAGS="$CPPFLAGS -I/usr/include"
fi
if test -d /usr/lib; then
  LDFLAGS="$LDFLAGS -L/usr/lib"
fi

AC_ARG_ENABLE(debug,
  AS_HELP_STRING([--enable-debug],
                 [enable debugging, default: yes]),
  [case "${enableval}" in
     yes) debug=true ;;
      no) debug=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]);;
   esac],
  [debug=true])
AM_CONDITIONAL([DEBUG], [test x"$debug" = x"true"])

AC_FUNC_ALLOCA

AC_CONFIG_FILES([Makefile
                 tests/Makefile])
AC_OUTPUT
