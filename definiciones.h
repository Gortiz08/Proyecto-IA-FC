#ifndef DEF_HEADER
#define DEF_HEADER

#define NO_PROBLEM -1
#define PROBLEM -2
#define True 1
#define False 0

//Se tienen las estructuras que se utilizaran en la implementacion del algoritmo//


//Estructura que se utiliza para leer los datos del archivo .ophs//
typedef struct{
	int puntos;
	int hoteles;
	int num_trips;
	double dist_max_tour;
	double *dist_max_trip;
	double *matriz_dist;
	float *puntajes;
}datos_problema;

//Estructura que se utiliza para asignar los valores a las variables del problema//
//La variable representa los arcos desde un punto a otro y pueden tomar los valores 0 o 1//
typedef struct{
	int origen;
	int llegada;
	int trip;
	int valor;
	int dominio[2];
}variable;


#endif