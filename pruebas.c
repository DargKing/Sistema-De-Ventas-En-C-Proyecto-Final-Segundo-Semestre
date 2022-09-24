#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "handlers/tabdb.h"
#include "handlers/clientes.h"
#include "handlers/caracteres.h"
#include "handlers/productos.h"
#include "handlers/ventas.h"

int main()
{
        FILE *fp;
        fp = fopen("database/productos.txt", "r+");

        if (fp == NULL)
                return -1;

        int lines = get_lines_venta_file();

        char ID[20];
        char ID_cliente[20];
        char date[20];
        char discount[20];

        char *productos;

        float precioTotal = 0;

        get_ID_venta(0, ID);
        get_ID_cliente_venta(0, ID_cliente);
        get_date_venta(0, date);
        get_discount_venta(0, discount);

        int row;
        int colLenProducts = 0;

        // Obtener la lista de productos comprados
        row = search_venta_ID_venta(ID);
        colLenProducts = get_len_col_ventas(row, 2);
        productos = (char *)malloc((colLenProducts + 1) * sizeof(char));

        get_productos_venta(row, productos);

        char subProducto[50];
        int x = 0;

        for (int i = 0; i < colLenProducts + 1; i++)
        {
                if (productos[i] != '/' && productos[i] != '\0')
                        subProducto[x] = productos[i];
                else{
                        subProducto[x] = '\0';

                        char strCantidad[20];
                        char strDescuento[20];
                        char ID_producto[20];
                        char strPrecio[20];
                        int precio;
                        int descuento;
                        int cantidad;


                        // Estas variable se encargan de marcar cuando termina ID, precio y descuento
                        int fID;
                        int fCantidad;
                        int fDescuento;

                        for(int j = 0; j < x + 1; j++){
                                if(subProducto[j] == '=')
                                        fID = j;
                                if(subProducto[j] == '?')
                                        fCantidad = j;
                                if(subProducto[j] == '\0')
                                        fDescuento = j;
                        }

                        substr(ID_producto, subProducto, 0, fID);
                        substr(strCantidad, subProducto, fID + 1, fCantidad);
                        substr(strDescuento, subProducto, fCantidad + 1, fDescuento);

                        row = search_product(ID_producto);

                        get_price_product(row, strPrecio);

                        precio = atoi(strPrecio);
                        descuento = atoi(strDescuento);
                        cantidad = atoi(strCantidad);


                        precioTotal += (precio - (precio * (descuento / 100))) * cantidad;

                        x = -1;
                }
                x++;
        }

        printf("%.2f\n", precioTotal);

        fclose(fp);
        return 0;
}