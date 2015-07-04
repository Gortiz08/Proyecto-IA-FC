


//definir que hace este .h


//parametros de entrada, que retorna.
int obtener_indice(int x, int y, int l);


//idem
void lectura(const char *nombre, datos_problema *instancia);

//
void llenar_dominio(variable **variables, datos_problema instancia);

//
void fc(int i, variable **variables, datos_problema instancia);

//
int Forward_Checking(int i, int var, variable **variables, datos_problema instancia);

//
void restablecer_dom(int i, int var, variable **variables);



//
int dim_x(int i, int ph);

//
int dim_y(int i, int ph);

//
int dim_z(int i, int ph);

//
int hotel_ini(int i, int j, int k, variable **variables, datos_problema instancia);

//
int hotel_final(int i, int j, int k, variable **variables, datos_problema instancia);

//
int hotel_inicial_trip(int i, int j, int k, variable **variables, datos_problema instancia);

//
int hotel_final_trip(int i, int j, int k, variable **variables, datos_problema instancia);

//
int unicidad(int i, int j, int k, variable **variables, datos_problema instancia);

//
int tiempo_max(int i, int j, int k, variable **variables, datos_problema instancia);

//
int revisar_restricciones(int i, int j, int k, variable **variables, datos_problema instancia);