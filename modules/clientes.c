/*Este archivo es un conjunto de funciones para poder manipular al archivo cliente
este ser conforma del nombre,la id, identificacion, phone, TdP..*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../handlers/caracteres.h"
#include "../handlers/tabdb.h"
#include <time.h>

// este sirve para crear una nueva linea en el archivo de texto, si la creacion de la linea es exitosa se
// devolvera 0 y si no se delvera -1
int new_client(char *ID, char *nombre, char *identificacion, char *phone, char *TdP)
{

        char client[500]; // se reserva el espacio de memoria
        char date[12];
        create_date(date); // se pasa como parametro un string vacio donde se leera la fecha//
        sprintf(client, "%s\t%s\t%s\t%s\t%s\t%s", ID, date, nombre, identificacion, phone, TdP);

        FILE *fp; // se reserva el espacio de memoria para el archivo

        fp = fopen("../database/clientes.txt", "r+"); // se llama a la funcion para poder leer el archivo
        if (fp == NULL)
                return -1;

        add_line_file(fp, client);

        fclose(fp);
        return 0; // significa que la funcion fue exitosa
}

int delete_client(int row) // funcion para eliminar la fila N del archivo cliente.txt
{

        FILE *fp; // se reserva el espacio de memoria para el archivo

        fp = fopen("../database/clientes.txt", "r+"); // se llama a la funcion para poder leer el archivo

        if (fp == NULL) // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        delete_line_file(fp, row);

        fclose(fp); // se cierra el archivo

        return 0; // significa que la funcion fue exitosa
}

int modify_name_clients(int row, char *nombre) // funcion para modificar la fila del archivo del nombre
{

        FILE *fp;

        fp = fopen("../database/clientes.txt", "r+");
        if (fp == NULL) // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        modify_col_file(fp, row, 2, nombre); // modificar la columna 2
        fclose(fp);                          // se cierra el archivo
        return 0;                            // significa que la funcion fue exitosa
}

int modify_dni_clients(int row, char *identificacion) // funcion para modificar fila del la identificacion

{
        FILE *fp;

        fp = fopen("../database/clientes.txt", "r+");
        if (fp == NULL) // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        modify_col_file(fp, row, 3, identificacion); // modificar la columna 3 del cliente

        fclose(fp); // se cierra el archivo
        return 0;   // significa que la funcion fue exitosa
}

int modify_phone_clients(int row, char *phone) // funncion paraa modificar la fila del numero del cliente
{

        FILE *fp;

        fp = fopen("../database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                               // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        modify_col_file(fp, row, 4, phone); // modificar la columna 4 del cliente
        fclose(fp);
        return 0; // significa que la funcion fue exitosa
}

int modify_TdP_clients(int row, char *TdP) // funcion para modificar la fila del la tipo de persona del cliente
{

        FILE *fp;

        fp = fopen("../database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                               // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        modify_col_file(fp, row, 5, TdP); // modificar la columna 5 del cliente

        fclose(fp); // se cierra el archivo
        return 0;   // significa que la funcion fue exitosa
}

int get_ID_clients(int row, char *ID) // funcion para leer la direccion en la que se ingreso los datos del usuario
{
        FILE *fp;

        fp = fopen("database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                            // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        read_col_file(fp, row, 0, ID);
        fclose(fp);
        return 0; // significa que la funcion fue exitosa
}

int get_date_clients(int row, char *date) // funcion para leer la fecha del cliente
{

        FILE *fp;

        fp = fopen("../database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                               // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        read_col_file(fp, row, 1, date);
        fclose(fp);// se cierra el archivo
        return 0; // significa que la funcion fue exitosa
}

int get_name_clients(int row, char *name) // funcion para obtener el nombre del cliente.
{

        FILE *fp;

        fp = fopen("../database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                               // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        read_col_file(fp, row, 2, name);
        fclose(fp);// se cierra el archivo
        return 0; // significa que la funcion fue exitosa
}

int get_dni_clients(int row, char *identificacion) // funcion para obtener la identificacion del cliente
{
        FILE *fp;

        fp = fopen("../database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                               // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        read_col_file(fp, row, 3, identificacion);
        fclose(fp);// se cierra el archivo
        return 0; // significa que la funcion fue exitosa
}

int get_phone_clients(int row, char *phone) // funcion para obtener el numero  del cliente
{

        FILE *fp;

        fp = fopen("../database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                               // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        read_col_file(fp, row, 4, phone);
        fclose(fp);// se cierra el archivo
        return 0; // significa que la funcion fue exitosa
}

int get_TdP_clients(int row, char *TdP) // funcion para agregar el tipo de persona del cliente
{

        FILE *fp;

        fp = fopen("../database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                               // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        read_col_file(fp, row, 5, TdP);
        fclose(fp);// se cierra el archivo
        return 0; // significa que la funcion fue exitosa
}

int get_lines_clients_file() // funciom para leer una linea entera del cliente
{
        FILE *fp;

        fp = fopen("database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                            // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        int jumplines = gets_lines_file(fp);

        fclose(fp);// se cierra el archivo
        return jumplines;
}

int get_jumplines_clients_file()
{
        FILE *fp;

        fp = fopen("database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                            // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        int jumplines = gets_jumplines_file(fp);

        fclose(fp);// se cierra el archivo
        return jumplines;
}

int isBlank(int row) // si la linea a la que apunta esta en blanco devuelve 1 y si no 0
{
        FILE *fp;
        fp = fopen("database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                            // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        int blank = is_blank(fp, row);

        fclose(fp);// se cierra el archivo
        return blank;
}

int search_clients(char *ID) // funcion para buscar en la base de datos los registros de los clientes por su id
{
        FILE *fp;
        fp = fopen("database/clientes.txt", "r+"); // abrir archivo
        if (fp == NULL)                            // si pf es igual a Null significa que no existe ningun archivo
                return -1;

        int row = search_data_file(fp, 0, ID); // se busca en todas las columnas N un id que coincida con el del parametro

        fclose(fp);// se cierra el archivo
        return row;
}
