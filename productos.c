#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <conio.h>
#include "caracteres.h"

struct producto
{
        char name[50];
        char ID[4];
        int price;
};

struct producto product_init(char *ID)
{
        struct producto product;
        const char *filename = "productos.txt";

        FILE *input_file = fopen(filename, "r");

        char *contents = NULL;
        size_t len = 0;

        while (getline(&contents, &len, input_file) != -1)
        {
                char temp_name[50];
                char temp_ID[4];
                int temp_price;
                int lastTab = 0;
                int x = 0;
                for (int i = 0; i < lenghtStr(contents) + 1; i++)
                {
                        if (contents[i] == '\t' || contents[i] == '\n' || contents[i] == '\0')
                        {
                                if (x == 0)
                                {
                                        char *temp = subString(contents, lastTab, i);
                                        strcpy(temp_name, temp);
                                        free(temp);
                                        temp = NULL;
                                }
                                if (x == 1)
                                {
                                        char *temp = subString(contents, lastTab, i);
                                        strcpy(temp_ID, temp);
                                        free(temp);
                                        temp = NULL;
                                }
                                if (x == 2)
                                {
                                        char *temp = subString(contents, lastTab, i);
                                        temp_price = atoi(temp);
                                        free(temp);
                                        temp = NULL;
                                }

                                lastTab = i + 1;
                                x++;
                        }
                }
                if (!strcmp(ID, temp_ID))
                {
                        strcpy(product.name, temp_name);
                        strcpy(product.ID, temp_ID);
                        product.price = temp_price;
                        return product;
                }
        }

        fclose(input_file);
        free(contents);
        return product;
}

int main()
{
        struct producto agua_emb = product_init("0001");
        printf("%s\n%s\n%d", agua_emb.name, agua_emb.ID, agua_emb.price);
        return 0;
}