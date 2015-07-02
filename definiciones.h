#ifndef DEF_HEADER
#define DEF_HEADER

//resumen de que hace este .h


//definir la estructura
typedef struct{
	int puntos;
	int hoteles;
	int num_trips;
	int dist_max_tour;
	int *dist_max_trip;
	double *matriz_dist;
	float *puntajes;
}datos_problema;


#endif