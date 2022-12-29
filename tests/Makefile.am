TESTS = check_word_wrap hello_simple_check.sh


TESTS_ENVIRONMENT = \
  PATH=$(top_srcdir):$(PATH) \
  export PATH;

check_PROGRAMS = check_word_wrap
check_DIR = $(top_builddir)/tests $(top_builddir)/src
check_word_wrap_SOURCES = word_wrap_check.c
check_word_wrap_CFLAGS = @CHECK_CFLAGS@
check_word_wrap_LDADD = $(top_builddir)/src/word_wrap.o $(top_builddir)/src/debug_log.o $(top_builddir)/src/printf.o @CHECK_LIBS@
