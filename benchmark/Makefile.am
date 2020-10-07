bin_PROGRAMS =

if DEBUG
AM_CFLAGS = -DDEBUG -O0 -ggdb -std=c89 -pedantic -fgnu89-inline
else
AM_CFLAGS = -DNDEBUG -O2 -std=c89 -pedantic -fgnu89-inline
endif

bin_PROGRAMS += benchmark_set
benchmark_set_SOURCES = \
	benchmark_set.c \
	$(top_builddir)/set.c
