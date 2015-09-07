#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
#include "funciones.h"



int main(int argc, char **argv){

	datos_problema instancia;
	//Leyendo los datos desde .ophs//
	lectura(argv[1], &instancia);

	int ph = ((instancia).puntos+(instancia).hoteles);

	variable *variables;
	variables = (variable*) malloc((ph*ph) * instancia.num_trips * sizeof(variable));
	
	//Llenando el dominio a las variables//
	llenar_dominio(&variables, &instancia);

	int *mejor_result;
	mejor_result =  (int*) malloc((ph*ph) * instancia.num_trips * sizeof(int));
	int index, trip = 0, k = 0, desde = 0, mejor_punt = 0;

	//Se inicializa fc con 0//
	fc(0, &mejor_punt, &mejor_result, &variables, &instancia);
	
	//Se utiliza para guardar el mejor resultado encontrado//
	//Se imprime una vez que halla terminado de encontrar todas las soluciones//
	printf("H0");
	while(trip < (instancia).num_trips){
		for(k = 0; k < (ph*ph) * instancia.num_trips; k++){
			index = trans3D_to_1D(desde,k,trip,ph,ph);
			if(mejor_result[index] == 1){
				if(k < (instancia).hoteles+2){
					trip += 1;
					printf("->H%d", k);
				}else{
					printf("->%d", k - ((instancia).hoteles+2));
				}
				desde = k;
			}
		}
	}
	printf(" | %d ", mejor_punt);
	printf("\n");

	
	free(variables);
	return 0;
}