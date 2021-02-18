all: libfacts_db.la

clean:
	rm -rf .libs *.o *.lo *.la *.gcno

check:
	${MAKE} -C tests check

.PHONY: all clean

.include <config.mk>
