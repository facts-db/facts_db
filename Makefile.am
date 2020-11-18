
ACLOCAL_AMFLAGS = -I build-aux/m4

bin_PROGRAMS =
CLEANFILES =
include_HEADERS =
lib_LTLIBRARIES =

if DEBUG
AM_CFLAGS = -DDEBUG -O0 -ggdb -std=c99 -pedantic
else
AM_CFLAGS = -DNDEBUG -O2 -std=c99 -pedantic
endif

lib_LTLIBRARIES += libfacts_db.la
libfacts_db_la_SOURCES = \
	binding.c \
	fact.c \
	facts.c \
	farmhash.c \
	rw.c \
	set.c \
	skiplist.c \
	spec.c
libfacts_db_la_LIBADD = -lm
include_HEADERS += \
	binding.h \
	fact.h \
	facts.h \
	farmhash.h \
	rw.h \
	set.h \
	skiplist.h \
	spec.h

SUBDIRS = . tests benchmark

benchmark:
	${MAKE} -C benchmark benchmark

.PHONY: benchmark
