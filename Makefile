all: main.o
	gcc lectura.o main.o forward.o restricciones.o -o proyecto -lm

main.o: lectura.o forward.o restricciones.o
	gcc -c -g -Wall main.c

lectura.o: lectura.c definiciones.h funciones.h
	gcc -c -g -Wall lectura.c

forward.o: forward.c definiciones.h funciones.h
	gcc -c -g -Wall forward.c

restricciones.o: restricciones.c definiciones.h funciones.h
	gcc -c -g restricciones.c

clean:
	rm *.o

test: proyecto 
	time ./proyecto Casos\ prueba/10-24-1-2.ophs

test100: proyecto
	./proyecto Casos\ prueba/100-240-15-10.ophs

test11: proyecto
	time ./proyecto Casos\ prueba/11-31-1-2.ophs

test04: proyecto
	./proyecto Casos\ prueba/4-20-1-2.ophs

test05: proyecto
	./proyecto Casos\ prueba/5-15-1-2.ophs

test03: proyecto
	./proyecto Casos\ prueba/3-7-0-1.ophs

testT1: proyecto
	time timeout 6400s ./proyecto Casos\ prueba/T1-65-1-2.ophs

test100-35: proyecto
	time timeout 6400s ./proyecto Casos\ prueba/100-35-2-3.ophs

test100-140: proyecto
	time timeout 6400s ./proyecto Casos\ prueba/100-140-15-10.ophs

test100-180: proyecto
	time timeout 6400s ./proyecto Casos\ prueba/100-180-15-8.ophs

test100-210: proyecto
	time timeout 6400s ./proyecto Casos\ prueba/100-210-15-6.ophs

test100-240: proyecto
	time timeout 6400s ./proyecto Casos\ prueba/100-240-15-10.ophs

test100-30: proyecto
	time timeout 6400s ./proyecto Casos\ prueba/100-30-1-2.ophs

test100-80: proyecto
	time timeout 6400s ./proyecto Casos\ prueba/100-80-12-6.ophs