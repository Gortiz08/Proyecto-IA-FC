#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "definiciones.h"
#include "funciones.h"


//Funcion que sirve para saber la posicion que ocupara una variable de 3 dimensiones//
//en un arreglo de una dimension. Se necesita la posicion en cada eje coordenado de la//
//variable de 3 dimensiones//
int obtener_indice(int x, int y, int l){
	return (x + y*l);
}

//Funcion que se encarga de la lectura del archivo .ophs//
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

	fscanf(archivo, "%lf", &((*instancia).dist_max_tour));

	//Se da memoria para guardar las distancias maximas de cada trip//
	(*instancia).dist_max_trip =(double *) malloc( (*instancia).num_trips * sizeof(double) );
	//Se guarda la distancia maxima de cada trip//
	for(i = 0; i < (*instancia).num_trips; i++){
		fscanf(archivo, "%lf", &((*instancia).dist_max_trip[i]));
	}


	ph = ((*instancia).puntos+(*instancia).hoteles);
	//Se da memoria a la matriz donde estaran guardadas las distancias//
	(*instancia).matriz_dist = (double *) malloc((ph*ph) * sizeof(double));
	//Se asigna memoria a las coordenadas x e y//
	x = malloc(ph*sizeof(double));
	y = malloc(ph*sizeof(double));
	// Se asigna memoria a los puntajes de cada POI y hotel//
	(*instancia).puntajes = (double *) malloc(ph*sizeof(double));

	for(i = 0; i < ph; i++){
		fscanf(archivo, "%lf", &(x[i]));
		fscanf(archivo, "%lf", &(y[i]));
		fscanf(archivo, "%lf", &((*instancia).puntajes[i]));
	}

	//Calculando distancia//
	for(i = 0; i < ph; i++){
		for(j= 0; j < ph; j++){
			dist = sqrt(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2));
			k = obtener_indice(i, j, ph);
			(*instancia).matriz_dist[k] = dist;
		}
	}
	free(x);
	free(y);

}


