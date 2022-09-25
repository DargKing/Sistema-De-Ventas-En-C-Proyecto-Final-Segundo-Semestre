/*
Haremos uso de la libreria tabdb y funciones propias para ser usadas en el fichero "facturas.txt",
aqui se almacenara los datos del usuario como si se tratase de una factura fisica.
Contamos con (por el momento) 8 columna que se encuentran clasificadas en:

CODIGO DE LA FACTURA	NUMERO DE FACTURA	NOMBRE DEL USUARIO	DOMICILIO DEL USUARIO	DNI	FECHA	ID DEL CLIENTE	PRECIO

Las funciones se dividiran en:

	Creacion de datos:
		create_new_invoices();

	Eliminacion de datos:
		delete_invoice();

	Lectura de datos:
		char get_ID_invoice();	
		char get_code_invoice();	
		int get_name_invoice();
		int get_zone_invoice();
		int get_dni_invoice();
		int get_date_invoice();
		int get_id_client_invoice();
		int get_price_invoice();
		char get_naturaleza();
		int extension();
		int admit_naturaleza();
		int isBlank_invoice();	
		int gets_lines_invoice();	
		int gets_jumplines_invoice();
		int admit_rif();
		char no_repeat();
		bool solo_number();

	Busqueda de datos:
		int ubication_code();

	Sistemas de ordenamiento:
		void sort_date_invoice();
		void sort_code_invoice();

	Añadir datos:
		char naturaleza();	"Opcional"
*/

int create_new_invoices(char *zone, char *rif_company, char *id_client, char *direction_company);
int delete_invoice(char *ID);

char get_ID_invoice(int i, char *str);	
char get_code_invoice(int i, char *str);	
int get_name_invoice(int row, char *str);
int get_zone_invoice(int row, char *str);
int get_dni_invoice(int row, char *str);
int get_date_invoice(int row, char *str);
int get_id_client_invoice(int row, char *str);
int get_price_invoice(int row, char *str);
char get_naturaleza(int row);

int admit_rif(char nationality[], char str[]);
int extension(char str[]);	
int ubication_code(char str[]);	
int admit_naturaleza(char chr);	

int isBlank_invoice(int i);	
int gets_lines_invoice();	
int gets_jumplines_invoice();	

char naturaleza(char opcion);	
char no_repeat(char rif[]);	

bool solo_number(char *str);	

void sort_date_invoice(struct STRUCTINVOICEDATA *DATOS, int p);
void sort_code_invoice(struct STRUCTINVOICEDATA *DATOS, int p);