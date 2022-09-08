int create_new_invoices(char *name, char *zone, char *dni, char *id_venta, char *price);
int delete_invoice(char *ID);


int modify_name_invoice(int row, char *str);
int modify_zone_invoice(int row, char *str);
int modify_dni_invoice(int row, char *str);
int modify_date_invoice(int row, char *str);
int modify_id_venta_invoice(int row, char *str);
int modify_price_invoice(int row, char *str);


int get_name_invoice(int row, char *str);
int get_zone_invoice(int row, char *str);
int get_dni_invoice(int row, char *str);
int get_date_invoice(int row, char *str);
int get_ID_venta_invoice(int row, char *str);
int get_price_invoice(int row, char *str);
char get_naturaleza(int row);

void empresa();	// Muestra los datos de la empresa	
void no_repeat(FILE *fp, char rif[]);	// Evitara ingresar un rif repetido (MISMO RIF EN UNA NATURALEZA IGUAL)
void factura_user(FILE *fp, int code, char name[], char city[], char rif[], float total);	//	Muestra en pantalla todos los elementos de la factura (falta productos)
int extension(char str[]);	// Calcula la cantidad de caracteres de una cadena de palabras
char naturaleza(char opcion);	// Devuelve la naturaleza de la persona
char unit_str(char str[]);	// Fusiona dos string en uno usando un '_' como un separador y evita que el usuario sobrepase la cantidad de caracteres establecidos
int admit_rif(char nationality[], char str[]);	//	Establece si un rif es admitido o no es valido
int ubication_code(FILE *fp, char str[]);	//	Busca la aparicion del elemento tecleado
