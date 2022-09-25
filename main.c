// Librerias
#include <windows.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

// Modulos
#include "handlers/user.h"
#include "handlers/error.h"

// Extensiones
#include "handlers/winProc.h"
#include "handlers/windows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR args, int ncmdShow)
{
        strcpy(main_class, "main");

        if (!CreateClasses(hInstance))
                return FALSE;

        MSG msg = {0};

        CreateLoginWindow();
        // CreateMainWindow();

        while (GetMessage(&msg, NULL, NULL, NULL))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        return 0;
}
