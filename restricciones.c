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

	return i/ph;
}

//se obtiene la dimension z del arreglo, equivalente a los trips//
int dim_z(int i, int ph){

	return i/ph/ph;
}


//Tour parte desde un hotel//
int hotel_ini(int i, int j, int k, variable **variables, datos_problema instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((instancia).puntos+(instancia).hoteles);
	
	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if((x1 == 0 && x1 == x2) && (trip1 == 1 && trip2 == 1)){
		if((*variables)[i].valor == 1 && k == 1){
			return False;
		}
	}
	return True;
}

//Tour termina en un hotel dispobible//
int hotel_final(int i, int j, int k, variable **variables, datos_problema instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((instancia).puntos+(instancia).hoteles);
	
	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if((instancia.num_trips-1 == trip1) && (trip1 == trip2) && (y1 == y2 && y1 == 1)){
		if((*variables)[i].valor == 1 && k == 1){
			return False;
		}
	}
	return True;
}

//Asegurar que el comienzo del trip sea un hotel disponible//
int hotel_inicial_trip(int i, int j, int k, variable **variables, datos_problema instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((instancia).puntos+(instancia).hoteles);


	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if((x1 < instancia.hoteles+2 && x2 < instancia.hoteles+2) && (trip1 == trip2)){
		if((*variables)[i].valor == 1 && k == 1){
			return False;
		}
	}
	return True;
}

//Asegurar que el final del trip sea un hotel disponible//
int hotel_final_trip(int i, int j, int k, variable **variables, datos_problema instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((instancia).puntos+(instancia).hoteles);


	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if((y1 < instancia.hoteles+2 && y2 < instancia.hoteles+2) && (trip1 == trip2)){
		if((*variables)[i].valor == 1 && k == 1){
			return False;
		}
	}
	return True;
}

/*
//Asegurar que si un trip finaliza en un hotel, el siguiente trip comienza en el mismo hotel//
int hotel_final_trip(int i, int j, int k, variable **variables, datos_problema instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int q;
	int ph = ((instancia).puntos+(instancia).hoteles);


	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);
	//FALTA POR TERMINAR//
	if((y1 < instancia.hoteles+2 && x2 < instancia.hoteles+2) && (trip1+1 == trip2) ){
		if((*variables)[i].valor == 1 && k == 0){
			return False;
		}
	}
	return True
}


//Asegurar conectividad entre todos los nodos dentro de cada trip//
int hotel_final_trip(int i, int j, int k, variable **variables, datos_problema instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int q;
	int ph = ((instancia).puntos+(instancia).hoteles);


	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);
	//FALTA POR TERMINAR//
	if((y1 < instancia.hoteles+2 && x2 < instancia.hoteles+2) && (trip1+1 == trip2) ){
		if((*variables)[i].valor == 1 && k == 0){
			return False;
		}
	}
	return True
}
*/


//Asegura que cada vertice sea visitado a lo mas una vez (unicidad de los vertices)//
int unicidad(int i, int j, int k, variable **variables, datos_problema instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((instancia).puntos+(instancia).hoteles);


	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if(x1 > instancia.hoteles+1 && x2 == x1){
		if((*variables)[i].valor == 1 && k == 1){
			return False;
		}
	}
	return True;
}

//Se limita el tiempo de cada trip//
int tiempo_max(int i, int j, int k, variable **variables, datos_problema instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int xs, ys;
	int w;
	int ph = ((instancia).puntos+(instancia).hoteles);
	int dist_rec = 0;


	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	if(trip1 == trip2 && k == 1){
		for(xs = 0; xs < x1; xs++){
			for(ys = 0; ys < y1; ys++){
				w = trans3D_to_1D(xs, ys, trip1, ph, ph);
				if((*variables)[w].valor == 1){
					w = obtener_indice(xs, ys, ph);
					dist_rec += instancia.matriz_dist[w];
				}
			}
		}
		w = obtener_indice(x2, y2, ph);
		dist_rec += instancia.matriz_dist[w];
		if(dist_rec > instancia.dist_max_trip[trip1]){
			return False;
		}
	}
	return True;
}


int revisar_restricciones(int i, int j, int k, variable **variables, datos_problema instancia){
		int r1 = hotel_ini(i, j, k, variables, instancia);
		int r2 = hotel_final(i, j, k, variables, instancia);
		int r3 = hotel_inicial_trip(i, j, k, variables, instancia);
		int r4 = hotel_final_trip(i, j, k, variables, instancia);
		int r5 = unicidad(i, j, k, variables, instancia);
		int r6 = tiempo_max(i, j, k, variables, instancia);

		return r1 && r2 && r3 && r4 && r5 && r6;
}