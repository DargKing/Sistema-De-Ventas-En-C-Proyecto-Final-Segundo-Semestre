int new_client(char *ID, char *nombre, char *identificacion, char *phone, char *TdP);
int delete_client(int row);// funcion para eliminar la fila N del archivo cliente.txt

int modify_name_clients(int row, char *nombre);// funcion para modificar la columna perteneciente al nombre
int modify_dni_clients(int row, char *identificacion);// funcion para modificar columna de la identificacion del archivo. tx
int modify_phone_clients(int row, char *phone);//funcion para modificar la columna del numero del telefono del archivo.txt
int modify_TdP_clients(int row, int TdP);//// funcion para modificar la columnas del la tipo de persona del archivo.txt

int search_clients(char *ID);// funcion para buscar en la base de datos los registros de los clientes por su id en el archivo.txt

int get_name_clients(int row, char *name);// funcion para obtener la identificacion del cliente en el archivo.txt
int get_ID_clients(int row, char *ID);// funcion para obtener el nombre del cliente en el archivo.txt
int get_dni_clients(int row, char *identificacion);// funcion para obtener la identificacion del cliente en el archivo.txt
int get_phone_clients(int row, char *phone);// funcion para obtener el numero  del cliente en el archivo.txt
int get_TdP_clients(int row, char *TdP);// funcion para agregar el tipo de persona del cliente en el archivo.txt

int get_lines_clients_file();// sirve para devolver todas las lineas del archivo.txt
int get_jumplines_clients_file();//sirve para devolver la cantidad de lineas que esten en blanco en el archivo.txt

int isBlank(int row);//sirve si la linea a la que apunta esta en blanco devuelve 1 y si no 0
