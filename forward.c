#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "definiciones.h"
#include "funciones.h"


int trans3D_to_2D(i,j,k,l,m){
	return i+l*j+k*l*m;
}

//se llenan las variables y el dominio con los datos//
void llenar_dominio(variable **variables, datos_problema instancia){
	int ph = ((instancia).puntos+(instancia).hoteles);
	int i, j, k;
	int index;


	for(i = 0; i< ph; i++){
		for(j = 0; j < ph; j++){
			for(k = 0; k < (instancia.num_trips); k++){
			index = trans3D_to_2D(i,j,k,ph,ph); 
			(*variables)[index].origen = i;
			(*variables)[index].llegada = j;
			(*variables)[index].trip = k;
			(*variables)[index].valor = 0;
			(*variables)[index].dominio[0] = NO_PROBLEM;
			(*variables)[index].dominio[1] = NO_PROBLEM;
			}
		}
	}
}


void fc(int i, variable **variables, datos_problema instancia){
	int l;
	int ph = ((instancia).puntos+(instancia).hoteles);
	int var = ph*ph*(instancia).num_trips;

	for(l = 0; l<2; l++){
		printf("%d %d \n", i, l);
		(*variables)[i].valor = l;
		if((*variables)[i].dominio[l] == NO_PROBLEM){
			if(i == var-1){
				//guardar solucion
				printf("encontro una solucion\n");
			}
			else{
				if(Forward_Checking(i, var, variables, instancia)){
					fc(i+1, variables, instancia);
				}
				restablecer_dom(i, var, variables);
			}
		}
	}
}

int Forward_Checking(int i, int var, variable **variables, datos_problema instancia){
	int flag;
	int j;
	int k;

	for(j = i+1; j < var; j++){
		flag = True;
		for(k = 0; k < 2; k++){
			if((*variables)[j].dominio[k] == NO_PROBLEM){
				//revisar restricciones//
				if(True){
					flag = False;
				}
				else{
					(*variables)[j].dominio[k] = i;
				}
			}
		}
		if(flag){
			return False;
		}
	}
	return True;
}

void restablecer_dom(int i, int var, variable **variables){
	int j, k;

	for(j = i+1; j < var; j++){
		for(k = 0; k < 2; k++){
			if((*variables)[j].dominio[k] == i){
				(*variables)[j].dominio[k] = NO_PROBLEM;
			}
		}
	}
}
