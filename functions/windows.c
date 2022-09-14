#include <windows.h>
#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windowsx.h>
#include "../handlers/windows.h"
#include "../handlers/winProc.h"
#include "../handlers/clientes.h"
#include "../handlers/struct.h"

yTabla = 0;
FirstMalloc = 0;
currentSort = DEFAULT_SORT;

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

        wS_Transparent.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wS_Transparent.hCursor = LoadCursor(NULL, IDC_ARROW);
        wS_Transparent.hInstance = hInstance;
        wS_Transparent.lpszClassName = "S_TRANSPARENT";
        wS_Transparent.lpfnWndProc = STransparentWindowProcedure;
        wS_Transparent.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassA(&wS_Transparent))
                return FALSE;

        WNDCLASSA wButtons = {0};

        wButtons.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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

        WNDCLASSA wDiv = {0};

        wDiv.hCursor = LoadCursor(NULL, IDC_ARROW);
        wDiv.hInstance = hInstance;
        wDiv.lpszClassName = "DIV";
        wDiv.lpfnWndProc = DivWindowProcedure;

        if (!RegisterClassA(&wDiv))
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

        dataClient = (STRUCTCLIENTESDATA *)malloc(sizeof(STRUCTCLIENTESDATA));
        hTableCliente = (STRUCTCLIENTESHWND *)malloc(sizeof(STRUCTCLIENTESHWND));
        CreateHeader();
}

void CreateHeaderTableClient()
{
        RECT rect;
        GetClientRect(hBodyClientes, &rect);
        float width = (rect.right - SCROLLBAR_WIDTH) / 6;
        HWND temp = CreateWindowA("BODY_ROW_CELL", NULL, WS_CHILD | WS_VISIBLE, 0, 0, rect.right, ROW_TABLE_HEIGHT, hBodyClientes, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Nombre", WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Apellido", WS_VISIBLE | WS_CHILD, width, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "DNI", WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Telefono", WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Naturaleza", WS_VISIBLE | WS_CHILD, (width * 4), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Fecha", WS_VISIBLE | WS_CHILD, (width * 5), 0, width + 3, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

void CreateRowTableClient(STRUCTCLIENTESDATA data, int i)
{
        RECT rect;
        GetClientRect(hBodyClientes, &rect);
        hTableCliente[i].container = CreateWindowA("BODY_ROW_CELL", NULL, WS_CHILD | WS_VISIBLE, 0, yTabla, rect.right, ROW_TABLE_HEIGHT, hTableContainer, i, NULL, NULL);
        float width = (rect.right - SCROLLBAR_WIDTH) / 6;

        char TipoDePersona[20];

        if (data.TdP[0] == 'V')
                strcpy(TipoDePersona, "Venezolano");
        else if (data.TdP[0] == 'G')
                strcpy(TipoDePersona, "Gubernamental");
        else if (data.TdP[0] == 'E')
                strcpy(TipoDePersona, "Extranjero");
        else
                strcpy(TipoDePersona, "Juridico");

        CreateWindowA("CELL", data.name, WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, hTableCliente[i].container, i, NULL, NULL);
        CreateWindowA("CELL", data.lastname, WS_VISIBLE | WS_CHILD, width, 0, width, ROW_TABLE_HEIGHT, hTableCliente[i].container, i, NULL, NULL);
        CreateWindowA("CELL", data.dni, WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, hTableCliente[i].container, i, NULL, NULL);
        CreateWindowA("CELL", data.phone, WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, hTableCliente[i].container, i, NULL, NULL);
        CreateWindowA("CELL", TipoDePersona, WS_VISIBLE | WS_CHILD, (width * 4), 0, width, ROW_TABLE_HEIGHT, hTableCliente[i].container, i, NULL, NULL);
        CreateWindowA("CELL", data.date, WS_VISIBLE | WS_CHILD, (width * 5), 0, width + 3, ROW_TABLE_HEIGHT, hTableCliente[i].container, i, NULL, NULL);
        yTabla += 20;
}

void CreateTableClient()
{
        int jumplines = get_jumplines_clients_file();
        int lines = get_lines_clients_file();

        free(dataClient);
        free(hTableCliente);

        dataClient = NULL;
        hTableCliente = NULL;

        dataClient = (STRUCTCLIENTESDATA *)malloc(sizeof(STRUCTCLIENTESDATA) * (jumplines + 1));
        hTableCliente = (STRUCTCLIENTESHWND *)malloc(sizeof(STRUCTCLIENTESHWND) * (jumplines + 1));

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
        RECT rectBodyClientes;
        GetClientRect(hBodyClientes, &rectBodyClientes);

        hTableContainer = CreateWindowA("DIV", NULL, WS_VISIBLE | WS_CHILD, 0, 20, rectBodyClientes.right - SCROLLBAR_WIDTH, (jumplines + 1) * ROW_TABLE_HEIGHT, hBodyClientes, NULL, NULL, NULL);

        int y = 0;
        for (int i = 0; i < jumplines; i++)
        {
                CreateRowTableClient(dataClient[i], i);
        }

        RECT rectMainWindow;

        GetClientRect(hMain, &rectMainWindow);

        RECT rectContainer;
        GetClientRect(hTableContainer, &rectContainer);

        HWND scrollBar;

        scrollBar = CreateWindowEx(0, "SCROLLBAR", NULL, WS_CHILD | WS_VISIBLE | SBS_VERT, rectBodyClientes.right - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, rectMainWindow.bottom - HeaderHeight, hBodyClientes, (HMENU)1001, (HINSTANCE)GetWindowLongA(hTableContainer, GWL_HINSTANCE), NULL);

        SCROLLINFO sbInfo;

        sbInfo.nPos = 0;
        sbInfo.nMin = 0;
        sbInfo.cbSize = sizeof(SCROLLINFO);

        if (rectContainer.bottom > rectMainWindow.bottom - HeaderHeight)
        {
                sbInfo.nMax = rectContainer.bottom;
                sbInfo.nPage = rectMainWindow.bottom - HeaderHeight;
                sbInfo.fMask = SIF_ALL;
        }
        else
        {
                sbInfo.nMax = 1;
                sbInfo.nPage = 1;
                sbInfo.fMask = SIF_DISABLENOSCROLL;
        }

        SetScrollInfo(scrollBar, SB_VERT, &sbInfo, TRUE);

        SetWindowLongA(scrollBar, GWLP_WNDPROC, (LONG)ScrollBarProc);
}

void CreateBodyCliente()
{
        yTabla = 0;
        RECT CRect;
        GetClientRect(hMain, &CRect);
        hBodyClientes = CreateWindowA("BODY", NULL, WS_VISIBLE | WS_CHILD, 0, 100, CRect.right, CRect.bottom - HeaderHeight, hMain, NULL, NULL, NULL);
        hTableCurrentRow = NULL;
        hCurrentBody = hBodyClientes;

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

void CreateFormClient(BOOL newClient, UINT client)
{
        if (newClient == TRUE)
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
