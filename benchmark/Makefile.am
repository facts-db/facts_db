
BENCHMARK = \
	set_insert

bin_PROGRAMS = \
	benchmark_set_insert
#	benchmark_set_remove \
#	benchmark_facts_add \
#	benchmark_facts_remove

if DEBUG
AM_CFLAGS = -DDEBUG -O0 -ggdb -std=c99 -pedantic -fgnu89-inline
else
AM_CFLAGS = -DNDEBUG -O2 -std=c99 -pedantic -fgnu89-inline
endif

LDFLAGS += ../libfacts_db.la

benchmark: ${BENCHMARK}

set_insert: benchmark_set_insert
	time ./benchmark_set_insert

benchmark_set_insert_SOURCES = benchmark_set_insert.c

.PHONY: benchmark set_insert
