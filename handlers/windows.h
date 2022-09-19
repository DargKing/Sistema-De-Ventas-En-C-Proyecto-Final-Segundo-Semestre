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

void CreateLoginWindow();
void CreateMainWindow();
void CreateHeader();
void CreateNavBar();

void CreateToolBarInventario();
void CreateToolsInventario();

void CreateToolBarClientes();
void CreateToolsClientes();

void CreateToolBarVentas();
void CreateToolsVentas();

void CreateBodyProductos();

void CreateTableClient();

void CreateWindowProducts();
void CreateHeaderWindowProducts(HWND hWnd, int cxHeader, int cyHeader);
void CreateTableProducts(HWND hWnd, int len, int x, int y, int cx, int cy);
void CreateHeaderTableProducts(HWND hWnd, int y);

void CreateTableListOfProducts(int x, int y, int cx, int cy);
void CreateHeaderTableCurrentProducts(HWND hWnd);

void CreateBodyClienteMainWindow();
void CreateBodyVentasMainWindow();

void loadImagesAdd();
void loadImagesModify();
void loadImagesDelete();

void CreateFormClient(BOOL newClient, UINT client);
void CreateFormProduct(BOOL newProduct, UINT product);

BOOL CreateClasses(HINSTANCE);
BOOL InitProgram(HINSTANCE);

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

#define HeaderHeight 100
#define NavHeight 25
#define ToolBarHeight HeaderHeight - NavHeight
#define SCROLLBAR_WIDTH 17
#define ROW_TABLE_HEIGHT 20