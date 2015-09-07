


//definir que hace este .h


//Se obtiene la posicion equivalente de una variable en un arreglo 3D a un arreglo 1D//
//(x,y,l) => (k)//
int obtener_indice(int x, int y, int l);

//Lectura del archivo .ophs//
void lectura(const char *nombre, datos_problema *instancia);

//Se inicializa y da valor a las distinas variables de la estructura variables//
void llenar_dominio(variable **variables, datos_problema* instancia);

//Funcion recursiva que se encarga de hacer el backtrack// 
void fc(int i, int *mejor_punt, int **mejor_result, variable **variables, datos_problema* instancia);

//Se revisa que se cumplan las restricciones del problema//
int Forward_Checking(int i, int var, variable **variables, datos_problema* instancia);

//Se restablecen los dominios de las variables con problema//
void restablecer_dom(int i, int var, variable **variables);

//Se linealiza un arreglo de 3 dimensiones//
int trans3D_to_1D(int i, int j, int k,int l,int m);

//A partir de la variable "i", del arreglo 1D, se obtiene la posicion en el eje X del arreglo 3D//
int dim_x(int i, int ph);

//A partir de la variable "i", del arreglo 1D, se obtiene la posicion en el eje Y del arreglo 3D//
int dim_y(int i, int ph);

//A partir de la variable "i", del arreglo 1D, se obtiene la posicion en el eje Z del arreglo 3D//
int dim_z(int i, int ph);

//Restriccion que asegura que se parta desde un hotel inicial (i = 0)//
int hotel_ini(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que se termine en un hotel final (i = 1)//
int hotel_final(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que el comienzo del trip sea un hotel disponible//
int hotel_inicial_trip(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que el final del trip sea un hotel disponible//
int hotel_final_trip(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que un trip comience en el mismo hotel donde se termino el trip anterior//
int hotel_final_hotel_inicial_trip(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que todos los nodos esten conectados dentro de cada trip//
int conectividad(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que cada vertice es visitado a lo mas una vez//
int unicidad(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que no se pase el tiempo limite para cada trip//
int tiempo_max(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que no hayan subtours dentro de cada Tour o solucion final//
int subtours(variable **variables, datos_problema* instancia);

//Se encarga de llamar a todas las funciones que revisan restricciones// 
int revisar_restricciones(int i, int j, int k, variable **variables, datos_problema* instancia);
