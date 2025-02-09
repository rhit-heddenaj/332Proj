all: simple_test.bin

simple_test.bin: simple_test.o

primes.bin: primes.o

CFLAGS += -ggdb

.PHONY: clean all

%.bin: %.o
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm -rf *.bin *.o
