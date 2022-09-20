/*
Este codigo hace uso de tabdb.h para modificar productos.txt, en productos.txt se encuentra la lista de productos actuales del sistema,
cuenta con 8 Columnas.

        ID  FECHA DE CREACION   NOMBRE DE PRODUCTO  PRECIO  DESCUENTO  CATEGORIA  STOCK  VISIBILIDAD

        Las funciones se dividen en obtener datos, modificar el archivo y buscar en el archivo

        MODIFICAR EL ARCHIVO
                new_pruduct()
                modify_product
                reduce_stock()
                hide_product()

        OBTENER DATOS
                get_ID_product()
                get_date_product()
                get_name_product()
                get_price_product()
                get_discount_product()
                get_category_product()
                get_stock_product()
                get_visibilitys_product()
                get_jumplines_product_file()
                get_lines_product_file()
                isBlank_product()

        BUSCAR EN EL ARCHIVO
                search_product()
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../handlers/caracteres.h"
#include "../handlers/tabdb.h"
#include <time.h>

int new_product(char *ID, char *name, char *price, char *discount, char *stock, char *category)
{

        char product[500];
        char date[14];
        create_date(date);

        char show[] = "T";

        sprintf(product, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", ID, date, name, price, discount, category, stock, show);

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        add_line_file(fp, product);

        fclose(fp);
        return 0;
}

int reduce_stock(int row, int quantity)
{
        FILE *fp;
        fp = fopen("database/productos.txt", "r+");

        if (fp == NULL)
                return -1;

        char amount[20];
        char newAmount[20];
        char temp[20];

        read_col_file(fp, row, 6, amount);

        int n = atoi(amount) - quantity;

        sprintf(temp, "%d", n);

        sprintf(newAmount, "%d", n);

        modify_col_file(fp, row, 6, amount);

        if (strlen(amount) == strlen(temp))
                delete_line_file(fp, row);

        fclose(fp);
        return 0;
}

int modify_product(char *lastID, char *date, char *name, char *price, char *discount, char *stock, char *category)
{

        char product[500];
        char ID[20];

        create_ID(ID);

        char show[] = "T";

        sprintf(product, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", ID, date, name, price, discount, category, stock, show);

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        hide_product(search_product(lastID));
        add_line_file(fp, product);

        fclose(fp);
        return 0;
}

int hide_product(int row)
{
        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 7, "F");

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

int get_price_product(int row, char *price)
{

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 3, price);
        fclose(fp);
        return 0;
}

int get_discount_product(int row, char *discount)
{
        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 4, discount);
        fclose(fp);
        return 0;
}

int get_category_product(int row, char *category)
{

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 5, category);
        fclose(fp);
        return 0;
}

int get_stock_product(int row, char *TdP)
{

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 6, TdP);
        fclose(fp);
        return 0;
}

int get_visibility_product(int row)
{

        FILE *fp;

        fp = fopen("database/productos.txt", "r+");
        if (fp == NULL)
                return -1;

        char str[10];

        read_col_file(fp, row, 7, str);

        fclose(fp);

        if (str[0] == 'T')
                return 1;

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

        int lines = get_lines_product_file();
        int i = 0;
        int jumplines = 0;

        while (i < lines)
        {
                if (!isBlank_product(i) && get_visibility_product(i))
                {
                        jumplines++;
                }
                i++;
        }

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