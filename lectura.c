#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "definiciones.h"
#include "funciones.h"


//resumen de funcion
int obtener_indice(int x, int y, int l){
	return (x + y*l);
}
//resumen de funcion
void lectura(const char *nombre, datos_problema *instancia){
	FILE *archivo;
	int i;
	int j;
	int k;
	double dist;
	int ph;
	double *x;
	double *y;


	archivo = fopen(nombre, "r");
	fscanf(archivo, "%d", &((*instancia).puntos));

	fscanf(archivo, "%d", &((*instancia).hoteles));

	fscanf(archivo, "%d", &((*instancia).num_trips));

	fscanf(archivo, "%d", &((*instancia).dist_max_tour));

	//Se da memoria para guardar las distancias maximas de cada trip.
	(*instancia).dist_max_trip = malloc((*instancia).num_trips*sizeof(int));
	//Se guarda la distancia maxima de cada trip.
	for(i = 0; i < (*instancia).num_trips; i++){
		fscanf(archivo, "%d", &((*instancia).dist_max_trip[i]));
	}


	ph = ((*instancia).puntos+(*instancia).hoteles);
	//Se da memoria a la matriz donde estaran guardadas las distancias.
	(*instancia).matriz_dist = malloc(ph*ph*sizeof(double));
	//Se asigna memoria a las coordenadas x e y.
	x = malloc(ph*sizeof(double));
	y = malloc(ph*sizeof(double));
	// Se asigna memoria a los puntajes de cada punto y hotel.
	(*instancia).puntajes = malloc(ph*sizeof(double));

	for(i = 0; i < ph; i++){
		fscanf(archivo, "%lf", &(x[i]));
		fscanf(archivo, "%lf", &(y[i]));
		fscanf(archivo, "%f", &((*instancia).puntajes[i]));
	}
	//
	for(i = 0; i < ph; i++){
		for(j= 0; j < ph; j++){
			dist = sqrt(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2));
			k = obtener_indice(i, j, ph);
			(*instancia).matriz_dist[k] = dist;
		}
	}

}


