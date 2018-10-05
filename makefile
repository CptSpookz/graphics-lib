CC = clang
CFLAGS = cg2d.o -Wall -lm -lX11
PROGS = exercicio

all: $(PROGS) 

lib:
	$(CC) -c cg2d.c

.PHONY: clean

clean:
	rm -f *.o *~ $(PROGS)
