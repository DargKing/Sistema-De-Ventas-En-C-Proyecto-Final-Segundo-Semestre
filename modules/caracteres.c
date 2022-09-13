#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "../handlers/caracteres.h"

#define COLOR_OPTION_SELECT "\x1b[35;40m"
#define COLOR_RESET "\x1b[0m"

int lenghtStr(char *str)
{
        int i = 0;
        while (str[i] != '\0')
        {
                i++;
        }
        return i;
}

bool caracteresEspeciales(char *str)
{
        int length = lenghtStr(str);

        char caracteresPermitidos[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                                       'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
                                       'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'T', 'U', 'V',
                                       'W', 'X', 'Y', ' ', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '~', '@', '_', '/',
                                       '+', ':', '.', '#', '^', '*', '%', '^', '\0'};

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

char *subString(const char *str, int from, int to)
{
        int length = to - from;
        char *dest = (char *)malloc(sizeof(char) * (length + 1));
        int x = 0;
        for (int i = from; i <= to; i++)
        {
                dest[x] = str[i];
                x++;
        }
        dest[length] = '\0';
        return dest;
}

void substr(char *dest, char *string, int from, int to) /* corta un string desde la casilla n (from) hasta la casilla m (to) y lo mete en dest */
{
        int length = to - from;
        int x = 0;
        for (int i = from; i <= to; i++)
        {
                dest[x] = string[i];
                x++;
        }
        dest[length] = '\0';
}

void cls()      /* Limpia la consola */
{
        printf("\e[1;1H\e[2J");
}

void create_ID(char *ID) /* Crea un ID Unico tomando la fecha y hora actual*/
{

        time_t rawtime;
        struct tm *info;
        time(&rawtime);

        info = localtime(&rawtime);

        strftime(ID, 20, "%y%m%H%I%M%S%p", info);
}

void create_date(char *date)    /* Inserta en el parametro date la fecha actual con el formato DIA-MES-AÑO */
{
        time_t rawtime;
        struct tm *info;
        time(&rawtime);

        info = localtime(&rawtime);

        strftime(date, 12, "%d-%m-%Y", info);
}
