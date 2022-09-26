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
        int acum = 0;
        int i = 0;

        while (1)
        {
                int temp;
                scanf("%d", &temp);
                if (temp == -1)
                        break;
                acum += temp;
                i++;
        }

        int promedio = acum / i;
        return 0;
}