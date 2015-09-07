all: main.o
	gcc lectura.o main.o forward.o restricciones.o -o ophs -lm

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

test03: ophs
	time ./ophs Casos\ prueba/3-7-0-1.ophs

test04: ophs
	time ./ophs Casos\ prueba/4-20-1-2.ophs

test05: ophs
	time ./ophs Casos\ prueba/5-15-1-2.ophs

test: ophs 
	time ./ophs Casos\ prueba/10-24-1-2.ophs

test11: ophs
	time ./ophs Casos\ prueba/11-31-1-2.ophs

testT1: ophs
	time timeout 6400s ./ophs Casos\ prueba/T1-65-1-2.ophs

test100-30: ophs
	time timeout 6400s ./ophs Casos\ prueba/100-30-1-2.ophs

test100-35: ophs
	time timeout 6400s ./ophs Casos\ prueba/100-35-2-3.ophs

test100-80: ophs
	time timeout 6400s ./ophs Casos\ prueba/100-80-12-6.ophs

test100-210: ophs
	time timeout 6400s ./ophs Casos\ prueba/100-210-15-6.ophs

test100-180: ophs
	time timeout 6400s ./ophs Casos\ prueba/100-180-15-8.ophs
	
test100-140: ophs
	time timeout 6400s ./ophs Casos\ prueba/100-140-15-10.ophs

test100-240: ophs
	time timeout 6400s ./ophs Casos\ prueba/100-240-15-10.ophs

