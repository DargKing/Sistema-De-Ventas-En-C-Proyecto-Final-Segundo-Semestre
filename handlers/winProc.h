#include <windows.h>

// Acciones del boton

#define CLOSE_APP -1
#define CLOSE_WINDOW 0
#define LOGIN_USER 1
#define SINGUP_USER 2
#define CLOSE_CLIENT_FORM 4

#define CREATE_CLIENT_FORM 5
#define MODIFY_CLIENT_FORM 6

#define WINDOW_PRODUCT_VENTAS 7
#define DELETE_PRODUCT_VENTAS 8
#define ADD_PRODUCT_VENTAS 9
#define CLOSE_WINDOW_PRODUCT_VENTAS 10
#define CLOSE_FORM_PRODUCT 11

#define ADD_PRODUCT_FORM 12
#define MODIFY_PRODUCT_FORM 13

#define NEW_VENTA 14
#define SELECT_CLIENT_VENTAS 15

#define CLOSE_WINDOW_CLIENTS_VENTAS 16
#define ADD_CLIENT_VENTAS 17
#define OPEN_FORM_CLIENTS_VENTAS 18
#define CREATE_CLIENT_FORM_VENTAS 19
#define VIEW_FACTURA 20
#define OPEN_SINGUP_USER_WINDOW 21


// Others

#define NAV_INVENTARIO 1
#define NAV_CLIENTES 2
#define NAV_VENTAS 3

#define LIST_CURRENT_PRODUCTS 1
#define LIST_PRODUCTS 2
#define LIST_CLIENTS 3
#define LIST_VENTAS 4 
#define LIST_PRODUCTS_VENTAS 5

#define TOOLBAR_IMAGE_NEW_INVENTARIO 1
#define TOOLBAR_IMAGE_DELETE_INVENTARIO 2
#define TOOLBAR_IMAGE_MODIFY_INVENTARIO 3

#define TOOLBAR_IMAGE_NEW_CLIENTE 4
#define TOOLBAR_IMAGE_DELETE_CLIENTE 5
#define TOOLBAR_IMAGE_MODIFY_CLIENTE 6

#define TOOLBAR_IMAGE_NEW_VENTAS 7
#define TOOLBAR_IMAGE_DELETE_VENTAS 8
#define TOOLBAR_IMAGE_MODIFY_VENTAS 9
#define TOOLBAR_IMAGE_HISTORIAL_VENTAS 10
#define TOOLBAR_IMAGE_VER_VENTAS 11

int First;
int yTabla;
int rows_clients_table;
int rows_product_table;
int rows_ventas_table;
int rows_currentProduct_table;

HWND hAlto, hAncho;

// Headers
HWND hMainHeader, hMainNav, hToolBarInventario, hToolBarClientes, hToolBarVentas;

// Body
HWND hBody, hBodyInventario, hBodyClientes, hBodyVentas;

// ToolBar
HWND hNavActual, hToolBarActual;

// Ventanas
HWND hMain, hLogin, hSingUp;

// Edits
HWND hName, hPassword, hRifCompany, hDireccionCompany;

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
HWND hNuevaVenta, hEliminarVenta, hModificarVenta, hToolHistorialVenta, hToolVerVenta;
HWND hWindowViewVenta;
// Forms

typedef struct CLIENTESHWND
{
    HWND container;
    HWND name;
    HWND zone;
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
    char zone[100];
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
    char discount[20];
    char stock[20];
    char date[20];
    char category[100];
} STRUCTPRODUCTOSDATA;

typedef struct VENTASDATA
{
    char ID[20];
    char ID_cliente[30];
    char discount[20];
    char productos[1000];
    char date[20];
} STRUCTVENTASDATA;

typedef struct PRODUCTOSHWND
{
    HWND container;
    HWND name;
    HWND price;
    HWND discount;
    HWND stock;
    HWND date;
    HWND category;
} STRUCTPRODUCTOSHWND;

typedef struct CURRENTPRODUCTOSDATA
{
    char ID[20];
    char name[100];
    char price[20];
    char discount[20];
    int amount;
    char category[100];
} STRUCTCURRENTPRODUCTOSDATA;

// User

typedef struct USERDATA{
    char ID[20];
    char username[100];
    char range[100];
    char password[100];
    char rif_company[100];
    char direccion[100];
} STRUCTUSERDATA;
STRUCTUSERDATA currentUser;

// Tabla


STRUCTCLIENTESHWND *hTableCliente;
// HWND *hTableCliente;

HWND hTableCurrentRow;

STRUCTCLIENTESDATA *dataClient;

STRUCTVENTASDATA *dataVentas;
STRUCTPRODUCTOSDATA *dataProductos;
HWND *h_rows_product_table;
HWND hTableContainer;

HWND hScrollBar;

HWND hWindowProduct;

HWND hTableVentas;
HWND hPrecioTotal;
HWND hFacturaWindow;

HWND hTableProduct;
HWND hTableCurrentProduct;

STRUCTCLIENTESHWND hCurrentClientVentas;
STRUCTCLIENTESDATA CurrentClientVentas;
STRUCTCURRENTPRODUCTOSDATA *CurrentProducts;
HWND* h_rows_currentProduct_table;
HWND* h_rows_ventas_table;

// Form
STRUCTCLIENTESHWND hFormClient;
STRUCTCLIENTESDATA currentDataC;

STRUCTPRODUCTOSHWND hFormProduct;
STRUCTPRODUCTOSDATA currentDataP;

HWND hCurrentBody;

// Images
HBITMAP hImageModify, hImageAdd, hImageDelete, hImageHistorial, hImageVer;
HBITMAP hNuevoProductoImage, hEliminarProductoImage, hModificarProductoImage,
    hNuevoClienteImage, hModificarClienteImage, hEliminarClienteImage,
    hNuevaVentaImage, hModificarVentaImage,  hHistorialVentaImage, hEliminarVentaImage, hVerVentaImage;

/*

DivWindowProcedure. Este manejador se encarga de manejar las tablas de datos, ejemplo la tabla de clientes, ventas o productos.

Mensajes
        WM_CREATE = En este mensaje se usa para ajustar el tamaño de las columnas de la tabla
        WM_PAINT = Se usa para pintar correctamente la ventana cuando se mueva el scrollbar
        WM_SIZE = Durante este mensaje se inserta el scrollbar si es necesario
        WM_VSCROLL = Se usa para controlar el scrollbar

*/

LRESULT CALLBACK DivWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
WinProc. Este manejador es uno vacio, el cual se utiliza para clases sin proposito y que no necesitan nada especial

Mensajes
        WM_DESTROY = Destruye la ventana

*/


LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

/*
LoginWindowProcedure. Esta ventana se encarga de manejar la ventana Login, Sirve para la clase LOGIN

Message
        WM_COMMAND = Dependiendo de lo que contenga el parametro wp sucedera...:
                CLOSE_WINDOW = Destruye la ventana
        WM_DESTROY = Termina la ejecucion del programa
*/

LRESULT CALLBACK LoginWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
ClientWindowProcedure. Esta funcion es una vacia, sirve para manejar las ventanas que no son la principal

Message
        WM_DESTROY = Destruye la ventana
*/

LRESULT CALLBACK ClientWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
ClientFacturaWindowProcedure. Se encarga de manejar la ventana Factura. 

Message
        WM_COMMAND = Dependiendo de lo que contenga el parametro wp sucedera...:
                CLOSE_WINDOW = Cierra la ventana
        WM_DESTROY = Cierra la ventana
        WM_SIZE = Establece el ScrollBar si es necesario
        WM_VSCROLL = Maneja el scrollbar
*/

LRESULT CALLBACK ClientFacturaWindowProcedure(HWND, UINT, WPARAM, LPARAM);


/*
MainWindowProcedure. Controla la ventana principal, no hace nada ademas de cerrar la aplicacion en general

Message
        WM_COMMAND = Dependiendo de lo que contenga el parametro wp sucedera...:
                CLOSE_WINDOW = Cierra la ventana
        WM_DESTROY = Acaba la ejecucion del programa
*/

LRESULT CALLBACK MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
        MainHeaderWindowProcedure. Este es un manejador vacio, no hace nada sirve para la clase HEADER
*/

LRESULT CALLBACK MainHeaderWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
MainNavWindowProcedure. Maneja el contenedor del nav.

Message
        WM_DESTROY = Cierra la ventana
        WM_PAINT = Pinta la ventana
*/

LRESULT CALLBACK MainNavWindowProcedure(HWND, UINT, WPARAM, LPARAM);


/*
ToolBarWindowProcedure. Maneja los mensajes de la barra de navegacion. Cuando se preciona una de las pestañas se cierra lo que se esta 
viendo y se cambia a otra

Message 
        WM_COMMAND = Dependiendo de lo que especifique el parametro wp hara lo siguiente
                NAV_INVENTARIO = Cerrara el body actual y llamara a la funcion CreateBodyProductos
                NAV_CLIENTES = Cerrara el body actual y llamara a la funcion CreateBodyClienteMainWindow
                NAV_VENTAS = Cerrara el body actual y llamara a la funcion CreateBodyVentasMainWindow
        
        WM_DESTROY = Cierra la ventana
        WM_MOUSEHOVER = Se hace un poco mas oscuro el fondo
        WM_MOUSELEAVE = Se reestablece el fondo
        WM_MOUSEMOVE = Se trakea el mouse para saber en que lugar esta en todo momento
        WM_LBUTTONDOWN = Se envia un mensaje a WM_COMMAND con el parametro wp segun su menu
        WM_PAINT = Pinta la ventana
*/

LRESULT CALLBACK ToolBarWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
ToolWindowProcedure. Maneja la clase TOOL, esta clase es parecida a los botones ya que cumplen la misma funcion pero con diferente diseño

Message
        WM_DESTROY = Destruye la ventana
        WM_LBUTTONDOWN = Despendiendo de el Menu de la ventana hara una accion diferente al presionarse
                TOOLBAR_IMAGE_DELETE_CLIENTE = Elimina el cliente seleccionado
                TOOLBAR_IMAGE_MODIFY_CLIENTE = Abre el formulario para modificar clientes
                TOOLBAR_IMAGE_NEW_CLIENTE = Abre el formulario para Crear Clientes

                TOOLBAR_IMAGE_NEW_INVENTARIO = Abre el formulario para crear productos
                TOOLBAR_IMAGE_MODIFY_INVENTARIO - Abre el formulario para modificar productos
                TOOLBAR_IMAGE_DELETE_INVENTARIO = Elimina el producto Seleccionado

                TOOLBAR_IMAGE_NEW_VENTAS = Cierra la seccion de ventas actual y abre la de nueva venta
                TOOLBAR_IMAGE_HISTORIAL_VENTAS = Cierra la seccion de ventas actual y abre el historial de ventas
                TOOLBAR_IMAGE_VER_VENTAS = Abre una ventana mostrando a detalle la venta seleccionada
        
        WM_CREATE = Al crearse la ventana se crea una ventana clase STATIC la cual servira para mostrar una imagen
        WM_MOUSEMOVE = Trakea el mouse
        WM_MOUSEHOVER = Si el mouse esta encima de la ventana entonces cambia a un color amarillo verdoso
        WM_MOUSELEAVE = El color se reestablece
        WM_PAINT = Se pinta en pantalla la ventana, despues de eso a la ventana dentro de esta se le establece una imagen especificada por su menu

*/

LRESULT CALLBACK ToolWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
STransparentWindowProcedure. Este manejador se encarga de la clase S_TRANSPARENT, esta clase es como un STATIC normal pero transparente

Message
        WM_PAINT = Pinta el texto con un fondo transparente, si en el Menu se le especifica SS_CENTER se centrara el texto
        WM_DESTROY = Destruye la ventana
*/

LRESULT CALLBACK STransparentWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
ButtonsWindowProcedure. Este se encarga de manejar los mensajes de los botones, este es el manejador mas extenso y el que mas uso se le da.

Mensajes

WM_PAINT = Se encarga de pintar los botones, los colores de este dependera de lo que se obtenga de su GetMenu
        Color Azul  
                NEW_VENTA:
                SELECT_CLIENT_VENTAS:
                ADD_CLIENT_VENTAS:
                VIEW_FACTURA:
                OPEN_SINGUP_USER_WINDOW:
                SINGUP_USER:


        Color Verde
                LOGIN_USER:
                CREATE_CLIENT_FORM:
                ADD_PRODUCT_VENTAS:
                ADD_PRODUCT_FORM:
                MODIFY_CLIENT_FORM:
                WINDOW_PRODUCT_VENTAS:
                MODIFY_PRODUCT_FORM:
                OPEN_FORM_CLIENTS_VENTAS:
                CREATE_CLIENT_FORM_VENTAS:


        Color Rojo
                CLOSE_WINDOW:
                CLOSE_CLIENT_FORM:
                DELETE_PRODUCT_VENTAS:
                CLOSE_WINDOW_PRODUCT_VENTAS:
                CLOSE_FORM_PRODUCT:
                CLOSE_WINDOW_CLIENTS_VENTAS:

WM_MOUSEMOVE = Trakea el mouse para saber si este se esta moviendo en la ventana
WM_MOUSEHOVER = Si el mouse pasa por encima de la ventana cambia a un color mas oscuro
WM_LBUTTONDOWN = El color de la ventana se vuelve mas oscuro que el de WM_MOUSEHOVER
WM_LBUTTONUP = El color de la ventana se reestablece y manda WM_COMMAND a si mismo
WM_MOUSELEAVE = El color de la ventana se reinicia al del comienzo si detecta que el mouse salio del area del boton
WM_DESTROY = Se destruye la ventana

WM_COMMAND = Al recibir este comando dependiendo del contenido en el paramentro wp hara lo siguiente
        SINGUP_USER = Creara un nuevo usuario, ocultara la ventana singup y mostrara de neuvo la ventana login
        OPEN_SINGUP_USER_WINDOW = Crea la ventana SingUp y cierra la ventana login
        LOGIN_USER = Logeara el usuario y destruira la ventana login
        VIEW_FACTURA = Mostrara la factura de la venta seleccionada
        CREATE_CLIENT_FORM_VENTAS = Crea un nuevo cliente tomando los datos del formulario clientes
        OPEN_FORM_CLIENTS_VENTAS = Crea el formulario para crear un cliente fuera de la pestaña clientes
        ADD_CLIENT_VENTAS = Se establecera como el que comprara el producto en la pestaña ventas
        CLOSE_WINDOW_CLIENTS_VENTAS = Cierra la ventana para seleccionar clientes
        SELECT_CLIENT_VENTAS = Crea la ventana para seleccionar el cliente para la venta
        NEW_VENTA = Registra una nueva venta
        CLOSE_FORM_PRODUCT = Cierra el formulario de productos
        CLOSE_WINDOW_PRODUCT_VENTAS = Cierra la ventana donde se seleccionan los productos que se compraran
        WINDOW_PRODUCT_VENTAS = Crea la ventana donde se seleccionaran los productos a vender
        ADD_PRODUCT_VENTAS = Añade el producto a la tabla de productos a vender
        DELETE_PRODUCT_VENTAS = Elimina el producto de la tabla de productos a vender
        ADD_PRODUCT_FORM = Crea un producto a partir de los datos de el formulario para crear productos
        MODIFY_PRODUCT_FORM = Modifica el producto especificado
        CREATE_CLIENT_FORM = Crea un nuevo usuario a partir de los datos del formulario de clientes
        CLOSE_WINDOW = Termina la ejecucion del programa
        CLOSE_CLIENT_FORM = Cierra el formulario para agregar o modificar clientes
*/

LRESULT CALLBACK ButtonsWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonGreenWindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonRedWindowProcedure(HWND, UINT, WPARAM, LPARAM);


/*
BodyClientWindowProcedure. Este manejador se usa en la clase BODY, esta clase ya no se usa

Mensajes
        WM_LBUTTONDOWN = si hTableCurrentRow contiene un identificador este cambia su valor por NULL
        WM_DESTROY = Destruye la ventana
*/

LRESULT CALLBACK BodyClientWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
BodyRowCellWindowProcedure. Se encarga de manejar los mensajes de la clase BODY_ROW_CELL, esta clase seria la que se encarga de ser
las filas en la tabla de clientes

mensajes

WM_LBUTTONDOWN = Al precionar se pone su identificador en hTableCurrentRow
WM_PAINT = Se pinta las columnas junto con la informacion correspondiente de la fila, ademas si la ventana es igual a hTableCurrentRow
        entonces se le pintara un borde mas grueso
        WM_DESTROY = Se destruira la ventana
*/

LRESULT CALLBACK BodyRowCellWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
BodyRowCellProductWindowProcedure. Se encarga de manejar los mensajes de la clase BODY_ROW_CELL_PRODUCT, esta clase seria la que se encarga de ser
las filas en la tabla de Productos

mensajes

WM_LBUTTONDOWN = Al precionar se pone el identificador de su ventana en hTableCurrentRow
WM_PAINT = Se pinta las columnas junto con la informacion correspondiente de la fila, ademas si la ventana es igual a hTableCurrentRow
        entonces se le pintara un borde mas grueso
        WM_DESTROY = Se destruira la ventana
*/

LRESULT CALLBACK BodyRowCellProductWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
BodyRowCellCurrentProductWindowProcedure. Se encarga de manejar los mensajes de la clase BODY_ROW_CELL_CURRENTPRODUCT, 
esta clase seria la que se encarga de ser las filas en la tabla de productos a comprar en el formulario de ventas

mensajes

WM_LBUTTONDOWN = Al precionar se pone el identificador de su ventana en hTableCurrentRow
WM_PAINT = Se pinta las columnas junto con la informacion correspondiente de la fila, ademas si la ventana es igual a hTableCurrentRow
        entonces se le pintara un borde mas grueso
        WM_DESTROY = Se destruira la ventana
*/

LRESULT CALLBACK BodyRowCellCurrentProductWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
BodyRowCellHistorialVentasWindowProcedure. Se encarga de manejar los mensajes de la clase BODY_ROW_CELL_HISTORIALVENTAS, 
esta clase seria la que se encarga de ser las filas en la tabla de Ventas

Mensajes

WM_LBUTTONDOWN = Al precionar se pone el identificador de su ventana en hTableCurrentRow
WM_PAINT = Se pinta las columnas junto con la informacion correspondiente de la fila, ademas si la ventana es igual a hTableCurrentRow
        entonces se le pintara un borde mas grueso
WM_DESTROY = Se destruira la ventana
*/

LRESULT CALLBACK BodyRowCellHistorialVentasWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
CellWindowProcedure. Se encarga de manejar una unica celda, este se usa en la clase CELL y esta para celdas individuales

mensajes

WM_PAINT = Pinta el texto y los bordes
WM_DESTROY = Se destruira la ventana
*/

LRESULT CALLBACK CellWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*
HeaderCellWindowProcedure. Se encarga de manejar una unica celda, este se usa en la clase HEADER_CELL y esta para celdas individuales.
Su proposito esta en la creacion de headers para las tablas y asi identificar las columnas

mensajes

WM_PAINT = Pinta el texto y los bordes
WM_DESTROY = Se destruira la ventana
*/

LRESULT CALLBACK HeaderCellWindowProcedure(HWND, UINT, WPARAM, LPARAM);
