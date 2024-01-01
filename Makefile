OUT=dice

all: main.o random.o
	gcc -o $(OUT) main.o random.o

main.o: main.c
	gcc main.c -c

random.o: random.c random.h
	gcc random.c -c
