#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "../handlers/tabdb.h"
#include "../handlers/caracteres.h"
#include "../handlers/facturas.h"

// Crear Nueva Factura

int create_new_invoices(char *name, char *zone, char *dni, char *id_venta, char *price)
{

        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        char ID[20];
        char date[10];
        char str[100];

        create_date(date);
        create_ID(ID);
        sprintf(str, "%s\t%s\t%s\t%s\t%s\t%s\t%s", ID, name, zone, dni, date, id_venta, price);

        add_line_file(fp, str);

        fclose(fp);
        return 0;
}

// Eliminar Factura

int delete_invoice(char *ID)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID);

        delete_line_file(fp, row);

        fclose(fp);
        return 0;
}

// Modificar Nombre

int modify_name_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 1, str);

        fclose(fp);
        return 0;
}

// Modificar Ciudad

int modify_zone_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 2, str);

        fclose(fp);
        return 0;
}

// Modificar DNI

int modify_dni_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 3, str);

        fclose(fp);
        return 0;
}

// Modificar Date

int modify_date_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 4, str);

        fclose(fp);
        return 0;
}

// Modificar ID venta

int modify_id_venta_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 5, str);

        fclose(fp);
        return 0;
}

// Modificar Price

int modify_price_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 6, str);

        fclose(fp);
        return 0;
}

// Obtener Nombre

int get_name_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 1, str);

        fclose(fp);
        return 0;
}

// Obtener domicilio o zona?

int get_zone_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 2, str);

        fclose(fp);
        return 0;
}

// Obtener la Cedula de identificacion

int get_dni_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 3, str);

        fclose(fp);
        return 0;
}

// Obtener la fecha de la factura

int get_date_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 4, str);

        fclose(fp);
        return 0;
}

// Obtener ID de la venta

int get_ID_venta_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 5, str);

        fclose(fp);
        return 0;
}

// Obtener Precio

int get_price_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 6, str);

        fclose(fp);
        return 0;
}


// Obtener naturaleza del cliente

char get_naturaleza(int row)
{
        char dni[20];
        get_dni_invoice(row, dni);
        return dni[0];
}