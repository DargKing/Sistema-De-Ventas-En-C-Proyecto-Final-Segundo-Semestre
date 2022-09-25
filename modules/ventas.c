#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../handlers/caracteres.h"
#include "../handlers/tabdb.h"
#include <time.h>

/*
        ARGUMENTO:
                Ingresara en la database una nueva venta  

        PARAMETROS:
                ID = El ID de la venta
                productos = Los productos que han sido comprados
                ID_clientes = El ID del cliente
                discount =  El descuento que poseera el precio del producto

*/

int new_ventas(char *ID, char *productos, char *ID_cliente, char *discount)    
{
        char product[100 + strlen(productos)];  // product inicialmente ocupara 100 bytes de memoria pero adicionalmente se agrega el tamaño de productos
        char date[14];  
        create_date(date); 

        char show[] = "T"; 

        sprintf(product, "%s\t%s\t%s\t%s\t%s\t%s", ID, date, productos, ID_cliente, discount, show);

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        add_line_file(fp, product); // Añadimos todos los datos de product en la database

        fclose(fp); // Cerramos el fichero
        return 0;
}

/*
        ARGUMENTO:
                 Modificara los datos una venta

        PARAMETROS:
                ID = El ID de la venta
                productos = Los productos que han sido comprados
                ID_clientes = El ID del cliente
                discount =  El descuento que poseera el precio del producto

*/

int modify_venta(char *ID, char *productos, char *ID_cliente, char *discount) 
{

        char product[strlen(productos) + 100]; // product inicialmente ocupara 100 bytes de memoria pero adicionalmente se agrega el tamaño de productos
        char date[14];
        create_date(date); // Creamos la fecha exacta al emitir la nueva venta usando como variable date

        char show[] = "T";
        // Hacemos uso de sprintf para convertir todos los datos en un solo string que es almacenado en product
        sprintf(product, "%s\t%s\t%s\t%s\t%s\t%s", ID, date, productos, ID_cliente, discount, show);

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID); // row hallara la posicion exacta en donde estara el ID 
        delete_line_file(fp, row); // Con la posicion dada en row eliminamos esa linea
        add_line_file(fp, product); // Añadimos todos los datos de producto a la database

        fclose(fp); // Cerramos el fichero
        return 0;
}

/*
        ARGUMENTO:
                Cambiara la visibilidad (show) de una venta

        PARAMETRO:
                row = La fila en donde estara show

*/

int hide_venta(int row) 
{
        FILE *fp;

        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        modify_col_file(fp, row, 7, "F"); // Modificamos la columna show cambiando la T (True) por F (False)

        fclose(fp); // Cerramos el fichero

        return 0;
}

/*
        ARGUMENTO:
                Obtendra el ID de venta

        PARAMETROS:
                row = La fila en donde esta ubicado la venta
                ID = El ID de venta 

*/

int get_ID_venta(int row, char *ID)
{
        FILE *fp;

        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 0, ID); // Leemos en la fila "row" y columna 0 (Columna exclusiva para el ID_venta) el valor y lo almacenamos en ID
        fclose(fp); // Cerramos el fichero
        return 0;
}

/*
        ARGUMENTO:
                Obtendra la fecha al realizar la venta

        PARAMETROS:
                row = La fila en donde esta ubicada la venta
                date = La fecha ak realizar la venta

*/ 

int get_date_venta(int row, char *date)
{

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 1, date); // Leemos en la fila "row" y columna 1 (Columna exclusiva para la fecha) el valor y lo almacenamos en date
        fclose(fp); // Cerramos el fichero
        return 0;
}

/*
        ARGUMENTO:
                Obtendra los productos que el usuario compro

        PARAMETROS:
                row = La fila en donde esta ubicada la venta
                productos = Los productos que fueron comprados

*/ 

int get_productos_venta(int row, char *productos)
{

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 2, productos); // Leemos en la fila "row" y columna 2 (Columna exclusiva para los productos) el valor y lo almacenamos en productos
        fclose(fp); // Cerramos el fichero
        return 0;
}

/*
        ARGUMENTO:
                Obtendra el ID del cliente

        PARAMETROS:
                row = La fila en donde esta ubicada la venta
                id_client = El id del cliente

*/


int get_ID_cliente_venta(int row, char *id_client)
{

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 3, id_client);  // Leemos en la fila "row" y columna 3 (Columna exclusiva para el ID del cliente) el valor y lo almacenamos en id_client
        fclose(fp); // Cerramos el fcihero
        return 0;
}

/*
        ARGUMENTO:
                Obtendra el descuento del producto

        PARAMETROS:
                row = La fila en donde esta ubicada la venta
                discount = El descuento del producto

*/

int get_discount_venta(int row, char *discount)
{
        FILE *fp;

        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el producto
        if (fp == NULL)
                return -1;

        read_col_file(fp, row, 4, discount);  // Leemos en la fila "row" y columna 4 (Columna exclusiva para el descuento) el valor y lo almacenamos en discount
        fclose(fp); // Cerramos el fichero
        return 0;
}

/*
        ARGUMENTO:
                Obtendra la visibilidad de la factura

        PARAMETRO:
                row = La fila en donde esta ubicada la visibilidad

*/

int get_visibility_venta(int row)
{

        FILE *fp;

        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        char str[10];

        read_col_file(fp, row, 5, str);  // Leemos en la fila "row" y columna 5 (Columna exclusiva para el show) el valor y lo almacenamos en str

        fclose(fp); // Cerramos el fichero

        if (str[0] == 'T') // Si el valor de show es 'T' se tomara como valido y retornara 1
                return 1;

        return 0; // Si show es diferente a 'T' se tomara como invalido la factura y retornara 0
}

/*
        ARGUMENTO:
                Devuelve el total de saltos de lineas (excepto los dos ultimos) del fichero "ventas.txt"

*/

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

/*
        ARGUMENTO:
                Devuelve la cantidad de lineas con contenido en el fichero "ventas.txt"

*/

int get_jumplines_venta_file()
{
        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        int lines = get_lines_venta_file();
        int i = 0;
        int jumplines = 0;

        while (i < lines)
        {
                if (!isBlank_venta(i) && get_visibility_venta(i))
                {
                        jumplines++;
                }
                i++;
        }

        fclose(fp);
        return jumplines;
}

/*
        ARGUMENTO:
                Devuelve el total de caracteres que contiene el segmento que abarca la fila "row" y columna "col"

        PARAMETROS:
                row = La fila en donde esta ubicada la venta
                col = La columna en donde este ubicada la venta

*/

int get_len_col_ventas(int row, int col)
{
        FILE *fp;

        fp = fopen("database/ventas.txt", "r+");
        if (fp == NULL)
                return -1;

        int len = get_len_col_file(fp, row, col);

        fclose(fp);
        return len;
}

/*
        ARGUMENTO:
                Obtendra el total de productos que fueron comprados

        PARAMETRO:
                ID = ID de la venta

*/

int get_amounts_products_venta(char *ID)
{
        FILE *fp;
        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;


        int row = search_venta_ID_venta(ID); // Busca la posicion del ID de venta y la almacena en row
        int lenColProductos = get_len_col_ventas(row, 2); // Devuelve el total de caracteres en la fila "row" (obtenida por el ID de venta) en la columna 
        int cantidadDeProductos = 1; // La cantidad de productos siempre comenzaran con uno

        char productos[lenColProductos + 2];

        get_productos_venta(row, productos);

        for (int i = 0; i < lenColProductos; i++) // Leera cada caracter de lenColProductos
        {
                if (productos[i] == '/') // Si encuentra un '/' en la lectura se incrementa en uno la cantidad de productos
                        cantidadDeProductos++;
        }

        fclose(fp); // Cerramos el fichero
        return cantidadDeProductos; // Retorna la cantidad de productos
}

/*
        ARGUMENTO:
                Retorna la cantidad de lineas en blanco que tiene el fichero "ventas.txt"

        PARAMETROS:
                row = La fila del fichero "ventas.txt" 

*/

int isBlank_venta(int row)
{
        FILE *fp;
        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        int blank = is_blank(fp, row); // blank almacenara el total de lineas en blanco que devuelva is_blank

        fclose(fp); // Cerramos el fichero
        return blank; // Retorna el total de lineas en blanco
}

/*
        ARGUMENTO:
                Retorna la posicion del ID de venta

        PARAMETROS:
                ID = El ID de venta

*/

int search_venta_ID_venta(char *ID)
{
        FILE *fp;
        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 0, ID); // Busca el ID de venta en el fichero y al encontrarlo nos devuelve su posicion

        fclose(fp); // Cerramos el fichero
        return row; // Retorna  la posicion 
}


/*
        ARGUMENTO:
                Retorna la posicion del ID del cliente

        PARAMETROS:
                ID = El ID del cliente

*/

int search_venta_ID_cliente(char *ID)
{
        FILE *fp;
        fp = fopen("database/ventas.txt", "r+"); // Iniciamos el fichero
        if (fp == NULL)
                return -1;

        int row = search_data_file(fp, 3, ID); // Busca el ID del cliente en el fichero y al encontrarlo nos devuelve su posicion

        fclose(fp); // Cerramos el fichero
        return row; // Retorna  la posicion 
}