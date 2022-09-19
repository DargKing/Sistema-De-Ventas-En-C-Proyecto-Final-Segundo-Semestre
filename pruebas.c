#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "handlers/tabdb.h"
#include "handlers/clientes.h"
#include "handlers/caracteres.h"

typedef struct CLIENTESDATA
{
        char ID[20];
        char name[100];
        char lastname[100];
        char dni[20];
        char phone[20];
        char TdP[20];
        char date[20];
} STRUCTCLIENTESDATA;

int main()
{
        STRUCTCLIENTESDATA data;
        
        get_ID_clients(0, data.ID);

        int row = search_clients(data.ID);

        printf("%d\n", row);
}