CC=gcc
CFLAGS=-g -Wall
SPECLIBS=
EXECUTABLES=simirnds

# the first program simply generates a matrix of random integers
simirnds: simirnds.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# let's just compare two geenrations
simitwo: simitwo.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
