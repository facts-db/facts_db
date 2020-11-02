
BENCHMARK = \
	set_insert \
	set_insert_overflow \
	set_get

bin_PROGRAMS = \
	benchmark_set_insert \
	benchmark_set_insert_overflow \
	benchmark_set_get
#	benchmark_set_remove \
#	benchmark_facts_add \
#	benchmark_facts_remove

if DEBUG
AM_CFLAGS = -DDEBUG -O0 -ggdb -std=c99 -pedantic -fgnu89-inline
else
AM_CFLAGS = -DNDEBUG -O2 -std=c99 -pedantic -fgnu89-inline
endif

AM_LDFLAGS = ../libfacts_db.la

benchmark: ${BENCHMARK}

set_insert: benchmark_set_insert
	time ./benchmark_set_insert

benchmark_set_insert_SOURCES = \
	benchmark_set_insert.c

set_insert_overflow: benchmark_set_insert_overflow
	time ./benchmark_set_insert_overflow

benchmark_set_insert_overflow_SOURCES = \
	benchmark_set_insert_overflow.c

set_get: benchmark_set_get
	time ./benchmark_set_get

benchmark_set_get_SOURCES = \
	benchmark_set_get.c

.PHONY: benchmark ${BENCHMARK}
