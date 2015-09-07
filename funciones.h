

//Se declaran los prototipos de todas las funciones utilizadas en el programa//




//Se obtiene la posicion equivalente de una variable en un arreglo 3D a un arreglo 1D//
//(x,y,l) => (k)//
int obtener_indice(int x, int y, int l);

//Lectura del archivo .ophs//
//Parametros de entrada:
//# nombre: ruta del archivo a leer
//# instancia: estructura de datos del problema
void lectura(const char *nombre, datos_problema *instancia);

//Se inicializa y da valor a las distinas variables de la estructura variables//
//Parametros de entrada:
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
void llenar_dominio(variable **variables, datos_problema* instancia);

//Funcion recursiva que se encarga de hacer el backtrack//
//Parametros de entrada:
//# i: indice de la variable a instanciar
//# mejor_punt: variable donde se guarda el mejor puntaje
//# mejor_result: arreglo donde se guarda el mejor resultado
//# nombre: ruta del archivo a leer
//# instancia: estructura de datos del problema
void fc(int i, int *mejor_punt, int **mejor_result, variable **variables, datos_problema* instancia);

//Se revisa que se cumplan las restricciones del problema//
//Parametros de entrada:
//# i: indice de la variable a instanciar
//# var: cantidad de variables totales en el problema
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable se queda sin dominio
//# Verdadero: En otro caso
int Forward_Checking(int i, int var, variable **variables, datos_problema* instancia);

//Se restablecen los dominios de las variables con problema//
//Parametros de entrada:
//# i: indice de la variable a instanciar
//# var: cantidad de variables totales en el problema
//# variables: estructura de las variables del problema
void restablecer_dom(int i, int var, variable **variables);

//Se linealiza un arreglo de 3 dimensiones//
//Parametros de entrada:
//# i: POI u hotel de salida en la variable
//# j: POI u hotel de llegada en la variable
//# k: Trip de la variable
//# l: suma de POI y hoteles
//# m: suma de POI y hoteles
//Retorno:
//# variable linealizada
int trans3D_to_1D(int i, int j, int k,int l,int m);

//A partir de la variable "i", del arreglo 1D, se obtiene la posicion en el eje X del arreglo 3D//
//Parametros de entrada:
//# i: variable linealizada
//# ph: suma de POI y hoteles
//Retorno:
//# componente x de la variable
int dim_x(int i, int ph);

//A partir de la variable "i", del arreglo 1D, se obtiene la posicion en el eje Y del arreglo 3D//
//Parametros de entrada:
//# i: variable linealizada
//# ph: suma de POI y hoteles
//Retorno:
//# componente y de la variable
int dim_y(int i, int ph);

//A partir de la variable "i", del arreglo 1D, se obtiene la posicion en el eje Z del arreglo 3D//
//Parametros de entrada:
//# i: variable linealizada
//# ph: suma de POI y hoteles
//Retorno:
//# componente z de la variable (trip)
int dim_z(int i, int ph);

//Restriccion que asegura que se parta desde un hotel inicial (i = 0)//
//Parametros de entrada:
//# i: indice de la variable actualmente instanciada
//# j: indice de la variable j-esima a instancias
//# k: valor del dominio que puede tomar la variable j-esima
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable no cumple con la restriccion
//# Verdadero: En otro caso
int hotel_ini(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que se termine en un hotel final (i = 1)//
//Parametros de entrada:
//# i: indice de la variable actualmente instanciada
//# j: indice de la variable j-esima a instancias
//# k: valor del dominio que puede tomar la variable j-esima
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable no cumple con la restriccion
//# Verdadero: En otro caso
int hotel_final(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que el comienzo del trip sea un hotel disponible//
//Parametros de entrada:
//# i: indice de la variable actualmente instanciada
//# j: indice de la variable j-esima a instancias
//# k: valor del dominio que puede tomar la variable j-esima
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable no cumple con la restriccion
//# Verdadero: En otro caso
int hotel_inicial_trip(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que el final del trip sea un hotel disponible//
//Parametros de entrada:
//# i: indice de la variable actualmente instanciada
//# j: indice de la variable j-esima a instancias
//# k: valor del dominio que puede tomar la variable j-esima
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable no cumple con la restriccion
//# Verdadero: En otro caso
int hotel_final_trip(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que un trip comience en el mismo hotel donde se termino el trip anterior//
//Parametros de entrada:
//# i: indice de la variable actualmente instanciada
//# j: indice de la variable j-esima a instancias
//# k: valor del dominio que puede tomar la variable j-esima
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable no cumple con la restriccion
//# Verdadero: En otro caso
int hotel_final_hotel_inicial_trip(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que todos los nodos esten conectados dentro de cada trip//
//Parametros de entrada:
//# i: indice de la variable actualmente instanciada
//# j: indice de la variable j-esima a instancias
//# k: valor del dominio que puede tomar la variable j-esima
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable no cumple con la restriccion
//# Verdadero: En otro caso
int conectividad(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que cada vertice es visitado a lo mas una vez//
//Parametros de entrada:
//# i: indice de la variable actualmente instanciada
//# j: indice de la variable j-esima a instancias
//# k: valor del dominio que puede tomar la variable j-esima
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable no cumple con la restriccion
//# Verdadero: En otro caso
int unicidad(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que no se pase el tiempo limite para cada trip//
//Parametros de entrada:
//# i: indice de la variable actualmente instanciada
//# j: indice de la variable j-esima a instancias
//# k: valor del dominio que puede tomar la variable j-esima
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable no cumple con la restriccion
//# Verdadero: En otro caso
int tiempo_max(int i, int j, int k, variable **variables, datos_problema* instancia);

//Restriccion que asegura que no hayan subtours dentro de cada Tour o solucion final//
//Parametros de entrada:
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable no cumple con la restriccion
//# Verdadero: En otro caso
int subtours(variable **variables, datos_problema* instancia);

//Se encarga de llamar a todas las funciones que revisan restricciones//
//Parametros de entrada:
//# i: indice de la variable actualmente instanciada
//# j: indice de la variable j-esima a instancias
//# k: valor del dominio que puede tomar la variable j-esima
//# variables: estructura de las variables del problema
//# instancia: estructura de datos del problema
//Retorno:
//# Falso: Si alguna variable no cumple con alguna restriccion
//# Verdadero: En otro caso
int revisar_restricciones(int i, int j, int k, variable **variables, datos_problema* instancia);
