#include <windows.h>
#include <windowsx.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wingdi.h>

#include "handlers/colors.h"
#include "handlers/user.h"
#include "handlers/winProc.h"
#include "handlers/draw.h"

int destroyingWindow = 0;
int mouseTrankingRed = 0;
int mouseTrankingGreen = 0;
int mouseTrack = 0;

void comprobarError()
{
        MessageBox(NULL, NULL, NULL, NULL);
}

LRESULT CALLBACK MainWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        switch (msg)
        {
        case WM_COMMAND:
                switch (wp)
                {
                case CLOSE_WINDOW:
                        DestroyWindow(hWnd);
                        break;
                }
                break;
        case WM_DESTROY:
                PostQuitMessage(0);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK LoginWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        char name_c[100], password_c[100];
        switch (msg)
        {
        case WM_COMMAND:
                switch (wp)
                {
                case CLOSE_WINDOW:
                        DestroyWindow(hWnd);
                        break;
                }
                break;
        case WM_DESTROY:
                if (!destroyingWindow)
                        PostQuitMessage(0);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK MainHeaderWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        switch (msg)
        {
        case WM_DESTROY:
                DestroyWindow(hWnd);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK MainNavWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        RECT rect;
        PAINTSTRUCT ps;
        HDC hdc;
        char text[100];
        switch (msg)
        {
        case WM_DESTROY:
                DestroyWindow(hWnd);
                break;
        case WM_PAINT:
                GetClientRect(hWnd, &rect);
                hdc = BeginPaint(hWnd, &ps);

                SetBkMode(hdc, TRANSPARENT);
                draw_border_bottom(rect, hdc, CreateSolidBrush(RGB(205, 205, 205)), 1);

                EndPaint(hWnd, &ps);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK ToolBarWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        RECT rect;
        PAINTSTRUCT ps;
        HDC hdc;
        char text[100];
        HMENU menu;
        ;
        switch (msg)
        {
        case WM_COMMAND:
                switch (wp)
                {
                case NAV_INVENTARIO:
                        if (hToolBarActual != hToolBarInventario)
                        {
                                ShowWindow(hToolBarActual, SW_HIDE);
                                ShowWindow(hToolBarInventario, SW_SHOW);
                                hToolBarActual = hToolBarInventario;
                        }
                        break;
                case NAV_CLIENTES:
                        if (hToolBarActual != hToolBarClientes)
                        {
                                ShowWindow(hToolBarActual, SW_HIDE);
                                ShowWindow(hToolBarClientes, SW_SHOW);
                                hToolBarActual = hToolBarClientes;
                        }
                        break;
                case NAV_VENTAS:
                        if (hToolBarActual != hToolBarVentas)
                        {
                                ShowWindow(hToolBarActual, SW_HIDE);
                                ShowWindow(hToolBarVentas, SW_SHOW);
                                hToolBarActual = hToolBarVentas;
                        }
                        break;
                }
                break;
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                break;
        case WM_MOUSEMOVE:
                if (!mouseTrack)
                {
                        MouseTrack(hWnd);
                        mouseTrack = 1;
                }
                break;
        case WM_MOUSELEAVE:
                mouseTrack = 0;
                if (hWnd != hNavActual)
                {
                        hdc = GetDC(hWnd);

                        GetClientRect(hWnd, &rect);
                        SetRect(&rect, rect.left + 2, rect.top + 2, rect.right - 2, rect.bottom - 2);

                        GetWindowTextA(hWnd, text, 100);

                        draw_bg_button(hdc, rect, CreateSolidBrush(RGB(235, 235, 235)), RGB(99, 110, 114), text);

                        ReleaseDC(hWnd, hdc);
                }
                break;
        case WM_MOUSEHOVER:
                hdc = GetDC(hWnd);

                GetClientRect(hWnd, &rect);
                SetRect(&rect, rect.left + 2, rect.top + 2, rect.right - 2, rect.bottom - 2);

                GetWindowTextA(hWnd, text, 100);

                draw_bg_button(hdc, rect, CreateSolidBrush(RGB(235, 235, 235)), RGB(0, 168, 255), text);

                ReleaseDC(hWnd, hdc);
                break;
        case WM_LBUTTONDOWN:
                if (hWnd == hNavActual)
                        return 0;
                hNavActual = hWnd;
                InvalidateRect(hMainHeader, NULL, TRUE);
                menu = GetMenu(hWnd);
                SendMessageA(hWnd, WM_COMMAND, menu, NULL);
                break;
        case WM_PAINT:
                GetClientRect(hWnd, &rect);
                hdc = BeginPaint(hWnd, &ps);

                SetBkMode(hdc, TRANSPARENT);
                GetWindowTextA(hWnd, text, 100);

                if (hWnd == hNavActual || First == 0)
                {
                        draw_border_top(rect, hdc, CreateSolidBrush(RGB(205, 205, 205)), 1);
                        draw_border_left(rect, hdc, CreateSolidBrush(RGB(205, 205, 205)), 1);
                        draw_border_right(rect, hdc, CreateSolidBrush(RGB(205, 205, 205)), 1);
                        SetTextColor(hdc, RGB(0, 168, 255));
                }
                else
                {
                        SetTextColor(hdc, RGB(99, 110, 114));
                        draw_border_bottom(rect, hdc, CreateSolidBrush(RGB(205, 205, 205)), 1);
                }
                DrawTextA(hdc, text, -1, &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

                EndPaint(hWnd, &ps);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK ToolWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        RECT rect;
        PAINTSTRUCT ps;
        HDC hdc;
        HDC hdcSource;
        char text[100];
        UINT menu;
        switch (msg)
        {
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                break;
        case WM_CREATE:
                menu = GetMenu(hWnd);
                switch (menu)
                {
                case TOOLBAR_IMAGE_NEW:
                        hNuevoProductoImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 50 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_NEW, NULL, NULL);
                        break;
                case TOOLBAR_IMAGE_MODIFY:
                        hModificarProductoImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 50 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_MODIFY, NULL, NULL);
                        if (hModificarProductoImage == NULL)
                                MessageBox(NULL, NULL, NULL, NULL);
                        break;
                case TOOLBAR_IMAGE_DELETE:
                        hEliminarProductoImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 50 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_DELETE, NULL, NULL);
                        break;
                }
                break;
        case WM_MOUSEMOVE:
                if (!mouseTrack)
                {
                        MouseTrack(hWnd);
                        mouseTrack = 1;
                }
                break;
        case WM_MOUSELEAVE:
                mouseTrack = 0;
                InvalidateRect(hWnd, NULL, TRUE);
                hdc = GetDC(hWnd);

                GetClientRect(hWnd, &rect);
                SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);

                GetWindowTextA(hWnd, text, 100);

                draw_bg_button(hdc, rect, CreateSolidBrush(RGB(240, 240, 240)), RGB(99, 110, 114), text);

                ReleaseDC(hWnd, hdc);
                break;
        case WM_MOUSEHOVER:
                hdc = GetDC(hWnd);

                GetClientRect(hWnd, &rect);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(201, 224, 167)));
                SetRect(&rect, rect.left, rect.top + 35, rect.right, rect.bottom);
                GetWindowTextA(hWnd, text, 100);

                draw_bg_button_multiline(hdc, rect, CreateSolidBrush(RGB(201, 224, 167)), RGB(0, 0, 0), text);
                InvalidateRect(hNuevoProductoImage, NULL, TRUE);

                ReleaseDC(hWnd, hdc);
                break;
        case WM_PAINT:
                GetClientRect(hWnd, &rect);
                hdc = BeginPaint(hWnd, &ps);

                menu = GetMenu(hWnd);

                hdcSource = CreateCompatibleDC(hdc);
                SelectObject(hdcSource, hImageModify);

                GetWindowTextA(hWnd, text, 100);

                FillRect(hdc, &rect, CreateSolidBrush(RGB(240, 240, 240)));

                SetRect(&rect, rect.left, rect.top + 35, rect.right, rect.bottom);
                draw_bg_button_multiline(hdc, rect, CreateSolidBrush(RGB(240, 240, 240)), RGB(0, 0, 0), text);

                switch (menu)
                {
                case TOOLBAR_IMAGE_NEW:
                        SendMessageA(hNuevoProductoImage, STM_SETIMAGE, IMAGE_BITMAP, hImageAdd);
                        break;
                case TOOLBAR_IMAGE_MODIFY:
                        SendMessageA(hModificarProductoImage, STM_SETIMAGE, IMAGE_BITMAP, hImageModify);
                        break;
                case TOOLBAR_IMAGE_DELETE:
                        SendMessageA(hEliminarProductoImage, STM_SETIMAGE, IMAGE_BITMAP, hImageDelete);
                        break;
                }

                EndPaint(hWnd, &ps);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK STransparentWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rect;
        char text[100];
        switch (msg)
        {
        case WM_PAINT:
                GetClientRect(hWnd, &rect);

                hdc = BeginPaint(hWnd, &ps);

                SetTextColor(hdc, RGB(0, 0, 0));
                SetBkMode(hdc, TRANSPARENT);

                GetWindowTextA(hWnd, text, 100);

                DrawTextA(hdc, text, -1, &rect, DT_SINGLELINE | DT_VCENTER);
                EndPaint(hWnd, &ps);

                return 0;
                break;
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK ButtonGreenWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        PAINTSTRUCT ps;
        HDC hdc;

        RECT rect;

        char text[100];
        char name_c[100], password_c[100];

        switch (msg)
        {
        case WM_COMMAND:
                switch (wp)
                {
                case LOGIN_USER:
                        GetWindowTextA(hName, name_c, 100);
                        GetWindowTextA(hPassword, password_c, 100);
                        int log = login(name_c, password_c);
                        if (log == -2)
                                MessageBox(NULL, "The user or the password is incorrect", "Login", MB_ICONERROR);
                        if (log == -1)
                                MessageBox(NULL, "Error, Database Not Exist", "ERROR", MB_ICONERROR);
                        if (log >= 0)
                        {
                                CreateMainWindow();
                                destroyingWindow = 1;
                                DestroyWindow(hWnd);
                        }
                        break;
                }
                break;
        case WM_LBUTTONUP:
                SendMessageA(hWnd, WM_COMMAND, LOGIN_USER, NULL);
                break;
        case WM_MOUSEMOVE:
                if (!mouseTrankingGreen)
                {
                        MouseTrack(hWnd);
                        mouseTrankingGreen = 1;
                }
                break;
        case WM_MOUSELEAVE:
                mouseTrankingGreen = 0;

                GetClientRect(hWnd, &rect);

                hdc = GetDC(hWnd);
                GetWindowTextA(hWnd, text, 100);

                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN), COLOR_BLACK, text);

                ReleaseDC(hWnd, hdc);
                break;
        case WM_LBUTTONDOWN:
                if (mouseTrankingGreen)
                {
                        GetClientRect(hWnd, &rect);
                        GetWindowTextA(hWnd, text, 100);

                        hdc = GetDC(hWnd);

                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN_CLICK), COLOR_WHITE, text);
                        ReleaseDC(hWnd, hdc);
                }
                break;
        case WM_MOUSEHOVER:
                GetClientRect(hWnd, &rect);
                hdc = GetDC(hWnd);

                GetWindowTextA(hWnd, text, 100);
                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN_HOVER), COLOR_WHITE, text);

                ReleaseDC(hWnd, hdc);
                break;
        case WM_PAINT:
                GetClientRect(hWnd, &rect);

                hdc = BeginPaint(hWnd, &ps);
                GetWindowTextA(hWnd, text, 100);

                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN), COLOR_BLACK, text);

                EndPaint(hWnd, &ps);
                return 0;
                break;
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                SendMessageA(hLogin, WM_COMMAND, CLOSE_WINDOW, NULL);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK ButtonRedWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        POINT pt;
        char Coords[100];

        PAINTSTRUCT ps;
        HDC hdc;

        RECT rect;
        RECT rect_temp;

        char text[100];
        char name_c[100], password_c[100];

        switch (msg)
        {
        case WM_COMMAND:
                switch (wp)
                {
                case CLOSE_WINDOW:
                        PostQuitMessage(0);
                        break;
                }
                break;
        case WM_LBUTTONUP:
                SendMessageA(hWnd, WM_COMMAND, CLOSE_WINDOW, NULL);
                break;
        case WM_MOUSEMOVE:
                if (!mouseTrankingRed)
                {
                        TRACKMOUSEEVENT mouse;
                        mouse.cbSize = sizeof(mouse);
                        mouse.hwndTrack = hWnd;
                        mouse.dwFlags = TME_HOVER | TME_LEAVE;
                        mouse.dwHoverTime = 10;
                        TrackMouseEvent(&mouse);
                        mouseTrankingRed = 1;
                }
                break;
        case WM_MOUSELEAVE:
                mouseTrankingRed = 0;

                GetClientRect(hWnd, &rect);

                hdc = GetDC(hWnd);
                GetWindowTextA(hWnd, text, 100);

                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED), COLOR_BLACK, text);

                ReleaseDC(hWnd, hdc);
                break;
        case WM_LBUTTONDOWN:
                if (mouseTrankingRed)
                {
                        GetClientRect(hWnd, &rect);
                        GetWindowTextA(hWnd, text, 100);

                        hdc = GetDC(hWnd);

                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED_CLICK), COLOR_WHITE, text);
                        ReleaseDC(hWnd, hdc);
                }
                break;
        case WM_MOUSEHOVER:
                GetClientRect(hWnd, &rect);
                hdc = GetDC(hWnd);

                GetWindowTextA(hWnd, text, 100);
                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED_HOVER), COLOR_WHITE, text);

                ReleaseDC(hWnd, hdc);
                break;
        case WM_PAINT:
                GetClientRect(hWnd, &rect);

                hdc = BeginPaint(hWnd, &ps);
                GetWindowTextA(hWnd, text, 100);

                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED), COLOR_BLACK, text);

                EndPaint(hWnd, &ps);
                return 0;
                break;
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}