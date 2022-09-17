#include <windows.h>

#define CLOSE_APP -1
#define CLOSE_WINDOW 0
#define LOGIN_USER 1
#define SINGUP_USER 2
#define CLOSE_CLIENT_FORM 4
#define CREATE_CLIENT_FORM 5
#define MODIFY_CLIENT_FORM 6
#define ADD_PRODUCT_VENTAS 7
#define DELETE_PRODUCT_VENTAS 8

#define NAV_INVENTARIO 1
#define NAV_CLIENTES 2
#define NAV_VENTAS 3

#define TOOLBAR_IMAGE_NEW_INVENTARIO 1
#define TOOLBAR_IMAGE_DELETE_INVENTARIO 2
#define TOOLBAR_IMAGE_MODIFY_INVENTARIO 3

#define TOOLBAR_IMAGE_NEW_CLIENTE 4
#define TOOLBAR_IMAGE_DELETE_CLIENTE 5
#define TOOLBAR_IMAGE_MODIFY_CLIENTE 6

#define TOOLBAR_IMAGE_NEW_VENTAS 7
#define TOOLBAR_IMAGE_DELETE_VENTAS 8
#define TOOLBAR_IMAGE_MODIFY_VENTAS 9

int First;
int yTabla;
int rows_clients_table;

HWND hAlto, hAncho;

// Headers
HWND hMainHeader, hMainNav, hToolBarInventario, hToolBarClientes, hToolBarVentas;

// Body
HWND hBody, hBodyInventario, hBodyClientes, hBodyVentas;

// ToolBar
HWND hNavActual, hToolBarActual;

// Ventanas
HWND hMain, hLogin;

// Edits
HWND hName, hPassword;

// Statics
HWND hStatic1, hStatic2;

// Login Buttons
HWND hButtonRed, hButtonGreen;

// Main Buttons
HWND hInventario, hClientes, hVentas;

// Inventario
HWND hNuevoProducto, hEliminarProducto, hModificarProducto;

// Clientes
HWND hNuevoCliente, hEliminarCliente, hModificarCliente;

// Ventas
HWND hNuevaVenta, hEliminarVenta, hModificarVenta;

// Forms

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
    char TdP[2];
    char date[20];
} STRUCTCLIENTESDATA;

typedef struct PRODUCTOSDATA
{
    char ID[20];
    char name[100];
    char price[20];
    char descount[20];
    char date[20];
} STRUCTPRODUCTOSDATA;

// Tabla

STRUCTCLIENTESHWND *hTableCliente;
HWND hTableCurrentRow;
STRUCTCLIENTESDATA *dataClient;
HWND hTableContainer;
HWND hScrollBar;

// Form
STRUCTCLIENTESHWND hFormClient;
STRUCTCLIENTESDATA currentDataC;

HWND hCurrentBody;

// Images
HBITMAP hImageModify, hImageAdd, hImageDelete;
HBITMAP hNuevoProductoImage, hEliminarProductoImage, hModificarProductoImage,
    hNuevoClienteImage, hModificarClienteImage, hEliminarClienteImage,
    hNuevaVentaImage, hModificarVentaImage, hEliminarVentaImage;

LRESULT CALLBACK DivWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ScrollBarProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK LoginWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ClientWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MainHeaderWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MainNavWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK ToolBarWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ToolWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK STransparentWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK ButtonsWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonGreenWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonRedWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK BodyClientWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK BodyRowCellWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CellWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HeaderCellWindowProcedure(HWND, UINT, WPARAM, LPARAM);
