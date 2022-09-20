int new_ventas(char *ID, char* productos, char *ID_cliente, char *discount);
int modify_venta(char *ID, char* productos, char *ID_cliente, char *discount);

int hide_venta(int row);

int get_ID_venta(int row, char *ID);
int get_date_venta(int row, char *date);
int get_productos_venta(int row, char *name);
int get_ID_cliente_venta(int row, char *price);
int get_discount_venta(int row, char *discount);
int get_visibility_venta(int row);

int get_lines_venta_file();
int get_jumplines_venta_file();

int isBlank_venta(int row);
int search_venta_ID_venta(char *ID);
int search_venta_ID_cliente(char *ID);