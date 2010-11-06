# directories
SRC=src
DEST=build
DOC=doc
NAME=embedded-cli-demo

# compiler settings
CC=colorgcc -O2 -Wall -ansi -pedantic

# dependencies

#main targets
all: main

doc:
	doxygen

clean:
	rm -fr ${DEST}  
	rm -fr ${DOC}
	
# sub targets
mkdir:
	mkdir -p ${DEST}

main: mkdir
	${CC} -o ${DEST}/${NAME} ${SRC}/main.c ${SRC}/cmd.c
