AC_INIT([hello_world], [0.1.0])
AC_LIB_LINKFLAGS([z])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
gl_EARLY
PKG_CHECK_MODULES([CHECK], [check >= 0.9.6]) 
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_FILES([
 Makefile
 lib/Makefile
 src/Makefile
 tests/Makefile
])

gl_INIT
AC_OUTPUT
