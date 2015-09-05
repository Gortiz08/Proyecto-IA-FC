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

	//Se inicializa fc con 0//
	fc(0, &variables, &instancia);
	

	free(variables);
	return 0;
}