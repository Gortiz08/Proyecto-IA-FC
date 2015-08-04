#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "definiciones.h"
#include "funciones.h"



//se obtiene la dimension x del arreglo//
int dim_x(int i, int ph){
	
	return i%ph;
}

//se obtiene la dimension y del arreglo//
int dim_y(int i, int ph){

	return (i/ph)%ph;
}

//se obtiene la dimension z del arreglo, equivalente a los trips//
int dim_z(int i, int ph){

	return (i/ph)/ph;
}


//Tour parte desde un hotel//
int hotel_ini(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int q, sum = 0;

	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);


	if((x1 == 0 && x1 == x2) && (trip1 == 0 && trip2 == 0)){
		if((*variables)[i].valor == 1 && k == 1){
			printf("R1, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
			return False;
		}
		//Revisa si hay alguna variable instanciada con 1//
		if((ph - 2) == y1 && k == 0){
			for(q = 0; q < ph; q++){
				sum += (*variables)[trans3D_to_1D(x1, q, trip1, ph, ph)].valor;
			}
			if(sum == 1){
				return True;
			}
			else{
				printf("R1, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
				return False;
			}
		}
	}
	return True;
}

//Tour termina en un hotel dispobible//
int hotel_final(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int q, sum = 0;

	x1 = dim_x(i, ph); //ultima que instancie
	x2 = dim_x(j, ph); //alguna de las que no he instanciado

	y1 = dim_y(i, ph); //componente y de la ultima variable instanciada (llegada) 
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if(((*instancia).num_trips-1 == trip1) && (trip1 == trip2) && (y1 == y2 && y1 == 1)){
		if((*variables)[i].valor == 1 && k == 1){
			printf("R2, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
			return False;
		}
		if((ph - 2) == x1 && k == 0){
			for(q = 0; q < ph; q++){
				sum += (*variables)[trans3D_to_1D(q, y1, trip1, ph, ph)].valor;
			}
			if(sum == 1){
				return True;
			}
			else{
				printf("R2, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
				return False;
			}
		}
	}
	return True;
}

//Asegurar que el comienzo del trip sea un hotel disponible//
int hotel_inicial_trip(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int q, h, sum = 0;

	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if((x1 < (*instancia).hoteles+2 && x2 < (*instancia).hoteles+2) && (trip1 == trip2)){
		if((*variables)[trans3D_to_1D(x1, y1, trip1, ph, ph)].valor == 1 && k == 1){
			printf("R3, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, k);
			return False;
		}
		if((*instancia).hoteles == x1 && y1 == (ph-1) && k == 0){
			for(q = 0; q < (*instancia).hoteles+2; q++){
				for(h = 0; h < ph; h++){
					sum += (*variables)[trans3D_to_1D(q, h, trip1, ph, ph)].valor;
				}
			}
			if(sum == 1){
				return True;
			}
			else{
				printf("R3, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, k);
				return False;
			}
		}
	}
	return True;
}

//Asegurar que el final del trip sea un hotel disponible//
int hotel_final_trip(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int h, q, sum = 0;

	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if((y1 < (*instancia).hoteles+2 && y2 < (*instancia).hoteles+2) && (trip1 == trip2)){
		if((*variables)[i].valor == 1 && k == 1){
			printf("R4, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, k);
			return False;
		}
		if((*instancia).hoteles+1 == y1 && x1 == (ph-2) && k == 0){
			for(q = 0; q < (*instancia).hoteles+2; q++){
				for(h = 0; h < ph; h++){
					sum += (*variables)[trans3D_to_1D(h, q, trip1, ph, ph)].valor;
					//printf("%d %d %d %d\n", q, h, trip1, sum );
				}
			}
			if(sum == 1){
				return True;
			}
			else{
				printf("R4, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, k);
				return False;
			}
		}
	}
	return True;
}


//Asegurar que si un trip finaliza en un hotel, el siguiente trip comienza en el mismo hotel//
int hotel_final_hotel_inicial_trip(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int h, q, sum = 0;


	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);
	if((x2 < (*instancia).hoteles+2) && x1 == x2 && trip1 == trip2 && trip1 > 0){
		for(q = 0; q < ph; q++){
			sum += (*variables)[trans3D_to_1D(q, x1, trip1-1, ph, ph)].valor;
		}
		if(sum == 1){
			if((*variables)[i].valor == 1 && k == 1){
				printf("R5, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
				return False;
			}
			if(ph-2 == y1){
				sum = 0;	
				for(q = 0; q < ph; q++){
					sum += (*variables)[trans3D_to_1D(x1, q, trip1, ph, ph)].valor;
				}
				if(sum == 0 && k == 0){
					printf("R5, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
					return False;
				}
			}
		}
		else{
			if(k == 1){
				printf("R5, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
				return False;
			}
		}
	}
	return True;
}


//Asegurar conectividad entre todos los nodos dentro de cada trip//
int conectividad(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int h, q, sum = 0;


	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if(ph-1 == x1 && y1 == x2 && trip1 == trip2 && y1 > (*instancia).hoteles+1){
		sum = 0;
		for(q = 0; q < ph; q++){
			sum += (*variables)[trans3D_to_1D(q, y1, trip1, ph, ph)].valor;
		}
		if(sum == 0 && k == 1){	
			printf("R6 sum = 0 y k = 1, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
			return False;
		}
	}
	if((y1 > (*instancia).hoteles+1) && (y1 == y2) && (trip1 == trip2)){
		for(q = 0; q < ph; q++){
			sum += (*variables)[trans3D_to_1D(y1, q, trip1, ph, ph)].valor;
		}
		if(sum == 1){
			if((*variables)[i].valor == 1 && k == 1){
				printf("R6 valor = 1 y K = 1, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
				return False;
			}
			if(ph-2 == x1){
				sum = 0;	
				for(q = 0; q < ph; q++){
					sum += (*variables)[trans3D_to_1D(q, y1, trip1, ph, ph)].valor;
				}
				if(sum == 0 && k == 0){
					printf("R6 sum = 0 y K = 0, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
					return False;
				}
			}
		}
		else{
			if(k == 1){
				printf("R6 K = 1, x1: %d, y1: %d, trip: %d ValorProblem: %d\n", x2, y2, trip1, (*variables)[i].valor);
				return False;
			}
		}
	}
	return True;
}


//Asegura que cada vertice sea visitado a lo mas una vez (unicidad de los vertices)//
int unicidad(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);


	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if(x2 == x1 && x1 > (*instancia).hoteles+1){
		if((*variables)[i].valor == 1 && k == 1){
			printf("R7, x1: %d, y1: %d, trip: %d, x2: %d, y2: %d, trip: %d, ValorProblem: %d\n", x1, y1, trip1, x2, y2, trip2, (*variables)[i].valor);
			return False;
		}
	}
	return True;
}

//Se limita el tiempo de cada trip//
int tiempo_max(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int trips, xs, ys;
	int w, index;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	double dist_rec = 0;


	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if(trip1 == trip2 && k == 1){
		for(index = 0; index <= i; index++){
			trips = dim_z(index,ph);
			if(trips == trip1){
				if((*variables)[index].valor == 1){
					xs = dim_x(index,ph);
					ys = dim_y(index,ph);
					w = obtener_indice(xs,ys,ph);
					dist_rec += (*instancia).matriz_dist[w];
				}
			}
		}
		w = obtener_indice(x2, y2, ph);
		dist_rec += (*instancia).matriz_dist[w];
		if(dist_rec > (*instancia).dist_max_trip[trip1]){
			printf("R8, x1: %d, y1: %d, trip: %d ValorProblem: %d distancia rec: %f \n", x2, y2, trip2, (*variables)[i].valor, dist_rec);
			return False;
		}
	}
	return True;
}


int revisar_restricciones(int i, int j, int k, variable **variables, datos_problema* instancia){
		int r1 = hotel_ini(i, j, k, variables, instancia);
		int r2 = hotel_final(i, j, k, variables, instancia);
		int r3 = hotel_inicial_trip(i, j, k, variables, instancia);
		int r4 = hotel_final_trip(i, j, k, variables, instancia);
		int r5 = hotel_final_hotel_inicial_trip(i, j, k, variables, instancia);
		int r6 = conectividad(i, j, k, variables, instancia);
		int r7 = unicidad(i, j, k, variables, instancia);
		int r8 = tiempo_max(i, j, k, variables, instancia);
		return r1 && r2 && r3 && r4 && r5 && r6 && r7 && r8;
}