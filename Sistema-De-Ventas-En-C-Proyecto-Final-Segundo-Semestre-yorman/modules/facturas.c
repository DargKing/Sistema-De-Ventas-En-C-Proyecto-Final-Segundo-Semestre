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

struct _datos // Struct con los datos del usuario
{
    int code[256];  // Aqui obtendra el codigo unico de la factura
    char nombre[RANGO];
    char domicilio[RANGO];
    char i_rif;
    char rif[10];
} datos;

struct _productos     //Vamos a tener todo lo refetente a un producto ordenado en esta struct 
{
    char item[40];
    char definiton[100];
    int amount;
    float price;
} product;


int main()  
{
    FILE *archivo, *productos;
    int linea;
    int fila;   // Almacenara la fila exacta

    char str[100];  // Leera el nombre del usuario en la facturas.txt
    char aux[2]; // Volvera el origen en un string para poder usar las funciones strcat, y strcpy
    char origen; // Obtendra la naturaleza de la persona... V, E, P, J, G
    char fusion[20];    // Concatenara el origen junto al rif para tener un solo string

    int i;
    int opcion;

    while(opcion != ESC){   // Mientras no presione Esc el programa seguira
    printf("1) Crear facturas\n");
    printf("2) Reporte de Facturas\n"); 
    printf("3) Eliminar Factura\n");
    printf("4) Modificar factura\n");
    printf("Presione la tecla Esc para salir\n");
    opcion = getch();
        switch(opcion){
            case 49:    // CREACION DE UNA FACTURA NUEVA
            archivo = fopen("facturas.txt", "a+");
            linea = 0;

    while (!feof(archivo)) {    // No permitira que se repita el mismo numero de codigo en el .txt
        fscanf(archivo, "%d", &datos.code[linea]); 
        fgets(str, 100, archivo);       
        linea++;
    }

    int may = 0;

    for(i = linea; i > 0; i--){
        if(datos.code[i] > may){
            may = datos.code[i] + 1;
        }   
    }

    fflush(stdin);
    printf("Dime tu nombre: \n"); gets(datos.nombre);

        if(datos.nombre[0] == NULL){    
            strcpy(datos.nombre, "Undefined");
        }

    while(unit_str(datos.nombre) == -1){    // Si el usuario no teclea nada (solamente presiona enter) mostrara el texto Undefined en la facturas.txt
        printf("Haz superado el limite de caracteres del nombre... Ingrese un nombre correcto\n");
        printf("Dime tu nombre: \n"); gets(datos.nombre);
        system("cls");      
    }

    printf("Dime tu domicilio: \n"); gets(datos.domicilio);
        
        if(datos.domicilio[0] == NULL){ 
            strcpy(datos.domicilio, "Undefined");
        }

    while(unit_str(datos.domicilio) == -1){ // Si el usuario no teclea nada (solamente presiona enter) mostrara el texto Undefined en la facturas.txt
        printf("Haz superado el limite de caracteres del domicilio.. Ingrese un domicilio correcto\n");
        printf("Dime domicilio: \n"); gets(datos.domicilio);
        system("cls");
    }
    system("cls");
    printf("Presione usando las mayusculas su opcion\n"); 
    printf("Eres una persona natural, teclea <V>\n");
    printf("Eres una persona natural extranjera, teclea <E>\n");
    printf("Eres una persona natural extranjera sin cedula, teclea <P>\n");
    printf("Eres un ente gubernamental, teclea <G>\n");
    printf("Eres un contribuyente juridico, teclea <J>\n");
    scanf("%c", &origen);

    while(naturaleza(origen) == -1){
        printf("Caracter invalido\n");
        getchar();
        scanf("%c", &origen);
    }

    aux[1] = '\0';
    aux[0] = origen;

    bool valor = false; 
    int digits;

        printf("Nota: Solamente se admiten numeros\n");
        printf("Dame el numero de tu rif: \n" );    
        fflush(stdin);      
        printf("%s-", aux);  scanf("%s", &datos.rif);
        while(admit_rif(aux, datos.rif) == -1){ 
            printf("Rif invalido, pon uno correcto\n");
            system("cls");
            printf("%s-", aux);  scanf("%s", &datos.rif);
    }   
    system("cls");
    strcpy(fusion, aux);
    strcat(fusion, datos.rif);

    no_repeat(archivo, fusion);  // Pensar una mejor forma que aventar al usuario fuera del programa XD     

    int amount, i;
    int cantidad;
    float total = 0;

    printf("Cantidad de producto: \n"); scanf("%d", &amount);

    fflush(stdin);      

    for(i = 0; i < amount; i++){
        printf("Dime el producto: \n"); gets(product.item); 

        printf("Establece una descripcion del producto: \n"); gets(product.definiton);
        printf("Precio del producto: \n"); scanf("%f", &product.price);
        fflush(stdin);

        total += product.price; // El total a pagar 
    }   
    
    factura_user(archivo, may, datos.nombre, datos.domicilio, fusion, total);
    
    fclose(archivo);

            break;
            case 50:    // REPORTE DE FACTURAS
            archivo = fopen("facturas.txt", "r+");
            
            if(archivo == NULL){
                printf("Error al abrir el archivo\n");
            }

    char rp[200];
    char code_2[5]; // Mostrara la factura que concuerde con el codigo unico tecleado
    char s;

    printf("Para ver todas las facturas... Teclee <1>\n");
    printf("Para las facturas segun su codigo unico... Teclee <2>\n");
    scanf("%d", &opcion);
    switch(opcion){ 
        case 1: 
    while(fgets(rp, 100, archivo) != NULL){ 
        printf("%s\n", rp);                 
    }                                       
    getchar();                              
    getchar();                              
        break;
        case 2: // Mostrar una factura en especifico y si deseas (presionando s o S) te mostrara la factura ampliada
        printf("Dime el codigo unico de la factura\n");
        fflush(stdin);
        scanf("%s", code_2);
        if(code_2 == ESC){
            break;
        }

        fila = ubication_code(archivo, code_2);
        read_line_file(archivo, fila, rp);  
        
        system("cls");

        printf("%s\n", rp);

        printf("Desea ver la factura ampliada?\n");
        printf("Presione <S> para Si\n");
        printf("Presione cualquier tecla para No\n");

        printf("Escoja una opcion\n");
        fflush(stdin);
        scanf("%c", &s);
        if(s == 's' || s == 'S'){
            char id[10], name[30], city[30], rif[12], date[20], total[20]; 
            
            read_col_file(archivo, fila, 0, id);
            read_col_file(archivo, fila, 1, name);
            read_col_file(archivo, fila, 2, city);
            read_col_file(archivo, fila, 3, rif);
            read_col_file(archivo, fila, 4, date);
            read_col_file(archivo, fila, 5, total);
            printf("--Datos de la empresa---\n");
            empresa(archivo);   
            printf("--Factura---\n");           
            printf("ID: %s\n", id);
            printf("Name: %s\n", name);
            printf("City: %s\n", city);
            printf("Rif: %s\n", rif);
            printf("Date: %s\n", date);
            printf("Total: %s\n", total);
            
            getchar();
            getchar();
        }   

        break;
    }
            fclose(archivo);
            break;

            case 51:    // ELIMINACION DE UNA FACTURA EXISTENTE
            archivo = fopen("facturas.txt", "r+");      
    
            if(archivo == NULL){
                printf("Error al abrir el archivo\n");
            }

            printf("Dime la el codigo unico de la factura a eliminar\n");
            scanf("%s", code_2);
            fila = search_data_file(archivo, 0, code_2);

            while((fila = search_data_file(archivo, 0, code_2)) == -1){
                printf("No existe esta factura, ingrese una factura correcta:\n");
                scanf("%s", code_2);
                fila = ubication_code(archivo, code_2);
            }

            delete_line_file(archivo, fila);
            fclose(archivo);
            break;

            case 52:    // MODIFICACION DE FACTURAS
        archivo = fopen("facturas.txt", "r+");
        
        if(archivo == NULL){
            printf("Error al abrir el archivo\n");
        }

    char fact[5];
    int col = 0;
    printf("Que factura desea modificar?\n");
    scanf("%s", &fact); 
    fila = ubication_code(archivo, fact);   // Creamos esta funcion para obtener la fila exacta en donde esta el code de la fila...                                 
// Obviamos la posibilidad de usar el search_data_file en la fila 240 por que retorna un -1 y borra todo el fichero txt.

    while(opcion != 5){

    printf("Que desea modificar de la factura?\n");
    printf("Teclee <1> para cambiar el nombre\n");
    printf("Teclee <2> para cambiar el domicilio\n");
    printf("Teclee <3> para cambiar el rif\n");
    printf("Teclee <4> para cambiar el total a pagar\n");   
    printf("Teclee <5> para salir\n");  
    scanf("%d", &opcion);       
    fflush(stdin);      
    system("cls");
 
 if(opcion == 1){

    char new_name[RANGO];
    col = 1;

    printf("Nuevo nombre del usuario: \n");
    fflush(stdin); 
    gets(new_name);

    if(new_name[0] == NULL){    
        strcpy(new_name, "Undefined");
    }

    while(unit_str(new_name) == -1){    // Si el usuario no teclea nada (solamente presiona enter) mostrara el texto Undefined en la facturas.txt
        printf("Haz superado el limite de caracteres del nombre.. Ingrese un nombre correcto\n");
        printf("Dime el nuevo nombre: \n"); gets(new_name);
        system("cls");
    }

    modify_col_file(archivo, fila, col, new_name);
    break;
  }

if(opcion == 2){
    char new_domicilio[RANGO];
    col = 2;

    printf("Nuevo domicilio del usuario: \n");
    fflush(stdin); 
    gets(new_domicilio);
    
    if(new_domicilio[0] == NULL){   
        strcpy(new_domicilio, "Undefined");
    }

    while(unit_str(new_domicilio) == -1){   // Si el usuario no teclea nada (solamente presiona enter) mostrara el texto Undefined en la facturas.txt
        printf("Haz superado el limite de caracteres del domicilio.. Ingrese un domicilio correcto\n");
        printf("Dime el nuevo domicilio: \n"); gets(new_domicilio);
        system("cls");
    }
  
    modify_col_file(archivo, fila, col, new_domicilio);   
    break;
    } 

if(opcion == 3){
    char fusion[15];
    char new_rif[10];
    col = 3;

    system("cls");
    printf("Presione usando las mayusculas su opcion\n"); 
    printf("Eres una persona natural, teclea <V>\n");
    printf("Eres una persona natural extranjera, teclea <E>\n");
    printf("Eres una persona natural extranjera sin cedula, teclea <P>\n");
    printf("Eres un ente gubernamental, teclea <G>\n");
    printf("Eres un contribuyente juridico, teclea <J>\n");
    scanf("%c", &origen);

    naturaleza(origen);

    while(naturaleza(origen) == -1){
        printf("Caracter invalido\n");
        getchar();
        scanf("%c", &origen);
    }

  aux[1] = '\0';
  aux[0] = origen;

  printf("Nuevo rif del usuario: \n");  

    printf("%s-", aux); scanf("%s", new_rif); 
    int digits = extension(new_rif);
    caracteresEspeciales(new_rif);
        while(admit_rif(aux, datos.rif) == -1){ 
            printf("Rif invalido, pon uno correcto\n");
            system("cls");
            printf("%s-", aux);  scanf("%s", &datos.rif);
    }

    strcpy(fusion, aux);
    strcat(fusion, new_rif); 
    modify_col_file(archivo, fila, col, fusion);
    break;
}       

if(opcion == 4){
    float new_total;
    char total_price[8];
    col = 5;

    printf("Nuevo total a pagar: \n");
    scanf("%f", &new_total);

    if(new_total <= 0){
        printf("Total invalido, ungrese un total correcto\n");
        scanf("%f", &new_total);
    }

    snprintf(total_price, 7, "%.2f", new_total);

    modify_col_file(archivo, fila, col, total_price);
    break;
    }

if(opcion == 5){ // Forma temporal... o no... de arreglar el bug (El bug es, al  presionar la opcion '5' se borra toda la informacion del txt de facturas)
    return 0; 
    }

        system("cls");
    }

    fclose(archivo);    


            case ESC:   // ESC tiene registrara el codigo ASCII de la tecla Esc del teclado por ende al presionarla se quitara el programa
                printf("Haz salido del programa\n");
                break;
            default:    // En caso de presionar una opcion que no este indicada previamente
                printf("Opcion no valida\n");
                fflush(stdin);
                getch();
                break;
        }
            system("cls");
    }

}