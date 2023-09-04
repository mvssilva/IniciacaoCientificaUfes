
FLAGS = -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -g

DEPS = horario.h
OBJ = horario.o main.o

LIBGRAPHS_DEPS = $(patsubst %.c,%.o,$(wildcard ./src/graphs/*.c)) 
LIBED_DEPS = $(patsubst %.c,%.o,$(wildcard ./src/ed/*.c)) 

all: main

%.o: %.c %.h
	gcc $(FLAGS) -c -o $@ $< 

libgraphs.a: $(LIBGRAPHS_DEPS)
	ar -crs libgraphs.a $(LIBGRAPHS_DEPS)

libed.a: $(LIBED_DEPS)
	ar -crs libed.a $(LIBED_DEPS)

main: main.c libgraphs.a libed.a 
	gcc $(FLAGS) -o main main.c -I src/graphs -I src/ed -L . -lgraphs -led -lm

clean:
	rm -f main libgraphs.a libed.a $(LIBGRAPHS_DEPS) $(LIBED_DEPS)
	
run:
	./main <entrada.txt

