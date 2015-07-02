all: main.o
	gcc lectura.o main.o -o proyecto -lm

main.o: lectura.o
	gcc -c main.c

lectura.o: lectura.c definiciones.h funciones.h
	gcc -c lectura.c

clean: main.o
	rm *.o

test: proyecto 
	./proyecto Casos\ prueba/10-24-1-2.ophs