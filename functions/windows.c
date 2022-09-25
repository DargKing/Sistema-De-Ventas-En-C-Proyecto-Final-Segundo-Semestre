/*
windows.c es el archivo encargado de la creacion de ventanas y componentes de la aplicacion.

Para la interfaz grafica usamos winapi32, en esta libreria los componentes como botones, texto y demas se llaman ventanas, a las ventanas se les puede 
imaginar como cajas vacias las cuales se tienen que pintar con datos establecidos por el desarrollador

Para crear una ventana se usa la funcion CreateWindowA(); Los argumentos de esta son

CreateWindowA(Clase de la funcion, Texto, Estilo de la funcion, Posicion en x, posicion y, ancho, alto, ventana padre, codigo de menu, instancia de la ventana, lParam);

Al usar esta funcion si funciona bien devuelve el identificador de la ventana, este identificador debe de guardarse en una variable HWND, en caso de que haya un error
Devuelve NULL

Los mas escenciales son la clase de la funcion y la ventana padre, la clase de la funcion en un campo 100% obligatorio, esta clase determinara su comportamiento
y su aspecto, ademas de que tambien manejara los mensajes de la ventana (Esto se explicara en winProc.c), despues esta la ventana padre, en este campo va una
estructura HWND que contendra el identificador de la ventana a la cual se acoplara la nueva ventana.

Siguiendo con el tema de las clases, para crear una clase se tiene que crear una variable con la estructura WNDCLASS y despues rellenar los datos de esta,
despues de rellenar los datos se pasa por la funcion RegisterClass, despues de eso la clase estara registrada
*/

#include <windows.h>
#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windowsx.h>
#include "../handlers/windows.h"
#include "../handlers/winProc.h"
#include "../handlers/productos.h"
#include "../handlers/facturas.h"
#include "../handlers/clientes.h"
#include "../handlers/ventas.h"
#include "../handlers/struct.h"
#include "../handlers/colors.h"

yTabla = 0;
FirstMalloc = 0;
currentSort = DEFAULT_SORT;
Window_product_is_open = 0;
rows_currentProduct_table = 0;

/*
        CreateClasses es uno de los primeros procesos que se hacen en el programa, este sirve para crear las
        clases de ventanas personalizadas, existen clases de ventanas ya preexistentes como STATIC o EDIT,
        Las cuales se usan mucho durante el programa, pero las clases personalizadas son lo que mas abunda
        ya que con esta se pueden crear controles y opciones fuera de la norma

        Parametros
        [INPUT] hInstance: Este parametro es la instancia de la ventana (No entiendo del todo bien que es pero se que
        si no esta, no funciona)

        Return BOOL (Este BOOL es una estructura de winapi, parecida al bool de stdbool.h)
        Esta funcion si se completa con exito devuelve TRUE,
        en caso de que suceda un error al registrar las clases devuelve FALSE
*/

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

        wClientWindow.lpfnWndProc = ClientFacturaWindowProcedure;
        wClientWindow.hbrBackground = (HBRUSH)CreateSolidBrush(COLOR_WHITE);
        wClientWindow.lpszClassName = "CLIENT_FACTURA";

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


/*
        CreateSingUp. Esta funcion se encarga de crear la ventana de crear usuario, en esta ventana se rellena el formulario y 
        si no hay ningun error en los datos se crea el usuario, despues de crearse se oculta la ventana (No se cierra).
        Si se preciona el boton Close, la ejecucion del programa completo termina

        Parametros (No tiene)

        Return void
*/

void CreateSingupWindow()
{
        int cxWindow = 350;
        int cyWindow = 280;
        int WPositionX = (WWidth / 2) - (cxWindow / 2);
        int WPositionY = (WHeight / 2) - (cyWindow / 2);

        hSingUp = CreateWindowA("LOGIN", NULL, WS_POPUP | WS_VISIBLE | WS_BORDER, WPositionX, WPositionY, cxWindow, cyWindow, NULL, NULL, NULL, NULL);

        CreateWindowA("S_TRANSPARENT", "Name:", WS_CHILD | WS_VISIBLE | SS_WHITEFRAME, 50, 30, 250, 20, hSingUp, NULL, NULL, NULL);
        hName = CreateWindowA("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 50, 50, 250, 20, hSingUp, NULL, NULL, NULL);

        CreateWindowA("S_TRANSPARENT", "Password:", WS_CHILD | WS_VISIBLE, 50, 80, 250, 20, hSingUp, NULL, NULL, NULL);
        hPassword = CreateWindowA("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 50, 100, 250, 20, hSingUp, NULL, NULL, NULL);

        CreateWindowW(L"S_TRANSPARENT", L"Rif Compañia:", WS_CHILD | WS_VISIBLE, 50, 130, 250, 20, hSingUp, NULL, NULL, NULL);
        CreateWindowA("STATIC", "J", WS_CHILD | WS_VISIBLE | SS_CENTER, 50, 150, 20, 20, hSingUp, NULL, NULL, NULL);
        CreateWindowA("S_TRANSPARENT", "-", WS_CHILD | WS_VISIBLE, 70, 150, 20, 20, hSingUp, SS_CENTER, NULL, NULL);
        hRifCompany = CreateWindowA("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 90, 150, 210, 20, hSingUp, NULL, NULL, NULL);

        CreateWindowW(L"S_TRANSPARENT", L"Direccion Compañia:", WS_CHILD | WS_VISIBLE, 50, 180, 250, 20, hSingUp, NULL, NULL, NULL);
        hDireccionCompany = CreateWindowA("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 50, 200, 250, 20, hSingUp, NULL, NULL, NULL);

        int cxButton = 120;

        CreateWindowA("BUTTON_P", "Sing Up", WS_CHILD | WS_VISIBLE, 50, 230, cxButton, 30, hSingUp, SINGUP_USER, NULL, NULL);
        CreateWindowA("BUTTON_P", "Close", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_VCENTER, 180, 230, cxButton, 30, hSingUp, CLOSE_WINDOW, NULL, NULL);
}

/*
        CreateLoginWindow. Al llamar a esta funcion se crea la ventana de inicio de sesion, esta es la segunda funcion que se llama al
        comenzar el programa. Despues de introducir los datos del usuario en el formulario se le da click en el boton Login, si los datos del usuario
        son correctos se cierra la ventana e inicia el programa principal. Si se quiere crear un usuario se preciona el boton Nuevo Usuario,
        al hacer esto se oculta (no se cierra) la ventana y se crea la ventana SingUp llamando a la funcion CreateSingupWindow().
        Si se preciona el boton Close, la ejecucion del programa completo termina

        Parametros (Ninguno)

        Return void
*/

void CreateLoginWindow()
{
        int CLoginWidth = 350;
        int CLoginHeight = 220;
        WHeight = GetSystemMetrics(SM_CYSCREEN);
        WWidth = GetSystemMetrics(SM_CXSCREEN);
        int WPositionX = (WWidth / 2) - (CLoginWidth / 2);
        int WPositionY = (WHeight / 2) - (CLoginHeight / 2);

        hLogin = CreateWindowA("LOGIN", NULL, WS_POPUP | WS_VISIBLE | WS_BORDER, WPositionX, WPositionY, CLoginWidth, CLoginHeight, NULL, NULL, NULL, NULL);

        hStatic1 = CreateWindowA("S_TRANSPARENT", "Name:", WS_CHILD | WS_VISIBLE | SS_WHITEFRAME, 50, 30, 250, 20, hLogin, NULL, NULL, NULL);
        hName = CreateWindowA("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 50, 50, 250, 20, hLogin, NULL, NULL, NULL);

        hStatic2 = CreateWindowA("S_TRANSPARENT", "Password:", WS_CHILD | WS_VISIBLE, 50, 80, 250, 20, hLogin, NULL, NULL, NULL);
        hPassword = CreateWindowA("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 50, 100, 250, 20, hLogin, NULL, NULL, NULL);

        int cxButton = 120;

        hButtonGreen = CreateWindowA("BUTTON_P", "Login", WS_CHILD | WS_VISIBLE, 50, 130, cxButton, 30, hLogin, LOGIN_USER, NULL, NULL);
        hButtonRed = CreateWindowA("BUTTON_P", "Close", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_VCENTER, 180, 130, cxButton, 30, hLogin, CLOSE_WINDOW, NULL, NULL);

        CreateWindowA("BUTTON_P", "Nuevo Usuario", WS_CHILD | WS_VISIBLE | BS_CENTER | BS_VCENTER, (CLoginWidth / 2) - (cxButton / 2), 170, cxButton, 30, hLogin, OPEN_SINGUP_USER_WINDOW, NULL, NULL);
}

/*
CreateMainWindow. Despues de iniciar sesion se llama a la funcion CreateMainWindow, esta va a ser la ventana principal del programa. Esta Ventana estara 
maximizada (No se debe salir de este modo ya que el programa no se le a agregado el rezise del contenido), despues de crearse esta ventana se llama a la funcion
CreateHeader, el cual creara el Header Principal del programa.
Esta funcion tambien tiene como objetivo el de poner en las variables puntero, que se encargaran de almacenar los datos de las tablas, un malloc para que puedan manipularse
como arrays y poder cambiarles el tamaño despues

Parametros Ninguno

Return void
*/

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

/*
        CreateHeader. Esta funcion crea el contenedor para que los demas componentes se acoplen a esta.
        Despues de crearse el contenedor se llama a CreateNavBar para que cree el la barra de navegacion

        Parametros Ninguno

        Return void
*/

void CreateHeader()
{
        RECT CRect;
        GetClientRect(hMain, &CRect);
        hMainHeader = CreateWindowA("HEADER", NULL, WS_VISIBLE | WS_CHILD, 0, 0, CRect.right, HeaderHeight, hMain, NULL, NULL, NULL);
        CreateNavBar();
}

/*
        CreateNavBar. Esta funcion Crea la barra de navegacion donde se viajara a los distintos aspectos de nuestro programa.
        Esta funcion solo se usa una ves y es al crear la ventana principal. Despues de crear la barra de navegacion se llama a 4 funciones en el siguiente orden
        CreateToolBarVentas, CreateToolBarInventario, CreateToolBarClientes y CreateBodyVentasMainWindow
        Las funciones CreateTollBar sirven para crear la barra de herramientas con las que se podra ver la tabla de ventas, eliminar una fila de cualquier tabla, agregar fila
        y modificar filas
        la funcion CreateBodyVentasMainWindow crea el formulario para crear nuevas ventas. esta se explicara mas detalladamente mas tarde

        Paramentros Ninguno

        Return void
*/

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

/*
CreateToolBarInventario. Esta funcion crea el contenedor para las herramientas, este contenedor seria la barra de tareas, al finalizar la funcion llama a la funcion
CreateToolsInventario para crear las herramientas para manejar la table de inventario

Parametros Ninguno

Return void
*/

void CreateToolBarInventario()
{
        hToolBarInventario = CreateWindowA("TOOLBAR_CONTAINER", NULL, WS_VISIBLE | WS_CHILD, 0, 25, CRect.right, ToolBarHeight, hMainHeader, NULL, NULL, NULL);
        ShowWindow(hToolBarInventario, SW_HIDE);
        CreateToolsInventario();
}

/*
        CreateToolsInventario. Esta funcion crea las herramientas para manejar la tabla de inventario. Estas herramientas son
        Crear producto, eliminar producto y modificar producto. al hacer click en Nuevo Producto se crea un formulario en el que se debe de introducir
        Los datos del producto. al precionar modificar producto se crea otro formulario en el que se modificaran los datos actuales del producto.
        Eliminar Producto elimina la fila seleccionada

        Parametros Ninguno

        Return void
*/

void CreateToolsInventario()
{
        hNuevoProducto = CreateWindowA("TOOL", "Nuevo Producto", WS_VISIBLE | WS_CHILD, 20, 0, 100, 75, hToolBarInventario, TOOLBAR_IMAGE_NEW_INVENTARIO, NULL, NULL);
        hModificarProducto = CreateWindowA("TOOL", "Modificar Producto", WS_VISIBLE | WS_CHILD, 120, 0, 100, 75, hToolBarInventario, TOOLBAR_IMAGE_MODIFY_INVENTARIO, NULL, NULL);
        hEliminarProducto = CreateWindowA("TOOL", "Eliminar Producto", WS_VISIBLE | WS_CHILD, 220, 0, 100, 75, hToolBarInventario, TOOLBAR_IMAGE_DELETE_INVENTARIO, NULL, NULL);
}


/*
CreateToolBarClientes. Esta funcion crea el contenedor para las herramientas, este contenedor seria la barra de tareas, al finalizar la funcion llama a la funcion
CreateToolsClientes para crear las herramientas para manejar la table de clientes.

Parametros Ninguno

Return void
*/

void CreateToolBarClientes()
{
        hToolBarClientes = CreateWindowA("TOOLBAR_CONTAINER", NULL, WS_VISIBLE | WS_CHILD, 0, 25, CRect.right, ToolBarHeight, hMainHeader, NULL, NULL, NULL);
        ShowWindow(hToolBarClientes, SW_HIDE);
        CreateToolsClientes();
}

/*
        CreateToolsClientes. Esta funcion crea las herramientas para manejar la tabla de inventario. Estas herramientas son
        Crear cliente, eliminar cliente y modificar cliente. al hacer click en Nuevo Cliente se crea un formulario en el que se debe de introducir
        Los datos del Cliente. al precionar modificar producto mientras se tiene una fila seleccionada de la tabla se crea otro formulario en el que se modificaran los 
        datos actuales del Cliente. Eliminar Cliente elimina la fila seleccionada

        Parametros Ninguno

        Return void
*/

void CreateToolsClientes()
{
        hNuevoCliente = CreateWindowA("TOOL", "Nuevo Cliente", WS_VISIBLE | WS_CHILD, 20, 0, 100, 75, hToolBarClientes, TOOLBAR_IMAGE_NEW_CLIENTE, NULL, NULL);
        hModificarCliente = CreateWindowA("TOOL", "Modificar Cliente", WS_VISIBLE | WS_CHILD, 120, 0, 100, 75, hToolBarClientes, TOOLBAR_IMAGE_MODIFY_CLIENTE, NULL, NULL);
        hEliminarCliente = CreateWindowA("TOOL", "Eliminar Cliente", WS_VISIBLE | WS_CHILD, 220, 0, 100, 75, hToolBarClientes, TOOLBAR_IMAGE_DELETE_CLIENTE, NULL, NULL);
}



/*
CreateToolBarVentas. Esta funcion crea el contenedor para las herramientas, este contenedor seria la barra de tareas, al finalizar la funcion llama a la funcion
CreateToolsVentas para crear las herramientas para manejar el formulario y tabla de ventas.

Parametros Ninguno

Return void
*/

void CreateToolBarVentas()
{
        hToolBarVentas = CreateWindowA("TOOLBAR_CONTAINER", NULL, WS_VISIBLE | WS_CHILD, 0, 25, CRect.right, ToolBarHeight, hMainHeader, NULL, NULL, NULL);
        CreateToolsVentas();
}

/*
        CreateToolsVentas. Esta funcion crea las herramientas para manejar el formulario de ventas y la tabla de ventas. Estas herramientas son
        Nueva Venta, Historial de Ventas y Ver Venta. Al hacer click en nueva venta se crea un formulario donde se podra introducir las nuevas ventas,
        si se preciona Historial de Ventas ese anterior formulario se cerrara y se abrira una tabla mostrando todas las ventas realizadas.
        Si se tiene precionado una fila en la tabla de ventas y se preciona Ver Venta entonces se mostrara en pantalla otra ventana mostrando el contenido de la venta

        Parametros Ninguno

        Return void
*/

void CreateToolsVentas()
{
        hNuevaVenta = CreateWindowA("TOOL", "Nueva Venta", WS_VISIBLE | WS_CHILD, 20, 0, 80, 75, hToolBarVentas, TOOLBAR_IMAGE_NEW_VENTAS, NULL, NULL);
        CreateWindowA("SEPARATOR", NULL, WS_CHILD | WS_VISIBLE, 110, 10, 1, ToolBarHeight - 20, hToolBarVentas, TOOLBAR_IMAGE_HISTORIAL_VENTAS, NULL, NULL);
        hToolHistorialVenta = CreateWindowA("TOOL", "Historial de Ventas", WS_VISIBLE | WS_CHILD, 120, 0, 90, 75, hToolBarVentas, TOOLBAR_IMAGE_HISTORIAL_VENTAS, NULL, NULL);
        hToolVerVenta = CreateWindowA("TOOL", "Ver Venta", WS_VISIBLE | WS_CHILD, 210, 0, 90, 75, hToolBarVentas, TOOLBAR_IMAGE_VER_VENTAS, NULL, NULL);
        // hModificarVenta = CreateWindowA("TOOL", "Modificar Venta", WS_VISIBLE | WS_CHILD, 300, 0, 90, 75, hToolBarVentas, TOOLBAR_IMAGE_MODIFY_VENTAS, NULL, NULL);
        // hEliminarVenta = CreateWindowA("TOOL", "Eliminar Venta", WS_VISIBLE | WS_CHILD, 390, 0, 90, 75, hToolBarVentas, TOOLBAR_IMAGE_DELETE_VENTAS, NULL, NULL);
}

/*
        CreateBodyClienteMainWindow(). Crea el contenedor de la tabla de clientes, este contenedor abarca la pantalla completa
        Esta funcion tambien hace el trabajo de buscar y almacenar los datos de los clientes actuales en clientes.txt y guardarlos en los array dataClient y hTableCliente.
        Estas dos variable son punteros que su tamaño se modificara con realloc y este dependera de la cantidad de clientes que haya en clientes.txt

        Esta funcion llama a otras dos funciones las cuales son CreateTableClient y CreateHeaderTableClient

        Parametros Ninguno

        Return void
*/

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

/*
CreateRowTableClient. Esta funcion crea una fila en la tabla, en estas se mostraran los datos del cliente

Parametros
        STRUCTCLIENTESDATA data = Este parametro es un registro donde estan almacenados los datos del cliente (Este parametro ya no se usa, quedo obsoleto)
        int i = El numero de fila actual, este parametro se introduce en la fila y se usa para identificar las filas.

Return void

*/

void CreateRowTableClient(STRUCTCLIENTESDATA data, int i)
{
        RECT rect;
        GetClientRect(hBodyClientes, &rect);
        int width = cxColumnTable * nColumnsTable;
        hTableCliente[i].container = CreateWindowA("BODY_ROW_CELL", NULL, WS_CHILD | WS_VISIBLE, 0, yTabla, width, ROW_TABLE_HEIGHT, hTableContainer, i, NULL, NULL);
        yTabla += 20;
}

/*
CreateTableClient. Esta funcion crea la tabla donde se veran los clientes almacenados en clientes.txt. Esta funcion contiene un bucle en el que llama a 
la funcion CreateRowTableClient la cual esta encargada de crear las filas de la tabla.

Parametros Ninguno

Return void
*/

void CreateTableClient()
{
        RECT rectBodyClientes;
        RECT rectMainWindow;

        GetClientRect(hBodyClientes, &rectBodyClientes);
        GetClientRect(hMain, &rectMainWindow);

        DWORD sTableContainer;

        nColumnsTable = 5;
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

/*
CreateHeaderTableClient. Se crea el header que identifica a las columnas de la tabla
Parametros Ninguno
Return void
*/

void CreateHeaderTableClient()
{
        RECT rect;
        GetClientRect(hBodyClientes, &rect);
        int width = cxColumnTable;

        HWND temp = CreateWindowA("BODY_ROW_CELL", NULL, WS_CHILD | WS_VISIBLE, 0, 0, cxColumnTable * nColumnsTable, ROW_TABLE_HEIGHT, hBodyClientes, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Nombre", WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Cedula", WS_VISIBLE | WS_CHILD, (width), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Telefono", WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Naturaleza", WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Fecha", WS_VISIBLE | WS_CHILD, (width * 4), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

/*
Carga La image add.bmp para su uso en el componente tool. Esta funcion se usa en winProc.c
*/

void loadImagesAdd()
{
        hImageAdd = (HBITMAP)LoadImageA(NULL, "img\\add.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}


/*
Carga La image modificar.bmp para su uso en el componente tool. Esta funcion se usa en winProc.c
*/

void loadImagesModify()
{
        hImageModify = (HBITMAP)LoadImageA(NULL, "img\\modificar.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}


/*
Carga La image delete.bmp para su uso en el componente tool. Esta funcion se usa en winProc.c
*/

void loadImagesDelete()
{
        hImageDelete = (HBITMAP)LoadImageA(NULL, "img\\delete.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}

/*
Carga La image lista.bmp para su uso en el componente tool. Esta funcion se usa en winProc.c
*/

void loadImagesHistorial()
{
        hImageHistorial = (HBITMAP)LoadImageA(NULL, "img\\lista.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}


/*
Carga La image ver.bmp para su uso en el componente tool. Esta funcion se usa en winProc.c
*/

void loadImagesView()
{
        hImageVer = (HBITMAP)LoadImageA(NULL, "img\\ver.bmp", IMAGE_BITMAP, 30, 30, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
}


/*
CreateFormClient. Esta funcion crea un formulario que se utiliza para crear y modificar un cliente. Son tres tipos, nuevoCliente, nuevoCliente fuera de la pestaña clientes
y modificar clientes. La diferencia entre los nuevos clientes es el boton para registrar los cambios.

Parametros
        BOOL newClient = Este marca si es un nuevo cliente, si es TRUE se mostrara el formulario para nuevo cliente
        UINT cliente = Este marca la pocision del cliente en el array dataClient
        BOOL ventas = este diferencia el lugar donde se llamo a esta funcion, para poder mostrar un formulario diferente en pantalla

return void
*/

void CreateFormClient(BOOL newClient, UINT client, BOOL ventas)
{
        if (newClient == TRUE && ventas != TRUE)
        {
                int CContainerWidth = 500;
                int CContainerHeight = 250;

                WINDOWPOS containerPos;
                WINDOWPOS namePos;
                WINDOWPOS zonePos;
                WINDOWPOS dniPos;
                WINDOWPOS phonePos;
                WINDOWPOS tdpPos;
                WINDOWPOS buttonRegisterPos;
                WINDOWPOS buttonClosePos;

                SetWindowPosition(&containerPos, WWidth / 2 - (CContainerWidth / 2), WHeight / 2 - (CContainerHeight / 2), CContainerWidth, CContainerHeight);

                SetWindowPosition(&namePos, CContainerWidth * 0.08, 20, CContainerWidth * 0.35, 18);

                SetWindowPosition(&tdpPos, CContainerWidth * 0.50, 20, 20, 18);
                SetWindowPosition(&dniPos, CContainerWidth * 0.55, 20, CContainerWidth * 0.30, 18);

                SetWindowPosition(&phonePos, CContainerWidth * 0.08, 90, CContainerWidth * 0.35, 18);

                SetWindowPosition(&zonePos, CContainerWidth * 0.50, 90, CContainerWidth * 0.37, 18);

                SetWindowPosition(&buttonRegisterPos, CContainerWidth * 0.35, 160, 100, 30);
                SetWindowPosition(&buttonClosePos, CContainerWidth * 0.60, 160, 100, 30);

                hFormClient.container = CreateWindowA("CLIENT_WINDOW", "Nuevo Cliente", WS_VISIBLE | WS_OVERLAPPEDWINDOW, containerPos.x, containerPos.y, containerPos.cx, containerPos.cy, NULL, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Name:", WS_VISIBLE | WS_CHILD, namePos.x, namePos.y, 45, namePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.name = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, namePos.x, namePos.y + 25, namePos.cx, namePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Cedula:", WS_VISIBLE | WS_CHILD, tdpPos.x, dniPos.y, 55, dniPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.TdP = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_CENTER, tdpPos.x, tdpPos.y + 25, tdpPos.cx, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);
                CreateWindowA("S_TRANSPARENT", "-", WS_CHILD | WS_VISIBLE, tdpPos.x + tdpPos.cx + 5, tdpPos.y + 25, 10, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.dni = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, dniPos.x + 8, dniPos.y + 25, dniPos.cx, dniPos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Phone:", WS_VISIBLE | WS_CHILD, phonePos.x, phonePos.y, 50, phonePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.phone = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, phonePos.x, phonePos.y + 25, phonePos.cx, phonePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Direccion:", WS_VISIBLE | WS_CHILD, zonePos.x, zonePos.y, 70, zonePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.zone = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, zonePos.x, zonePos.y + 25, zonePos.cx, zonePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("BUTTON_P", "Registrar", WS_VISIBLE | WS_CHILD, buttonRegisterPos.x, buttonRegisterPos.y, buttonRegisterPos.cx, buttonRegisterPos.cy, hFormClient.container, CREATE_CLIENT_FORM, NULL, NULL);
                CreateWindowA("BUTTON_P", "Cancelar", WS_VISIBLE | WS_CHILD, buttonClosePos.x, buttonClosePos.y, buttonClosePos.cx, buttonClosePos.cy, hFormClient.container, CLOSE_CLIENT_FORM, NULL, NULL);
        }
        else if (newClient == TRUE && ventas == TRUE)
        {
                int CContainerWidth = 500;
                int CContainerHeight = 250;

                WINDOWPOS containerPos;
                WINDOWPOS namePos;
                WINDOWPOS zonePos;
                WINDOWPOS dniPos;
                WINDOWPOS phonePos;
                WINDOWPOS tdpPos;
                WINDOWPOS buttonRegisterPos;
                WINDOWPOS buttonClosePos;

                SetWindowPosition(&containerPos, WWidth / 2 - (CContainerWidth / 2), WHeight / 2 - (CContainerHeight / 2), CContainerWidth, CContainerHeight);

                SetWindowPosition(&namePos, CContainerWidth * 0.08, 20, CContainerWidth * 0.35, 18);

                SetWindowPosition(&tdpPos, CContainerWidth * 0.50, 20, 20, 18);
                SetWindowPosition(&dniPos, CContainerWidth * 0.55, 20, CContainerWidth * 0.30, 18);

                SetWindowPosition(&phonePos, CContainerWidth * 0.08, 90, CContainerWidth * 0.35, 18);

                SetWindowPosition(&zonePos, CContainerWidth * 0.50, 90, CContainerWidth * 0.37, 18);

                SetWindowPosition(&buttonRegisterPos, CContainerWidth * 0.35, 160, 100, 30);
                SetWindowPosition(&buttonClosePos, CContainerWidth * 0.60, 160, 100, 30);

                hFormClient.container = CreateWindowA("CLIENT_WINDOW", "Nuevo Cliente", WS_VISIBLE | WS_OVERLAPPEDWINDOW, containerPos.x, containerPos.y, containerPos.cx, containerPos.cy, NULL, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Name:", WS_VISIBLE | WS_CHILD, namePos.x, namePos.y, 45, namePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.name = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, namePos.x, namePos.y + 25, namePos.cx, namePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Cedula:", WS_VISIBLE | WS_CHILD, tdpPos.x, dniPos.y, 55, dniPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.TdP = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_CENTER, tdpPos.x, tdpPos.y + 25, tdpPos.cx, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);
                CreateWindowA("S_TRANSPARENT", "-", WS_CHILD | WS_VISIBLE, tdpPos.x + tdpPos.cx + 5, tdpPos.y + 25, 10, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.dni = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, dniPos.x + 8, dniPos.y + 25, dniPos.cx, dniPos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Phone:", WS_VISIBLE | WS_CHILD, phonePos.x, phonePos.y, 50, phonePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.phone = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, phonePos.x, phonePos.y + 25, phonePos.cx, phonePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Direccion:", WS_VISIBLE | WS_CHILD, zonePos.x, zonePos.y, 70, zonePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.zone = CreateWindowA("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, zonePos.x, zonePos.y + 25, zonePos.cx, zonePos.cy, hFormClient.container, NULL, NULL, NULL);

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
                WINDOWPOS zonePos;
                WINDOWPOS dniPos;
                WINDOWPOS phonePos;
                WINDOWPOS tdpPos;
                WINDOWPOS buttonRegisterPos;
                WINDOWPOS buttonClosePos;

                SetWindowPosition(&containerPos, WWidth / 2 - (CContainerWidth / 2), WHeight / 2 - (CContainerHeight / 2), CContainerWidth, CContainerHeight);

                SetWindowPosition(&namePos, CContainerWidth * 0.08, 20, CContainerWidth * 0.35, 18);

                SetWindowPosition(&tdpPos, CContainerWidth * 0.50, 20, 20, 18);
                SetWindowPosition(&dniPos, CContainerWidth * 0.55, 20, CContainerWidth * 0.30, 18);

                SetWindowPosition(&phonePos, CContainerWidth * 0.08, 90, CContainerWidth * 0.35, 18);

                SetWindowPosition(&zonePos, CContainerWidth * 0.50, 90, CContainerWidth * 0.37, 18);

                SetWindowPosition(&buttonRegisterPos, CContainerWidth * 0.35, 160, 100, 30);
                SetWindowPosition(&buttonClosePos, CContainerWidth * 0.60, 160, 100, 30);

                hFormClient.container = CreateWindowA("CLIENT_WINDOW", "Nuevo Cliente", WS_VISIBLE | WS_OVERLAPPEDWINDOW, containerPos.x, containerPos.y, containerPos.cx, containerPos.cy, NULL, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Name:", WS_VISIBLE | WS_CHILD, namePos.x, namePos.y, 45, namePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.name = CreateWindowA("EDIT", currentDataC.name, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, namePos.x, namePos.y + 25, namePos.cx, namePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Cedula:", WS_VISIBLE | WS_CHILD, tdpPos.x, dniPos.y, 55, dniPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.TdP = CreateWindowA("EDIT", currentDataC.TdP, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_CENTER, tdpPos.x, tdpPos.y + 25, tdpPos.cx, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);
                CreateWindowA("S_TRANSPARENT", "-", WS_CHILD | WS_VISIBLE, tdpPos.x + tdpPos.cx + 5, tdpPos.y + 25, 10, tdpPos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.dni = CreateWindowA("EDIT", currentDataC.dni, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, dniPos.x + 8, dniPos.y + 25, dniPos.cx, dniPos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("STATIC", "Phone:", WS_VISIBLE | WS_CHILD, phonePos.x, phonePos.y, 50, phonePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.phone = CreateWindowA("EDIT", currentDataC.phone, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, phonePos.x, phonePos.y + 25, phonePos.cx, phonePos.cy, hFormClient.container, NULL, NULL, NULL);

                int rowFactura = search_invoice_id_client(currentDataC.ID);
                char direccion[100];
                get_zone_invoice(rowFactura, direccion);

                CreateWindowA("STATIC", "Direccion:", WS_VISIBLE | WS_CHILD, zonePos.x, zonePos.y, 70, zonePos.cy, hFormClient.container, NULL, NULL, NULL);
                hFormClient.zone = CreateWindowA("EDIT", direccion, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, zonePos.x, zonePos.y + 25, zonePos.cx, zonePos.cy, hFormClient.container, NULL, NULL, NULL);

                CreateWindowA("BUTTON_P", "Registrar", WS_VISIBLE | WS_CHILD, buttonRegisterPos.x, buttonRegisterPos.y, buttonRegisterPos.cx, buttonRegisterPos.cy, hFormClient.container, MODIFY_CLIENT_FORM, NULL, NULL);
                CreateWindowA("BUTTON_P", "Cancelar", WS_VISIBLE | WS_CHILD, buttonClosePos.x, buttonClosePos.y, buttonClosePos.cx, buttonClosePos.cy, hFormClient.container, CLOSE_CLIENT_FORM, NULL, NULL);
        }
}

/*
CreateFormVentas. Crea el formulario de ventas, este se divide en tres partes, el cliente, los botones para registrar y 
agregar productos a la venta, y la tabla que muestra los productos que se compraran. Al finalizar la funcion llama a la funcion CreateTableListOfProducts.

Paramentros Ninguno

Return void

*/

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

/*
CreateTableListOfProducts. Crea la lista de productos que se van a vender

Parametros
        int x = Esta es la posicion en x del componente
        int y = Esta es la posicion en y del componente
        int cx = Esta es la anchura del componente
        int cy = Esta es la altura del componente

return void
*/

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

/*
CreateHeaderTableCurrentProducts. Crea el header que identificara las columnas de las tablas

Parametros
        HWND hWnd = Pasa el identificador del componente que servira como contenedor

Return void
*/

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

/*
CreateFooterTotalVentas. Crea un footer donde se mostrara el precio total de la venta
Parametros
        HWND hWnd = Identificador del contenedor
        int x = posicion en x
        int y = posicion en y
        int cx = ancho del footer
*/

void CreateFooterTotalVentas(HWND hWnd, int x, int y, int cx)
{
        RECT rect;
        GetClientRect(hWnd, &rect);

        HWND temp = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE, x, y, cx * 2, ROW_TABLE_HEIGHT, hWnd, NULL, NULL, NULL);
        CreateWindowA("CELL", "Total:", WS_VISIBLE | WS_CHILD, 0, 0, cx, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        hPrecioTotal = CreateWindowA("HEADER_CELL", NULL, WS_VISIBLE | WS_CHILD, cx, 0, cx, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);

        int position = GetMenu(hTableCurrentRow);

        STRUCTVENTASDATA data = dataVentas[position];
        int cantidadDeProductos = get_amounts_products_venta(data.ID);
        int row = search_venta_ID_venta(data.ID);
        int lenColProductos = get_len_col_ventas(row, 2);

        char productos[lenColProductos + 4];

        get_productos_venta(row, productos);

        char subProducto[50];
        x = 0;
        int w = 0;
        char comprobacionDeCaracter[2];

        STRUCTCURRENTPRODUCTOSDATA productosVenta[cantidadDeProductos + 1];
        float precioTotal = 0;

        for (int i = 0; i < lenColProductos; i++)
        {
                if (productos[i] != '/' && productos[i] != '\0')
                {
                        subProducto[x] = productos[i];
                }
                else
                {
                        subProducto[x] = '\0';

                        // Estas variable se encargan de marcar cuando termina ID, precio y descuento
                        int fID;
                        int fCantidad;
                        int fDescuento;

                        for (int j = 0; j < x + 1; j++)
                        {
                                if (subProducto[j] == '=')
                                        fID = j;
                                if (subProducto[j] == '?')
                                        fCantidad = j;
                                if (subProducto[j] == '\0')
                                        fDescuento = j;
                        }

                        char amount[20];

                        substr(productosVenta[w].ID, subProducto, 0, fID);
                        substr(amount, subProducto, fID + 1, fCantidad);
                        substr(productosVenta[w].discount, subProducto, fCantidad + 1, fDescuento);

                        productosVenta[w].amount = atoi(amount);
                        char precioProducto[100];
                        get_price_product(search_product(productosVenta[w].ID), precioProducto);

                        precioTotal += (float)(productosVenta[w].amount * (atoi(precioProducto) - (atoi(precioProducto) * (atoi(productosVenta[w].discount) / 100))));

                        x = -1;
                        w++;
                }
                x++;
        }

        precioTotal *= 1.16;

        char precioFactura[100];
        sprintf(precioFactura, "%.2f Bs", precioTotal);

        SetWindowTextA(hPrecioTotal, precioFactura);
}

/*
CreateHeaderTableProductsVentas. Crea una fila en las que sus columnas sirven como guia para la tabla de productos que se encuentra en la ventana 
facturas o al inspeccionar la venta

Parametros 
        HWND hWnd = Identificador del contenedor
        int x = posicion en x
        int y = posicion en y
        int cx = ancho del componente

return void
*/

void CreateHeaderTableProductsVentas(HWND hWnd, int x, int y, int cx)
{
        RECT rect;
        GetClientRect(hWnd, &rect);
        int width = cx;

        HWND temp = CreateWindowA("BODY_ROW_CELL_HISTORIALVENTAS", NULL, WS_CHILD | WS_VISIBLE, x + 1, y, width * 4, ROW_TABLE_HEIGHT, hWnd, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Producto", WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Cantidad", WS_VISIBLE | WS_CHILD, width, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Descuento", WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Precio", WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

/*
CreateWindowFactura. Crea la ventana factura, esta se encarga de mostrar la factura de una venta. esta contiene rif de la empresa y direccion.
Productos comprados, el total, nombre, domicilio y cedula del cliente, entre otros

parametros ninguno

return void
*/

void CreateWindowFactura()
{
        int cxWindow = 500;
        int cyWindow = 500;
        int xWindow = (WWidth / 4) - (cxWindow / 2);
        int yWindow = (WHeight / 2) - (cyWindow / 2);

        hFacturaWindow = CreateWindowA("CLIENT_FACTURA", "Factura", WS_VISIBLE | WS_OVERLAPPEDWINDOW, xWindow, yWindow, cxWindow, cyWindow, NULL, NULL, NULL, NULL);
        int position = GetMenu(hTableCurrentRow);

        STRUCTVENTASDATA data = dataVentas[position];

        int rowFactura = search_invoice_id_client(data.ID_cliente);

        char nombre[100];
        char direccionCliente[100];
        char dniCliente[100];

        int margin_left = 20;
        int margin_top = 10;
        cxWindow -= 15;

        char text[200];
        CreateWindowA("S_TRANSPARENT", "SENIAT", WS_CHILD | WS_VISIBLE, cxWindow / 2 - 50 + margin_left, margin_top, 100, 20, hFacturaWindow, NULL, NULL, NULL);

        char direccion_company[100];
        char rif_company[100];

        get_direction_company_invoice(rowFactura, direccion_company);
        get_rif_company_invoice(rowFactura, rif_company);

        sprintf(text, "%s. J-%s", direccion_company, rif_company);
        CreateWindowA("S_TRANSPARENT", text, WS_CHILD | WS_VISIBLE, (cxWindow / 2) - (((strlen(text) + 1) * 7) / 2), margin_top + 20, (strlen(text) + 1) * 7, 20, hFacturaWindow, SS_CENTER, NULL, NULL);

        CreateWindowA("SEPARATOR", NULL, WS_CHILD | WS_VISIBLE, margin_left, margin_top + 60, cxWindow - (margin_left * 2), 1, hFacturaWindow, NULL, NULL, NULL);

        int datosCliente = margin_top + 60;
        int rowCliente = search_clients(data.ID_cliente);
        get_name_clients(rowCliente, nombre);
        get_dni_clients(rowCliente, dniCliente);


        sprintf(text, "Nombre: %s", nombre);
        get_zone_invoice(rowFactura, direccionCliente);

        CreateWindowA("S_TRANSPARENT", text, WS_CHILD | WS_VISIBLE, margin_left, datosCliente + 20, strlen(text) * 8, 20, hFacturaWindow, NULL, NULL, NULL);
        
        sprintf(text, "Direccion: %s", direccionCliente);
        CreateWindowA("S_TRANSPARENT", text, WS_CHILD | WS_VISIBLE, margin_left, datosCliente + 40, strlen(text) * 8, 20, hFacturaWindow, NULL, NULL, NULL);
        
        sprintf(text, "Cedula: %s", dniCliente);
        CreateWindowA("S_TRANSPARENT", text, WS_CHILD | WS_VISIBLE, margin_left, datosCliente + 60, strlen(text) * 8, 20, hFacturaWindow, NULL, NULL, NULL);

        CreateWindowA("SEPARATOR", NULL, WS_CHILD | WS_VISIBLE, margin_left, datosCliente + 100, cxWindow - (margin_left * 2), 1, hFacturaWindow, NULL, NULL, NULL);

        int datosProducto = datosCliente + 100;
        int cantidadDeProductos = get_amounts_products_venta(data.ID);
        int cyTable = cantidadDeProductos * ROW_TABLE_HEIGHT;

        int yFooter = cyTable + datosProducto + 30;

        CreateWindowA("DIV", NULL, WS_CHILD | WS_VISIBLE, margin_left, datosProducto + 30, cxWindow - (margin_left * 2), cyTable, hFacturaWindow, LIST_PRODUCTS_VENTAS, NULL, NULL);
        CreateHeaderTableProductsVentas(hFacturaWindow, margin_left, datosProducto + 10, (cxWindow - (margin_left * 2)) / 4);
        CreateFooterTotalVentas(hFacturaWindow, margin_left + (cxColumnTableProductsVentas * 2), yFooter, cxColumnTableProductsVentas);
}

/*
Esta funcion crea una ventana que muestra los datos del cliente, los productos comprados y el precio, ademas de eso tambien contiene un boton que al hacer click
llama a la funcion CreateWindowFactura

Parametros ninguno

return void
*/

void CreateWindowViewVenta()
{
        int cxWindow = 500;
        int cyWindow = 620;
        int xWindow = (WWidth / 2) - (cxWindow / 2);
        int yWindow = (WHeight / 2) - (cyWindow / 2);
        hWindowViewVenta = CreateWindowA("CLIENT_WINDOW", "Datos Venta", WS_VISIBLE | WS_OVERLAPPEDWINDOW, xWindow, yWindow, cxWindow, cyWindow, NULL, NULL, NULL, NULL);

        STRUCTVENTASDATA data = dataVentas[(int)GetMenu(hTableCurrentRow)];

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

        int cxTable = cxWindow - (margin_left * 2);
        int cyTable = cyWindow - margin_top - 160;
        int yTable = margin_top + 80;

        CreateWindowA("DIV", NULL, WS_VISIBLE | WS_CHILD, margin_left, yTable, cxTable, cyTable, hWindowViewVenta, LIST_PRODUCTS_VENTAS, NULL, NULL);

        int yFooter = cyTable + yTable;

        CreateHeaderTableProductsVentas(hWindowViewVenta, margin_left, yTable - 20, cxColumnTableProductsVentas);
        CreateFooterTotalVentas(hWindowViewVenta, margin_left + (cxColumnTableProductsVentas * 2), yFooter, cxColumnTableProductsVentas);
        CreateWindowA("BUTTON_P", "Ver Factura", WS_VISIBLE | WS_CHILD | WS_BORDER, margin_left, yFooter + 5, 150, 30, hWindowViewVenta, VIEW_FACTURA, NULL, NULL);
}

/*
CreateHeaderTableVentas. Crea un header que sirve como guia para las columnas de la table de ventas

parametros
        HWND hWnd = identificador del contenedor
        int x = posicion en x
        int y = posicion en y
*/

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

/*
CreateTableListOfVentas. Crea la tabla de ventas, en esta se mostraran todas las ventas realizadas

parametros
        HWND hWnd = identificador del contenedor
        int xTable = posicion x respecto al contenedor
        int yTable = posicion y respecto al contenedor
        int cxTable = ancho de la tabla
        int cyTable = altura de la tabla
*/

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


/*
GetDataTableListofVentas. Esta funcion se utiliza para crear de nuevo la lista de ventas

parametros
        int cx, anchura del componente
        int cy, altura del componente
*/

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

/*
CreateBodyVentasMainWindow. Esta funcion crea la tabla de ventas.

parametros
        BOOL newSell = este se encarga de identificar si se esta creando el formulario de ventas o el historial de ventas, si es TRUE se crea el formulario de ventas
        si no lo es se crea la tabla de ventas
*/

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

/*
CreateWindowProducts. Esta funcion crea la ventana para elegir el producto a comprar.

parametros ninguno

return void
*/

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

/*
        CreateFormProduct. Crea el formulario para introducir un nuevo producto o para modificar uno ya existente.

        parametros
                BOOL newProduct = si es TRUE se creara un formulario vacio para poder crear un nuevo producto, si es FALSE se creara el formulario con 
                los datos del producto a modificar
                UINT product = Indica la posicion del producto en el array dataProducts
*/

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

/*
CreateBodyProductos. Crea el contenedor de la tabla de productos, tambien tiene el trabajo de almacenar en el array dataProductos los datos del producto

Parametros Ninguno

Return void
*/

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

/*
CreateHeaderWindowProducts. se encarga de crear una fila para poder identificar las columnas dde la tabla de productos

Parametros
        HWND hWnd = Identificador del contenedor
        int cxHeader = Ancho del Header
        int cyHeader = Alto del Header

return void
*/

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


/*
CreateTableProducts. Crea la tabla de productos.

Parametros
        HWND hWnd = el identificador del contenedor
        int len = la cantidad de productos
        int x = posicion en x respecto al contenedor
        int y = posicion en y respecto al contenedor
        int cx = Ancho de la tabla
        int cy = alto de la tabla
*/

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

/*
CreateHeaderTableProducts. Crea El  header para la tabla de productos. este header sirve para identificar las columnas de la tabla

parametros
        HWND hWnd = identificador del contenedor
        int y = posicion en y respecto al contenedor

return voids=
*/

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


/*
CreateRowTableClientPortable. Se encarga de crear filas en el contenedor. esta funcion fue echa para la ventana para elegir clientes

Parametros
        HWND hWnd = identificador del contenedor
        int width = anchura del componente
*/

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

/*
CreateTableListOfClients. Crea la lista de clientes, esta funcion esta hecha para la ventana de elegir clientes

parametros
        HWND hWnd = identificador del contenedor
        int x = posicion en x
        int y = posicion en y
        int cxTable = Ancho de la tabla
        int cyTable = Alto de la tabla

return void
*/

void CreateTableListOfClients(HWND hWnd, int x, int y, int cxTable, int cyTable)
{
        nColumnsTable = 5;

        DWORD sTableContainer;

        if (rows_clients_table > cyTable / ROW_TABLE_HEIGHT)
                sTableContainer = WS_VISIBLE | WS_CHILD | WS_VSCROLL;
        else
        {
                sTableContainer = WS_VISIBLE | WS_CHILD;
        }

        hTableContainer = CreateWindowExA(0, "DIV", NULL, sTableContainer, x, y, cxTable, cyTable, hWnd, LIST_CLIENTS, NULL, NULL);

        CreateRowTableClientPortable(hTableContainer, cxColumnTable * 5);
}

/*
CreateHeaderTableClients. Crear el header de la tabla de clientes, esta diseñada para la ventana de elegir clientes

parametros
        HWND hWnd = identificador del contenedor
        int y = posicion en y
*/

void CreateHeaderTableClients(HWND hWnd, int y)
{
        RECT rect;
        GetClientRect(hWnd, &rect);
        int width = cxColumnTable;

        HWND temp = CreateWindowA("BODY_ROW_CELL_PRODUCT", NULL, WS_CHILD | WS_VISIBLE, 0, y, width * 5, ROW_TABLE_HEIGHT, hWnd, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Nombre", WS_VISIBLE | WS_CHILD, 0, 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Cedula", WS_VISIBLE | WS_CHILD, (width), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Telefono", WS_VISIBLE | WS_CHILD, (width * 2), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Naturaleza", WS_VISIBLE | WS_CHILD, (width * 3), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
        CreateWindowA("HEADER_CELL", "Fecha", WS_VISIBLE | WS_CHILD, (width * 4), 0, width, ROW_TABLE_HEIGHT, temp, NULL, NULL, NULL);
}

/*
CreateHeaderClientsVentas. Crea el header de la ventana de seleccionar clientes, este header contiene distintos botones donde se podra crear un usuario, seleccionar un
usuario y cerrar la ventana

parametros
        HWND hWnd = identificador del contenedor
        int cxHeader = ancho del header
        int cyHeader = alto del header

return void
*/

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

/*
CreateWindowClients. Crea la ventana para seleccionar un cliente, esto es necesario para poder realizar una compra

parametros ninguno

return void
*/

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
        CreateTableListOfClients(hBodyClientes, 0, 80, cxWindow, cyWindow - 120);
        CreateHeaderTableClients(hBodyClientes, 60);
}