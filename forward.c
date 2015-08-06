#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "definiciones.h"
#include "funciones.h"


int trans3D_to_1D(i,j,k,l,m){
	return i+l*j+k*l*m;
}

//se llenan las variables y el dominio con los datos//
void llenar_dominio(variable **variables, datos_problema* instancia){
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int i, j, k;
	int index;


	for(i = 0; i< ph; i++){
		for(j = 0; j < ph; j++){
			for(k = 0; k < ((*instancia).num_trips); k++){
				index = trans3D_to_1D(i,j,k,ph,ph); 
				(*variables)[index].origen  = i;
				(*variables)[index].llegada = j;
				(*variables)[index].trip = k;
				(*variables)[index].valor = 0;
				(*variables)[index].dominio[0] = NO_PROBLEM;
				if(i > (*instancia).hoteles+1 && j > (*instancia).hoteles+1 && i == j){
					(*variables)[index].dominio[1] = PROBLEM;				
				}
				else{
					(*variables)[index].dominio[1] = NO_PROBLEM;
				}
			}
		}
	}
}


void fc(int i, variable **variables, datos_problema* instancia){
	int l;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int var = ph*ph*(*instancia).num_trips;

	int h,j,k, index;

	int x1, y1, z1;

	int desde = 0, trip = 0, punt = 0, lugar = 0;
	double dist_trip[(*instancia).num_trips];

	for(k = 0; k < (*instancia).num_trips; k++){
		dist_trip[k] = 0;
	}


	for(l = 0; l<2; l++){
		(*variables)[i].valor = l;
		//printf("origen: %d, destino: %d, Trip: %d  Valor: %d dominio: %d \n", (*variables)[i].origen, (*variables)[i].llegada, (*variables)[i].trip, (*variables)[i].valor, (*variables)[i].dominio[l]);
		if((*variables)[i].dominio[l] == NO_PROBLEM){
			if(i == var-1){
				//guardar solucion
				printf("H0");
				while(desde != 1 && trip < (*instancia).num_trips){
					for(k = 0; k < ph; k++){
						index = trans3D_to_1D(desde,k,trip,ph,ph);
						if((*variables)[index].valor == 1){
							lugar = obtener_indice(desde, k, ph);
							dist_trip[trip] += (*instancia).matriz_dist[lugar];
							punt += (*instancia).puntajes[k];
							if(k < (*instancia).hoteles+2){
								trip += 1;
								printf("->H%d", k);
							}else{
								printf("->%d", k - ((*instancia).hoteles+2));
							}
							desde = k;
						}
					}
				}
				printf(" | %d ", punt);
				for(k = 0; k < (*instancia).num_trips; k++){
					printf("| Trip %d: %f ", k +1, dist_trip[k]);
					dist_trip[k] = 0;
				}
				printf("\n");

				// for(k = 0; k < (*instancia).num_trips; k++){
				// 	for(h = 0; h < ph; h++){
				// 		for(j = 0; j < ph ; j++){
				// 			index = trans3D_to_1D(h,j,k,ph,ph);
				// 			if((*variables)[index].valor == 1){
				// 				printf(" I:%d   >>T:%d>>   F:%d", (*variables)[index].origen, (*variables)[index].trip , (*variables)[index].llegada);
				// 			}
				// 		}
				// 	}
				// }
				// printf("\n");

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

int Forward_Checking(int i, int var, variable **variables, datos_problema* instancia){
	int flag;
	int j;
	int k;

	for(j = i+1; j < var; j++){
		flag = True;
		for(k = 0; k < 2; k++){
			//printf("Revisando:  x1: %d, y1: %d, trip: %d, K = %d dominio: %d \n", (*variables)[j].origen, (*variables)[j].llegada, (*variables)[j].trip, k, (*variables)[j].dominio[k]);
			if((*variables)[j].dominio[k] == NO_PROBLEM){
				//revisar restricciones//
				if(revisar_restricciones(i, j, k, variables, instancia)){
					flag = False;
				}
				else{
					(*variables)[j].dominio[k] = i;
				}
			}
			//printf("(despues)Revisando:  x1: %d, y1: %d, trip: %d, dominio: %d \n", (*variables)[j].origen, (*variables)[j].llegada, (*variables)[j].trip, (*variables)[j].dominio[k]);
		}
		if(flag){
			//printf("se deja sin dominio a x1: %d, y1: %d, trip: %d \n", (*variables)[j].origen, (*variables)[j].llegada, (*variables)[j].trip);
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
		(*variables)[j].valor = 0;
	}
}
