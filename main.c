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

	llenar_dominio(&variable, &instancia);

	fc(0, &variable, &instancia);
	
	return 0;
}