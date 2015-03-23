CC=gcc
CFLAGS=-g -Wall
SPECLIBS=
EXECUTABLES=simirnds simitwo simitwo2

# the first program simply generates a matrix of random integers
simirnds: simirnds.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# let's just compare two geenrations and loop back to the nearest common in paris of generations.
simitwo: simitwo.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# let's just compare two geenrations and loop back to the nearest common in paris of generations.
simitwo2: simitwo2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
