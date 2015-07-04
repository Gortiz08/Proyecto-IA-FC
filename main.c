#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
#include "funciones.h"

int main(int argc, char **argv){
	int i;

	datos_problema instancia;
	lectura(argv[1], &instancia);
	
	int ph = ((instancia).puntos+(instancia).hoteles);

	variable *variable;
	variable = malloc(sizeof(variable)*(ph*ph)*instancia.num_trips);

	llenar_dominio(&variable, instancia);

	fc(0, &variable, instancia);



	for(i=0; i < ph; i++){
		printf("%f \n", instancia.puntajes[i]);
	}

	/*for(i=0; i < ph*ph; i++){
		if(i % ph == 0)printf("\n");
		printf("%.2f ", instancia.matriz_dist[i]);
		
	}*/




	return 0;
}