all: main.o
	gcc lectura.o main.o forward.o -o proyecto -lm

main.o: lectura.o forward.o
	gcc -c -g main.c

lectura.o: lectura.c definiciones.h funciones.h
	gcc -c -g lectura.c

forward.o: forward.c definiciones.h funciones.h
	gcc -c -g forward.c

clean:
	rm *.o

test: proyecto 
	./proyecto Casos\ prueba/10-24-1-2.ophs

test100: proyecto
	./proyecto Casos\ prueba/100-240-15-10.ophs

test11: proyecto
	./proyecto Casos\ prueba/11-31-1-2.ophs