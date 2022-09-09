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

// Aparicion del string (En ocasiones usar search_data_file retorna -1 a pesar que si exista el str, pues esto lo evita)
int ubication_code(FILE *fp, char str[]){  
        int fila;
        fp = fopen("facturas.txt","r");
        fila = search_data_file(fp, 0, str);
        fclose(fp);
        return fila;
}

 // Datos de la empresa 
void empresa(FILE *fp){   
        const char rif_emp[20] = "J-123456789";
        const char name_emp[RANGO] = "Kiosco humilde";
        const char ubicacion_emp[MAX] = "Puerto Ordaz";
        const char telef_emp[20] = "0414-9156515";

        printf("Rif: %s\n", rif_emp);
        printf("%s\n", name_emp);
        printf("%s\n", ubicacion_emp);
        printf("Telf: %s\n", telef_emp);

}       

// Determina si es valido o no el rif
int admit_rif(char nationality[], char str[]){  
                int digits;
                caracteresEspeciales(str);
                digits = extension(str);
                if(digits == 9 && caracteresEspeciales(str) == false){
                        return 0;
                }
                return -1;
}

// No permitira que se repita el mismo rif
void no_repeat(FILE *fp, char rif[]){      
        char cont[100];
        fp = fopen("facturas.txt", "r");

        if(fp == NULL){
                printf("Error al abrir el archivo... (no_repeat)\n");
        }

        int fila = search_data_file(fp, 3, rif);
        read_col_file(fp, fila, 3, cont);

  if(!strcmp(cont, rif)){
        exit(1);
  }  
  fclose(fp);
}

// Funcion con los datos del usuario
void factura_user(FILE *fp, int code, char name[], char city[], char rif[], float total){  
        time_t a;
    struct tm *fecha;
    char date[15];
    time(&a);

        char cont[200];
        char aux[10];
        char total_price[10];

        fecha = localtime(&a);  
                                                                                
        snprintf(aux, 5, "%.4d", code);         
        strftime(date, 14, "%d-%m-%Y", fecha);  
        snprintf(total_price, 10, "%.2f", total);

        strcpy(cont, aux);                                      
        strcat(cont, "\t");                                     
        strcat(cont, name);                                     
        strcat(cont, "\t");                                     
        strcat(cont, city);
        strcat(cont, "\t");
        strcat(cont, rif);
        strcat(cont, "\t");
        strcat(cont, date);
        strcat(cont, "\t");
        strcat(cont, total_price);

        add_line_file(fp, cont);

}

// Convierte los espacios en '_' y evita que el usuario sobrepase los caracteres permitidos
char unit_str(char str[]){      
        int j;
        int i = 0;
        for (j = 0; str[j] != '\0'; j++) {
                i++;
        if (str[j] == ' ') str[j] = '_';
        if(i >= 32){
                return -1;
        }
    }

        return str[j];
}

// Naturaleza de la persona 
char naturaleza(char opcion){   
        char nat;
        switch(opcion){
                case 86:
                        return nat = *"V";
                break;
                case 69:
                        return nat = *"E";
                break;
                case 80:
                        return nat = *"P";
                break;
                case 71:
                        return nat = *"G";
                break;
                case 74:
                        return nat = *"J";
                break;

                default:
                        return -1;
                        break;
        }
}

 // Devulve el numero de caracteres de una cadena (string)
int extension(char str[]){     
        int i = 0;
        while (str[i] != '\0')
        {
                i++;
        }
        return i;
}