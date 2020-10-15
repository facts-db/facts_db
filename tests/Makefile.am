
if DEBUG
AM_CFLAGS = -DDEBUG -O0 -ggdb -std=c99 -pedantic -fgnu89-inline
else
AM_CFLAGS = -DDEBUG -O2 -std=c99 -pedantic -fgnu89-inline
endif

TESTS = check_fact check_skiplist
check_PROGRAMS = check_fact check_skiplist

check_fact_SOURCES = \
	check_fact.c \
	$(top_builddir)/fact.c
check_fact_CFLAGS = @CHECK_CFLAGS@ ${AM_CFLAGS}
check_fact_LDADD = @CHECK_LIBS@

check_skiplist_SOURCES = \
	check_skiplist.c \
	$(top_builddir)/skiplist.h \
	$(top_builddir)/skiplist.c
check_skiplist_CFLAGS = @CHECK_CFLAGS@ ${AM_CFLAGS}
check_skiplist_LDADD = @CHECK_LIBS@
