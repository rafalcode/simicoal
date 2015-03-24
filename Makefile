CC=gcc
CFLAGS=-g -Wall
SPECLIBS=-lcairo -lm
EXECUTABLES=simirnds simitwo simitwo2 simitwoc simitwoc2

# the first program simply generates a matrix of random integers
simirnds: simirnds.c
	${CC} ${CFLAGS} -o $@ $^

# let's just compare two geenrations and loop back to the nearest common in paris of generations.
simitwo: simitwo.c
	${CC} ${CFLAGS} -o $@ $^

# let's just compare two generations and loop back to the nearest common in paris of generations. Got this sorted out.
simitwo2: simitwo2.c
	${CC} ${CFLAGS} -o $@ $^

# simitwo2 with cairo this time
simitwoc: simitwoc.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# simitwo2 with cairo this time
simitwoc2: simitwoc2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
