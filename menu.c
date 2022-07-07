#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "caracteres.h"

void suma()
{
        float a, b, c;
        puts("Inserte N1: ");
        scanf("%f", &a);
        puts("Inserte N2: ");
        scanf("%f", &b);

        c = a + b;

        printf("\nLa suma de %f y %f es %f", a, b, c);
}

int main()
{
        cls();
        bool run_main = true, run_second = true;
        int eleccion;

        while (run_main)
        {
                eleccion = select(2, "ELIGE UNA OPCION",
                                  "1- ADELANTE", "2- SALIR");
                if (eleccion == -1 || eleccion == 1)
                        break;
                if (eleccion == 0)
                {
                        while (run_second)
                        {
                                int eleccion2 = select(2, "ELIGE UNA OPCION 1", "1- HACER SUMA", "2- ATRAS");
                                if (eleccion2 == -1){
                                        run_main = false;
                                        break;
                                }
                                if(eleccion2 == 0)
                                        suma();
                                if(eleccion2 == 1)
                                        break;
                        }
                }
        }

        puts("Vuelva pronto CTM");
}