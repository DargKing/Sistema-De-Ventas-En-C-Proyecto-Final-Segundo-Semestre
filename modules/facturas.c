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


///////////////////////////////////////////////////////////////////

void empresa(FILE *fp)  //      Datos de la empresa 
{       
        const char rif_emp[20] = "J-123456789";
        const char name_emp[RANGO] = "Kiosco humilde";
        const char ubicacion_emp[MAX] = "Puerto Ordaz";
        const char telef_emp[20] = "0414-9156515";

        printf("Rif: %s\n", rif_emp);
        printf("%s\n", name_emp);
        printf("%s\n", ubicacion_emp);
        printf("Telf: %s\n", telef_emp);

}       

char no_repeat(FILE *fp, char rif[])    //      No permitira que se repita el mismo rif
{       
        char cont[100];
        fp = fopen("facturas.txt", "r+");

        if(fp == NULL){
                return -1;
        }

        int fila = search_data_file(fp, 3, rif);
        read_col_file(fp, fila, 3, cont);

        if(!strcmp(cont, rif))
        {
                return -1;
        }  

        fclose(fp);
}

void factura_user(FILE *fp, char code[], char name[], char city[], char rif[], char total[])    //      Funcion con los datos del usuario
{               

        char ID[20];
        time_t a;
        struct tm *fecha;
        char date[15];
        time(&a);

                char cont[200]; // Almacenara el total de caracteres de los campos de la factura

                fecha = localtime(&a);  
                
                create_ID(ID);  // Creamos el ID de la factura

                strftime(date, 14, "%d-%m-%Y", fecha);  // Convertimos la fecha en un string

                strcpy(cont, ID);
                strcat(cont, "\t");
                strcat(cont, code);
                strcat(cont, "\t");                             
                strcat(cont, name);                                     
                strcat(cont, "\t");                                     
                strcat(cont, city);
                strcat(cont, "\t");
                strcat(cont, rif);
                strcat(cont, "\t");
                strcat(cont, date);
                strcat(cont, "\t");
                strcat(cont, total);
                strcat(cont, "$");
                add_line_file(fp, cont);
}

void sort_code_invoice(struct STRUCTINVOICEDATA *DATOS, int p)  //      Ordenara mediante el uso del metodo burbuja los codigos de las facturas
{
        char ID[5];
        char ID2[5];

        char cod[4], cod2[4];
        STRUCTINVOICEDATA temp;

        for(int i = 1; i <= p; i++)
        {
                for(int j = 1; j <= p - i; j++)
                {
                        strcpy(ID, DATOS[j].code);
                        strcpy(ID2, DATOS[j + 1].code);

                        substr(cod, ID, 1, 4);
                        substr(cod2, ID, 1, 4);

                        if(atoi(cod) < atoi(cod2))
                                continue;
                        else if(atoi(ID) > atoi(ID2))
                        {
                                temp = DATOS[j];
                                DATOS[j] = DATOS[j + 1];
                                DATOS[j + 1] = temp;
                        }
                }
        }
}

void sort_date_invoice(struct STRUCTINVOICEDATA *DATOS, int p)  //      Ordenara usando el metodo burbuja las fecha en orden descendente de las facturas
{
        char date1[11], date2[11];
        char year1[5], year2[5];
        char mes1[3], mes2[3];
        char day1[3], day2[3];

        STRUCTINVOICEDATA temp;

        for (int i = 0; i <= p; i++)
        {
                for (int j = 1; j <= p - i; j++)
                {  
                        strcpy(date1, DATOS[j].date);
                        strcpy(date2, DATOS[j + 1].date);
        
                        substr(day1, date1,  0, 2);
                        substr(day2, date2,  0, 2);

                        substr(mes1, date1,  3, 5);
                        substr(mes2, date2,  3, 5);

                        substr(year1, date1, 6, 10);
                        substr(year2, date2,  6, 10);

                        if(atoi(year1) < atoi(year2))
                                continue;

                        else if(atoi(year1) > atoi(year2))
                        {
                                temp = DATOS[j];
                                DATOS[j] = DATOS[j + 1];
                                DATOS[j + 1] = temp;
                                continue;
                        }

                        else if(atoi(mes1) > atoi(mes2))
                        {
                                temp = DATOS[j];
                                DATOS[j] = DATOS[j + 1];
                                DATOS[j + 1] = temp;
                                continue;
                        }

                        else if(atoi(day1) > atoi(day2))
                        {
                                temp = DATOS[j];
                                DATOS[j] = DATOS[j + 1];
                                DATOS[j + 1] = temp;
                                continue;
                        }
                }
        }           
}



//      Funciones de tipo char

char naturaleza(char opcion)    //      Naturaleza de la persona 
{       
        char nat;
        switch(opcion)
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

// Funciones de tipo int

int admit_rif(char nationality[], char str[])   //      Determina si es valido o no el rif
{       
        int digits;
        solo_number(str);
        digits = extension(str);
        if(digits == 9 && solo_number(str) == false)
        {
                return 0;
        }
        return -1;
}

int extension(char str[])       //      Devulve el numero de caracteres de una cadena (string)
{       
        int i = 0;
        while (str[i] != '\0')
        {
                        i++;
        }
        return i;
}

int ubication_code(FILE *fp, char str[])        //      Aparicion del string
{       
        int fila;
        fp = fopen("facturas.txt","r");
        fila = search_data_file(fp, 1, str);
        fclose(fp);
        return fila;
}

int admit_naturaleza(char chr)  //      Determinara si la naturaleza de la persona es correcta
{

        if(chr == 'V' || chr == 'E' || chr == 'G' || chr == 'J')
        {
                return 1;
        }
        return 0;
}

// Funciones de tipo bool

bool solo_number(char *str)     //      Determinara que los numeros del rif no sean letras
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

// Funciones similares pertenecientes de tabdb

int isBlank_invoice(int i)      //      Revisa si en el fichero de "facturas.txt" hay lineas en blanco o no
{
        FILE *fp;
        fp = fopen("facturas.txt", "r+");
        if(fp == NULL) 
        {
                return -1;              
        }

        int space = is_blank(fp, i);
        fclose(fp);

        return space;
}

int gets_lines_invoice()        //      Devuelve el total de saltos de lineas (excepto los dos ultimos) del fichero "facturas.txt"
{
        FILE *fp;
        fp = fopen("facturas.txt", "r+");

        if(fp == NULL)
        {
                return -1;
        }

        int lines = gets_lines_file(fp);

        fclose(fp);
        return lines;
}

int gets_jumplines_invoice()  //        Devuelve la cantidad de lineas con contenido en el fichero "facturas.txt"  
{
        FILE *fp;
        fp = fopen("facturas.txt", "r+");

        if(fp == NULL){
                return -1;
        }

        int lines = gets_jumplines_file(fp);

        fclose(fp);
        return lines;
}

char read_ID_invoice(int i, char *str)  //      Devuelve el id de la facturas
{
        FILE *fp;
        fp = fopen("facturas.txt", "r+");

        if(fp == NULL){
                return -1;
        }

        read_col_file(fp, i, 0, str);

        fclose(fp);
}

char read_code_invoice(int i, char *str)        // Devuelve el codigo unico de la factura
{       
        FILE *fp;
        fp = fopen("facturas.txt", "r+");

        if(fp == NULL){
                return -1;
        }

        read_col_file(fp, i, 1, str);

        fclose(fp);
}

char read_name_invoice(int i, char *str)        // Devuelve el nombre escrito de la factura
{
        FILE *fp;
        fp = fopen("facturas.txt", "r+");

        if(fp == NULL)
        {
                return -1;
        }

        read_col_file(fp, i, 2, str);

        fclose(fp);
}

char read_city_invoice(int i, char *str)        // Devuelve el domicilio escrito en la factura
{
        FILE *fp;
        fp = fopen("facturas.txt", "r+");

        if(fp == NULL)
        {
                return -1;
        }

        read_col_file(fp, i, 3, str);

        fclose(fp);
}

char read_rif_invoice(int i, char *str) // Devuelve el rif de la factura
{
        FILE *fp;
        fp = fopen("facturas.txt", "r+");

        if(fp == NULL)
        {
                return -1;
        }

        read_col_file(fp, i, 4, str);

        fclose(fp);
}

char read_date_invoice(int i, char *str)        // Devuelve la fecha de impresion de la factura
{       
        FILE *fp;
        fp = fopen("facturas.txt", "r+");

        if(fp == NULL)
        {
                return -1;
        }

        read_col_file(fp, i, 5, str);

        fclose(fp);
}

char read_price_invoice(int i, char *str)       // Devuelve el precio total en la factura
{
        FILE *fp;
        fp = fopen("facturas.txt", "r");

        if(fp == NULL)
        {
                return -1;
        }

        read_col_file(fp, i, 6, str);

        fclose(fp);
}