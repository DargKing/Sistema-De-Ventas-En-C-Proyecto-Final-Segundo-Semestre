int login(char *username, char *password);
int create_new_user(char *username, char *password, char* range, char* rif, char* direccion);

int search_user(char *username);
int get_data_user(int row, char *ID, char *username, char *password, char *range, char* rif, char* direccion);
int modify_user(char *ID, char *username, char *password, char *rif, char *direccion);

int change_password(char *ID, char *newPassword);
int change_username(char *ID, char *newUsername);
int delete_user(char* ID);

int set_admin(char* ID);
int set_user(char* ID);