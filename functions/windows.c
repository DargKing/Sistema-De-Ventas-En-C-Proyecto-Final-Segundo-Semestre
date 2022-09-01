#include <windows.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <windowsx.h>
#include "../handlers/windows.h"
#include "../handlers/winProc.h"
#include "../handlers/clientes.h"

typedef struct
{
        char name[100];
        char lastname[100];
        char dni[20];
        char phone[20];
        char TdP[20];
} CLIENTESDATA;

int yTabla = 20;

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

        wMainHeader.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
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

        WNDCLASSA wToolBarContainer = {0};

        wToolBarContainer.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(235, 235, 235));
        wToolBarContainer.hCursor = LoadCursor(NULL, IDC_ARROW);
        wToolBarContainer.hInstance = hInstance;
        wToolBarContainer.lpszClassName = "TOOLBAR_CONTAINER";
        wToolBarContainer.lpfnWndProc = MainWindowProcedure;
        wToolBarContainer.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wToolBarContainer))
                return FALSE;

        WNDCLASSA wBody = {0};

        wBody.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
        wBody.hCursor = LoadCursor(NULL, IDC_ARROW);
        wBody.hInstance = hInstance;
        wBody.lpszClassName = "BODY";
        wBody.lpfnWndProc = MainWindowProcedure;

        if (!RegisterClassA(&wBody))
                return FALSE;

        WNDCLASSA wCell = {0};

        wCell.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
        wCell.hCursor = LoadCursor(NULL, IDC_ARROW);
        wCell.hInstance = hInstance;
        wCell.lpszClassName = "CELL";
        wCell.lpfnWndProc = CellWindowProcedure;

        if (!RegisterClassA(&wCell))
                return FALSE;

        WNDCLASSA wHeaderCell = {0};

        wHeaderCell.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
        wHeaderCell.hCursor = LoadCursor(NULL, IDC_ARROW);
        wHeaderCell.hInstance = hInstance;
        wHeaderCell.lpszClassName = "HEADER_CELL";
        wHeaderCell.lpfnWndProc = HeaderCellWindowProcedure;

        if (!RegisterClassA(&wHeaderCell))
                return FALSE;

        WNDCLASSA wBodyRowCell = {0};

        wBodyRowCell.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
        wBodyRowCell.hCursor = LoadCursor(NULL, IDC_ARROW);
        wBodyRowCell.hInstance = hInstance;
        wBodyRowCell.lpszClassName = "BODY_ROW_CELL";
        wBodyRowCell.lpfnWndProc = HeaderCellWindowProcedure;

        if (!RegisterClassA(&wBodyRowCell))
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

        hTableCliente = (struct CLIENTESHWND *)malloc(sizeof(struct CLIENTESHWND));
        CreateHeader();
}

void CreateHeaderTableClient()
{
        RECT rect;
        GetClientRect(hBodyInventario, &rect);
        float width = rect.right / 5 - 10;
        CreateWindowA("HEADER_CELL", "Nombre", WS_VISIBLE | WS_CHILD, 25, 0, width, 20, hBodyInventario, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Apellido", WS_VISIBLE | WS_CHILD, 25 - 4 + width, 0, width, 20, hBodyInventario, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "DNI", WS_VISIBLE | WS_CHILD, 25 - 6 + (width * 2), 0, width, 20, hBodyInventario, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Telefono", WS_VISIBLE | WS_CHILD, 25 - 8 + (width * 3), 0, width, 20, hBodyInventario, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Naturaleza", WS_VISIBLE | WS_CHILD, 25 - 10 + (width * 4), 0, width, 20, hBodyInventario, NULL, NULL, NULL);
}

void CreateRowTableClient(CLIENTESDATA data, int i)
{
        RECT rect;
        GetClientRect(hBodyInventario, &rect);
        hTableCliente[i].container = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE, 25, yTabla, rect.right - 63, 20, hBodyInventario, i, NULL, NULL);
        float width = rect.right / 5 - 10;
        CreateWindowA("CELL", data.name, WS_VISIBLE | WS_CHILD, 0, 0, width, 20, hTableCliente[i].container, i, NULL, NULL);
        CreateWindowA("CELL", data.lastname, WS_VISIBLE | WS_CHILD, width - 3, 0, width, 20, hTableCliente[i].container, i, NULL, NULL);
        CreateWindowA("CELL", data.dni, WS_VISIBLE | WS_CHILD, (width * 2) - 6, 0, width, 20, hTableCliente[i].container, i, NULL, NULL);
        CreateWindowA("CELL", data.phone, WS_VISIBLE | WS_CHILD, (width * 3) - 9, 0, width, 20, hTableCliente[i].container, i, NULL, NULL);
        CreateWindowA("CELL", data.TdP, WS_VISIBLE | WS_CHILD, (width * 4) - 12, 0, width, 20, hTableCliente[i].container, i, NULL, NULL);
        yTabla += 20;
}

void CreateTableClient()
{
        int jumplines = get_jumplines_clients_file();
        CLIENTESDATA data[jumplines];

        hTableCliente = (struct CLIENTESHWND *)realloc(hTableCliente, sizeof(struct CLIENTESHWND) * jumplines);

        for (int i = 0; i < jumplines; i++)
        {
                get_name_clients(i, data[i].name);
                get_lastname_clients(i, data[i].lastname);
                get_dni_clients(i, data[i].dni);
                get_phone_clients(i, data[i].phone);
                get_TdP_clients(i, data[i].TdP);
        }
        int y = 0;
        for (int i = 0; i < jumplines; i++)
        {
                CreateRowTableClient(data[i], i);
        }
}

void CreateBodyCliente()
{
        RECT CRect;
        GetClientRect(hMain, &CRect);
        hBodyInventario = CreateWindowA("BODY", NULL, WS_VISIBLE | WS_CHILD, 0, 100, CRect.right, CRect.bottom - HeaderHeight, hMain, NULL, NULL, NULL);
        CreateHeaderTableClient();
        CreateTableClient();
}

void loadImagesAdd()
{
        hImageAdd = (HBITMAP)LoadImageA(NULL, "C:\\Users\\yorman\\Documents\\trabajos yorman\\semestre 2\\tecnicas de programacion\\C\\PROYECTOFINAL\\img\\add.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}

void loadImagesModify()
{
        hImageModify = (HBITMAP)LoadImageA(NULL, "C:\\Users\\yorman\\Documents\\trabajos yorman\\semestre 2\\tecnicas de programacion\\C\\PROYECTOFINAL\\img\\modificar.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}

void loadImagesDelete()
{
        hImageDelete = (HBITMAP)LoadImageA(NULL, "C:\\Users\\yorman\\Documents\\trabajos yorman\\semestre 2\\tecnicas de programacion\\C\\PROYECTOFINAL\\img\\delete.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}

void CreateHeader()
{
        RECT CRect;
        GetClientRect(hMain, &CRect);
        hMainHeader = CreateWindowA("MAIN_HEADER", NULL, WS_VISIBLE | WS_CHILD, 0, 0, CRect.right, HeaderHeight, hMain, NULL, NULL, NULL);
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
        CreateToolBarClientes();

        CreateBodyCliente();

        CreateToolBarVentas();
        hToolBarActual = hToolBarInventario;
}

// Body

void CreateBody()
{
        RECT CRect;
        GetClientRect(hMain, &CRect);
        hBody = CreateWindowA("BODY", NULL, WS_VISIBLE | WS_CHILD, 0, 100, CRect.right, CRect.bottom - HeaderHeight, hMain, NULL, NULL, NULL);
}

// Inventario

void CreateToolBarInventario()
{
        hToolBarInventario = CreateWindowA("TOOLBAR_CONTAINER", NULL, WS_VISIBLE | WS_CHILD, 0, 25, CRect.right, ToolBarHeight, hMainHeader, NULL, NULL, NULL);

        CreateToolsInventario();
}

void CreateToolsInventario()
{
        hNuevoProducto = CreateWindowA("TOOL", "Nuevo Producto", WS_VISIBLE | WS_CHILD, 20, 0, 100, 75, hToolBarInventario, TOOLBAR_IMAGE_NEW_INVENTARIO, NULL, NULL);
        hModificarProducto = CreateWindowA("TOOL", "Modificar Producto", WS_VISIBLE | WS_CHILD, 120, 0, 100, 75, hToolBarInventario, TOOLBAR_IMAGE_MODIFY_INVENTARIO, NULL, NULL);
        hEliminarProducto = CreateWindowA("TOOL", "Eliminar Producto", WS_VISIBLE | WS_CHILD, 220, 0, 100, 75, hToolBarInventario, TOOLBAR_IMAGE_DELETE_INVENTARIO, NULL, NULL);
}

// Clientes

void CreateToolBarClientes()
{
        hToolBarClientes = CreateWindowA("TOOLBAR_CONTAINER", NULL, WS_VISIBLE | WS_CHILD, 0, 25, CRect.right, ToolBarHeight, hMainHeader, NULL, NULL, NULL);
        ShowWindow(hToolBarClientes, SW_HIDE);
        CreateToolsClientes();
}

void CreateToolsClientes()
{
        hNuevoCliente = CreateWindowA("TOOL", "Nuevo Cliente", WS_VISIBLE | WS_CHILD, 20, 0, 100, 75, hToolBarClientes, TOOLBAR_IMAGE_NEW_CLIENTE, NULL, NULL);
        hModificarCliente = CreateWindowA("TOOL", "Modificar Cliente", WS_VISIBLE | WS_CHILD, 120, 0, 100, 75, hToolBarClientes, TOOLBAR_IMAGE_MODIFY_CLIENTE, NULL, NULL);
        hEliminarCliente = CreateWindowA("TOOL", "Eliminar Cliente", WS_VISIBLE | WS_CHILD, 220, 0, 100, 75, hToolBarClientes, TOOLBAR_IMAGE_DELETE_CLIENTE, NULL, NULL);
}

void CreateToolBarVentas()
{
        hToolBarVentas = CreateWindowA("TOOLBAR_CONTAINER", NULL, WS_VISIBLE | WS_CHILD, 0, 25, CRect.right, ToolBarHeight, hMainHeader, NULL, NULL, NULL);
        ShowWindow(hToolBarVentas, SW_HIDE);
        CreateToolsVentas();
}

void CreateToolsVentas()
{
        hNuevaVenta = CreateWindowA("TOOL", "Nueva Venta", WS_VISIBLE | WS_CHILD, 20, 0, 80, 75, hToolBarVentas, TOOLBAR_IMAGE_NEW_VENTAS, NULL, NULL);
        hEliminarVenta = CreateWindowA("TOOL", "Modificar Venta", WS_VISIBLE | WS_CHILD, 100, 0, 90, 75, hToolBarVentas, TOOLBAR_IMAGE_MODIFY_VENTAS, NULL, NULL);
        hModificarVenta = CreateWindowA("TOOL", "Eliminar Venta", WS_VISIBLE | WS_CHILD, 190, 0, 90, 75, hToolBarVentas, TOOLBAR_IMAGE_DELETE_VENTAS, NULL, NULL);
}
