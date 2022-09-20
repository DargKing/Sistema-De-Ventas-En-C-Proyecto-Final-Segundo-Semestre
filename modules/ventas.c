#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../handlers/caracteres.h"
#include "../handlers/tabdb.h"
#include <time.h>

int new_ventas(char *ID, char* productos, char *ID_cliente, char *discount)
{
        char product[100 + strlen(productos)];
        char date[14];
        create_date(date);

        char show[] = "T";

        sprintf(product, "%s\t%s\t%s\t%s\t%s\t%s", ID, date, productos, ID_cliente, discount, show);

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        add_line_file(fp, product);

        fclose(fp);
        return 0;
}

int modify_venta(char *ID, char* productos, char *ID_cliente, char *discount)
{

        char product[strlen(productos) + 100];
        char date[14];
        create_date(date);

        char show[] = "T";

        sprintf(product, "%s\t%s\t%s\t%s\t%s\t%s", ID, date, productos, ID_cliente, discount, show);

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID);

        delete_line_file(fp, row);
        add_line_file(fp, product);

        fclose(fp);
        return 0;
}

int hide_venta(int row)
{
        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 7, "F");

        fclose(fp);

        return 0;
}

int get_ID_venta(int row, char *ID)
{
        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 0, ID);
        fclose(fp);
        return 0;
}

int get_date_venta(int row, char *date)
{

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 1, date);
        fclose(fp);
        return 0;
}

int get_productos_venta(int row, char *name)
{

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 2, name);
        fclose(fp);
        return 0;
}

int get_ID_cliente_venta(int row, char *price)
{

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 3, price);
        fclose(fp);
        return 0;
}

int get_discount_venta(int row, char *discount)
{
        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 4, discount);
        fclose(fp);
        return 0;
}

int get_visibility_venta(int row)
{

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        char str[10];

        read_col_file(fp, row, 5, str);

        fclose(fp);

        if (str[0] == 'T')
                return 1;

        return 0;
}

int get_lines_venta_file()
{
        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        int jumplines = gets_lines_file(fp);

        fclose(fp);
        return jumplines;
}

int get_jumplines_venta_file()
{
        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        int lines = get_lines_product_file();
        int i = 0;
        int jumplines = 0;

        while(i < lines){
                if(get_visibility_product(i)){
                        jumplines++;
                }
                i++;
        }

        fclose(fp);
        return jumplines;
}

int isBlank_venta(int row)
{
        FILE *fp;
        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        int blank = get_visibility_product(row);

        fclose(fp);
        return blank;
}

int search_venta_ID_venta(char *ID)
{
        FILE *fp;
        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID);

        fclose(fp);
        return row;
}

int search_venta_ID_cliente(char *ID)
{
        FILE *fp;
        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 3, ID);

        fclose(fp);
        return row;
}