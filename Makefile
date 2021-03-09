LIB = libfacts_db.la

all: ${LIB}

benchmark: ${LIB}
	${MAKE} -C benchmark

clean:
	rm -rf .libs *.o *.lo *.la *.gcno
	${MAKE} -C tests clean
	${MAKE} -C benchmark clean

test: ${LIB}

install: ${LIB}
	${LIBTOOL} --mode install ${INSTALL} -o root -g wheel -m 0755 ${LIB} ${LIBDIR}

.PHONY: all benchmark clean install tests

.include <config.mk>
