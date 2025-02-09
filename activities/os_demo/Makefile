all: glue illusionist referee

.PHONY: all clean

glue: glue.c
	gcc -o glue glue.c

illusionist: illusionist.c
	gcc -o illusionist illusionist.c -fno-stack-protector

referee: referee.c
	gcc -o referee referee.c

clean:
	rm -rf glue illusionist referee malloc fptrs
