#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "caracteres.h"
#include "tabdb.h"
#include "user.h"

typedef struct
{
        char email[100];
        char password[100];
        char username[100];
        char ID[20];
        char range[20];
        int login;
} USERS;

int main()
{
        cls();

        int desicion = select(2, NULL, "Log In", "Sing Up");
        if (desicion == -1)
        {
                puts("Nos Vemos Pronto");
                return 0;
        }

        cls();

        USERS user;

        user.login = 0;

        if (desicion == 0)
        {
                puts("Introduce El Email");
                gets(user.email);

                puts("Introduce El Password");
                gets(user.password);

                int analisis = login(user.email, user.password);

                if (analisis == -1)
                {
                        puts("Error en el archivo");
                        return -1;
                }
                if (analisis == -2)
                {
                        puts("Email o Password Incorrectos");
                        return 0;
                }

                if (analisis >= 0)
                {
                        get_data_user(analisis, user.ID, user.email, user.password,
                                      user.username, user.range);
                        user.login = 1;
                        puts("Login Successfully");
                }
        }

        if (desicion == 1)
        {
                puts("Introduce tu email");
                gets(user.email);

                puts("Introduce tu contraseña");
                gets(user.password);

                puts("Introduce tu username");
                gets(user.username);

                int create = create_new_user(user.email, user.password, user.username, "USER");

                if (create == -1)
                {
                        puts("Error, Problemas en el archivo");
                        return -1;
                }

                if (create == 0)
                {
                        puts("Error, Email Existente");
                        return 0;
                }

                if (create == 1)
                {
                        get_data_user(search_user(user.email), user.ID, user.email,
                                      user.password, user.username, user.range);
                }
        }

        puts(user.range);

        if (strcmp(user.range, "ADMIN"))
                desicion = select(4, NULL, "Change Password", "Delete User", "Set Admin", "Exit");
        else
                desicion = select(4, NULL, "Change Password", "Delete User", "Set User", "Exit");

        // cls();
        char temp[100];

        switch (desicion)
        {
        case -1:
                puts("Vuelva Pronto");
                return 0;
                break;
        case 0:
                puts("Introduce la nueva contraseña");

                gets(temp);

                change_password(user.ID, temp);

                puts("Se ha cambiado la contraseña");
                break;
        case 1:
                puts("Introdusca su password para confirmar");

                gets(temp);

                if (!strcmp(temp, user.password))
                {
                        int del = delete_user(user.ID);
                        if (del == -1)
                        {
                                puts("Error, problemas en el archivo");
                        }
                        if (del == 0)
                        {
                                puts("Usuario no encontrado");
                        }
                        if (del == 1)
                        {
                                puts("Usuario eliminado sesion terminada");
                        }
                        return 0;
                }

                puts("Contraseña incorrecta");
                return 0;

                break;

        case 2:
                if (strcmp(user.range, "ADMIN"))
                {
                        set_admin(user.ID);
                        puts("Ahora eres admin");
                }
                else
                {
                        set_user(user.ID);
                        puts("Ahora eres user");
                }
                break;
        }
        return 0;
}