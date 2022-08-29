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