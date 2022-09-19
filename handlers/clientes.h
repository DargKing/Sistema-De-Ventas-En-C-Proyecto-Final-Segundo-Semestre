int new_client(char *ID, char *nombre, char *identificacion, char *phone, char *TdP);
int delete_client(int row);

int modify_name_clients(int row, char *nombre);
int modify_dni_clients(int row, char *identificacion);
int modify_phone_clients(int row, char *phone);
int modify_TdP_clients(int row, int TdP);

int search_clients(char *ID);

int get_ID_clients(int row, char *ID);
int get_name_clients(int row, char *name);
int get_dni_clients(int row, char *identificacion);
int get_phone_clients(int row, char *phone);
int get_TdP_clients(int row, char *TdP);

int get_lines_clients_file();
int get_jumplines_clients_file();

int isBlank(int row);
