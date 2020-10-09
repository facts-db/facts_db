
if DEBUG
AM_CFLAGS = -DDEBUG -O0 -ggdb -std=c99 -pedantic -fgnu89-inline
else
AM_CFLAGS = -DDEBUG -O2 -std=c99 -pedantic -fgnu89-inline
endif

TESTS = check_skiplist check_set
check_PROGRAMS = check_skiplist check_set
check_skiplist_SOURCES = \
	check_skiplist.c \
	$(top_builddir)/skiplist.h \
	$(top_builddir)/skiplist.c
check_skiplist_CFLAGS = @CHECK_CFLAGS@ ${AM_CFLAGS}
check_skiplist_LDADD = @CHECK_LIBS@

check_set_SOURCES = \
	check_set.c \
	$(top_builddir)/set.c \
	$(top_builddir)/skiplist.c
check_set_CFLAGS = @CHECK_CFLAGS@ ${AM_CFLAGS}
check_set_LDADD = @CHECK_LIBS@
