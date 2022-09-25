#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "../handlers/tabdb.h"
#include "../handlers/caracteres.h"
#include "../handlers/facturas.h"

// Crear Nueva Factura

int create_new_invoices(char *zone, char *rif_company, char *id_client, char *direction_company)
{

        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        char ID[20];
        char date[14];
        char str[300];

        create_date(date);
        create_ID(ID);

        sprintf(str, "%s\t%s\t%s\t%s\t%s\t%s\tT", ID, zone, rif_company, date, id_client, direction_company);

        add_line_file(fp, str);

        fclose(fp);
        return 0;
}

// Ocultar Linea Anterior

int hide_invoice(int i)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        modify_col_file(fp, i, 6, "F");

        fclose(fp);
        return 0;
}

// Crear Nueva Factura

int modify_invoices(char *ID, char *zone, char *rif_company, char *date, char *id_client, char *direction_company)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        char str[300];

        sprintf(str, "%s\t%s\t%s\t%s\t%s\t%s\tT", ID, zone, rif_company, date, id_client, direction_company);

        delete_line_file(fp, search_data_file(fp, 0, ID));
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

// Devuelve el id de la factura

char get_ID_invoice(int i, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
        {
                return -1;
        }

        read_col_file(fp, i, 0, str);

        fclose(fp);
}

// Devuelve el domicilio del cliente

int get_zone_invoice(int i, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
        {
                return -1;
        }

        read_col_file(fp, i, 1, str);

        fclose(fp);
}

// Obtener Nombre

int get_rif_company_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 2, str);

        fclose(fp);
        return 0;
}

// Obtener domicilio o zona?

int get_date_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 3, str);

        fclose(fp);
        return 0;
}

// Obtener la Cedula de identificacion

int get_id_client_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 4, str);

        fclose(fp);
        return 0;
}

// Obtener la fecha de la factura

int get_direction_company_invoice(int row, char *str)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 5, str);

        fclose(fp);
        return 0;
}

// Obtener ID de la venta

int get_visibility_invoice(int row)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
                return -1;

        char str[2];

        read_col_file(fp, row, 6, str);

        if (strcpy(str, "T"))
                return 1;

        fclose(fp);
        return 0;
}

// No permitira que se repita el mismo rif

char no_repeat(char rif[])
{
        char cont[100];
        FILE *fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
        {
                return -1;
        }

        int fila = search_data_file(fp, 3, rif);
        read_col_file(fp, fila, 3, cont);

        if (!strcmp(cont, rif))
        {
                return -1;
        }

        fclose(fp);
}

// Naturaleza de la persona

char naturaleza(char opcion)
{
        char nat;
        switch (opcion)
        {
        case 86:
                return nat = 'V';
                break;
        case 69:
                return nat = 'E';
                break;
        case 80:
                return nat = 'P';
                break;
        case 71:
                return nat = 'G';
                break;
        case 74:
                return nat = 'J';
                break;

        default:
                fflush(stdin);
                return -1;
                break;
        }
}

// Determina si es valido o no el rif

int admit_rif(char nationality[], char str[])
{
        int digits;
        solo_number(str);
        digits = extension(str);
        if (digits == 9 && solo_number(str) == false)
        {
                return 0;
        }
        return -1;
}

// Devuelve el numero de caracteres de una cadena (string)

int extension(char str[])
{
        int i = 0;
        while (str[i] != '\0')
        {
                i++;
        }
        return i;
}

// Determinara si la naturaleza de la persona es correcta

int admit_naturaleza(char chr)
{

        if (chr == 'V' || chr == 'E' || chr == 'G' || chr == 'J')
        {
                return 1;
        }
        return 0;
}

// Determinara que los numeros del rif no sean letras

bool solo_number(char *str)
{
        int length = lenghtStr(str);

        char caracteresPermitidos[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'};

        int length2 = lenghtStr(caracteresPermitidos);

        for (size_t i = 0; i < length; i++)
        {
                bool isValid = false;
                for (size_t x = 0; x < length2; x++)
                {
                        if (str[i] == caracteresPermitidos[x])
                        {
                                isValid = true;
                        }
                }

                if (isValid == false)
                {
                        return true;
                }
        }
        return false;
}

// Revisa si en el fichero de "facturas.txt" hay lineas en blanco o no

int isBlank_invoice(int i)
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");
        if (fp == NULL)
        {
                return -1;
        }

        int space = is_blank(fp, i);
        fclose(fp);

        return space;
}

// Devuelve el total de saltos de lineas (excepto los dos ultimos) del fichero "facturas.txt"

int gets_lines_invoice()
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
        {
                return -1;
        }

        int lines = gets_lines_file(fp);

        fclose(fp);
        return lines;
}

// Devuelve la cantidad de lineas con contenido en el fichero "facturas.txt"

int gets_jumplines_invoice()
{
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
        {
                return -1;
        }

        int lines = gets_jumplines_file(fp);

        fclose(fp);
        return lines;
}

int search_invoice_id_client(char* ID){
        FILE *fp;
        fp = fopen("database/facturas.txt", "r+");

        if (fp == NULL)
        {
                return -1;
        }

        int row = search_data_file(fp, 4, ID);

        fclose(fp);
        return row;
}