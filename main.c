// Librerias
#include <windows.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

// Modulos
#include "handlers/user.h"

// Extensiones
#include "handlers/winProc.h"

char main_class[] = "Main";

void CreateLoginWindow();
void CreateMainWindow();
void CreateHeader(HWND);
void CreateNavBar();

void CreateToolBarInventario();
void CreateToolsInventario();

void CreateToolBarClientes();
void CreateToolsClientes();

void CreateToolBarVentas();
void CreateToolsVentas();

void loadImages();

BOOL CreateClasses(HINSTANCE);
BOOL InitProgram(HINSTANCE);

HINSTANCE hInst;

RECT CRect;
int WHeight, WWidth;
#define HeaderHeight 100
#define NavHeight 25
#define ToolBarHeight HeaderHeight - NavHeight

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR args, int ncmdShow)
{

        if (!CreateClasses(hInstance))
                return FALSE;

        MSG msg = {0};

        // CreateLoginWindow();
        loadImages();
        CreateMainWindow();

        while (GetMessage(&msg, NULL, NULL, NULL))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        return 0;
}

BOOL CreateClasses(HINSTANCE hInstance)
{
        WNDCLASSA wMain = {0};

        wMain.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
        wMain.hCursor = LoadCursor(NULL, IDC_ARROW);
        wMain.hInstance = hInstance;
        wMain.lpszClassName = main_class;
        wMain.lpfnWndProc = MainWindowProcedure;

        if (!RegisterClassA(&wMain))
                return FALSE;

        WNDCLASSA wLogin = {0};

        wLogin.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
        wLogin.hCursor = LoadCursor(NULL, IDC_ARROW);
        wLogin.hInstance = hInstance;
        wLogin.lpszClassName = "LOGIN";
        wLogin.lpfnWndProc = LoginWindowProcedure;
        wLogin.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wLogin))
                return FALSE;

        WNDCLASSA wS_Transparent = {0};

        wS_Transparent.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wS_Transparent.hCursor = LoadCursor(NULL, IDC_ARROW);
        wS_Transparent.hInstance = hInstance;
        wS_Transparent.lpszClassName = "S_TRANSPARENT";
        wS_Transparent.lpfnWndProc = STransparentWindowProcedure;
        wS_Transparent.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wS_Transparent))
                return FALSE;

        WNDCLASSA wButtonGreen = {0};

        wButtonGreen.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wButtonGreen.hCursor = LoadCursor(NULL, IDC_HAND);
        wButtonGreen.hInstance = hInstance;
        wButtonGreen.lpszClassName = "BUTTON_GREEN";
        wButtonGreen.lpfnWndProc = ButtonGreenWindowProcedure;
        wButtonGreen.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wButtonGreen))
                return FALSE;

        WNDCLASSA wButtonRed = {0};

        wButtonRed.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wButtonRed.hCursor = LoadCursor(NULL, IDC_HAND);
        wButtonRed.hInstance = hInstance;
        wButtonRed.lpszClassName = "BUTTON_RED";
        wButtonRed.lpfnWndProc = ButtonRedWindowProcedure;
        wButtonRed.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wButtonRed))
                return FALSE;

        WNDCLASSA wMainHeader = {0};

        wMainHeader.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(235, 235, 235));
        wMainHeader.hCursor = LoadCursor(NULL, IDC_ARROW);
        wMainHeader.hInstance = hInstance;
        wMainHeader.lpszClassName = "MAIN_HEADER";
        wMainHeader.lpfnWndProc = MainHeaderWindowProcedure;
        wMainHeader.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wMainHeader))
                return FALSE;

        WNDCLASSA wToolBar = {0};

        wToolBar.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(235, 235, 235));
        wToolBar.hCursor = LoadCursor(NULL, IDC_ARROW);
        wToolBar.hInstance = hInstance;
        wToolBar.lpszClassName = "TOOL_BAR";
        wToolBar.lpfnWndProc = ToolBarWindowProcedure;
        wToolBar.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wToolBar))
                return FALSE;

        WNDCLASSA wMainNav = {0};

        wMainNav.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(235, 235, 235));
        wMainNav.hCursor = LoadCursor(NULL, IDC_ARROW);
        wMainNav.hInstance = hInstance;
        wMainNav.lpszClassName = "MAIN_NAV";
        wMainNav.lpfnWndProc = MainNavWindowProcedure;
        wMainNav.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wMainNav))
                return FALSE;

        WNDCLASSA wTools = {0};

        wTools.hCursor = LoadCursor(NULL, IDC_ARROW);
        wTools.hInstance = hInstance;
        wTools.lpszClassName = "TOOL";
        wTools.lpfnWndProc = ToolWindowProcedure;
        wTools.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wTools))
                return FALSE;

        return TRUE;
}

void CreateLoginWindow()
{
        int CLoginWidth = 350;
        int CLoginHeight = 200;
        WHeight = GetSystemMetrics(SM_CYSCREEN);
        WWidth = GetSystemMetrics(SM_CXSCREEN);
        int WPositionX = (WWidth / 2) - (CLoginWidth / 2);
        int WPositionY = (WHeight / 2) - (CLoginHeight / 2);

        hLogin = CreateWindowA("LOGIN", NULL, WS_POPUP | WS_VISIBLE | WS_BORDER, WPositionX, WPositionY, CLoginWidth, CLoginHeight, NULL, NULL, NULL, NULL);

        hStatic1 = CreateWindowA("S_TRANSPARENT", "Name:", WS_CHILD | WS_VISIBLE | SS_WHITEFRAME, 50, 30, 250, 20, hLogin, NULL, NULL, NULL);
        hName = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 50, 50, 250, 20, hLogin, NULL, NULL, NULL);

        hStatic2 = CreateWindowA("S_TRANSPARENT", "Password:", WS_CHILD | WS_VISIBLE, 50, 80, 250, 20, hLogin, NULL, NULL, NULL);
        hPassword = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 50, 100, 250, 20, hLogin, NULL, NULL, NULL);

        hButtonGreen = CreateWindowA("BUTTON_GREEN", "Login", WS_CHILD | WS_VISIBLE, 50, 130, 120, 40, hLogin, (HMENU)LOGIN_USER, NULL, NULL);

        hButtonRed = CreateWindowA("BUTTON_RED", "Close", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_VCENTER, 180, 130, 120, 40, hLogin, (HMENU)CLOSE_WINDOW, NULL, NULL);
}

void CreateMainWindow()
{
        WHeight = GetSystemMetrics(SM_CYSCREEN);
        WWidth = GetSystemMetrics(SM_CXSCREEN);

        int CMainHeight = WHeight - (WHeight * 0.10);
        int CMainWidth = WWidth - (WWidth * 0.10);

        int WPositionX = (WWidth / 2) - (CMainWidth / 2);
        int WPositionY = (WHeight / 2) - (CMainHeight / 2);

        hMain = CreateWindowA(main_class, "Sistema De Ventas", WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE, WPositionX, WPositionY, CMainWidth, CMainHeight,
                              NULL, NULL, NULL, NULL);
        CreateHeader(hMain);
}

void loadImages()
{
        hImageModify = (HBITMAP)LoadImageA(NULL, "C:\\Users\\yorman\\Documents\\trabajos yorman\\semestre 2\\tecnicas de programacion\\C\\PROYECTOFINAL\\img\\modificar.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
        hImageAdd = (HBITMAP)LoadImageA(NULL, "C:\\Users\\yorman\\Documents\\trabajos yorman\\semestre 2\\tecnicas de programacion\\C\\PROYECTOFINAL\\img\\modificar.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
        hImageDelete = (HBITMAP)LoadImageA(NULL, "C:\\Users\\yorman\\Documents\\trabajos yorman\\semestre 2\\tecnicas de programacion\\C\\PROYECTOFINAL\\img\\modificar.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}

void CreateHeader(HWND hWnd)
{
        RECT CRect;
        GetClientRect(hWnd, &CRect);
        hMainHeader = CreateWindowA("MAIN_HEADER", NULL, WS_VISIBLE | WS_CHILD, 0, 0, CRect.right, HeaderHeight, hWnd, NULL, NULL, NULL);
        CreateNavBar();
}

void CreateNavBar()
{
        GetClientRect(hMain, &CRect);
        hMainNav = CreateWindowA("MAIN_NAV", NULL, WS_VISIBLE | WS_CHILD, 0, 0, CRect.right, NavHeight, hMainHeader, NULL, NULL, NULL);

        First = 0;
        hInventario = CreateWindowA("TOOL_BAR", "Inventario", WS_VISIBLE | WS_CHILD, 20, 0, 100, NavHeight, hMainNav, NAV_INVENTARIO, NULL, NULL);
        First = 1;
        hNavActual = hInventario;

        hClientes = CreateWindowA("TOOL_BAR", "Clientes", WS_VISIBLE | WS_CHILD, 120, 0, 100, NavHeight, hMainNav, NAV_CLIENTES, NULL, NULL);
        hVentas = CreateWindowA("TOOL_BAR", "Ventas", WS_VISIBLE | WS_CHILD, 220, 0, 100, NavHeight, hMainNav, NAV_VENTAS, NULL, NULL);
        CreateToolBarInventario();
        // CreateToolBarClientes();
        // CreateToolBarVentas();
        hToolBarActual = hToolBarInventario;
}

// Inventario

void CreateToolBarInventario()
{
        hToolBarInventario = CreateWindowA("STATIC", NULL, WS_VISIBLE | WS_CHILD, 0, 25, CRect.right, ToolBarHeight, hMainHeader, NULL, NULL, NULL);
        CreateToolsInventario();
}

void CreateToolsInventario()
{
        hNuevoProducto = CreateWindowA("TOOL", "Nuevo Producto", WS_VISIBLE | WS_CHILD, 20, 0, 100, 75, hToolBarInventario, TOOLBAR_IMAGE_NEW, NULL, NULL);
        hModificarProducto = CreateWindowA("TOOL", "Modificar Producto", WS_VISIBLE | WS_CHILD, 120, 0, 100, 75, hToolBarInventario, TOOLBAR_IMAGE_MODIFY, NULL, NULL);
        hEliminarProducto = CreateWindowA("TOOL", "Eliminar Producto", WS_VISIBLE | WS_CHILD, 220, 0, 100, 75, hToolBarInventario, TOOLBAR_IMAGE_DELETE, NULL, NULL);
}

// Clientes

void CreateToolBarClientes()
{
        hToolBarClientes = CreateWindowA("STATIC", NULL, WS_VISIBLE | WS_CHILD, 0, 25, CRect.right, ToolBarHeight, hMainHeader, NULL, NULL, NULL);
        ShowWindow(hToolBarClientes, SW_HIDE);
        CreateToolsClientes();
}

void CreateToolsClientes()
{
        hNuevoCliente = CreateWindowA("TOOL", "Nuevo Cliente", WS_VISIBLE | WS_CHILD, 20, 0, 100, 75, hToolBarClientes, NULL, NULL, NULL);
        hModificarCliente = CreateWindowA("TOOL", "Modificar Cliente", WS_VISIBLE | WS_CHILD, 120, 0, 100, 75, hToolBarClientes, NULL, NULL, NULL);
        hEliminarCliente = CreateWindowA("TOOL", "Eliminar Cliente", WS_VISIBLE | WS_CHILD, 220, 0, 100, 75, hToolBarClientes, NULL, NULL, NULL);
}

void CreateToolBarVentas()
{
        hToolBarVentas = CreateWindowA("STATIC", NULL, WS_VISIBLE | WS_CHILD, 0, 25, CRect.right, ToolBarHeight, hMainHeader, NULL, NULL, NULL);
        ShowWindow(hToolBarVentas, SW_HIDE);
        CreateToolsVentas();
}

void CreateToolsVentas()
{
        hNuevaVenta = CreateWindowA("TOOL", "Nueva Venta", WS_VISIBLE | WS_CHILD, 20, 0, 80, 75, hToolBarVentas, NULL, NULL, NULL);
        hEliminarVenta = CreateWindowA("TOOL", "Modificar Venta", WS_VISIBLE | WS_CHILD, 100, 0, 90, 75, hToolBarVentas, NULL, NULL, NULL);
        hModificarVenta = CreateWindowA("TOOL", "Eliminar Venta", WS_VISIBLE | WS_CHILD, 190, 0, 90, 75, hToolBarVentas, NULL, NULL, NULL);
}