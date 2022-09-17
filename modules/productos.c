#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../handlers/caracteres.h"
#include "../handlers/tabdb.h"
#include <time.h>

int new_product(char *ID, char* name, char* price,int discount, char category)
{

        char client[500];
        char date[12];
        create_date(date);

        char show[] = "TRUE";

        sprintf(client, "%s\t%s\t%s\t%s\t%s\t%s\t%s", ID, date, name, price, discount, category, show);

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        add_line_file(fp, client);

        fclose(fp);
}

int hide_product(int row)
{

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 6, "FALSE");

        fclose(fp);

        return 0;
}

int get_ID_product(int row, char *ID)
{
        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 0, ID);
        fclose(fp);
        return 0;
}

int get_date_product(int row, char *date)
{

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 1, date);
        fclose(fp);
        return 0;
}

int get_name_product(int row, char *name)
{

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 2, name);
        fclose(fp);
        return 0;
}

int get_price_product(int row, char *apellido)
{

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 3, apellido);
        fclose(fp);
        return 0;
}

int get_discount_product(int row, char *identificacion)
{
        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 4, identificacion);
        fclose(fp);
        return 0;
}

int get_category_product(int row, char *phone)
{

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 5, phone);
        fclose(fp);
        return 0;
}

int get_visibility_product(int row, char *TdP)
{

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 6, TdP);
        fclose(fp);
        return 0;
}

int get_lines_product_file()
{
        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        int jumplines = gets_lines_file(fp);

        fclose(fp);
        return jumplines;
}

int get_jumplines_product_file()
{
        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        int jumplines = gets_jumplines_file(fp);

        fclose(fp);
        return jumplines;
}

int isBlank_product(int row)
{
        FILE *fp;
        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        int blank = is_blank(fp, row);

        fclose(fp);
        return blank;
}

int search_product(char *ID)
{
        FILE *fp;
        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID);

        fclose(fp);
        return row;
}