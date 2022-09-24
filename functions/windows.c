#include <windows.h>
#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windowsx.h>
#include "../handlers/windows.h"
#include "../handlers/winProc.h"
#include "../handlers/productos.h"
#include "../handlers/clientes.h"
#include "../handlers/ventas.h"
#include "../handlers/struct.h"
#include "../handlers/colors.h"

yTabla = 0;
FirstMalloc = 0;
currentSort = DEFAULT_SORT;
Window_product_is_open = 0;
rows_currentProduct_table = 0;

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

        WNDCLASSA wClientWindow = {0};

        wClientWindow.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
        wClientWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
        wClientWindow.hInstance = hInstance;
        wClientWindow.lpszClassName = "CLIENT_WINDOW";
        wClientWindow.lpfnWndProc = ClientWindowProcedure;
        wClientWindow.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wClientWindow))
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

        wS_Transparent.hCursor = LoadCursor(NULL, IDC_ARROW);
        wS_Transparent.hInstance = hInstance;
        wS_Transparent.lpszClassName = "S_TRANSPARENT";
        wS_Transparent.lpfnWndProc = STransparentWindowProcedure;
        wS_Transparent.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wS_Transparent))
                return FALSE;

        WNDCLASSA wButtons = {0};

        wButtons.hCursor = LoadCursor(NULL, IDC_HAND);
        wButtons.hInstance = hInstance;
        wButtons.lpszClassName = "BUTTON_P";
        wButtons.lpfnWndProc = ButtonsWindowProcedure;
        wButtons.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wButtons))
                return FALSE;

        WNDCLASSA wMainHeader = {0};

        wMainHeader.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
        wMainHeader.hCursor = LoadCursor(NULL, IDC_ARROW);
        wMainHeader.hInstance = hInstance;
        wMainHeader.lpszClassName = "HEADER";
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
        wBody.lpfnWndProc = BodyClientWindowProcedure;

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
        wBodyRowCell.lpfnWndProc = BodyRowCellWindowProcedure;

        if (!RegisterClassA(&wBodyRowCell))
                return FALSE;

        wBodyRowCell.lpszClassName = "BODY_ROW_CELL_PRODUCT";
        wBodyRowCell.lpfnWndProc = BodyRowCellProductWindowProcedure;

        if (!RegisterClassA(&wBodyRowCell))
                return FALSE;

        wBodyRowCell.lpszClassName = "BODY_ROW_CELL_CURRENTPRODUCT";
        wBodyRowCell.lpfnWndProc = BodyRowCellCurrentProductWindowProcedure;

        if (!RegisterClassA(&wBodyRowCell))
                return FALSE;

        wBodyRowCell.lpszClassName = "BODY_ROW_CELL_HISTORIALVENTAS";
        wBodyRowCell.lpfnWndProc = BodyRowCellHistorialVentasWindowProcedure;

        if (!RegisterClassA(&wBodyRowCell))
                return FALSE;

        WNDCLASSA wDiv = {0};

        wDiv.hCursor = LoadCursor(NULL, IDC_ARROW);
        wDiv.hInstance = hInstance;
        wDiv.lpszClassName = "DIV";
        wDiv.lpfnWndProc = DivWindowProcedure;

        if (!RegisterClassA(&wDiv))
                return FALSE;

        WNDCLASSA wSeparator = {0};

        wSeparator.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
        wSeparator.hCursor = LoadCursor(NULL, IDC_ARROW);
        wSeparator.hInstance = hInstance;
        wSeparator.lpszClassName = "SEPARATOR";
        wSeparator.lpfnWndProc = WinProc;

        if (!RegisterClassA(&wSeparator))
                return FALSE;

        WNDCLASSA wContainerVacio = {0};

        wContainerVacio.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(235, 235, 235));
        wContainerVacio.hCursor = LoadCursor(NULL, IDC_ARROW);
        wContainerVacio.hInstance = hInstance;
        wContainerVacio.lpszClassName = "CONTAINER_VACIO";
        wContainerVacio.lpfnWndProc = WinProc;

        if (!RegisterClassA(&wContainerVacio))
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

        hButtonGreen = CreateWindowA("BUTTON_P", "Login", WS_CHILD | WS_VISIBLE, 50, 130, 120, 40, hLogin, LOGIN_USER, NULL, NULL);

        hButtonRed = CreateWindowA("BUTTON_P", "Close", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_VCENTER, 180, 130, 120, 40, hLogin, CLOSE_WINDOW, NULL, NULL);
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

        UpdateWindow(hMain);

        dataClient = (STRUCTCLIENTESDATA *)malloc(sizeof(STRUCTCLIENTESDATA));
        hTableCliente = (STRUCTCLIENTESHWND *)malloc(sizeof(STRUCTCLIENTESHWND));

        h_rows_product_table = (HWND *)malloc(sizeof(HWND));
        dataProductos = (STRUCTPRODUCTOSDATA *)malloc(sizeof(STRUCTPRODUCTOSDATA));

        h_rows_currentProduct_table = (HWND *)malloc(sizeof(HWND));
        CurrentProducts = (STRUCTPRODUCTOSDATA *)malloc(sizeof(STRUCTPRODUCTOSDATA));

        dataVentas = (STRUCTVENTASDATA *)malloc(sizeof(STRUCTVENTASDATA));
        h_rows_ventas_table = (HWND *)malloc(sizeof(HWND));

        CreateHeader();
}

void CreateHeaderTableClient()
{
        RECT rect;
        GetClientRect(hBodyClientes, &rect);
        int width = cxColumnTable;

        HWND temp = CreateWindowA("BODY_ROW_CELL", NULL, WS_CHILD | WS_VISIBLE, 0, 0, cxColumnTable * nColumnsTable, ROW_TABLE_HEIGHT, hBodyClientes, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Nombre", WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Apellido", WS_VISIBLE | WS_CHILD, width, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "DNI", WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Telefono", WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Naturaleza", WS_VISIBLE | WS_CHILD, (width * 4), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Fecha", WS_VISIBLE | WS_CHILD, (width * 5), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

void CreateRowTableClient(STRUCTCLIENTESDATA data, int i)
{
        RECT rect;
        GetClientRect(hBodyClientes, &rect);
        int width = cxColumnTable * nColumnsTable;
        hTableCliente[i].container = CreateWindowA("BODY_ROW_CELL", NULL, WS_CHILD | WS_VISIBLE, 0, yTabla, width, ROW_TABLE_HEIGHT, hTableContainer, i, NULL, NULL);
        yTabla += 20;
}

void CreateTableClient()
{
        RECT rectBodyClientes;
        RECT rectMainWindow;

        GetClientRect(hBodyClientes, &rectBodyClientes);
        GetClientRect(hMain, &rectMainWindow);

        DWORD sTableContainer;

        nColumnsTable = 6;
        if (rows_clients_table > (rectMainWindow.bottom - HeaderHeight) / ROW_TABLE_HEIGHT)
                sTableContainer = WS_VISIBLE | WS_CHILD | WS_VSCROLL;
        else
                sTableContainer = WS_VISIBLE | WS_CHILD;

        hTableContainer = CreateWindowExA(0, "DIV", NULL, sTableContainer, 0, 20, rectBodyClientes.right, rectBodyClientes.bottom - ROW_TABLE_HEIGHT, hBodyClientes, LIST_CLIENTS, NULL, NULL);

        int y = 0;
        for (int i = 0; i < rows_clients_table; i++)
        {
                CreateRowTableClient(dataClient[i], i);
        }
}

void CreateBodyClienteMainWindow()
{
        yTabla = 0;
        RECT CRect;
        GetClientRect(hMain, &CRect);
        hBodyClientes = CreateWindowA("BODY", NULL, WS_VISIBLE | WS_CHILD, 0, 100, CRect.right, CRect.bottom - HeaderHeight, hMain, NULL, NULL, NULL);
        hTableCurrentRow = NULL;
        hCurrentBody = hBodyClientes;

        rows_clients_table = get_jumplines_clients_file();
        int lines = get_lines_clients_file();

        free(dataClient);
        free(hTableCliente);

        dataClient = NULL;
        hTableCliente = NULL;

        dataClient = (STRUCTCLIENTESDATA *)malloc(sizeof(STRUCTCLIENTESDATA) * (rows_clients_table + 1));
        hTableCliente = (STRUCTCLIENTESHWND *)malloc(sizeof(STRUCTCLIENTESHWND) * (rows_clients_table + 1));

        int i = 0;
        int x = 0;

        char text[300];

        while (i < lines)
        {
                if (!isBlank(i))
                {
                        get_ID_clients(i, dataClient[x].ID);
                        get_date_clients(i, dataClient[x].date);
                        get_name_clients(i, dataClient[x].name);
                        get_lastname_clients(i, dataClient[x].lastname);
                        get_dni_clients(i, dataClient[x].dni);
                        get_phone_clients(i, dataClient[x].phone);
                        get_TdP_clients(i, dataClient[x].TdP);
                        x++;
                }
                i++;
        }

        switch (currentSort)
        {
        case DATE_SORT_DES:
                SortDateStructClient(dataClient, 0, x);
                break;
        case DATE_SORT_ASD:
                SortDateStructClient(dataClient, 1, x);
                break;
        }

        CreateTableClient();
        CreateHeaderTableClient();
}

void loadImagesAdd()
{
        hImageAdd = (HBITMAP)LoadImageA(NULL, "img\\add.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}

void loadImagesModify()
{
        hImageModify = (HBITMAP)LoadImageA(NULL, "img\\modificar.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}

void loadImagesDelete()
{
        hImageDelete = (HBITMAP)LoadImageA(NULL, "img\\delete.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}

void loadImagesHistorial()
{
        hImageHistorial = (HBITMAP)LoadImageA(NULL, "img\\lista.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}

void loadImagesView()
{
        hImageVer = (HBITMAP)LoadImageA(NULL, "img\\ver.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}

void CreateHeader()
{
        RECT CRect;
        GetClientRect(hMain, &CRect);
        hMainHeader = CreateWindowA("HEADER", NULL, WS_VISIBLE | WS_CHILD, 0, 0, CRect.right, HeaderHeight, hMain, NULL, NULL, NULL);
        CreateNavBar();
}

void CreateNavBar()
{
        GetClientRect(hMain, &CRect);
        hMainNav = CreateWindowA("MAIN_NAV", NULL, WS_VISIBLE | WS_CHILD, 0, 0, CRect.right, NavHeight, hMainHeader, NULL, NULL, NULL);

        First = 0;
        hVentas = CreateWindowA("TOOL_BAR", "Ventas", WS_VISIBLE | WS_CHILD, 20, 0, 100, NavHeight, hMainNav, NAV_VENTAS, NULL, NULL);
        First = 1;
        hInventario = CreateWindowA("TOOL_BAR", "Inventario", WS_VISIBLE | WS_CHILD, 120, 0, 100, NavHeight, hMainNav, NAV_INVENTARIO, NULL, NULL);
        hClientes = CreateWindowA("TOOL_BAR", "Clientes", WS_VISIBLE | WS_CHILD, 220, 0, 100, NavHeight, hMainNav, NAV_CLIENTES, NULL, NULL);
        hNavActual = hVentas;

        CreateToolBarVentas();
        CreateToolBarInventario();
        CreateToolBarClientes();

        hToolBarActual = hToolBarVentas;

        CreateBodyVentasMainWindow(TRUE);
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
        ShowWindow(hToolBarInventario, SW_HIDE);
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
        CreateToolsVentas();
}

void CreateToolsVentas()
{
        hNuevaVenta = CreateWindowA("TOOL", "Nueva Venta", WS_VISIBLE | WS_CHILD, 20, 0, 80, 75, hToolBarVentas, TOOLBAR_IMAGE_NEW_VENTAS, NULL, NULL);
        CreateWindowA("SEPARATOR", NULL, WS_CHILD | WS_VISIBLE, 110, 10, 1, ToolBarHeight - 20, hToolBarVentas, TOOLBAR_IMAGE_HISTORIAL_VENTAS, NULL, NULL);
        hToolHistorialVenta = CreateWindowA("TOOL", "Historial de Ventas", WS_VISIBLE | WS_CHILD, 120, 0, 90, 75, hToolBarVentas, TOOLBAR_IMAGE_HISTORIAL_VENTAS, NULL, NULL);
        hToolVerVenta = CreateWindowA("TOOL", "Ver Venta", WS_VISIBLE | WS_CHILD, 210, 0, 90, 75, hToolBarVentas, TOOLBAR_IMAGE_VER_VENTAS, NULL, NULL);
        hModificarVenta = CreateWindowA("TOOL", "Modificar Venta", WS_VISIBLE | WS_CHILD, 300, 0, 90, 75, hToolBarVentas, TOOLBAR_IMAGE_MODIFY_VENTAS, NULL, NULL);
        hEliminarVenta = CreateWindowA("TOOL", "Eliminar Venta", WS_VISIBLE | WS_CHILD, 390, 0, 90, 75, hToolBarVentas, TOOLBAR_IMAGE_DELETE_VENTAS, NULL, NULL);
}

void CreateTableProductosVentas(STRUCTPRODUCTOSDATA *data, int x)
{
}

void CreateFormClient(BOOL newClient, UINT client, BOOL ventas)
{
        if (newClient == TRUE && ventas != TRUE)
        {
                int CContainerWidth = 500;
                int CContainerHeight = 250;

                WINDOWPOS containerPos;
                WINDOWPOS namePos;
                WINDOWPOS lastnamePos;
                WINDOWPOS dniPos;
                WINDOWPOS phonePos;
                WINDOWPOS tdpPos;
                WINDOWPOS buttonRegisterPos;
                WINDOWPOS buttonClosePos;

                SetWindowPosition(&containerPos, WWidth / 2 - (CContainerWidth / 2), WHeight / 2 - (CContainerHeight / 2), CContainerWidth, CContainerHeight);

                SetWindowPosition(&namePos, CContainerWidth * 0.08, 20, CContainerWidth * 0.35, 18);
                SetWindowPosition(&lastnamePos, CContainerWidth * 0.55, 20, CContainerWidth * 0.35, 18);

                SetWindowPosition(&dniPos, CContainerWidth * 0.08, 90, CContainerWidth * 0.35, 18);
                SetWindowPosition(&phonePos, CContainerWidth * 0.55, 90, CContainerWidth * 0.35, 18);

                SetWindowPosition(&tdpPos, CContainerWidth * 0.08, 160, 20, 18);

                SetWindowPosition(&buttonRegisterPos, CContainerWidth * 0.35, 160, 100, 30);
                SetWindowPosition(&buttonClosePos, CContainerWidth * 0.60, 160, 100, 30);

                hFormClient.container = CreateWindowA("CLIENT_WINDOW", "Nuevo Cliente", WS_VISIBLE | WS_OVERLAPPEDWINDOW, containerPos.x, containerPos.y, containerPos.cx, containerPos.cy, NULL, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Name:", WS_VISIBLE | WS_CHILD, namePos.x, namePos.y, 45, namePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.name = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, namePos.x, namePos.y + 25, namePos.cx, namePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Lastname:", WS_VISIBLE | WS_CHILD, lastnamePos.x, lastnamePos.y, 70, lastnamePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.lastname = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, lastnamePos.x, lastnamePos.y + 25, lastnamePos.cx, lastnamePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "DNI:", WS_VISIBLE | WS_CHILD, dniPos.x, dniPos.y, 30, dniPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.dni = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, dniPos.x, dniPos.y + 25, dniPos.cx, dniPos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Phone:", WS_VISIBLE | WS_CHILD, phonePos.x, phonePos.y, 50, phonePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.phone = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, phonePos.x, phonePos.y + 25, phonePos.cx, phonePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "TdP:", WS_VISIBLE | WS_CHILD, tdpPos.x, tdpPos.y, 35, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.TdP = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_CENTER, tdpPos.x + 45, tdpPos.y, tdpPos.cx, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("BUTTON_P", "Registrar", WS_VISIBLE | WS_CHILD, buttonRegisterPos.x, buttonRegisterPos.y, buttonRegisterPos.cx, buttonRegisterPos.cy, hFormClient.container, CREATE_CLIENT_FORM, NULL, NULL);
                CreateWindowA("BUTTON_P", "Cancelar", WS_VISIBLE | WS_CHILD, buttonClosePos.x, buttonClosePos.y, buttonClosePos.cx, buttonClosePos.cy, hFormClient.container, CLOSE_CLIENT_FORM, NULL, NULL);
        }
        else if (newClient == TRUE && ventas == TRUE)
        {
                int CContainerWidth = 500;
                int CContainerHeight = 250;

                WINDOWPOS containerPos;
                WINDOWPOS namePos;
                WINDOWPOS lastnamePos;
                WINDOWPOS dniPos;
                WINDOWPOS phonePos;
                WINDOWPOS tdpPos;
                WINDOWPOS buttonRegisterPos;
                WINDOWPOS buttonClosePos;

                SetWindowPosition(&containerPos, WWidth / 2 - (CContainerWidth / 2), WHeight / 2 - (CContainerHeight / 2), CContainerWidth, CContainerHeight);

                SetWindowPosition(&namePos, CContainerWidth * 0.08, 20, CContainerWidth * 0.35, 18);
                SetWindowPosition(&lastnamePos, CContainerWidth * 0.55, 20, CContainerWidth * 0.35, 18);

                SetWindowPosition(&dniPos, CContainerWidth * 0.08, 90, CContainerWidth * 0.35, 18);
                SetWindowPosition(&phonePos, CContainerWidth * 0.55, 90, CContainerWidth * 0.35, 18);

                SetWindowPosition(&tdpPos, CContainerWidth * 0.08, 160, 20, 18);

                SetWindowPosition(&buttonRegisterPos, CContainerWidth * 0.35, 160, 100, 30);
                SetWindowPosition(&buttonClosePos, CContainerWidth * 0.60, 160, 100, 30);

                hFormClient.container = CreateWindowA("CLIENT_WINDOW", "Nuevo Cliente", WS_VISIBLE | WS_OVERLAPPEDWINDOW, containerPos.x, containerPos.y, containerPos.cx, containerPos.cy, NULL, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Name:", WS_VISIBLE | WS_CHILD, namePos.x, namePos.y, 45, namePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.name = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, namePos.x, namePos.y + 25, namePos.cx, namePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Lastname:", WS_VISIBLE | WS_CHILD, lastnamePos.x, lastnamePos.y, 70, lastnamePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.lastname = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, lastnamePos.x, lastnamePos.y + 25, lastnamePos.cx, lastnamePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "DNI:", WS_VISIBLE | WS_CHILD, dniPos.x, dniPos.y, 30, dniPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.dni = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, dniPos.x, dniPos.y + 25, dniPos.cx, dniPos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Phone:", WS_VISIBLE | WS_CHILD, phonePos.x, phonePos.y, 50, phonePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.phone = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, phonePos.x, phonePos.y + 25, phonePos.cx, phonePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "TdP:", WS_VISIBLE | WS_CHILD, tdpPos.x, tdpPos.y, 35, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.TdP = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_CENTER, tdpPos.x + 45, tdpPos.y, tdpPos.cx, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("BUTTON_P", "Registrar", WS_VISIBLE | WS_CHILD, buttonRegisterPos.x, buttonRegisterPos.y, buttonRegisterPos.cx, buttonRegisterPos.cy, hFormClient.container, CREATE_CLIENT_FORM_VENTAS, NULL, NULL);
                CreateWindowA("BUTTON_P", "Cancelar", WS_VISIBLE | WS_CHILD, buttonClosePos.x, buttonClosePos.y, buttonClosePos.cx, buttonClosePos.cy, hFormClient.container, CLOSE_CLIENT_FORM, NULL, NULL);
        }
        else
        {
                currentDataC = dataClient[client];

                int CContainerWidth = 500;
                int CContainerHeight = 250;

                WINDOWPOS containerPos;
                WINDOWPOS namePos;
                WINDOWPOS lastnamePos;
                WINDOWPOS dniPos;
                WINDOWPOS phonePos;
                WINDOWPOS tdpPos;
                WINDOWPOS buttonRegisterPos;
                WINDOWPOS buttonClosePos;

                SetWindowPosition(&containerPos, WWidth / 2 - (CContainerWidth / 2), WHeight / 2 - (CContainerHeight / 2), CContainerWidth, CContainerHeight);

                SetWindowPosition(&namePos, CContainerWidth * 0.08, 20, CContainerWidth * 0.35, 18);
                SetWindowPosition(&lastnamePos, CContainerWidth * 0.55, 20, CContainerWidth * 0.35, 18);

                SetWindowPosition(&dniPos, CContainerWidth * 0.08, 90, CContainerWidth * 0.35, 18);
                SetWindowPosition(&phonePos, CContainerWidth * 0.55, 90, CContainerWidth * 0.35, 18);

                SetWindowPosition(&tdpPos, CContainerWidth * 0.08, 160, 20, 18);

                SetWindowPosition(&buttonRegisterPos, CContainerWidth * 0.35, 160, 100, 30);
                SetWindowPosition(&buttonClosePos, CContainerWidth * 0.60, 160, 100, 30);

                hFormClient.container = CreateWindowA("CLIENT_WINDOW", "Nuevo Cliente", WS_VISIBLE | WS_OVERLAPPEDWINDOW, containerPos.x, containerPos.y, containerPos.cx, containerPos.cy, NULL, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Name:", WS_VISIBLE | WS_CHILD, namePos.x, namePos.y, 45, namePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.name = CreateWindowA("EDIT", currentDataC.name, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, namePos.x, namePos.y + 25, namePos.cx, namePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Lastname:", WS_VISIBLE | WS_CHILD, lastnamePos.x, lastnamePos.y, 70, lastnamePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.lastname = CreateWindowA("EDIT", currentDataC.lastname, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, lastnamePos.x, lastnamePos.y + 25, lastnamePos.cx, lastnamePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "DNI:", WS_VISIBLE | WS_CHILD, dniPos.x, dniPos.y, 30, dniPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.dni = CreateWindowA("EDIT", currentDataC.dni, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, dniPos.x, dniPos.y + 25, dniPos.cx, dniPos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Phone:", WS_VISIBLE | WS_CHILD, phonePos.x, phonePos.y, 50, phonePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.phone = CreateWindowA("EDIT", currentDataC.phone, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, phonePos.x, phonePos.y + 25, phonePos.cx, phonePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "TdP:", WS_VISIBLE | WS_CHILD, tdpPos.x, tdpPos.y, 35, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.TdP = CreateWindowA("EDIT", currentDataC.TdP, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_CENTER, tdpPos.x + 45, tdpPos.y, tdpPos.cx, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("BUTTON_P", "Registrar", WS_VISIBLE | WS_CHILD, buttonRegisterPos.x, buttonRegisterPos.y, buttonRegisterPos.cx, buttonRegisterPos.cy, hFormClient.container, MODIFY_CLIENT_FORM, NULL, NULL);
                CreateWindowA("BUTTON_P", "Cancelar", WS_VISIBLE | WS_CHILD, buttonClosePos.x, buttonClosePos.y, buttonClosePos.cx, buttonClosePos.cy, hFormClient.container, CLOSE_CLIENT_FORM, NULL, NULL);
        }
}

void CreateFormVentas() // Cliente (DNI, Nombre, Telefono, TdP)
{

        RECT rect;

        GetClientRect(hBodyVentas, &rect);

        int margin_top = 10;
        int margin_left = 50;

        int seccion_clientes = 43 + margin_top;
        int seccion_productos = 173 + margin_top;

        int width = rect.right / 4;

        CreateWindowA("S_TRANSPARENT", "Nueva Venta", WS_CHILD | WS_VISIBLE, margin_left, 20 + margin_top, width, 20, hBodyVentas, NULL, NULL, NULL);

        char text[30];
        {
                int ySeparador = 50 + margin_top;
                CreateWindowA("SEPARATOR", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, margin_left, ySeparador, (rect.right * 0.3), 1, hBodyVentas, NULL, NULL, NULL);
                CreateWindowA("SEPARATOR", NULL, WS_CHILD | WS_VISIBLE, rect.right - (rect.right * 0.3) - margin_left, ySeparador, (rect.right * 0.3), 1, hBodyVentas, NULL, NULL, NULL);
                CreateWindowA("SEPARATOR", NULL, WS_CHILD | WS_VISIBLE, margin_left + (rect.right * 0.39), ySeparador, rect.right * 0.1, 1, hBodyVentas, NULL, NULL, NULL);
        }

        CreateWindowA("BUTTON_P", "Seleccionar Cliente", WS_CHILD | WS_VISIBLE, margin_left, ((seccion_clientes + margin_top)) - (30 / 2) + 50 + margin_top, 150, 30,
                      hBodyVentas, SELECT_CLIENT_VENTAS, NULL, NULL);

        CreateWindowA("S_TRANSPARENT", "CLIENTE", WS_CHILD | WS_VISIBLE, (rect.right / 2) - (width / 2), 20 + seccion_clientes, width, 20, hBodyVentas,
                      SS_CENTER, NULL, NULL);

        CreateWindowA("S_TRANSPARENT", "Nombre: ", WS_CHILD | WS_VISIBLE, rect.right / 3, 30 + seccion_clientes, width, 20, hBodyVentas, NULL, NULL, NULL);
        hCurrentClientVentas.name = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, rect.right / 3, 50 + seccion_clientes,
                                                  width, 20, hBodyVentas, NULL, NULL, NULL);

        CreateWindowA("S_TRANSPARENT", "Cedula: ", WS_CHILD | WS_VISIBLE, rect.right / 3 + width + 50, 30 + seccion_clientes,
                      width, 20, hBodyVentas, NULL, NULL, NULL);

        hCurrentClientVentas.TdP = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, rect.right / 3 + width + 50, seccion_clientes + 50,
                                                 15, 20, hBodyVentas, NULL, NULL, NULL);
        CreateWindowA("S_TRANSPARENT", "-", WS_CHILD | WS_VISIBLE, rect.right / 3 + width + 65, 50 + seccion_clientes,
                      15, 20, hBodyVentas, SS_CENTER, NULL, NULL);
        hCurrentClientVentas.dni = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, margin_left + width + (rect.right - (width * 2) - (margin_left * 2)),
                                                 50 + seccion_clientes, width, 20, hBodyVentas, NULL, NULL, NULL);

        CreateWindowA("S_TRANSPARENT", "Telefono: ", WS_CHILD | WS_VISIBLE, rect.right / 3, 80 + seccion_clientes, width, 20, hBodyVentas, NULL, NULL, NULL);
        hCurrentClientVentas.phone = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, rect.right / 3, 100 + seccion_clientes,
                                                   width, 20, hBodyVentas, NULL, NULL, NULL);

        {
                int ySeparador = seccion_productos + margin_top;
                CreateWindowA("SEPARATOR", NULL, WS_CHILD | WS_VISIBLE, margin_left, ySeparador, (rect.right * 0.3), 1, hBodyVentas, NULL, NULL, NULL);
                CreateWindowA("SEPARATOR", NULL, WS_CHILD | WS_VISIBLE, rect.right - (rect.right * 0.3) - margin_left, ySeparador, (rect.right * 0.3), 1, hBodyVentas, NULL, NULL, NULL);
                CreateWindowA("SEPARATOR", NULL, WS_CHILD | WS_VISIBLE, margin_left + (rect.right * 0.39), ySeparador, rect.right * 0.1, 1, hBodyVentas, NULL, NULL, NULL);
        }

        CreateWindowA("S_TRANSPARENT", "PRODUCTOS", WS_CHILD | WS_VISIBLE, (rect.right / 2) - (width / 2), 20 + seccion_productos, width, 20, hBodyVentas,
                      SS_CENTER, NULL, NULL);

        int cxButton = 200;

        /*
                Para Poder obtener el margen entre cada objeto se necesita seguir la siguiente ecuacion
                Margin = (Ancho Contenedor - (Ancho Objeto * Cantidad de objetos)) / (Cantidad de Objetos - 1)
        */

        int xButton[3];
        int marginButtons = (rect.right - (margin_left * 2) - (cxButton * 3)) / 2;

        xButton[0] = margin_left;
        xButton[1] = margin_left + cxButton + marginButtons;
        xButton[2] = (rect.right - margin_left) - cxButton;

        CreateWindowA("BUTTON_P", "Agregar Producto", WS_CHILD | WS_VISIBLE | WS_BORDER, xButton[0], 45 + seccion_productos, cxButton, 30, hBodyVentas, WINDOW_PRODUCT_VENTAS, NULL, NULL);
        CreateWindowA("BUTTON_P", "Eliminar Producto", WS_CHILD | WS_VISIBLE | WS_BORDER, xButton[1], 45 + seccion_productos, cxButton, 30, hBodyVentas, DELETE_PRODUCT_VENTAS, NULL, NULL);
        CreateWindowA("BUTTON_P", "Registrar Venta", WS_CHILD | WS_VISIBLE | WS_BORDER, xButton[2], 45 + seccion_productos, cxButton, 30, hBodyVentas, NEW_VENTA, NULL, NULL);

        pTableCurrentProduct.x = margin_left;
        pTableCurrentProduct.y = seccion_productos + 90;
        pTableCurrentProduct.cx = rect.right - (margin_left * 2);
        pTableCurrentProduct.cy = rect.bottom - (seccion_productos + 100);

        CreateTableListOfProducts(pTableCurrentProduct.x, pTableCurrentProduct.y, pTableCurrentProduct.cx, pTableCurrentProduct.cy);
}

void CreateTableListOfProducts(int x, int y, int cx, int cy)
{
        hTableCurrentProduct = CreateWindowA("DIV", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, cx, cy, hBodyVentas, LIST_CURRENT_PRODUCTS, NULL, NULL);

        int i = 0;

        int yRows = 20;

        for (int i = 0; i < rows_currentProduct_table; i++)
        {
                h_rows_currentProduct_table[i] = CreateWindowA("BODY_ROW_CELL_CURRENTPRODUCT", NULL, WS_CHILD | WS_VISIBLE, 0, yRows, cxColumnTableCurrentProduct * 6, ROW_TABLE_HEIGHT, hTableCurrentProduct, (HMENU)i, NULL, NULL);
                yRows += ROW_TABLE_HEIGHT;
        }
        CreateHeaderTableCurrentProducts(hTableCurrentProduct);
}

void CreateHeaderTableCurrentProducts(HWND hWnd)
{
        RECT rect;
        GetClientRect(hBodyClientes, &rect);
        int width = cxColumnTableCurrentProduct;

        HWND temp = CreateWindowA("BODY_ROW_CELL_CURRENTPRODUCT", NULL, WS_CHILD | WS_VISIBLE, 0, 0, width * 6, ROW_TABLE_HEIGHT, hWnd, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Producto", WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Categoria", WS_VISIBLE | WS_CHILD, width, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Cantidad", WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Descuento", WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Precio", WS_VISIBLE | WS_CHILD, (width * 4), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Precio Total", WS_VISIBLE | WS_CHILD, (width * 5), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

void CreateFooterTotalVentas(HWND hWnd, int x, int y, int cx)
{
        RECT rect;
        GetClientRect(hWnd, &rect);

        HWND temp = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE, x, y, cx * 2, ROW_TABLE_HEIGHT, hWnd, NULL, NULL, NULL);
        CreateWindowA("CELL", "Total:", WS_VISIBLE | WS_CHILD, 0, 0, cx, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        hPrecioTotal = CreateWindowA("HEADER_CELL", NULL, WS_VISIBLE | WS_CHILD, cx, 0, cx, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

void CreateHeaderTableProductsVentas(HWND hWnd, int x, int y)
{
        RECT rect;
        GetClientRect(hWnd, &rect);
        int width = cxColumnTableProductsVentas;

        HWND temp = CreateWindowA("BODY_ROW_CELL_HISTORIALVENTAS", NULL, WS_CHILD | WS_VISIBLE, x + 1, y, width * 4, ROW_TABLE_HEIGHT, hWnd, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Producto", WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Cantidad", WS_VISIBLE | WS_CHILD, width, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Descuento", WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Precio", WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

void CreateWindowViewVenta()
{
        int cxWindow = 500;
        int cyWindow = 620;
        int xWindow = (WWidth / 2) - (cxWindow / 2);
        int yWindow = (WHeight / 2) - (cyWindow / 2);
        hWindowViewVenta = CreateWindowA("CLIENT_WINDOW", "Datos Venta", WS_VISIBLE | WS_OVERLAPPEDWINDOW, xWindow, yWindow, cxWindow, cyWindow, NULL, NULL, NULL, NULL);

        STRUCTVENTASDATA data = dataVentas[(int) GetMenu(hTableCurrentRow)];


        int cxText = 135;
        int cyText = 18;

        int margin_left = 50;
        int margin_top = 40;

        int row;

        char nombre_cliente[100];
        char descuento[20];
        
        row = search_clients(data.ID_cliente);
        get_name_clients(row, nombre_cliente);

        sprintf(descuento, "%s%%", data.discount);

        CreateWindowA("STATIC", "Cliente: ", WS_VISIBLE | WS_CHILD, margin_left, margin_top, 55, cyText, hWindowViewVenta, NULL, NULL, NULL);
        CreateWindowA("STATIC", nombre_cliente, WS_VISIBLE | WS_CHILD, margin_left, margin_top + cyText + 1, cxText, cyText, hWindowViewVenta, NULL, NULL, NULL);

        CreateWindowA("STATIC", "Descuento: ", WS_VISIBLE | WS_CHILD, margin_left + cxText + 20, margin_top, 80, cyText, hWindowViewVenta, NULL, NULL, NULL);
        CreateWindowA("STATIC", descuento, WS_VISIBLE | WS_CHILD | SS_CENTER, margin_left + cxText + 20, margin_top + cyText + 1, 30, cyText, hWindowViewVenta, NULL, NULL, NULL);

        CreateWindowA("STATIC", "Fecha: ", WS_VISIBLE | WS_CHILD, margin_left + cxText + 80 + 40, margin_top, 50, cyText, hWindowViewVenta, NULL, NULL, NULL);
        CreateWindowA("STATIC", data.date, WS_VISIBLE | WS_CHILD, margin_left + cxText + 80 + 40, margin_top + cyText + 1, cxText, cyText, hWindowViewVenta, NULL, NULL, NULL);

        CreateWindowA("DIV", NULL, WS_VISIBLE | WS_CHILD, margin_left, margin_top + 80, cxWindow - (margin_left * 2), cyWindow - margin_top - 160, hWindowViewVenta, LIST_PRODUCTS_VENTAS, NULL, NULL);
        CreateHeaderTableProductsVentas(hWindowViewVenta, margin_left, margin_top + 60);
        CreateFooterTotalVentas(hWindowViewVenta, margin_left + (cxColumnTableProductsVentas * 2), margin_top + 80 + cyWindow - margin_top - 160, cxColumnTableProductsVentas);
}

void CreateHeaderTableVentas(HWND hWnd, int x, int y)
{
        RECT rect;
        GetClientRect(hBodyClientes, &rect);
        int width = cxColumnTableVentas;

        HWND temp = CreateWindowA("BODY_ROW_CELL_HISTORIALVENTAS", NULL, WS_CHILD | WS_VISIBLE, x, y, width * 5, ROW_TABLE_HEIGHT, hWnd, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Cliente", WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Descuento", WS_VISIBLE | WS_CHILD, width, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Precio", WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Precio con IVA", WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Fecha", WS_VISIBLE | WS_CHILD, (width * 4), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

void CreateTableListofVentas(HWND hWnd, int xTable, int yTable, int cxTable, int cyTable)
{
        hTableVentas = CreateWindowA("DIV", NULL, WS_CHILD | WS_VISIBLE, xTable, yTable, cxTable, cyTable, hBodyVentas, LIST_VENTAS, NULL, NULL);

        int i = 0;

        int yRows = 0;

        for (int i = 0; i < rows_ventas_table; i++)
        {
                h_rows_ventas_table[i] = CreateWindowA("BODY_ROW_CELL_HISTORIALVENTAS", NULL, WS_CHILD | WS_VISIBLE, 0, yRows, cxColumnTableVentas * 5, ROW_TABLE_HEIGHT, hTableVentas, (HMENU)i, NULL, NULL);
                yRows += ROW_TABLE_HEIGHT;
        }
        CreateHeaderTableVentas(hBodyVentas, 0, 0);
}

void GetDataTableListofVentas(int cx, int cy)
{
        rows_ventas_table = get_jumplines_venta_file();
        int lines = get_lines_venta_file();
        dataVentas = (STRUCTVENTASDATA *)realloc(NULL, sizeof(STRUCTVENTASDATA) * (rows_ventas_table + 1));
        h_rows_ventas_table = (HWND *)realloc(NULL, sizeof(HWND) * (rows_ventas_table + 1));

        int i = 0;
        int x = 0;

        while (i < lines)
        {
                if (!isBlank_venta(i) && get_visibility_venta(i))
                {
                        get_ID_venta(i, dataVentas[x].ID);
                        get_ID_cliente_venta(i, dataVentas[x].ID_cliente);
                        get_date_venta(i, dataVentas[x].date);
                        get_discount_venta(i, dataVentas[x].discount);
                        x++;
                }
                i++;
        }
        CreateTableListofVentas(hBodyVentas, 0, 20, cx, cy - ROW_TABLE_HEIGHT);
}

void CreateBodyVentasMainWindow(BOOL newSell)
{
        RECT rectMainWindow;
        GetClientRect(hMain, &rectMainWindow);

        int margin = 20;

        WINDOWPOS body;

        int cx = rectMainWindow.right / 2;
        int cy = rectMainWindow.bottom - (margin * 2) - HeaderHeight;
        int x = (rectMainWindow.right / 2) - (cx / 2);
        int y = HeaderHeight + margin;

        hBodyVentas = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE, x, y, cx, cy, hMain, NULL, NULL, NULL);
        hCurrentBody = hBodyVentas;

        if (newSell == TRUE)
                CreateFormVentas();
        else
                GetDataTableListofVentas(cx, cy);
}

void CreateWindowProducts()
{

        int cxWindow = 700, cyWindow = 500;
        int x = (WWidth / 2) - (cxWindow / 2), y = (WHeight / 2) - (cyWindow / 2);
        hWindowProduct = CreateWindowA("CLIENT_WINDOW", "Agregar Producto", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, cxWindow, cyWindow, NULL, NULL, NULL, NULL);
        CreateHeaderWindowProducts(hWindowProduct, cxWindow, 60);

        rows_product_table = get_jumplines_product_file();
        int lines = get_lines_product_file();

        dataProductos = (STRUCTPRODUCTOSDATA *)realloc(NULL, sizeof(STRUCTPRODUCTOSDATA) * (rows_product_table + 1));
        h_rows_product_table = (HWND *)realloc(NULL, sizeof(HWND) * (rows_product_table + 1));

        int i = 0;
        int j = 0;

        while (i < lines)
        {
                if (!isBlank_product(i))
                {
                        if (get_visibility_product(i))
                        {
                                get_ID_product(i, dataProductos[j].ID);
                                get_date_product(i, dataProductos[j].date);
                                get_name_product(i, dataProductos[j].name);
                                get_price_product(i, dataProductos[j].price);
                                get_stock_product(i, dataProductos[j].stock);
                                get_discount_product(i, dataProductos[j].discount);
                                get_category_product(i, dataProductos[j].category);
                                j++;
                        }
                }
                i++;
        }

        CreateTableProducts(hWindowProduct, rows_product_table, 0, 80, cxWindow - 15, cyWindow - 60 - 60);

        CreateHeaderTableProducts(hWindowProduct, 60);
}

void CreateFormProduct(BOOL newProduct, UINT product)
{
        if (newProduct == TRUE)
        {
                int CContainerWidth = 500;
                int CContainerHeight = 250;

                WINDOWPOS containerPos;
                WINDOWPOS namePos;
                WINDOWPOS categoryPos;
                WINDOWPOS discountPos;
                WINDOWPOS pricePos;
                WINDOWPOS stockPos;
                WINDOWPOS buttonRegisterPos;
                WINDOWPOS buttonClosePos;

                SetWindowPosition(&containerPos, WWidth / 2 - (CContainerWidth / 2), WHeight / 2 - (CContainerHeight / 2), CContainerWidth, CContainerHeight);

                SetWindowPosition(&namePos, CContainerWidth * 0.08, 20, CContainerWidth * 0.35, 18);
                SetWindowPosition(&categoryPos, CContainerWidth * 0.55, 20, CContainerWidth * 0.35, 18);

                SetWindowPosition(&discountPos, CContainerWidth * 0.08, 90, CContainerWidth * 0.35, 18);
                SetWindowPosition(&pricePos, CContainerWidth * 0.55, 90, CContainerWidth * 0.35, 18);

                SetWindowPosition(&stockPos, CContainerWidth * 0.08, 160, 30, 18);

                SetWindowPosition(&buttonRegisterPos, CContainerWidth * 0.35, 160, 100, 30);
                SetWindowPosition(&buttonClosePos, CContainerWidth * 0.60, 160, 100, 30);

                hFormProduct.container = CreateWindowA("CLIENT_WINDOW", "Nuevo Cliente", WS_VISIBLE | WS_OVERLAPPEDWINDOW, containerPos.x, containerPos.y, containerPos.cx, containerPos.cy, NULL, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Nombre:", WS_VISIBLE | WS_CHILD, namePos.x, namePos.y, 60, namePos.cy, hFormProduct.container, NULL, NULL, NULL);
                hFormProduct.name = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, namePos.x, namePos.y + 25, namePos.cx, namePos.cy, hFormProduct.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Categoria:", WS_VISIBLE | WS_CHILD, categoryPos.x, categoryPos.y, 70, categoryPos.cy, hFormProduct.container, NULL, NULL, NULL);
                hFormProduct.category = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, categoryPos.x, categoryPos.y + 25, categoryPos.cx, categoryPos.cy, hFormProduct.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Descuento:", WS_VISIBLE | WS_CHILD, discountPos.x, discountPos.y, 75, discountPos.cy, hFormProduct.container, NULL, NULL, NULL);
                hFormProduct.discount = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, discountPos.x, discountPos.y + 25, discountPos.cx, discountPos.cy, hFormProduct.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Precio:", WS_VISIBLE | WS_CHILD, pricePos.x, pricePos.y, 50, pricePos.cy, hFormProduct.container, NULL, NULL, NULL);
                hFormProduct.price = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, pricePos.x, pricePos.y + 25, pricePos.cx, pricePos.cy, hFormProduct.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Stock:", WS_VISIBLE | WS_CHILD, stockPos.x, stockPos.y, 45, stockPos.cy, hFormProduct.container, NULL, NULL, NULL);
                hFormProduct.stock = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_CENTER, stockPos.x + 50, stockPos.y, stockPos.cx, stockPos.cy, hFormProduct.container, NULL, NULL, NULL);

                CreateWindowA("BUTTON_P", "Registrar", WS_VISIBLE | WS_CHILD, buttonRegisterPos.x, buttonRegisterPos.y, buttonRegisterPos.cx, buttonRegisterPos.cy, hFormProduct.container, ADD_PRODUCT_FORM, NULL, NULL);
                CreateWindowA("BUTTON_P", "Cancelar", WS_VISIBLE | WS_CHILD, buttonClosePos.x, buttonClosePos.y, buttonClosePos.cx, buttonClosePos.cy, hFormProduct.container, CLOSE_FORM_PRODUCT, NULL, NULL);
        }
        else
        {
                currentDataP = dataProductos[product];

                int CContainerWidth = 500;
                int CContainerHeight = 250;

                WINDOWPOS containerPos;
                WINDOWPOS namePos;
                WINDOWPOS categoryPos;
                WINDOWPOS discountPos;
                WINDOWPOS pricePos;
                WINDOWPOS stockPos;
                WINDOWPOS buttonRegisterPos;
                WINDOWPOS buttonClosePos;

                SetWindowPosition(&containerPos, WWidth / 2 - (CContainerWidth / 2), WHeight / 2 - (CContainerHeight / 2), CContainerWidth, CContainerHeight);

                SetWindowPosition(&namePos, CContainerWidth * 0.08, 20, CContainerWidth * 0.35, 18);
                SetWindowPosition(&categoryPos, CContainerWidth * 0.55, 20, CContainerWidth * 0.35, 18);

                SetWindowPosition(&discountPos, CContainerWidth * 0.08, 90, CContainerWidth * 0.35, 18);
                SetWindowPosition(&pricePos, CContainerWidth * 0.55, 90, CContainerWidth * 0.35, 18);

                SetWindowPosition(&stockPos, CContainerWidth * 0.08, 160, 30, 18);

                SetWindowPosition(&buttonRegisterPos, CContainerWidth * 0.35, 160, 100, 30);
                SetWindowPosition(&buttonClosePos, CContainerWidth * 0.60, 160, 100, 30);

                hFormProduct.container = CreateWindowA("CLIENT_WINDOW", "Nuevo Cliente", WS_VISIBLE | WS_OVERLAPPEDWINDOW, containerPos.x, containerPos.y, containerPos.cx, containerPos.cy, NULL, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Name:", WS_VISIBLE | WS_CHILD, namePos.x, namePos.y, 60, namePos.cy, hFormProduct.container, NULL, NULL, NULL);
                hFormProduct.name = CreateWindowA("EDIT", currentDataP.name, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, namePos.x, namePos.y + 25, namePos.cx, namePos.cy, hFormProduct.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Categoria:", WS_VISIBLE | WS_CHILD, categoryPos.x, categoryPos.y, 70, categoryPos.cy, hFormProduct.container, NULL, NULL, NULL);
                hFormProduct.category = CreateWindowA("EDIT", currentDataP.category, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, categoryPos.x, categoryPos.y + 25, categoryPos.cx, categoryPos.cy, hFormProduct.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Descuento:", WS_VISIBLE | WS_CHILD, discountPos.x, discountPos.y, 75, discountPos.cy, hFormProduct.container, NULL, NULL, NULL);
                hFormProduct.discount = CreateWindowA("EDIT", currentDataP.discount, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, discountPos.x, discountPos.y + 25, discountPos.cx, discountPos.cy, hFormProduct.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Precio:", WS_VISIBLE | WS_CHILD, pricePos.x, pricePos.y, 50, pricePos.cy, hFormProduct.container, NULL, NULL, NULL);
                hFormProduct.price = CreateWindowA("EDIT", currentDataP.price, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, pricePos.x, pricePos.y + 25, pricePos.cx, pricePos.cy, hFormProduct.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Stock:", WS_VISIBLE | WS_CHILD, stockPos.x, stockPos.y, 45, stockPos.cy, hFormProduct.container, NULL, NULL, NULL);
                hFormProduct.stock = CreateWindowA("EDIT", currentDataP.stock, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_CENTER, stockPos.x + 50, stockPos.y, stockPos.cx, stockPos.cy, hFormProduct.container, NULL, NULL, NULL);

                CreateWindowA("BUTTON_P", "Registrar", WS_VISIBLE | WS_CHILD, buttonRegisterPos.x, buttonRegisterPos.y, buttonRegisterPos.cx, buttonRegisterPos.cy, hFormProduct.container, MODIFY_PRODUCT_FORM, NULL, NULL);
                CreateWindowA("BUTTON_P", "Cancelar", WS_VISIBLE | WS_CHILD, buttonClosePos.x, buttonClosePos.y, buttonClosePos.cx, buttonClosePos.cy, hFormProduct.container, CLOSE_FORM_PRODUCT, NULL, NULL);
        }
}

void CreateBodyProductos()
{
        RECT rectMainWindow;
        GetClientRect(hMain, &rectMainWindow);

        int cxBody = rectMainWindow.right / 1.8;
        int cyBody = rectMainWindow.bottom - HeaderHeight - 40;
        int xBody = (rectMainWindow.right / 2) - (cxBody / 2);
        int yBody = HeaderHeight + 20;

        hBodyInventario = CreateWindowA("CONTAINER_VACIO", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, xBody, yBody, cxBody, cyBody, hMain, NULL, NULL, NULL);
        hCurrentBody = hBodyInventario;

        rows_product_table = get_jumplines_product_file();
        int lines = get_lines_product_file();

        char text[20];

        dataProductos = (STRUCTPRODUCTOSDATA *)realloc(NULL, sizeof(STRUCTPRODUCTOSDATA) * (rows_product_table + 1));
        h_rows_product_table = (HWND *)realloc(NULL, sizeof(HWND) * (rows_product_table + 1));

        int i = 0;
        int x = 0;

        while (i < lines)
        {
                if (!isBlank_product(i) && get_visibility_product(i))
                {
                        get_ID_product(i, dataProductos[x].ID);
                        get_date_product(i, dataProductos[x].date);
                        get_name_product(i, dataProductos[x].name);
                        get_price_product(i, dataProductos[x].price);
                        get_stock_product(i, dataProductos[x].stock);
                        get_discount_product(i, dataProductos[x].discount);
                        get_category_product(i, dataProductos[x].category);
                        x++;
                }
                i++;
        }


        CreateTableProducts(hBodyInventario, rows_product_table, 0, 0, cxBody, cyBody - 20);

        CreateHeaderTableProducts(hBodyInventario, 0);
}

void CreateHeaderWindowProducts(HWND hWnd, int cxHeader, int cyHeader)
{
        RECT rect;
        GetClientRect(hWnd, &rect);

        HWND headerWindowProduct = CreateWindowA("CONTAINER_VACIO", NULL, WS_CHILD | WS_VISIBLE, 0, 0, cxHeader, cyHeader, hWnd, NULL, NULL, NULL);

        int cxButton = 100;
        int cyButton = 30;
        int yButton = (cyHeader / 2) - (cyButton / 2);

        int cxEdit = 100;
        int cyEdit = 20;
        int yEdit = (cyHeader / 2) - (cyEdit / 2);

        char text[100];

        HWND button = CreateWindowA("BUTTON_P", "Agregar", WS_CHILD | WS_VISIBLE, 100, yButton, cxButton, cyButton, headerWindowProduct, ADD_PRODUCT_VENTAS, NULL, NULL);
        CreateWindowA("BUTTON_P", "Cancelar", WS_CHILD | WS_VISIBLE, 220, yButton, cxButton, cyButton, headerWindowProduct, CLOSE_WINDOW_PRODUCT_VENTAS, NULL, NULL);
        CreateWindowA("EDIT", "Search", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 340, yEdit, cxEdit, cyEdit, headerWindowProduct, NULL, NULL, NULL);
}

void CreateTableProducts(HWND hWnd, int len, int x, int y, int cx, int cy)
{
        hTableProduct = CreateWindowA("DIV", NULL, WS_CHILD | WS_VISIBLE, x, y, cx, cy, hWnd, LIST_PRODUCTS, NULL, NULL);


        int yRows = 0;

        for (int i = 0; i < len; i++)
        {
                h_rows_product_table[i] = CreateWindowA("BODY_ROW_CELL_PRODUCT", NULL, WS_CHILD | WS_VISIBLE, 0, yRows, cxColumnTableProduct * 6, ROW_TABLE_HEIGHT, hTableProduct, (HMENU)i, NULL, NULL);
                yRows += ROW_TABLE_HEIGHT;
        }
}

void CreateHeaderTableProducts(HWND hWnd, int y)
{
        RECT rect;
        GetClientRect(hBodyClientes, &rect);
        int width = cxColumnTableProduct;

        HWND temp = CreateWindowA("BODY_ROW_CELL_PRODUCT", NULL, WS_CHILD | WS_VISIBLE, 0, y, width * 6, ROW_TABLE_HEIGHT, hWnd, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Producto", WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Categoria", WS_VISIBLE | WS_CHILD, width, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Stock", WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Descuento", WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Precio Total", WS_VISIBLE | WS_CHILD, (width * 4), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Fecha", WS_VISIBLE | WS_CHILD, (width * 5), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

void CreateRowTableClientPortable(HWND hWnd, int width)
{
        char text[100];
        yTabla = 0;
        for (int i = 0; i < rows_clients_table; i++)
        {
                hTableCliente[i].container = CreateWindowA("BODY_ROW_CELL", NULL, WS_CHILD | WS_VISIBLE, 0, yTabla, width, ROW_TABLE_HEIGHT, hTableContainer, i, NULL, NULL);
                yTabla += 20;
        }
}

void CreateTableListOfClients(HWND hWnd, int x, int y, int cxTable, int cyTable)
{
        nColumnsTable = 6;

        DWORD sTableContainer;

        if (rows_clients_table > cyTable / ROW_TABLE_HEIGHT)
                sTableContainer = WS_VISIBLE | WS_CHILD | WS_VSCROLL;
        else
        {
                sTableContainer = WS_VISIBLE | WS_CHILD;
        }

        hTableContainer = CreateWindowExA(0, "DIV", NULL, sTableContainer, x, y, cxTable, cyTable, hWnd, LIST_CLIENTS, NULL, NULL);

        CreateRowTableClientPortable(hTableContainer, cxColumnTable * 6);
}

void CreateHeaderTableClients(HWND hWnd, int y)
{
        RECT rect;
        GetClientRect(hWnd, &rect);
        int width = cxColumnTable;

        HWND temp = CreateWindowA("BODY_ROW_CELL_PRODUCT", NULL, WS_CHILD | WS_VISIBLE, 0, y, width * 6, ROW_TABLE_HEIGHT, hWnd, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Nombre", WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Apellido", WS_VISIBLE | WS_CHILD, width, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Cedula", WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Telefono", WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Naturaleza", WS_VISIBLE | WS_CHILD, (width * 4), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Fecha", WS_VISIBLE | WS_CHILD, (width * 5), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

void CreateHeaderClientsVentas(HWND hWnd, int cxHeader, int cyHeader)
{
        RECT rect;
        GetClientRect(hWnd, &rect);

        HWND headerWindowProduct = CreateWindowA("CONTAINER_VACIO", NULL, WS_CHILD | WS_VISIBLE, 0, 0, cxHeader, cyHeader, hWnd, NULL, NULL, NULL);

        int cxButton = 100;
        int cyButton = 30;
        int yButton = (cyHeader / 2) - (cyButton / 2);

        int cxEdit = 100;
        int cyEdit = 20;
        int yEdit = (cyHeader / 2) - (cyEdit / 2);

        char text[100];

        CreateWindowA("BUTTON_P", "Agregar", WS_CHILD | WS_VISIBLE, 100, yButton, cxButton, cyButton, headerWindowProduct, ADD_CLIENT_VENTAS, NULL, NULL);
        CreateWindowA("BUTTON_P", "Nuevo Cliente", WS_CHILD | WS_VISIBLE, 220, yButton, cxButton + 20, cyButton, headerWindowProduct, OPEN_FORM_CLIENTS_VENTAS, NULL, NULL);
        CreateWindowA("BUTTON_P", "Cancelar", WS_CHILD | WS_VISIBLE, 360, yButton, cxButton, cyButton, headerWindowProduct, CLOSE_WINDOW_CLIENTS_VENTAS, NULL, NULL);
        CreateWindowA("EDIT", "Search", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 480, yEdit, cxEdit, cyEdit, headerWindowProduct, NULL, NULL, NULL);
}

void CreateWindowClients()
{
        int cxWindow = 700, cyWindow = 500;
        int x = (WWidth / 2) - (cxWindow / 2), y = (WHeight / 2) - (cyWindow / 2);
        hBodyClientes = CreateWindowA("CLIENT_WINDOW", "Seleccionar Cliente", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, cxWindow, cyWindow, NULL, NULL, NULL, NULL);
        CreateHeaderWindowProducts(hWindowProduct, cxWindow, 60);

        rows_clients_table = get_jumplines_clients_file();
        int lines = get_lines_clients_file();

        free(dataClient);
        free(hTableCliente);

        dataClient = NULL;
        hTableCliente = NULL;

        dataClient = (STRUCTCLIENTESDATA *)malloc(sizeof(STRUCTCLIENTESDATA) * (rows_clients_table + 1));
        hTableCliente = (STRUCTCLIENTESHWND *)malloc(sizeof(STRUCTCLIENTESHWND) * (rows_clients_table + 1));

        int i = 0;
        x = 0;

        char text[300];

        while (i < lines)
        {
                if (!isBlank(i))
                {
                        get_ID_clients(i, dataClient[x].ID);
                        get_date_clients(i, dataClient[x].date);
                        get_name_clients(i, dataClient[x].name);
                        get_lastname_clients(i, dataClient[x].lastname);
                        get_dni_clients(i, dataClient[x].dni);
                        get_phone_clients(i, dataClient[x].phone);
                        get_TdP_clients(i, dataClient[x].TdP);
                        x++;
                }
                i++;
        }

        switch (currentSort)
        {
        case DATE_SORT_DES:
                SortDateStructClient(dataClient, 0, x);
                break;
        case DATE_SORT_ASD:
                SortDateStructClient(dataClient, 1, x);
                break;
        }

        CreateHeaderClientsVentas(hBodyClientes, cxWindow, 60);
        CreateTableListOfClients(hBodyClientes, 0, 80, cxWindow - 15, cyWindow - 120);
        CreateHeaderTableClients(hBodyClientes, 60);
}