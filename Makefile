OUT=dice

all: main.o random.o roll.o
	gcc -o $(OUT) main.o random.o roll.o

main.o: main.c
	gcc main.c -c

random.o: random.c random.h
	gcc random.c -c

roll.o: roll.c roll.h random.h
	gcc roll.c -c

install: all
	cp $(OUT) /bin/

uninstall:
	rm /bin/$(OUT)

clean:
	rm *.o -f
