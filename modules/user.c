/*
Este modulo se encarga de escribir y leer el archivo users.txt, en este estan almacenados los distintos usuarios.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../handlers/tabdb.h"
#include "../handlers/user.h"

/*
Login. Se encarga de comprobar si el parametro username y password existen en el archivo y coinciden

Parametros
        [INPUT] char* username
        [INPUT] char* password

Return
        int -1 = En caso de que el archivo no exista devuelve -1
        int -2 = Si el usuario no existe o la contraseña no coincide con los datos devuelve -2
        int fila = en caso de que se encuentre el usuario y la contraseña coincide devuelve la fila del usuario
*/

int login(char *username, char *password)
{
        FILE *fp;

        fp = fopen("./database/users.txt", "r+");
        if (fp == NULL)
                return -1;

        int fila = search_data_file(fp, 1, username);

        if (fila == -1)
        {
                fclose(fp);
                return -2;
        }

        char temp_password[100];
        read_col_file(fp, fila, 2, temp_password);

        if (strcmp(temp_password, password))
        {
                fclose(fp);
                return -2;
        }

        fclose(fp);

        return fila;
}

/*
create_new_user. Crea un nuevo usuario

Parametros
        [INPUT] char *username
        [INPUT] char* password
        [INPUT] char* range (Parametro no usado)
        [INPUT] char* rif
        [INPUT] char* direccion

Return 
        int -1 = Devuelve -1 si el archivo no se encuetra
        int 1 = si la funcion termina con exito
*/

int create_new_user(char *username, char *password, char *range, char *rif, char *direccion)
{
        FILE *fp;

        fp = fopen("./database/users.txt", "r+");
        if (fp == NULL)
                return -1;

        char ID[20];

        create_ID(ID);

        char line[500];

        sprintf(line, "%s\t%s\t%s\t%s\t%s\t%s", ID, username, password, "USER", rif, direccion);

        add_line_file(fp, line);

        fclose(fp);

        return 1;
}

/*
modify_user. Lo mismo que create_new_user pero agregando el ID, y ocultando la anterior linea con ese ID

Parametro
        [INPUT] char* ID 
        [INPUT] char* username 
        [INPUT] char* password
        [INPUT] char* rif
        [INPUT] char* direccion

return
        int -1 = Si el archivo no se encuentra
        int 1 = si la funcion finalizo exitosamente
*/

int modify_user(char *ID, char *username, char *password, char *rif, char *direccion)
{
        FILE *fp;

        fp = fopen("./database/users.txt", "r+");
        if (fp == NULL)
                return -1;

        char line[500];

        delete_user(ID);
        sprintf(line, "%s\t%s\t%s\t%s\t%s\t%s", ID, username, password, "USER", rif, direccion);

        add_line_file(fp, line);

        fclose(fp);

        return 1;
}

/*
search_user. Busca un usuario a partir del username

Paramentros
        [INPUT] username

return
        int -1 = cuando no se encuentra el archivo users.txt
        int -2 = si no se encuentra el usuario
        int row = Devuelve la final donde se encuentra el usuario si lo encuentra

*/

int search_user(char *username)
{
        FILE *fp;

        fp = fopen("./database/users.txt", "r+");
        if (fp == NULL)
                return -1;

        int resul = search_data_file(fp, 1, username);

        if (resul == -1)
                return -2;

        fclose(fp);
        return resul;
}


/*
get_data_user. Obtiene los datos del usuario y los guarda en las variable pasadas en los parametros

        [INPUT] int row = Esta es la fila del usuario
        [OUTPUT] char* ID = guarda en este parametro el ID del usuario
        [OUTPUT] char* username = guarda en este parametro el nombre del usuario
        [OUTPUT] char* password = guarda en este parametro la contraseña del usuario
        [OUTPUT] char* range = guarda en este parametro el rango del usuario
        [OUTPUT] char* rif = guarda en este parametro el rif de la compañia del usuario
        [OUTPUT] char* direccion = guarda en este parametro la direccion de la compañia del usuario
*/

int get_data_user(int row, char *ID, char *username, char *password, char *range, char *rif, char *direccion)
{
        FILE *fp;

        fp = fopen("./database/users.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 0, ID);
        read_col_file(fp, row, 1, username);
        read_col_file(fp, row, 2, password);
        read_col_file(fp, row, 3, range);
        read_col_file(fp, row, 4, rif);
        read_col_file(fp, row, 5, direccion);

        fclose(fp);
        return 0;
}

/*
change_password. cambia la contraseña de la fila en la que el ID que se pase coincida

Parametros
        [INPUT] char* ID
        [INPUT] char* newPassword

return
        int -1 = si el archivo users.txt no se encuentra
        int 0 = si el ID no es encontrado
        int 1 = si la funcion termino con exito
*/

int change_password(char *ID, char *newPassword)
{
        FILE *fp;
        fp = fopen("./database/users.txt", "r+");
        if (fp == NULL)
                return -1;

        int search = search_data_file(fp, 0, ID);

        if (search == -1)
        {
                fclose(fp);
                return 0;
        }

        char temp[100];
        read_col_file(fp, search, 2, temp);

        modify_col_file(fp, search, 2, newPassword);

        fclose(fp);
        return 1;
}

/*
change_password. cambia el usuario de la fila en la que el ID que se pase coincida

Parametros
        [INPUT] char* ID
        [INPUT] char* newUsername

return
        int -1 = si el archivo users.txt no se encuentra
        int 0 = si el ID no es encontrado
        int 1 = si la funcion termino con exito
*/

int change_username(char *ID, char *newUsername)
{
        FILE *fp;
        fp = fopen("./database/users.txt", "r+");
        if (fp == NULL)
                return -1;

        int search = search_data_file(fp, 0, ID);

        if (search == -1)
        {
                fclose(fp);
                return 0;
        }

        char temp[100];
        read_col_file(fp, search, 1, temp);

        modify_col_file(fp, search, 1, newUsername);

        fclose(fp);
        return 1;
}

/*
delete_user. Elimina el usuario que coincida con la Id especificada

parametros
        [INPUT]char* ID

return
        int -1 = si el archivo users.txt no se encuentra
        int 0 = si no se encuentra el ID
        int 1 = si la funcion termina con exito
*/

int delete_user(char *ID)
{
        FILE *fp;
        fp = fopen("./database/users.txt", "r+");
        if (fp == NULL)
                return -1;

        int search = search_data_file(fp, 0, ID);

        if (search == -1)
        {
                fclose(fp);
                return 0;
        }

        delete_line_file(fp, search);
        fclose(fp);

        return 1;
}

/*
ser_admin y set_user son funciones que al no se utilizaron, estas funciones cambian el rango de un usuario a ADMIN o USER respectivamente.

parametros
        [INPUT] char* ID

return
        int -1 = si el archivo users.txt no se encuentra o si no se encuentra el ID
        int 1 = si la funcion termina con exito

*/

int set_admin(char *ID)
{
        FILE *fp;
        fp = fopen("./database/users.txt", "r+");
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID);

        if (row == -1)
        {
                fclose(fp);
                return -1;
        }

        modify_col_file(fp, row, 3, "ADMIN");

        fclose(fp);
        return 1;
}

int set_user(char *ID)
{
        FILE *fp;
        fp = fopen("./database/users.txt", "r+");
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID);

        if (row == -1)
        {
                fclose(fp);
                return -1;
        }

        modify_col_file(fp, row, 3, "USER");

        fclose(fp);
        return 1;
}