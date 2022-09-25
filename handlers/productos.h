int new_product(char *ID, char* name, char* price, char* discount, char* stock, char* category);

int modify_product(char *lastID, char* date, char *name, char *price, char *discount, char *stock, char *category);

int hide_product(int row);

int get_ID_product(int row, char *ID);

int get_date_product(int row, char *date);

int get_name_product(int row, char *name);

int get_price_product(int row, char *price);

int get_discount_product(int row, char *discount);

int get_category_product(int row, char *category);

int get_stock_product(int row, char *TdP);

int get_visibility_product(int row);

int get_lines_product_file();

int get_jumplines_product_file();

int isBlank_product(int row);

int search_product(char *ID);
int reduce_stock(int row, int quantity);