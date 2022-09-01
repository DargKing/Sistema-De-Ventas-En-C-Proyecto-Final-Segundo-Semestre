#include <windows.h>

#define CLOSE_WINDOW 0
#define LOGIN_USER 1
#define SINGUP_USER 2

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

typedef struct CLIENTESHWND
{
    HWND container;
    HWND name;
    HWND lastname;
    HWND dni;
    HWND phone;
    HWND TdP;
};

struct CLIENTESHWND *hTableCliente;

// Images
HBITMAP hImageModify, hImageAdd, hImageDelete;
HBITMAP hNuevoProductoImage, hEliminarProductoImage, hModificarProductoImage,
    hNuevoClienteImage, hModificarClienteImage, hEliminarClienteImage,
    hNuevaVentaImage, hModificarVentaImage, hEliminarVentaImage;

LRESULT CALLBACK LoginWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MainHeaderWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MainNavWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK ToolBarWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ToolWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK STransparentWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK ButtonGreenWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonRedWindowProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK CellWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HeaderCellWindowProcedure(HWND, UINT, WPARAM, LPARAM);