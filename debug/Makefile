SRC = $(wildcard *c)
BINS = al.bin student.bin selection.bin

CFLAGS += -ggdb -Werror

.PHONY: all clean

all: ${BINS}

# update the dependency for student.bin
student.bin: sllist.c sllist.h

%.bin: %.o
	${CC} ${CFLAGS} ${LDLIBS} -o $@ $^

clean:
	rm -rf ${BINS} *.o
