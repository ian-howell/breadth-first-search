CC = g++
LINKER = -lncurses
EXECUTABLE = bfs
OBJECTS = bfs.o
CFLAGS =

.SUFFIXES: .cpp
.cpp.o: $<
	g++ -c ${CFLAGS} $< -o $@

default: all
all: ${EXECUTABLE}
${EXECUTABLE}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o $@ ${LINKER}

clean:
	-@rm -f core > /dev/null 2>&1
	-@rm -f driver > /dev/null 2>&1
	-@rm -f ${OBJECTS}  > /dev/null 2>&1

# Dependency list
bfs.o: bfs.cpp
