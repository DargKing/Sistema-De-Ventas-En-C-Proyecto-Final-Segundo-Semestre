#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../handlers/tabdb.h"
#include "../handlers/user.h"

/*
        ARGUMENTO:
                Permitira al usuario poder logearse a su cuenta, o en caso contrario, no logearse al no poseer una cuenta

        PARAMETROS:
                email = email introducido por el usuario
                password = contrasena introducida por el usuario

*/

int login(char *email, char *password)
{
        FILE *fp;

        fp = fopen("./database/users.txt", "r+"); // Inicia el fichero 
        if (fp == NULL)
                return -1;

        int fila = search_data_file(fp, 1, email); // Obtenemos la posicion de email

        if (fila == -1) // Si fila es igual a -1 se tomara como un error
        {
                fclose(fp);
                return -2;
        }

        char temp_password[100]; 
        read_col_file(fp, fila, 2, temp_password); // Guardamos en temp_pasword el string obtenido en read_col_file

        if (strcmp(temp_password, password)) // Comparamos el password con el temp_password
        {
                fclose(fp);     // En caso de no haber semejanza se retorna un -2 y se cierra el fichero
                return -2;
        }

        fclose(fp); // Cerramos el fichero

        return fila; // Nos devuelve la fila
}

/*
        ARGUMENTO:
                Creara en el fichero "user.txt" un nuevo usuario
        PARAMETROS:

                username = Nombre que el usuario decida
                password = contrasena que el nuevo usuario decidira
                range = Mostrara si es USER o ADMIN el usuario (Columna obsoleta)
                rif = El rif de identidad del usuario
                direccion = Ubicacion de su vivienda
*/

int create_new_user(char *username, char *password, char* range, char* rif, char* direccion)
{
        FILE *fp;

        fp = fopen("./database/users.txt", "r+"); // Inicica el fichero
        if (fp == NULL)
                return -1;

        if (search_data_file(fp, 1, username) != -1) // Si ya existe un nombre existente retorna 0
                return 0;

        char ID[20];

        create_ID(ID); // Creamos el ID del cliente

        char line[320];

        // Volvemos en un string llamado line todos los datos
        sprintf(line, "%s\t%s\t%s\t%s\t%s\t%s", ID, username, password, "USER", rif, direccion);

        add_line_file(fp, line); // Añadimos en el fichero line

        fclose(fp); // Cerramos el fichero

        return 1;
}

/*
        ARGUMENTO:
                Retornara la posicion del usuario

        PARAMETRO:
                username = Nombre del usuario
*/

int search_user(char *username)
{
        FILE *fp;

        fp = fopen("./database/users.txt", "r+"); // Inicicamos el fichero
        if (fp == NULL)
                return -1;

        int resul = search_data_file(fp, 1, username); // Buscamos el username del usuario

        if (resul == -1) // Si no existe retorna -2
                return -2;

        fclose(fp); // Cerramos el fichero
        return resul; // Retorna la posicion del username
}

/*
        ARGUMENTO:
                Obtendra todos los datos del usuario

        PARAMETROS:
                row = La fila que desea obtener los datos
                ID = ID del usuario
                username = Nombre del usuario
                password = La contrasena del usuario
                range = El rango (USER o ADMIN) del usuario (obsoleta)
                rif = El rif del usuario
                direccion = Direccion de vivienda del usuario
*/

int get_data_user(int row, char *ID, char *username, char *password, char *range, char* rif, char* direccion)
{
        FILE *fp;

        fp = fopen("./database/users.txt", "r+"); // Inicia le fichero
        if (fp == NULL)
                return -1;

        // Leermos los datos de cada columna
        read_col_file(fp, row, 0, ID);
        read_col_file(fp, row, 1, username);
        read_col_file(fp, row, 2, password);
        read_col_file(fp, row, 3, range);
        read_col_file(fp, row, 4, rif);
        read_col_file(fp, row, 5, direccion);

        fclose(fp); // Cerramos el fichero
        return 0;
}

/*
        ARGUMENTO:
                Cambia la contrasena del usuario

        PARAMETROS:
                ID = ID del usuario
                newPassword = La nueva contrasena tecleada por el usuario
*/

int change_password(char *ID, char *newPassword)
{
        FILE *fp;
        fp = fopen("./database/users.txt", "r+"); // Inicia el fichero
        if (fp == NULL)
                return -1;

        int search = search_data_file(fp, 0, ID); // Buscamos el ID del usuario

        if (search == -1) // Si no existe se cierra el fichero y retorna 0
        {
                fclose(fp);
                return 0;
        }

        char temp[100];
        read_col_file(fp, search, 2, temp); // Guardamos en temp el string obtenido en read_col_file

        if (!strcmp(temp, newPassword))  // Comparamos temp con la new_password
        {       
                fclose(fp);
                return 2;
        }

        modify_col_file(fp, search, 2, newPassword); // Modificamos la columna contrasena del usuario

        fclose(fp); // Cerramos el fichero
        return 1;
}

/*
        ARGUMENTO:
                Cambia el username del usuario

        PARAMETROS:
                ID = ID del usuario
                newUsername = El neuvo username teckeado por el usuario
*/


int change_username(char *ID, char *newUsername)
{
        FILE *fp;
        fp = fopen("./database/users.txt", "r+"); // Inicia el fichero
        if (fp == NULL)
                return -1;

        int search = search_data_file(fp, 0, ID); // Buscamos el ID del usuario

        if (search == -1)
        {
                fclose(fp);
                return 0;
        }

        char temp[100];
        read_col_file(fp, search, 1, temp); // Guardamos en temp el string obtenido en read_col_file

        if (!strcmp(temp, newUsername)) // Comparamos temp con el newUsername
        {
                fclose(fp);
                return 2;
        }

        modify_col_file(fp, search, 1, newUsername); // Modificamos el username del usuario

        fclose(fp); // Cerramos el fichero
        return 1;
}

/*
        ARGUMENTO:
                Elimina una fila de datos (1 usuario)

        PARAMETRO:
                ID = ID del usuario
*/


int delete_user(char *ID)
{
        FILE *fp;
        fp = fopen("./database/users.txt", "r+"); // Inicia el fichero
        if (fp == NULL)
                return -1;

        int search = search_data_file(fp, 0, ID); // Buscamos el ID del usuario

        if (search == -1)
        {
                fclose(fp);
                return 0;
        }

        delete_line_file(fp, search); // Eliminamos la fila que coincida (Todos los datos del usuario)
        fclose(fp); // Cerramos el fichero

        return 1;
}

/*
        ARGUMENTO:
                Cambia el range a ADMIN al usuario

        PARAMETRO:
                ID = ID del usuario
*/


int set_admin(char *ID)
{
        FILE *fp;
        fp = fopen("./database/users.txt", "r+"); // Inicia el fichero
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID); // Buscamos el ID del usuario

        if (row == -1)
        {
                fclose(fp);
                return -1;
        }

        modify_col_file(fp, row, 3, "ADMIN"); // Modificamos el show del usuario para que aparezca ADMIN

        fclose(fp); // Cerramos el fichero
        return 1;
}

/*
        ARGUMENTO:
                Cambia el range a USER al usuario

        PARAMETRO:
                ID = ID del usuario
*/


int set_user(char *ID)
{
        FILE *fp;
        fp = fopen("./database/users.txt", "r+"); // Inicia el fichero
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID); // Buscamos el ID del usuario

        if (row == -1)
        {
                fclose(fp);
                return -1;
        }

        modify_col_file(fp, row, 3, "USER"); // Modificamos el show del usuario para que aparezca ADMIN

        fclose(fp); // Cerramos el fichero
        return 1;
}