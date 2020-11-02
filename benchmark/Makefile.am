
BENCHMARK = \
	set_add \
	set_add_overflow \
	set_get \
	set_remove

bin_PROGRAMS = \
	benchmark_set_add \
	benchmark_set_add_overflow \
	benchmark_set_get \
	benchmark_set_remove
#	benchmark_facts_add \
#	benchmark_facts_remove

if DEBUG
AM_CFLAGS = -DDEBUG -O0 -ggdb -std=c99 -pedantic -fgnu89-inline
else
AM_CFLAGS = -DNDEBUG -O2 -std=c99 -pedantic -fgnu89-inline
endif

AM_LDFLAGS = ../libfacts_db.la

benchmark: ${BENCHMARK}

set_add: benchmark_set_add
	time ./benchmark_set_add

benchmark_set_add_SOURCES = \
	benchmark_set_add.c

set_add_overflow: benchmark_set_add_overflow
	time ./benchmark_set_add_overflow

benchmark_set_add_overflow_SOURCES = \
	benchmark_set_add_overflow.c

set_get: benchmark_set_get
	time ./benchmark_set_get

benchmark_set_get_SOURCES = \
	benchmark_set_get.c

set_remove: benchmark_set_remove
	time ./benchmark_set_remove

benchmark_set_remove_SOURCES = \
	benchmark_set_remove.c

.PHONY: benchmark ${BENCHMARK}
