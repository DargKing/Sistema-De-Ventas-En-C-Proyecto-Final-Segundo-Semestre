#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <conio.h>
#include "caracteres.h"

struct datosUsuario {
        char email[128];
        char password[128];
};

bool caracteresEspeciales(char *str);

bool comprobar(char *email, char *password)
{
        const char *filename = "input.txt";

        FILE *input_file = fopen(filename, "r");
        if (!input_file)
                return false;

        char *contents = NULL;
        size_t len = 0;

        bool run = true;

        while (getline(&contents, &len, input_file) != -1)
        {
                char *emailDB;
                char *passwordDB;
                int lastTab = 0;
                int x = 0;
                for (int i = 0; i < lenghtStr(contents) + 1; i++)
                {
                        if (contents[i] == '\t' || contents[i] == '\n' || contents[i] == '\0')
                        {
                                if (x == 0)
                                {
                                        emailDB = subString(contents, lastTab, i);
                                }
                                if (x == 1)
                                {
                                        passwordDB = subString(contents, lastTab, i);
                                }
                                
                                lastTab = i + 1;
                                x++;
                        }
                }

                if (!strcmp(password, passwordDB) && !strcmp(email, emailDB))
                {
                        fclose(input_file);
                        free(contents);
                        return true;
                }
        }

        fclose(input_file);
        free(contents);
        return false;
}

int main()
{

        int num;
        char email[128];
        char password[128];

        printf("Email\n");
        scanf("%127s", &email);

        printf("Password\n");
        scanf("%127s", &password);

        if (caracteresEspeciales(email) == true || caracteresEspeciales(password) == true)
        {
                printf("Error: Ingreso Caracteres no Permitidos\n");
                return 0;
        }

        if (comprobar(email, password) == false)
        {
                printf("Error: El email no existe o contraseña equivocada, intentelo otra ves");
                return 0;
        }

        printf("Login successful\n");

        return 0;
}