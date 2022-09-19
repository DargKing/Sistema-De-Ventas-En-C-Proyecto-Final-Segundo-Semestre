#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "handlers/tabdb.h"
#include "handlers/clientes.h"
#include "handlers/caracteres.h"
#include "handlers/productos.h"


int main()
{
        FILE* fp;
        fp = fopen("database/productos.txt", "r+");

        if(fp == NULL)
                return -1;

        char ID[20];

        hide_product(1);

        fclose(fp);
        return 0;
}