SRC = $(wildcard *c)
BINS = pointer.bin demo.bin fork_demo.bin fork_list.bin advanced.bin

CFLAGS += -ggdb -Werror

.PHONY: all clean

all: ${BINS}

%.bin: %.o
	${CC} ${CFLAGS} ${LDLIBS} -o $@ $^

clean:
	rm -rf ${BINS} *.o
