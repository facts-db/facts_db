
if DEBUG
AM_CFLAGS = -DDEBUG -O0 -ggdb -std=c99 -pedantic -fgnu89-inline
else
AM_CFLAGS = -DDEBUG -O2 -std=c99 -pedantic -fgnu89-inline
endif

AM_CFLAGS += -fprofile-arcs -ftest-coverage

TESTS = check_fact check_skiplist check_facts
check_PROGRAMS = check_fact check_facts check_skiplist
CLEANFILES = *.gcda *.gcno
GCOV =

check_fact_SOURCES = \
	check_fact.c \
	$(top_builddir)/fact.c
check_fact_CFLAGS = @CHECK_CFLAGS@ ${AM_CFLAGS}
check_fact_LDADD = @CHECK_LIBS@

fact.c.gcov:
	gcov check_fact-fact.c
GCOV += fact.c.gcov

check_facts_SOURCES = \
	check_facts.c \
	$(top_builddir)/binding.c \
	$(top_builddir)/fact.c \
	$(top_builddir)/facts.c \
	$(top_builddir)/skiplist.c
check_facts_CFLAGS = @CHECK_CFLAGS@ ${AM_CFLAGS}
check_facts_LDADD = @CHECK_LIBS@

facts.c.gcov:
	gcov check_facts-facts.c
GCOV += facts.c.gcov

check_skiplist_SOURCES = \
	check_skiplist.c \
	$(top_builddir)/skiplist.c
check_skiplist_CFLAGS = @CHECK_CFLAGS@ ${AM_CFLAGS}
check_skiplist_LDADD = @CHECK_LIBS@

skiplist.c.gcov:
	gcov check_skiplist-skiplist.c
GCOV += skiplist.c.gcov

gcov: ${GCOV}

.PHONY: gcov ${GCOV}
