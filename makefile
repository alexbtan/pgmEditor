CC=gcc
CCFLAGS = -g -std=c99
MODULES = pgmReadFile.c pgmIsEmpty.c pgmArgCheck.c pgmWriteFile.c


all: pgmReduce pgmComp pgmEcho pgma2b pgmb2a pgmTile pgmAssemble

clean:
	rm -f pgmReduce pgmComp pgmEcho pgma2b pgmb2a pgmTile pgmAssemble

pgmEcho:	pgmEcho.c ${MODULES}
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.c ${MODULES}

pgmComp:	pgmComp.c ${MODULES}
	${CC} ${CCFLAGS} -o pgmComp pgmComp.c ${MODULES}

pgma2b:		pgma2b.c ${MODULES}
	${CC} ${CCFLAGS} -o pgma2b pgma2b.c ${MODULES}

pgmb2a:		pgmb2a.c ${MODULES}
	${CC} ${CCFLAGS} -o pgmb2a pgmb2a.c ${MODULES}

pgmReduce:	pgmReduce.c	${MODULES}
	${CC} ${CCFLAGS} -o pgmReduce pgmReduce.c ${MODULES}

pgmTile:	pgmTile.c ${MODULES}
	${CC} ${CCFLAGS} -o pgmTile pgmTile.c ${MODULES} pgmSplit.c

pgmAssemble:	pgmAssemble.c ${MODULES}
	${CC} ${CCFLAGS} -o pgmAssemble pgmAssemble.c ${MODULES} pgmSplit.c