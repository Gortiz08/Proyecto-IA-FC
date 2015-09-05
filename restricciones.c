#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "definiciones.h"
#include "funciones.h"



//A partir de la variable "i", del arreglo 1D, se obtiene la posicion en el eje X del arreglo 3D//
int dim_x(int i, int ph){
	
	return i%ph;
}

//A partir de la variable "i", del arreglo 1D, se obtiene la posicion en el eje Y del arreglo 3D//
int dim_y(int i, int ph){

	return (i/ph)%ph;
}

//A partir de la variable "i", del arreglo 1D, se obtiene la posicion en el eje Z (trips) del arreglo 3D//
int dim_z(int i, int ph){

	return (i/ph)/ph;
}


//Asegura que el tour parta desde un hotel (Hotel = 0)//
int hotel_ini(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int q, sum = 0;

	//Se obtienen las componentes que se necesiten (x, y, z) de las variables i y j//
	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);


	//Si i es el hotel inicial y j quiere ser el hotel inicial, ambos en el trip 0//
	//se retorna Falso//
	if((x1 == 0 && x1 == x2) && (trip1 == 0 && trip2 == 0)){
		if((*variables)[i].valor == 1 && k == 1){
			return False;
		}
		//Si se esta en la penultima posicion de las variables que pueden ser hoteles iniciales..// 
		//..se suman todas las variables anteriores. Si la suma no es 1 se retorna Falso//
		//Falso porque quiere decir que no existe hotel inicial//
		if((ph - 2) == y1 && k == 0){
			for(q = 0; q < ph; q++){
				sum += (*variables)[trans3D_to_1D(x1, q, trip1, ph, ph)].valor;
			}
			if(sum == 1){
				return True;
			}
			else{
				return False;
			}
		}
	}
	return True;
}

//Asegura que el tour termina en un hotel dispobible//
int hotel_final(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int y2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int q, sum = 0;

	//Se obtienen las componentes que se necesiten (x, y, z) de las variables i y j//
	x1 = dim_x(i, ph);

	y1 = dim_y(i, ph); 
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	//Si se esta en el trip final, i y j pertenecen al trip final y la componente "y" de i y j es un hotel final//
	if(((*instancia).num_trips-1 == trip1) && (trip1 == trip2) && (y1 == y2 && y1 == 1)){
		//Si la variable i ya es el hotel final y j quiere ser un hotel final, se retorna Falso//
		if((*variables)[i].valor == 1 && k == 1){
			return False;
		}
		//Si se esta en la penultima variable de las que pueden ser hoteles finales (i) y el valor del dominio de j es 0//
		//Se suman todas las variables hacia atras, si la suma no es 1, se retorna Falso//
		//Falso porque quiere decir que no existe un hotel final en el Tour//
		if((ph - 2) == x1 && k == 0){
			for(q = 0; q < ph; q++){
				sum += (*variables)[trans3D_to_1D(q, y1, trip1, ph, ph)].valor;
			}
			if(sum == 1){
				return True;
			}
			else{
				return False;
			}
		}
	}
	return True;
}

//Asegura que el comienzo del trip sea un hotel disponible//
int hotel_inicial_trip(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int q, h, sum = 0;

	//Se obtienen las componentes que se necesiten (x, y, z) de las variables i y j//
	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	//Si la variable i y j pertenece a alguno de los hoteles y ambas variables estan en el mismo trip//
	if((x1 < (*instancia).hoteles+2 && x2 < (*instancia).hoteles+2) && (trip1 == trip2)){
		//Si i ya es un hotel y j quiere ser un hotel, se retorna Falso//
		if((*variables)[trans3D_to_1D(x1, y1, trip1, ph, ph)].valor == 1 && k == 1){
			return False;
		}
		//Si se esta en la ultima variable de los que pueden ser hoteles y el valor del dominio de j es 0//
		//Se suman todos valores de los hoteles, si la suma no es 1 se retorna Falso//
		//Se retorna Falso porque quiere decir que no existe un hotel ya instanciado en el trip//
		if((*instancia).hoteles == x1 && y1 == (ph-1) && k == 0){
			for(q = 0; q < (*instancia).hoteles+2; q++){
				for(h = 0; h < ph; h++){
					sum += (*variables)[trans3D_to_1D(q, h, trip1, ph, ph)].valor;
				}
			}
			if(sum == 1){
				return True;
			}
			else{
				return False;
			}
		}
	}
	return True;
}

//Asegurar que el final del trip sea un hotel disponible//
int hotel_final_trip(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int y2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int h, q, sum = 0;

	//Se obtienen las componentes que se necesiten (x, y, z) de las variables i y j//
	x1 = dim_x(i, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	//Restriccion que funciona con la misma logica que la anterior//
	//Solo que ahora se chequea para un hotel final en el trip//

	if((y1 < (*instancia).hoteles+2 && y2 < (*instancia).hoteles+2) && (trip1 == trip2)){
		if((*variables)[i].valor == 1 && k == 1){
			return False;
		}
		if((*instancia).hoteles+1 == y1 && x1 == (ph-2) && k == 0){
			for(q = 0; q < (*instancia).hoteles+2; q++){
				for(h = 0; h < ph; h++){
					sum += (*variables)[trans3D_to_1D(h, q, trip1, ph, ph)].valor;
				}
			}
			if(sum == 1){
				return True;
			}
			else{
				return False;
			}
		}
	}
	return True;
}


//Asegurar que si un trip finaliza en un hotel, el siguiente trip comienza en el mismo hotel//
int hotel_final_hotel_inicial_trip(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int q, sum = 0;

	//Se obtienen las componentes que se necesiten (x, y, z) de las variables i y j//
	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	//Si i y j son hoteles y estan en el mismo trip (que no es el primero)//
	//Se procede a sumar todas las variables que ya fueron instanciadas (como hoteles de llegada)//
	if((x2 < (*instancia).hoteles+2) && x1 == x2 && trip1 == trip2 && trip1 > 0){
		for(q = 0; q < ph; q++){
			sum += (*variables)[trans3D_to_1D(q, x1, trip1-1, ph, ph)].valor;
		}
		//Si la suma es 1 y "j" quiere ser un hotel, se retorna Falso//
		if(sum == 1){
			if((*variables)[i].valor == 1 && k == 1){
				return False;
			}
			//Si estoy en el penultimo de los hoteles, se procede a sumar de nuevo//
			if(ph-2 == y1){
				sum = 0;	
				for(q = 0; q < ph; q++){
					sum += (*variables)[trans3D_to_1D(x1, q, trip1, ph, ph)].valor;
				}
				//Si la suma del valor de las variables es 0 y j no quiere ser un hotel, se retorna Falso//
				//Falso porque al no haber hotel previamente instanciado, j deberia ser un hotel//
				if(sum == 0 && k == 0){
					return False;
				}
			}
		}
		else{
			//Si la suma es 0 y j quiere ser un hotel, se retorna Falso//
			//Falso porque al ser la suma 0, quiere decir que no existe hotel de llegada, por ende..//
			//..no puede haber hotel de salida//
			if(k == 1){
				return False;
			}
		}
	}
	return True;
}


//Asegurar conectividad entre todos los nodos dentro de cada trip//
int conectividad(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1, y1, trip1;
	int x2, y2, trip2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int q;

	//Identificadores que nos permiten saber si la variable en cuestion se utiliza para llegar o para salir del POI u hotel//
	int flag_salgo_x = False, flag_llego_x = False, flag_salgo_y = False, flag_llego_y = False;
	//Identificador que nos permite saber si la variable a estudiar pertenece a las variables que llegan o a las que salen//
	int flag_pertenece;
	
	int sum_salgo_x = 0, sum_llega_x = 0, sum_salgo_y = 0, sum_llega_y = 0;
	int pos;

	//Se obtienen las componentes que se necesiten (x, y, z) de las variables i y j//
	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	y1 = dim_y(i, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);


	//Si j es un POI, obtengo obtengo todas las variables que empiecen con la misma coordenada x que j//
	if(x2 > (*instancia).hoteles+1){
		for(q = 0; q < ph; q++){
			pos = trans3D_to_1D(x2, q, trip2, ph, ph);
			if(pos == j){
				//Si la flag es 0, quiere decir que la variable j esta "saliendo"//
				flag_pertenece = 0;
			}
			//Si las variables obtenidas anteriormente son menores o iguales a la variable i//
			//sumo todos los que salen desde el x2 que han sido instanciados//
			if(pos <= i){
				sum_salgo_x += (*variables)[pos].valor;
			}
			//reviso que todos los que salen del x2 y no han sido instanciados, puedan tomar el valor 1// 
			else{
				if(pos != j && (*variables)[pos].dominio[1] == NO_PROBLEM){
					//True cuando pueden valer 1//
					flag_salgo_x = True;
					break;
				}
			}
		}

		for(q = 0; q < ph; q++){
			pos = trans3D_to_1D(q, x2, trip2, ph, ph);
			if(pos == j){
				//Si la flag es 1, quiere decir que la variable j esta "llegando"//
				flag_pertenece = 1;
			}
			//Si las variables obtenidas anteriormente son menores o iguales a la variable i//
			//sumo todos los que llegan al x2 que han sido instanciados//
			if(pos <= i){
				sum_llega_x += (*variables)[pos].valor;
			}
			//reviso que todos los que llegan al x2 y no han sido instanciados, puedan tomar el valor 1// 
			else{
				if(pos != j && (*variables)[pos].dominio[1] == NO_PROBLEM){
					flag_llego_x = True;
					break;
				}
			}
		}

		//Restricciones para cuando j sale (x2)//


		if(sum_salgo_x == 0 && sum_llega_x == 1 && k == 0 && flag_pertenece == 0 && flag_salgo_x == False){
			return False;
		}
		else if(sum_salgo_x == 1 && sum_llega_x == 0 && k == 0 && flag_pertenece == 1 && flag_llego_x == False){
			return False;
		}
		else if(sum_salgo_x == 1 && k == 1 & flag_pertenece == 0){
			return False;
		}
		else if(sum_llega_x == 1 && k == 1 & flag_pertenece == 1){
			return False;
		}
		if(sum_salgo_x == 0 && sum_llega_x == 0 && k == 1 && flag_pertenece == 0 && flag_llego_x == False){
			return False;
		}
		if(sum_salgo_x == 0 && sum_llega_x == 0 && k == 1 && flag_pertenece == 1 && flag_salgo_x == False){
			return False;
		}
	}

	//Si j es un POI, obtengo obtengo todas las variables que terminen con la misma coordenada y que j//
	if(y2 > (*instancia).hoteles+1){
		for(q = 0; q < ph; q++){
			pos = trans3D_to_1D(q, y2, trip2, ph, ph);
			if(pos == j){
				//Si la flag es 0, quiere decir que la variable j esta "llegando"//
				flag_pertenece = 0;
			}
			//Si las variables obtenidas anteriormente son menores o iguales a la variable i//
			//sumo todos los que llegan al y2 que han sido instanciados//
			if(pos <= i){
				sum_salgo_y += (*variables)[pos].valor;
			}
			//reviso que todos los que llegan al y2 y no han sido instanciados, puedan tomar el valor 1// 
			else{
				if(pos != j && (*variables)[pos].dominio[1] == NO_PROBLEM){
					flag_salgo_y = True;
					break;
				}
			}
		}

		for(q = 0; q < ph; q++){
			pos = trans3D_to_1D(y2, q, trip2, ph, ph);
			if(pos == j){
				//Si la flag es 1, quiere decir que la variable j esta "saliendo"//
				flag_pertenece = 1;
			}
			//Si las variables obtenidas anteriormente son menores o iguales a la variable i//
			//sumo todos los que salen del y2 que han sido instanciados//
			if(pos <= i){
				sum_llega_y += (*variables)[pos].valor;
			}
			//reviso que todos los que salen del y2 y no han sido instanciados, puedan tomar el valor 1// 
			else{
				if(pos != j && (*variables)[pos].dominio[1] == NO_PROBLEM){
					flag_llego_y = True;
					break;
				}
			}
		}

		//restricciones para cuando j llega (y2)//


		if(sum_salgo_y == 0 && sum_llega_y == 1 && k == 0 && flag_pertenece == 0 && flag_salgo_y == False){
			return False;
		}
		else if(sum_salgo_y == 1 && sum_llega_y == 0 && k == 0 && flag_pertenece == 1 && flag_llego_y == False){
			return False;
		}
		else if(sum_salgo_y == 1 && k == 1 & flag_pertenece == 0){
			return False;
		}
		else if(sum_llega_y == 1 && k == 1 & flag_pertenece == 1){
			return False;
		}
		if(sum_salgo_y == 0 && sum_llega_y == 0 && k == 1 && flag_pertenece == 0 && flag_llego_y == False){
			return False;
		}
		if(sum_salgo_y == 0 && sum_llega_y == 0 && k == 1 && flag_pertenece == 1 && flag_salgo_y == False){
			return False;
		}
	}

	return True;
}


//Asegura que cada vertice sea visitado a lo mas una vez (unicidad de los vertices)//
int unicidad(int i, int j, int k, variable **variables, datos_problema* instancia){
	int x1;
	int x2;
	int ph = ((*instancia).puntos+(*instancia).hoteles);

	//Se obtienen las componentes que se necesiten (x, y, z) de las variables i y j//
	x1 = dim_x(i, ph);
	x2 = dim_x(j, ph);

	//Si la coordenada x de i y j son la misma, e i no es un hotel//
	if(x2 == x1 && x1 > (*instancia).hoteles+1){
		//Si el valor de la variable i es 1 y j quiere tomar el mismo valor, retorna Falso//
		//Falso porque ya existe un vertice visitado, en este caso, x1//
		if((*variables)[i].valor == 1 && k == 1){
			return False;
		}
	}
	return True;
}

//Se limita el tiempo de cada trip//
int tiempo_max(int i, int j, int k, variable **variables, datos_problema* instancia){
	int trip1;
	int x2, y2, trip2;
	int trips, xs, ys;
	int w, index;
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	double dist_rec = 0;

	//Se obtienen las componentes que se necesiten (x, y, z) de las variables i y j//
	x2 = dim_x(j, ph);
	y2 = dim_y(j, ph);

	trip1 = dim_z(i, ph);
	trip2 = dim_z(j, ph);

	//Si i y j estan en el mismo trip, y el valor de j quiere ser 1//
	//Se suman todas las distancias de las variables i que tienen valor 1//
	if(trip1 == trip2 && k == 1){
		for(index = 0; index <= i; index++){
			trips = dim_z(index,ph);
			if(trips == trip1){
				if((*variables)[index].valor == 1){
					xs = dim_x(index,ph);
					ys = dim_y(index,ph);
					w = obtener_indice(xs,ys,ph);
					dist_rec += (*instancia).matriz_dist[w];
				}
			}
		}
		w = obtener_indice(x2, y2, ph);
		dist_rec += (*instancia).matriz_dist[w];
		//Si la distancia recorrida (incluyendo la variable j), es mayor a la distancia maxima del trip, retorna Falso//
		if(dist_rec > (*instancia).dist_max_trip[trip1]){
			return False;
		}
	}
	return True;
}

//Se chequea que la solucion final no contenga subtour//
int subtours(variable **variables, datos_problema* instancia){
	int ph = ((*instancia).puntos+(*instancia).hoteles);
	int trip = 0, pos = 0, q, k, index, desde = 0;
	int i, j, t;
	int count = 0;

	//Arreglo del tamaño de la cantidad de POIs, se parten todos los campos con 0//
	int posicion[(*instancia).puntos-2];
	for(q = 0; q < (*instancia).puntos-2; q++){
		posicion[q] = 0;
	}

	//Se itera en todos los trips dentro del tour//
	while(trip < (*instancia).num_trips){
		for(k = 0; k < ph; k++){
			index = trans3D_to_1D(desde,k,trip,ph,ph);
			//Se extraen todas las variables instanciadas en el tour (candidatas a solucion)//
			if((*variables)[index].valor == 1){
				//Mientras k sea menor que el numero de hoteles, se suma un trip//
				if(k < (*instancia).hoteles+2){
					trip += 1;
				}else{
					pos += 1;
					posicion[k-((*instancia).hoteles+2)] = pos;				
				}
				desde = k;
				break;
			}
		}
	}


	for(i = 0; i < (*instancia).puntos-2; i++){
		for(j = 0; j < (*instancia).puntos-2; j++){
			count = 0;
			for(t = 0; t < (*instancia).num_trips; t++){
				count += (*variables)[trans3D_to_1D(i+(*instancia).hoteles+2, j+(*instancia).hoteles+2, t, ph, ph)].valor;
			}

			if(count == 1 && posicion[i] == 0 && posicion[j] == 0){
				return False;
			}
		}
	}

	return True;
}


//Se encarga de llamar a todas las restricciones y chequearlas, si alguna de ellas retorna Falso, toda la sentencia es Falsa//
int revisar_restricciones(int i, int j, int k, variable **variables, datos_problema* instancia){
	int r1 = hotel_ini(i, j, k, variables, instancia);
	int r2 = hotel_final(i, j, k, variables, instancia);
	int r3 = hotel_inicial_trip(i, j, k, variables, instancia);
	int r4 = hotel_final_trip(i, j, k, variables, instancia);
	int r5 = hotel_final_hotel_inicial_trip(i, j, k, variables, instancia);
	int r6 = conectividad(i, j, k, variables, instancia);
	int r7 = unicidad(i, j, k, variables, instancia);
	int r8 = tiempo_max(i, j, k, variables, instancia);
	return r1 && r2 && r3 && r4 && r5 && r6 && r7 && r8;
}