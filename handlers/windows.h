#include <windows.h>

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

void CreateTableClient();


void loadImagesAdd();
void loadImagesModify();
void loadImagesDelete();

BOOL CreateClasses(HINSTANCE);
BOOL InitProgram(HINSTANCE);

HINSTANCE hInst;

RECT CRect;
int WHeight, WWidth;
#define HeaderHeight 100
#define NavHeight 25
#define ToolBarHeight HeaderHeight - NavHeight