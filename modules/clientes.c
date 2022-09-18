#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../handlers/caracteres.h"
#include "../handlers/tabdb.h"
#include <time.h>

int new_client(char *ID, char *nombre, char *apellido, char *identificacion, char *phone, char *TdP)
{

        char client[500];
        char date[12];
        create_date(date);
        sprintf(client, "%s\t%s\t%s\t%s\t%s\t%s\t%s", ID, date, nombre, apellido, identificacion, phone, TdP);

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        add_line_file(fp, client);

        fclose(fp);
}

int delete_client(int row)
{

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        delete_line_file(fp, row);

        fclose(fp);

        return 0;
}

int modify_name_clients(int row, char *nombre)
{

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 2, nombre);
        fclose(fp);
        return 0;
}

int modify_lastname_clients(int row, char *apellido)
{

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 3, apellido);
        fclose(fp);
        return 0;
}

int modify_dni_clients(int row, char *identificacion)

{
        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 4, identificacion);

        fclose(fp);
        return 0;
}

int modify_phone_clients(int row, char *phone)
{

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 5, phone);

        fclose(fp);
        return 0;
}

int modify_TdP_clients(int row, char *TdP)
{

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 6, TdP);

        fclose(fp);
        return 0;
}

int get_ID_clients(int row, char *ID)
{
        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 0, ID);
        fclose(fp);
        return 0;
}

int get_date_clients(int row, char *date)
{

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 1, date);
        fclose(fp);
        return 0;
}

int get_name_clients(int row, char *name)
{

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 2, name);
        fclose(fp);
        return 0;
}

int get_lastname_clients(int row, char *apellido)
{

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 3, apellido);
        fclose(fp);
        return 0;
}

int get_dni_clients(int row, char *identificacion)
{
        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 4, identificacion);
        fclose(fp);
        return 0;
}

int get_phone_clients(int row, char *phone)
{

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 5, phone);
        fclose(fp);
        return 0;
}

int get_TdP_clients(int row, char *TdP)
{

        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 6, TdP);
        fclose(fp);
        return 0;
}

int get_lines_clients_file()
{
        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        int jumplines = gets_lines_file(fp);

        fclose(fp);
        return jumplines;
}

int get_jumplines_clients_file()
{
        FILE *fp;

        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        int jumplines = gets_jumplines_file(fp);

        fclose(fp);
        return jumplines;
}

int isBlank(int row)
{
        FILE *fp;
        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        int blank = is_blank(fp, row);

        fclose(fp);
        return blank;
}

int search_clients(char *ID)
{
        FILE *fp;
        fp = fopen("database/clientes.txt", "r+");
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID);

        fclose(fp);
        return row;
}