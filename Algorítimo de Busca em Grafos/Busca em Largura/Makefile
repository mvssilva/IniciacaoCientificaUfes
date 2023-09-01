
FLAGS = -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -g

DEPS = horario.h
OBJ = horario.o main.o

LIBSEARCH_DEPS = $(patsubst %.c,%.o,$(wildcard ./src/search/*.c)) 
LIBED_DEPS = $(patsubst %.c,%.o,$(wildcard ./src/ed/*.c)) 

all: main

%.o: %.c %.h
	gcc $(FLAGS) -c -o $@ $< 

libsearch.a: $(LIBSEARCH_DEPS)
	ar -crs libsearch.a $(LIBSEARCH_DEPS)

libed.a: $(LIBED_DEPS)
	ar -crs libed.a $(LIBED_DEPS)

main: main.c libsearch.a libed.a 
	gcc $(FLAGS) -o main main.c -I src/search -I src/ed -L . -lsearch -led -lm

clean:
	rm -f main libsearch.a libed.a $(LIBSEARCH_DEPS) $(LIBED_DEPS)
	
run:
	./main <entrada.txt

