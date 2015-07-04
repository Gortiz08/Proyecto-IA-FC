


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