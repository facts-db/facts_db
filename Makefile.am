
ACLOCAL_AMFLAGS = -I build-aux/m4

bin_PROGRAMS =
CLEANFILES =
include_HEADERS =
lib_LTLIBRARIES =

if DEBUG
AM_CFLAGS = -DDEBUG -O0 -ggdb -std=c89 -pedantic -fgnu89-inline
else
AM_CFLAGS = -DNDEBUG -O2 -std=c89 -pedantic -fgnu89-inline
endif

lib_LTLIBRARIES += libfacts_db.la
libfacts_db_la_SOURCES = \
	set.c \
	set_skiplist.c \
	skiplist.c
include_HEADERS += \
	set.h \
	set_skiplist.h \
	skiplist.h

SUBDIRS = tests benchmark

benchmark:
	${MAKE} -C benchmark benchmark

.PHONY: benchmark
