all: libfacts_db.la

clean:
	rm -rf .libs *.o *.lo *.la *.gcno
	${MAKE} -C tests clean
	${MAKE} -C benchmark clean

check:
	${MAKE} -C tests

tests: check

benchmark:
	${MAKE} -C benchmark

.PHONY: all clean tests benchmark

.include <config.mk>
