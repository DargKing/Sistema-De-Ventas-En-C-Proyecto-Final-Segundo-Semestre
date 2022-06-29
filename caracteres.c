#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// #include "caracteres.h"

int lenghtStr(char *str)
{
        int i = 0;
        while (str[i] != '\0' && i < 50)
        {
                i++;
        }
        return i;
}

bool caracteresEspeciales(char *str)
{
        int length = lenghtStr(str);

        char caracteresPermitidos[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                                       'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1',
                                       '2', '3', '4', '5', '6', '7', '8', '9', '~', '@', '_', '/', '+', ':', '.', '#',
                                       '^', '*', '%', '^', '\0'};

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
        char *dest = (char*)malloc(sizeof(char) * (length + 1));
        int x = 0;
        for (int i = from; i <= to; i++){
                dest[x] = str[i];
                x++;
        }
        dest[length] = '\0';
        return dest;
}