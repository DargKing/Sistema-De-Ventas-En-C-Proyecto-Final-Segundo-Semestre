#include <windows.h>

#define CLOSE_WINDOW 0
#define LOGIN_USER 1
#define SINGUP_USER 2

#define NAV_INVENTARIO 1
#define NAV_CLIENTES 2
#define NAV_VENTAS 3

#define TOOLBAR_IMAGE_NEW 1
#define TOOLBAR_IMAGE_DELETE 2
#define TOOLBAR_IMAGE_MODIFY 3


int First;

HWND hAlto, hAncho;

// Headers
HWND hMainHeader, hMainNav, hToolBarInventario, hToolBarClientes, hToolBarVentas;

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


// Images 
HBITMAP hImageModify, hImageAdd, hImageDelete, hNuevoProductoImage, hEliminarProductoImage, hModificarProductoImage;

LRESULT CALLBACK MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LoginWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MainHeaderWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MainNavWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ToolBarWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ToolWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK STransparentWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonGreenWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonRedWindowProcedure(HWND, UINT, WPARAM, LPARAM);