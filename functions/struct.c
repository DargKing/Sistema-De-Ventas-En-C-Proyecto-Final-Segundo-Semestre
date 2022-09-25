#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "../handlers/winProc.h"
#include "../handlers/clientes.h"
#include "../handlers/struct.h"
#include "../handlers/caracteres.h"

int filas = 0;

/* Función para acomodar la lista según el nombre por orden alfabetico, de
la A a la Z */

void order_alphabetically ()
{
    for (int i = 0; i < filas-1; i++)
    {
        for (int j = i+1; j < filas; j++)
        {
            if (strcmp(lista[i].name, lista[j].name) > 0)
            {
                reordering (i, j);
            }
        }
    }
}


//Función para ordenar la lista según el precio del producto

void order_by_price ()
{
    int total_price[999];

    for (int i = 0; i < filas-1; i++)
    {
        for (int j = i+1; j < filas; j++)
        {
            total_price[i] = atof(lista[i].price) - (atof(lista[i].price) * (atof(lista[i].descount) / 100));
            total_price[j] = atof(lista[j].price) - (atof(lista[j].price) * (atof(lista[j].descount) / 100));

            if (total_price[i] < total_price[j])
            {
                reordering (i, j);
            }
        }
    }
}


//Función para ordenar la lista según el descount que tenga el producto

void order_by_discount ()
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < filas; j++)
        {
            if (atof(lista[i].descount) < atof(lista[j].descount))
            {
                reordering (i, j);
            }
        }
    }
}



/* Función para invertir el orden de los elementos de la lista, se usará después de
haber llamado otra función de ordenamiento. Todas las funciones de ordenamiento
acomodan los valores de forma ascendente, por lo que esta función reordanaría la
lista de forma descendente */

void invest_list ()
{
    for (int i = 0; i < filas-1; i++)
    {
        for (int j = i+1; j < filas; j++)
        {
            reordering (i, j);
        }
    }
}


/* Función para reordenar la lista. Toma un valor "i" y un valor "j" que
son las ublicaciones en los arrays y los intercambia de lugar */

void reordering (int i, int j)
{
    char c_ordenar[26];
    float f_ordenar;
    int i_ordenar;

    strcpy(c_ordenar, lista[i].name);
    strcpy(lista[i].name, lista[j].name);
    strcpy(lista[j].name, c_ordenar);

    f_ordenar      = lista[i].price;
    lista[i].price = lista[j].price;
    lista[j].price = f_ordenar;

    f_ordenar         = lista[i].descount;
    lista[i].descount = lista[j].descount;
    lista[j].descount = f_ordenar;

    i_ordenar   = lista[i].ID;
    lista[i].ID = lista[j].ID;
    lista[j].ID = i_ordenar;

    i_ordenar      = lista[i].stock;
    lista[i].stock = lista[j].stock;
    lista[j].stock = i_ordenar;
}


void delete_table_row_client(char* ID)
{
        int row = search_clients(ID);

        delete_client(row);

        DestroyWindow(hBodyClientes);
}

void SortDateStructClient(STRUCTCLIENTESDATA *data, int type, int len)
{
        if (type == 0)
        {
                for (int i = 1; i < len; i++)
                {
                        for (int z = 0; z < len - i; z++)
                        {
                                char date1[16];
                                char date2[16];

                                strcpy(date1, data[z].date);
                                strcpy(date2, data[z + 1].date);

                                char mounth1[5];
                                char mounth2[5];

                                substr(mounth1, date1, 3, 5);
                                substr(mounth2, date2, 3, 5);

                                char day1[5];
                                char day2[5];

                                substr(day1, date1, 0, 2);
                                substr(day2, date2, 0, 2);

                                char year1[8];
                                char year2[8];

                                substr(year1, date1, 6, 10);
                                substr(year2, date2, 6, 10);

                                if (atoi(year1) < atoi(year2))
                                        continue;
                                else if (atoi(year1) > atoi(year2))
                                {
                                        STRUCTCLIENTESDATA temp;
                                        temp = data[z];
                                        data[z] = data[z + 1];
                                        data[z + 1] = temp;
                                        continue;
                                }
                                else if (atoi(mounth1) > atoi(mounth2))
                                {
                                        STRUCTCLIENTESDATA temp;
                                        temp = data[z];
                                        data[z] = data[z + 1];
                                        data[z + 1] = temp;
                                        continue;
                                }
                                else if (atoi(day1) > atoi(day2))
                                {
                                        STRUCTCLIENTESDATA temp;
                                        temp = data[z];
                                        data[z] = data[z + 1];
                                        data[z + 1] = temp;
                                }
                        }
                }
        }
        else if (type == 1)
        {
                for (int i = 1; i < len; i++)
        {
                for (int z = 0; z < len - i; z++)
                {
                        char date1[12];
                        char date2[12];

                        strcpy(date1, data[z].date);
                        strcpy(date2, data[z + 1].date);

                        char mounth1[5];
                        char mounth2[5];

                        substr(mounth1, date1, 3, 5);
                        substr(mounth2, date2, 3, 5);

                        char day1[5];
                        char day2[5];

                        substr(day1, date1, 0, 2);
                        substr(day2, date2, 0, 2);

                        char year1[5];
                        char year2[5];

                        substr(year1, date1, 6, 10);
                        substr(year2, date2, 6, 10);

                        if (atoi(year1) > atoi(year2))
                                continue;
                        else if (atoi(year1) < atoi(year2))
                        {
                                STRUCTCLIENTESDATA temp;
                                temp = data[z];
                                data[z] = data[z + 1];
                                data[z + 1] = temp;
                                continue;
                        }
                        else if (atoi(mounth1) < atoi(mounth2))
                        {
                                STRUCTCLIENTESDATA temp;
                                temp = data[z];
                                data[z] = data[z + 1];
                                data[z + 1] = temp;
                                continue;
                        }
                        else if (atoi(day1) < atoi(day2))
                        {
                                STRUCTCLIENTESDATA temp;
                                temp = data[z];
                                data[z] = data[z + 1];
                                data[z + 1] = temp;
                        }
                }
        }
        }
}

void SetWindowPosition(WINDOWPOS* pos, int x, int y, int cx, int cy){
        pos->x = x;
        pos->y = y;
        pos->cx = cx;
        pos->cy = cy;
}