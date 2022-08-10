#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdShow)
{
        WNDCLASSW wc = {0};

        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hInstance = hInst;
        wc.lpszClassName = L"myWindowsClass";
        wc.lpfnWndProc = WindowProcedure;

        if (!RegisterClassW(&wc))
                return -1;
        CreateWindowW(L"myWindowsClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
                      NULL, NULL, NULL, NULL);
        
        MSG msg = {0};

        while(GetMessage(&msg, NULL, NULL, NULL)){
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        switch(msg)
        {
                case WM_DESTROY:
                        PostQuitMessage(0);
                        break;
                default:
                        DefWindowProcW(hWnd, msg, wp, lp);
        }
}