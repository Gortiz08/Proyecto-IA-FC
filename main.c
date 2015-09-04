#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
#include "funciones.h"

int main(int argc, char **argv){

	datos_problema instancia;
	lectura(argv[1], &instancia);

	int ph = ((instancia).puntos+(instancia).hoteles);

	variable *variables;
	variables = (variable*) malloc((ph*ph) * instancia.num_trips * sizeof(variable));
	
	llenar_dominio(&variables, &instancia);

	fc(0, &variables, &instancia);
	

	free(variables);
	return 0;
}