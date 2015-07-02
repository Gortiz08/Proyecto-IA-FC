#include <stdio.h>
#include "definiciones.h"
#include "funciones.h"

int main(int argc, char **argv){
	int i;

	datos_problema instancia;
	lectura(argv[1], &instancia);
	
	int ph = ((instancia).puntos+(instancia).hoteles);

	for(i=0; i < ph; i++){
		printf("%f \n", instancia.puntajes[i]);
	}

	/*for(i=0; i < ph*ph; i++){
		if(i % ph == 0)printf("\n");
		printf("%.2f ", instancia.matriz_dist[i]);
		
	}*/




	return 0;
}