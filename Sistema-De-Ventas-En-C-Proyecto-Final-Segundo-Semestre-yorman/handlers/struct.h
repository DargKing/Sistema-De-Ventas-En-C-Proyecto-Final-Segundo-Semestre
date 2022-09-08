#include <windows.h>

void delete_table_row_client(int i);
void SortDateStructClient(STRUCTCLIENTESDATA *data, int type, int len);

typedef struct CLIENTESHWND
{
    HWND container;
    HWND name;
    HWND lastname;
    HWND dni;
    HWND phone;
    HWND TdP;
} STRUCTCLIENTESHWND;

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

typedef struct INVENTARIODATA
{
	int id[256];
	char name[26];
	char category[20];
	float price_base;
	float discount;
	float price_final;
	int stock;
} STRUCTINVENTARIODATA;

typedef struct FACTURASDATA
{
	int code[256];
	char name[34];
	char city[34];
	char rif[12];
	char date[12];
	float price;
} STRUCTFACTURASDATA;