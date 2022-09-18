void empresa();	// Muestra los datos de la empresa	
void factura_user(FILE *archivo, char code[], char name[], char city[], char rif[], char total[]);	//	Muestra en pantalla todos los elementos de la factura (falta productos)

char no_repeat(FILE *fp, char rif[]);	// Evitara ingresar un rif repetido (MISMO RIF Y NATURALEZA)
char naturaleza(char opcion);	// Devuelve la naturaleza de la persona

int admit_rif(char nationality[], char str[]);	//	Establece si un rif es admitido o no es valido
int extension(char str[]);	// Calcula la cantidad de caracteres de una cadena de palabras
int ubication_code(FILE *archivo, char str[]);	//	Busca la aparicion del elemento tecleado
int admit_naturaleza(char chr);	// Leera la inicial del char y determinara si es valido o no	

bool solo_number(char *str);	// Leera el rif (sin contar la naturaleza) y permitira continuar si solo hay numeros

// Funciones nacidas de tabdb
int isBlank_invoice(int i);	// Revisa si en el fichero de "facturas.txt" hay lineas en blanco o no
int gets_lines_invoice();	// Devuelve el total de saltos de lineas (excepto los dos ultimos) del fichero "facturas.txt"
int gets_jumplines_invoice();	// Devuelve la cantidad de lineas con contenido en el fichero "facturas.txt"

char read_ID_invoice(int i, char *str);	// Lee en la fila X el ID de la factura
char read_code_invoice(int i, char *str);	// Lee en la fila X el codigo de la factura
char read_name_invoice(int i, char *str);	// Lee en la fila X el nombre en la factura
char read_city_invoice(int i, char *str);	// Lee en la fila X la ciudad en la factura
char read_rif_invoice(int i, char *str);	// Lee en la fila X el rif en la factura
char read_date_invoice(int i, char *str);	// Lee en la fila X la fecha en la factura
char read_price_invoice(int i, char *str);	// Lee en la fila X el precio en la factura