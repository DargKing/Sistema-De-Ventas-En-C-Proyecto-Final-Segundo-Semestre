#include <windows.h>

#define DEFAULT_SORT 0
#define DATE_SORT_ASD 1
#define DATE_SORT_DES 2
#define NAME_SORT_ASD 3
#define NAME_SORT_DES 4
#define LASTNAME_SORT_ASD 5
#define LASTNAME_SORT_DES 6
#define TDP_SORT_ASD 7
#define TDP_SORT_DES 8
#define PHONE_SORT_ASD 9
#define PHONE_SORT_DES 10
#define DNI_SORT_ASD 11
#define DNI_SORT_DES 12

char main_class[5];

/*
        CreateLoginWindow. Al llamar a esta funcion se crea la ventana de inicio de sesion, esta es la segunda funcion que se llama al
        comenzar el programa. Despues de introducir los datos del usuario en el formulario se le da click en el boton Login, si los datos del usuario
        son correctos se cierra la ventana e inicia el programa principal. Si se quiere crear un usuario se preciona el boton Nuevo Usuario,
        al hacer esto se oculta (no se cierra) la ventana y se crea la ventana SingUp llamando a la funcion CreateSingupWindow().
        Si se preciona el boton Close, la ejecucion del programa completo termina

        Parametros (Ninguno)

        Return void
*/

void CreateLoginWindow();

/*
        CreateSingUp. Esta funcion se encarga de crear la ventana de crear usuario, en esta ventana se rellena el formulario y 
        si no hay ningun error en los datos se crea el usuario, despues de crearse se oculta la ventana (No se cierra).
        Si se preciona el boton Close, la ejecucion del programa completo termina

        Parametros (No tiene)

        Return void
*/

void CreateSingupWindow();

/*
CreateMainWindow. Despues de iniciar sesion se llama a la funcion CreateMainWindow, esta va a ser la ventana principal del programa. Esta Ventana estara 
maximizada (No se debe salir de este modo ya que el programa no se le a agregado el rezise del contenido), despues de crearse esta ventana se llama a la funcion
CreateHeader, el cual creara el Header Principal del programa.
Esta funcion tambien tiene como objetivo el de poner en las variables puntero, que se encargaran de almacenar los datos de las tablas, un malloc para que puedan manipularse
como arrays y poder cambiarles el tamaño despues

Parametros Ninguno

Return void
*/

void CreateMainWindow();

/*
        CreateHeader. Esta funcion crea el contenedor para que los demas componentes se acoplen a esta.
        Despues de crearse el contenedor se llama a CreateNavBar para que cree el la barra de navegacion

        Parametros Ninguno

        Return void
*/

void CreateHeader();

/*
CreateHeaderTableVentas. Crea un header que sirve como guia para las columnas de la table de ventas

parametros
        HWND hWnd = identificador del contenedor
        int x = posicion en x
        int y = posicion en y
*/

void CreateHeaderTableVentas(HWND hWnd, int x, int y);

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

void CreateNavBar();


/*
CreateToolBarInventario. Esta funcion crea el contenedor para las herramientas, este contenedor seria la barra de tareas, al finalizar la funcion llama a la funcion
CreateToolsInventario para crear las herramientas para manejar la table de inventario

Parametros Ninguno

Return void
*/

void CreateToolBarInventario();

/*
        CreateToolsInventario. Esta funcion crea las herramientas para manejar la tabla de inventario. Estas herramientas son
        Crear producto, eliminar producto y modificar producto. al hacer click en Nuevo Producto se crea un formulario en el que se debe de introducir
        Los datos del producto. al precionar modificar producto se crea otro formulario en el que se modificaran los datos actuales del producto.
        Eliminar Producto elimina la fila seleccionada

        Parametros Ninguno

        Return void
*/

void CreateToolsInventario();


/*
CreateToolBarClientes. Esta funcion crea el contenedor para las herramientas, este contenedor seria la barra de tareas, al finalizar la funcion llama a la funcion
CreateToolsClientes para crear las herramientas para manejar la table de clientes.

Parametros Ninguno

Return void
*/

void CreateToolBarClientes();

/*
        CreateToolsClientes. Esta funcion crea las herramientas para manejar la tabla de inventario. Estas herramientas son
        Crear cliente, eliminar cliente y modificar cliente. al hacer click en Nuevo Cliente se crea un formulario en el que se debe de introducir
        Los datos del Cliente. al precionar modificar producto mientras se tiene una fila seleccionada de la tabla se crea otro formulario en el que se modificaran los 
        datos actuales del Cliente. Eliminar Cliente elimina la fila seleccionada

        Parametros Ninguno

        Return void
*/

void CreateToolsClientes();


/*
CreateToolBarVentas. Esta funcion crea el contenedor para las herramientas, este contenedor seria la barra de tareas, al finalizar la funcion llama a la funcion
CreateToolsVentas para crear las herramientas para manejar el formulario y tabla de ventas.

Parametros Ninguno

Return void
*/

void CreateToolBarVentas();

/*
        CreateToolsVentas. Esta funcion crea las herramientas para manejar el formulario de ventas y la tabla de ventas. Estas herramientas son
        Nueva Venta, Historial de Ventas y Ver Venta. Al hacer click en nueva venta se crea un formulario donde se podra introducir las nuevas ventas,
        si se preciona Historial de Ventas ese anterior formulario se cerrara y se abrira una tabla mostrando todas las ventas realizadas.
        Si se tiene precionado una fila en la tabla de ventas y se preciona Ver Venta entonces se mostrara en pantalla otra ventana mostrando el contenido de la venta

        Parametros Ninguno

        Return void
*/

void CreateToolsVentas();

/*
CreateBodyProductos. Crea el contenedor de la tabla de productos, tambien tiene el trabajo de almacenar en el array dataProductos los datos del producto

Parametros Ninguno

Return void
*/

void CreateBodyProductos();

/*
CreateTableClient. Esta funcion crea la tabla donde se veran los clientes almacenados en clientes.txt. Esta funcion contiene un bucle en el que llama a 
la funcion CreateRowTableClient la cual esta encargada de crear las filas de la tabla.

Parametros Ninguno

Return void
*/

void CreateTableClient();

/*
CreateWindowProducts. Esta funcion crea la ventana para elegir el producto a comprar.

parametros ninguno

return void
*/

void CreateWindowProducts();

/*
CreateHeaderWindowProducts. se encarga de crear una fila para poder identificar las columnas dde la tabla de productos

Parametros
        HWND hWnd = Identificador del contenedor
        int cxHeader = Ancho del Header
        int cyHeader = Alto del Header

return void
*/

void CreateHeaderWindowProducts(HWND hWnd, int cxHeader, int cyHeader);

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

void CreateTableProducts(HWND hWnd, int len, int x, int y, int cx, int cy);

/*
CreateHeaderTableProducts. Crea El  header para la tabla de productos. este header sirve para identificar las columnas de la tabla

parametros
        HWND hWnd = identificador del contenedor
        int y = posicion en y respecto al contenedor

return voids=
*/

void CreateHeaderTableProducts(HWND hWnd, int y);

/*
CreateWindowFactura. Crea la ventana factura, esta se encarga de mostrar la factura de una venta. esta contiene rif de la empresa y direccion.
Productos comprados, el total, nombre, domicilio y cedula del cliente, entre otros

parametros ninguno

return void
*/

void CreateWindowFactura();

/*
Esta funcion crea una ventana que muestra los datos del cliente, los productos comprados y el precio, ademas de eso tambien contiene un boton que al hacer click
llama a la funcion CreateWindowFactura

Parametros ninguno

return void
*/

void CreateWindowViewVenta();

/*
GetDataTableListofVentas. Esta funcion se utiliza para crear de nuevo la lista de ventas

parametros
        int cx, anchura del componente
        int cy, altura del componente
*/

void GetDataTableListofVentas(int cx, int cy);

/*
CreateTableListOfVentas. Crea la tabla de ventas, en esta se mostraran todas las ventas realizadas

parametros
        HWND hWnd = identificador del contenedor
        int xTable = posicion x respecto al contenedor
        int yTable = posicion y respecto al contenedor
        int cxTable = ancho de la tabla
        int cyTable = altura de la tabla
*/

void CreateTableListofVentas(HWND hWnd, int xTable, int yTable, int cxTable, int cyTable);

/*
CreateTableListOfProducts. Crea la lista de productos que se van a vender

Parametros
        int x = Esta es la posicion en x del componente
        int y = Esta es la posicion en y del componente
        int cx = Esta es la anchura del componente
        int cy = Esta es la altura del componente

return void
*/

void CreateTableListOfProducts(int x, int y, int cx, int cy);

/*
CreateHeaderTableCurrentProducts. Crea el header que identificara las columnas de las tablas

Parametros
        HWND hWnd = Pasa el identificador del componente que servira como contenedor

Return void
*/

void CreateHeaderTableCurrentProducts(HWND hWnd);

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

void CreateHeaderTableProductsVentas(HWND hWnd, int x, int y, int cx);

/*
        CreateBodyClienteMainWindow(). Crea el contenedor de la tabla de clientes, este contenedor abarca la pantalla completa
        Esta funcion tambien hace el trabajo de buscar y almacenar los datos de los clientes actuales en clientes.txt y guardarlos en los array dataClient y hTableCliente.
        Estas dos variable son punteros que su tamaño se modificara con realloc y este dependera de la cantidad de clientes que haya en clientes.txt

        Esta funcion llama a otras dos funciones las cuales son CreateTableClient y CreateHeaderTableClient

        Parametros Ninguno

        Return void
*/

void CreateBodyClienteMainWindow();

/*
CreateBodyVentasMainWindow. Esta funcion crea la tabla de ventas.

parametros
        BOOL newSell = este se encarga de identificar si se esta creando el formulario de ventas o el historial de ventas, si es TRUE se crea el formulario de ventas
        si no lo es se crea la tabla de ventas
*/

void CreateBodyVentasMainWindow(BOOL type);

/*
CreateWindowClients. Crea la ventana para seleccionar un cliente, esto es necesario para poder realizar una compra

parametros ninguno

return void
*/

void CreateWindowClients();

/*
CreateRowTableClient. Esta funcion crea una fila en la tabla, en estas se mostraran los datos del cliente

Parametros
        STRUCTCLIENTESDATA data = Este parametro es un registro donde estan almacenados los datos del cliente (Este parametro ya no se usa, quedo obsoleto)
        int i = El numero de fila actual, este parametro se introduce en la fila y se usa para identificar las filas.

Return void

*/

void CreateRowTableClient(STRUCTCLIENTESDATA data, int i);

/*
CreateHeaderTableClients. Crear el header de la tabla de clientes, esta diseñada para la ventana de elegir clientes

parametros
        HWND hWnd = identificador del contenedor
        int y = posicion en y
*/

void CreateHeaderTableClients(HWND hWnd, int y);

/*
CreateRowTableClientPortable. Se encarga de crear filas en el contenedor. esta funcion fue echa para la ventana para elegir clientes

Parametros
        HWND hWnd = identificador del contenedor
        int width = anchura del componente
*/

void CreateRowTableClientPortable(HWND hWnd, int width);

/*
CreateHeaderTableClient. Se crea el header que identifica a las columnas de la tabla
Parametros Ninguno
Return void
*/

void CreateHeaderTableClient();

/*
CreateHeaderClientsVentas. Crea el header de la ventana de seleccionar clientes, este header contiene distintos botones donde se podra crear un usuario, seleccionar un
usuario y cerrar la ventana

parametros
        HWND hWnd = identificador del contenedor
        int cxHeader = ancho del header
        int cyHeader = alto del header

return void
*/

void CreateHeaderClientsVentas(HWND hWnd, int cxHeader, int cyHeader);

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

void CreateTableListOfClients(HWND hWnd, int x, int y, int cxTable, int cyTable);

/*
CreateFooterTotalVentas. Crea un footer donde se mostrara el precio total de la venta
Parametros
        HWND hWnd = Identificador del contenedor
        int x = posicion en x
        int y = posicion en y
        int cx = ancho del footer
*/

void CreateFooterTotalVentas(HWND hWnd, int x, int y, int cx);

/*
Carga La image add.bmp para su uso en el componente tool. Esta funcion se usa en winProc.c
*/

void loadImagesAdd();

/*
Carga La image modificar.bmp para su uso en el componente tool. Esta funcion se usa en winProc.c
*/

void loadImagesModify();

/*
Carga La image delete.bmp para su uso en el componente tool. Esta funcion se usa en winProc.c
*/

void loadImagesDelete();

/*
Carga La image lista.bmp para su uso en el componente tool. Esta funcion se usa en winProc.c
*/

void loadImagesHistorial();

/*
Carga La image ver.bmp para su uso en el componente tool. Esta funcion se usa en winProc.c
*/

void loadImagesView();

/*
CreateFormClient. Esta funcion crea un formulario que se utiliza para crear y modificar un cliente. Son tres tipos, nuevoCliente, nuevoCliente fuera de la pestaña clientes
y modificar clientes. La diferencia entre los nuevos clientes es el boton para registrar los cambios.

Parametros
        BOOL newClient = Este marca si es un nuevo cliente, si es TRUE se mostrara el formulario para nuevo cliente
        UINT cliente = Este marca la pocision del cliente en el array dataClient
        BOOL ventas = este diferencia el lugar donde se llamo a esta funcion, para poder mostrar un formulario diferente en pantalla

return void
*/

void CreateFormClient(BOOL newClient, UINT client, BOOL ventas);

/*
        CreateFormProduct. Crea el formulario para introducir un nuevo producto o para modificar uno ya existente.

        parametros
                BOOL newProduct = si es TRUE se creara un formulario vacio para poder crear un nuevo producto, si es FALSE se creara el formulario con 
                los datos del producto a modificar
                UINT product = Indica la posicion del producto en el array dataProducts
*/

void CreateFormProduct(BOOL newProduct, UINT product);

/*
CreateFormVentas. Crea el formulario de ventas, este se divide en tres partes, el cliente, los botones para registrar y 
agregar productos a la venta, y la tabla que muestra los productos que se compraran. Al finalizar la funcion llama a la funcion CreateTableListOfProducts.

Paramentros Ninguno

Return void

*/

void CreateFormVentas();

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

BOOL CreateClasses(HINSTANCE);

HINSTANCE hInst;

RECT CRect;
WINDOWPOS pTableCurrentProduct;
int WHeight, WWidth;
int FirstMalloc;
int currentSort;
int cxColumnTable;
int nColumnsTable;
int Window_product_is_open;
int cxColumnTableProduct;
int cxColumnTableCurrentProduct;
int cxColumnTableVentas;
int cxColumnTableProductsVentas;

#define HeaderHeight 100
#define NavHeight 25
#define ToolBarHeight HeaderHeight - NavHeight
#define SCROLLBAR_WIDTH 17
#define ROW_TABLE_HEIGHT 20