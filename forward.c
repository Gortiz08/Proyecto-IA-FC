#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "definiciones.h"
#include "funciones.h"


//funcion encargada de pasar desde un arreglo de 3 dimensiones, a un arreglo de 1 dimension//
int trans3D_to_1D(i,j,k,l,m){
	return i+l*j+k*l*m;
}

//se llenan las variables y el dominio con datos//
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


//Funcion principal del forward checking, es la encargada de realizar la recursion, ademas de avanzar//
//e ir instanciando las variables hasta llegar a la ultima.//
//Es la encargada de llamar a Forward_Checking() para ir filtrando los dominios//
//Una vez terminada la iteracion, es la encargada de llamar a restablecer_dom()//
void fc(int i, variable **variables, datos_problema* instancia){
	int l;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int var = ph*ph*(*instancia).num_trips;

	int k, index;

	int desde = 0, trip = 0, punt = 0, lugar = 0;
	double dist_trip[(*instancia).num_trips];

	for(k = 0; k < (*instancia).num_trips; k++){
		dist_trip[k] = 0;
	}


	for(l = 0; l<2; l++){
		//Se asigna 0 o 1 al valor de la variable//
		(*variables)[i].valor = l;
		printf("Variable => origen: %d, destino: %d, Trip: %d  Valor: %d dominio: %d %d \n", (*variables)[i].origen, (*variables)[i].llegada, (*variables)[i].trip, (*variables)[i].valor, (*variables)[i].dominio[0], (*variables)[i].dominio[1]);
		if((*variables)[i].dominio[l] == NO_PROBLEM){
			if(i == var-1){
				//Se verifica que la solucion no tenga subtour, si no tiene subtour se imprime//
				if(subtours(variables, instancia)){
					printf("H0");
					while(trip < (*instancia).num_trips){
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
				}
			}
			else{
				//Se chequean las restricciones//
				//si no encuentra ni un problema se procede a llamar a fc(i+1)//
				if(Forward_Checking(i, var, variables, instancia)){
					fc(i+1, variables, instancia);
				}
				//Se trata de restablecer el dominio de la variable actual//
				restablecer_dom(i, var, variables);
			}
		}
	}
}


//Funcion encargada de chequear que las restricciones se cumplan//
//Se verifica la variable actual con las posibles futuras variables// 
int Forward_Checking(int i, int var, variable **variables, datos_problema* instancia){
	int flag;
	int j;
	int k;

	for(j = i+1; j < var; j++){
		flag = True;
		for(k = 0; k < 2; k++){
			if((*variables)[j].dominio[k] == NO_PROBLEM){
				//Se revisan las restricciones//
				//Si se encuentra algun problema, se retorna False y al valor k del //
				//dominio de la variable j-esima se le asigna i (que es la variable con la cual tiene problemas)//
				//En caso contrario, retorna True y se procede a revisar la siguiente variable j-esima, hasta finalizar// 
				if(revisar_restricciones(i, j, k, variables, instancia)){
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


//Funcion que restablece los dominios de las variables cuando el algoritmo comienza a hacer Backtrack// 
void restablecer_dom(int i, int var, variable **variables){
	int j, k;

	for(j = i+1; j < var; j++){
		for(k = 0; k < 2; k++){
			//Si el valor k del dominio de la variable j-esima es igual al valor de la variable i//
			//se restablece el valor k de dicha variable a "NO_PROBLEM"//
			if((*variables)[j].dominio[k] == i){
				(*variables)[j].dominio[k] = NO_PROBLEM;
			}
		}
		//Se restablece a 0 el "valor" de la variable j-esima//
		(*variables)[j].valor = 0;
	}
}
