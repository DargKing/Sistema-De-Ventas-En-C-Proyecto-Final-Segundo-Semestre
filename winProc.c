#include <windows.h>
#include <windowsx.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wingdi.h>
#include <math.h>

#include "handlers/colors.h"
#include "handlers/user.h"
#include "handlers/winProc.h"
#include "handlers/windows.h"
#include "handlers/draw.h"
#include "handlers/error.h"
#include "handlers/struct.h"
#include "handlers/caracteres.h"
#include "handlers/clientes.h"

int destroyingWindow = 0;
int mouseTranking = 0;
int mouseTrack = 0;

LRESULT CALLBACK DivWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        char text[100];

        int newPos;
        int oldPos;

        SCROLLINFO scrollInfo;
        RECT rect;
        RECT rectMainWindow;
        RECT rectContainer;
        int cxClient, cyClient;
        SCROLLINFO sbInfo;

        PAINTSTRUCT ps;
        HDC hdc;
        int inicio, fin, y;

        switch (msg)
        {
        case WM_SIZE:

                cxClient = LOWORD(lp);
                cyClient = HIWORD(lp);

                GetClientRect(hMain, &rectMainWindow);

                sbInfo.nPos = 0;
                sbInfo.nMin = 0;
                sbInfo.cbSize = sizeof(SCROLLINFO);
                // sprintf(text, "%d Mayor", cyClient);
                // MessageBoxA(NULL, text, NULL, MB_OK);

                if (cyClient > 1)
                {
                        sbInfo.nMax = jumplines - 1;
                        sbInfo.nPage = (cyClient / 20);
                        sbInfo.fMask = SIF_ALL;
                }
                else
                {
                        sbInfo.nMax = 1;
                        sbInfo.nPage = 1;
                        sbInfo.fMask = SIF_DISABLENOSCROLL;
                }

                SetScrollInfo(hWnd, SB_VERT, &sbInfo, TRUE);

                break;
        case WM_VSCROLL:

                scrollInfo.cbSize = sizeof(SCROLLINFO);
                scrollInfo.fMask = SIF_POS | SIF_RANGE | SIF_TRACKPOS | SIF_PAGE;

                GetScrollInfo(hWnd, SB_VERT, &scrollInfo);

                oldPos = scrollInfo.nPos;

                switch (LOWORD(wp))
                {
                case SB_PAGEUP:
                        scrollInfo.nPos -= rect.bottom - HeaderHeight;
                        break;
                case SB_PAGEDOWN:
                        GetClientRect(hMain, &rect);
                        scrollInfo.nPos += rect.bottom - HeaderHeight;
                        break;
                case SB_BOTTOM:
                        scrollInfo.nPos = scrollInfo.nMax;
                        break;
                case SB_TOP:
                        scrollInfo.nPos = scrollInfo.nMin;
                        break;
                case SB_LINEUP:
                        if (scrollInfo.nPos > 0)
                                scrollInfo.nPos -= 1;
                        break;
                case SB_LINEDOWN:
                        GetClientRect(hTableContainer, &rect);

                        if (scrollInfo.nPos < scrollInfo.nMax - scrollInfo.nPage)
                                scrollInfo.nPos += 1;
                        break;
                case SB_THUMBTRACK:
                case SB_THUMBPOSITION:
                        scrollInfo.nPos = HIWORD(wp);
                        break;
                }

                scrollInfo.fMask = SIF_POS;
                SetScrollInfo(hWnd, SB_VERT, &scrollInfo, TRUE);

                newPos = scrollInfo.nPos;

                if (newPos != oldPos)
                {
                        GetClientRect(hWnd, &rect);
                        // ScrollWindowEx(hWnd, 0, oldPos - newPos, &rect, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
                        ScrollWindow(hWnd, 0, ROW_TABLE_HEIGHT * (oldPos - newPos), NULL, NULL);
                        // rect.top = newPos;
                        // rect.bottom = newPos + scrollInfo.nPage;
                        // InvalidateRect(hTableContainer, &rect, TRUE);
                        UpdateWindow(hWnd);
                }
                break;
        case WM_PAINT:
                hdc = BeginPaint(hWnd, &ps);

                scrollInfo.cbSize = sizeof(SCROLLINFO);
                scrollInfo.fMask = SIF_POS;

                GetScrollInfo(hWnd, SB_VERT, &scrollInfo);

                inicio = max((long)0, scrollInfo.nPos + ps.rcPaint.top / ROW_TABLE_HEIGHT);
                fin = min((long)jumplines - 1, scrollInfo.nPos + ps.rcPaint.bottom / ROW_TABLE_HEIGHT);

                for (int i = inicio; i <= fin; i++)
                {
                        y = ROW_TABLE_HEIGHT * (i - scrollInfo.nPos);
                        InvalidateRect(hTableCliente[i].container, NULL, FALSE);
                }

                EndPaint(hWnd, &ps);
                break;
        case WM_DESTROY:
                DestroyWindow(hWnd);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK ScrollBarProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        char text[100];
        int newPos;
        int oldPos;
        SCROLLINFO scrollInfo;
        RECT rect;

        switch (msg)
        {
        case WM_VSCROLL:

                scrollInfo.cbSize = sizeof(SCROLLINFO);
                scrollInfo.fMask = SIF_POS | SIF_RANGE | SIF_TRACKPOS | SIF_PAGE;

                GetScrollInfo(hWnd, SB_VERT, &scrollInfo);

                oldPos = scrollInfo.nPos;

                switch (LOWORD(wp))
                {
                case SB_PAGEUP:
                        scrollInfo.nPos -= rect.bottom - HeaderHeight;
                        break;
                case SB_PAGEDOWN:
                        GetClientRect(hMain, &rect);
                        scrollInfo.nPos += rect.bottom - HeaderHeight;
                        break;
                case SB_BOTTOM:
                        scrollInfo.nPos = scrollInfo.nMax;
                        break;
                case SB_TOP:
                        scrollInfo.nPos = scrollInfo.nMin;
                        break;
                case SB_LINEUP:
                        if (scrollInfo.nPos > 0)
                                scrollInfo.nPos -= 20;
                        break;
                case SB_LINEDOWN:
                        GetClientRect(hTableContainer, &rect);

                        if (scrollInfo.nPos < rect.bottom - scrollInfo.nPage)
                                scrollInfo.nPos += 20;
                        break;
                case SB_THUMBTRACK:
                        scrollInfo.nPos = HIWORD(wp);
                        break;
                }

                scrollInfo.fMask = SIF_POS;
                SetScrollInfo(hWnd, SB_VERT, &scrollInfo, TRUE);

                newPos = scrollInfo.nPos;

                if (newPos != oldPos)
                {
                        GetClientRect(hTableContainer, &rect);
                        ScrollWindowEx(hTableContainer, 0, oldPos - newPos, &rect, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN);
                        rect.top = newPos;
                        rect.bottom = newPos + scrollInfo.nPage;
                        // InvalidateRect(hTableContainer, &rect, TRUE);
                        UpdateWindow(hTableContainer);
                }
                break;
        default:
                CallWindowProcA(DefWindowProcA, hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK ClientWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
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
                DestroyWindow(hWnd);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
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
        RECT rect;
        PAINTSTRUCT ps;
        HDC hdc;
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
                                DestroyWindow(hCurrentBody);
                        }
                        break;
                case NAV_CLIENTES:
                        if (hToolBarActual != hToolBarClientes)
                        {
                                ShowWindow(hToolBarActual, SW_HIDE);
                                ShowWindow(hToolBarClientes, SW_SHOW);
                                hToolBarActual = hToolBarClientes;
                                DestroyWindow(hCurrentBody);
                                CreateBodyCliente();
                        }
                        break;
                case NAV_VENTAS:
                        if (hToolBarActual != hToolBarVentas)
                        {
                                ShowWindow(hToolBarActual, SW_HIDE);
                                ShowWindow(hToolBarVentas, SW_SHOW);
                                hToolBarActual = hToolBarVentas;
                                DestroyWindow(hCurrentBody);
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
        int i = 0;
        switch (msg)
        {
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                break;
        case WM_LBUTTONDOWN:
                menu = GetMenu(hWnd);

                switch (menu)
                {
                case TOOLBAR_IMAGE_DELETE_CLIENTE:
                        if (hTableCurrentRow == NULL)
                                return 0;
                        while (hTableCurrentRow != hTableCliente[i].container)
                                i++;
                        delete_table_row_client(dataClient[i].ID);
                        CreateBodyCliente();
                        break;
                case TOOLBAR_IMAGE_MODIFY_CLIENTE:
                        if (hTableCurrentRow != NULL)
                        {
                                if (hTableCurrentRow == NULL)
                                        return 0;
                                while (hTableCurrentRow != hTableCliente[i].container)
                                        i++;
                                CreateFormClient(FALSE, i);
                        }
                        break;
                case TOOLBAR_IMAGE_NEW_CLIENTE:
                        CreateFormClient(TRUE, -1);
                        break;
                }

                break;
        case WM_CREATE:
                menu = GetMenu(hWnd);
                switch (menu)
                {

                // Inventario
                case TOOLBAR_IMAGE_NEW_INVENTARIO:
                        hNuevoProductoImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 50 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_NEW_INVENTARIO, NULL, NULL);
                        break;
                case TOOLBAR_IMAGE_DELETE_INVENTARIO:
                        hEliminarProductoImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 50 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_DELETE_INVENTARIO, NULL, NULL);
                        break;
                case TOOLBAR_IMAGE_MODIFY_INVENTARIO:
                        hModificarProductoImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 50 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_MODIFY_INVENTARIO, NULL, NULL);
                        break;

                // CLientes
                case TOOLBAR_IMAGE_NEW_CLIENTE:
                        hNuevoClienteImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 50 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_NEW_INVENTARIO, NULL, NULL);
                        break;
                case TOOLBAR_IMAGE_DELETE_CLIENTE:
                        hEliminarClienteImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 50 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_DELETE_INVENTARIO, NULL, NULL);
                        break;
                case TOOLBAR_IMAGE_MODIFY_CLIENTE:
                        hModificarClienteImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 50 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_MODIFY_INVENTARIO, NULL, NULL);
                        break;

                // Ventas
                case TOOLBAR_IMAGE_NEW_VENTAS:
                        hNuevaVentaImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 40 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_NEW_INVENTARIO, NULL, NULL);
                        break;
                case TOOLBAR_IMAGE_DELETE_VENTAS:
                        hEliminarVentaImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 45 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_DELETE_INVENTARIO, NULL, NULL);
                        break;
                case TOOLBAR_IMAGE_MODIFY_VENTAS:
                        hModificarVentaImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 45 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_MODIFY_INVENTARIO, NULL, NULL);
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

                draw_bg_button(hdc, rect, CreateSolidBrush(RGB(235, 235, 235)), RGB(99, 110, 114), text);

                ReleaseDC(hWnd, hdc);
                break;
        case WM_MOUSEHOVER:
                hdc = GetDC(hWnd);

                menu = GetMenu(hWnd);

                GetClientRect(hWnd, &rect);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(201, 224, 167)));
                SetRect(&rect, rect.left, rect.top + 35, rect.right, rect.bottom);
                GetWindowTextA(hWnd, text, 100);

                draw_bg_button_multiline(hdc, rect, CreateSolidBrush(RGB(201, 224, 167)), RGB(0, 0, 0), text);
                InvalidateRect(hNuevoProductoImage, NULL, TRUE);

                switch (menu)
                {

                // Inventario
                case TOOLBAR_IMAGE_NEW_INVENTARIO:
                        InvalidateRect(hNuevoProductoImage, NULL, TRUE);
                        break;
                case TOOLBAR_IMAGE_MODIFY_INVENTARIO:
                        InvalidateRect(hModificarProductoImage, NULL, TRUE);
                        break;
                case TOOLBAR_IMAGE_DELETE_INVENTARIO:
                        InvalidateRect(hEliminarProductoImage, NULL, TRUE);
                        break;

                // Clientes
                case TOOLBAR_IMAGE_NEW_CLIENTE:
                        InvalidateRect(hNuevoClienteImage, NULL, TRUE);
                        break;
                case TOOLBAR_IMAGE_MODIFY_CLIENTE:
                        InvalidateRect(hModificarClienteImage, NULL, TRUE);
                        break;
                case TOOLBAR_IMAGE_DELETE_CLIENTE:
                        InvalidateRect(hEliminarClienteImage, NULL, TRUE);
                        break;

                // Ventas
                case TOOLBAR_IMAGE_NEW_VENTAS:
                        InvalidateRect(hNuevaVentaImage, NULL, TRUE);
                        break;
                case TOOLBAR_IMAGE_MODIFY_VENTAS:
                        InvalidateRect(hModificarVentaImage, NULL, TRUE);
                        break;
                case TOOLBAR_IMAGE_DELETE_VENTAS:
                        InvalidateRect(hEliminarVentaImage, NULL, TRUE);
                        break;
                }

                ReleaseDC(hWnd, hdc);
                break;
        case WM_PAINT:
                GetClientRect(hWnd, &rect);
                hdc = BeginPaint(hWnd, &ps);

                menu = GetMenu(hWnd);

                GetWindowTextA(hWnd, text, 100);

                FillRect(hdc, &rect, CreateSolidBrush(RGB(235, 235, 235)));

                SetRect(&rect, rect.left, rect.top + 35, rect.right, rect.bottom);
                draw_bg_button_multiline(hdc, rect, CreateSolidBrush(RGB(235, 235, 235)), RGB(0, 0, 0), text);

                switch (menu)
                {

                // iNVENTARIO
                case TOOLBAR_IMAGE_NEW_INVENTARIO:
                        loadImagesAdd();
                        SendMessageA(hNuevoProductoImage, STM_SETIMAGE, IMAGE_BITMAP, hImageAdd);
                        break;
                case TOOLBAR_IMAGE_MODIFY_INVENTARIO:
                        loadImagesModify();
                        SendMessageA(hModificarProductoImage, STM_SETIMAGE, IMAGE_BITMAP, hImageModify);
                        break;
                case TOOLBAR_IMAGE_DELETE_INVENTARIO:
                        loadImagesDelete();
                        SendMessageA(hEliminarProductoImage, STM_SETIMAGE, IMAGE_BITMAP, hImageDelete);
                        break;

                // CLIENTE
                case TOOLBAR_IMAGE_NEW_CLIENTE:
                        loadImagesAdd();
                        SendMessageA((HWND)hNuevoClienteImage, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hImageAdd);
                        break;
                case TOOLBAR_IMAGE_MODIFY_CLIENTE:
                        loadImagesModify();
                        SendMessageA(hModificarClienteImage, STM_SETIMAGE, IMAGE_BITMAP, hImageModify);
                        break;
                case TOOLBAR_IMAGE_DELETE_CLIENTE:
                        loadImagesDelete();
                        SendMessageA(hEliminarClienteImage, STM_SETIMAGE, IMAGE_BITMAP, hImageDelete);
                        break;

                // VENTAS
                case TOOLBAR_IMAGE_NEW_VENTAS:
                        loadImagesAdd();
                        SendMessageA(hNuevaVentaImage, STM_SETIMAGE, IMAGE_BITMAP, hImageAdd);
                        break;
                case TOOLBAR_IMAGE_MODIFY_VENTAS:
                        loadImagesModify();
                        SendMessageA(hModificarVentaImage, STM_SETIMAGE, IMAGE_BITMAP, hImageModify);
                        break;
                case TOOLBAR_IMAGE_DELETE_VENTAS:
                        loadImagesDelete();
                        SendMessageA(hEliminarVentaImage, STM_SETIMAGE, IMAGE_BITMAP, hImageDelete);
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

LRESULT CALLBACK ButtonsWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        PAINTSTRUCT ps;
        HDC hdc;

        RECT rect;

        char text[100];
        char name_c[100], password_c[100];

        int menu;

        STRUCTCLIENTESDATA dataC;

        switch (msg)
        {
        case WM_COMMAND:
                switch (wp)
                {
                case MODIFY_CLIENT_FORM:
                        GetWindowTextA(hFormClient.name, dataC.name, 100);
                        GetWindowTextA(hFormClient.lastname, dataC.lastname, 100);
                        GetWindowTextA(hFormClient.phone, dataC.phone, 20);
                        GetWindowTextA(hFormClient.TdP, dataC.TdP, 2);
                        GetWindowTextA(hFormClient.dni, dataC.dni, 20);

                        int row;

                        if (strcmp(dataC.name, currentDataC.name))
                        {
                                row = search_clients(currentDataC.ID);
                                modify_name_clients(row, dataC.name);
                        }

                        if (strcmp(dataC.lastname, currentDataC.lastname))
                        {
                                row = search_clients(currentDataC.ID);
                                modify_lastname_clients(row, dataC.lastname);
                        }

                        if (strcmp(dataC.dni, currentDataC.dni))
                        {
                                row = search_clients(currentDataC.ID);
                                modify_dni_clients(row, dataC.dni);
                        }

                        if (strcmp(dataC.phone, currentDataC.phone))
                        {
                                row = search_clients(currentDataC.ID);
                                modify_phone_clients(row, dataC.phone);
                        }

                        if (strcmp(dataC.TdP, currentDataC.TdP))
                        {
                                row = search_clients(currentDataC.ID);
                                modify_TdP_clients(row, dataC.TdP);
                        }

                        DestroyWindow(hFormClient.container);
                        DestroyWindow(hBodyClientes);
                        CreateBodyCliente();

                        break;
                case CREATE_CLIENT_FORM:
                        GetWindowTextA(hFormClient.name, dataC.name, 100);
                        GetWindowTextA(hFormClient.lastname, dataC.lastname, 100);
                        GetWindowTextA(hFormClient.phone, dataC.phone, 20);
                        GetWindowTextA(hFormClient.TdP, dataC.TdP, 2);
                        GetWindowTextA(hFormClient.dni, dataC.dni, 20);

                        create_ID(dataC.ID);

                        new_client(dataC.ID, dataC.name, dataC.lastname, dataC.dni, dataC.phone, dataC.TdP);

                        DestroyWindow(hFormClient.container);
                        DestroyWindow(hBodyClientes);
                        CreateBodyCliente();
                        break;
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
                case CLOSE_WINDOW:
                        PostQuitMessage(0);
                        break;
                case CLOSE_CLIENT_FORM:
                        DestroyWindow(hFormClient.container);
                        break;
                }
                break;
        case WM_LBUTTONUP:
                menu = GetMenu(hWnd);
                SendMessageA(hWnd, WM_COMMAND, menu, NULL);
                break;
        case WM_MOUSEMOVE:
                if (!mouseTranking)
                {
                        MouseTrack(hWnd);
                        mouseTranking = 1;
                }
                break;
        case WM_MOUSELEAVE:
                mouseTranking = 0;

                GetClientRect(hWnd, &rect);
                hdc = GetDC(hWnd);
                menu = GetMenu(hWnd);
                GetWindowTextA(hWnd, text, 100);

                switch (menu)
                {
                case LOGIN_USER:
                case CREATE_CLIENT_FORM:
                case MODIFY_CLIENT_FORM:
                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN), COLOR_BLACK, text);
                        break;
                case CLOSE_WINDOW:
                case CLOSE_CLIENT_FORM:
                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED), COLOR_BLACK, text);
                        break;
                }

                ReleaseDC(hWnd, hdc);
                break;
        case WM_LBUTTONDOWN:
                if (mouseTranking)
                {
                        menu = GetMenu(hWnd);
                        switch (menu)
                        {
                        case LOGIN_USER:
                        case CREATE_CLIENT_FORM:
                        case MODIFY_CLIENT_FORM:
                                GetClientRect(hWnd, &rect);
                                GetWindowTextA(hWnd, text, 100);

                                hdc = GetDC(hWnd);

                                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN_CLICK), COLOR_WHITE, text);
                                ReleaseDC(hWnd, hdc);
                                break;
                        case CLOSE_WINDOW:
                        case CLOSE_CLIENT_FORM:
                                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED_CLICK), COLOR_WHITE, text);
                                break;
                        }
                }
                break;
        case WM_MOUSEHOVER:
                GetClientRect(hWnd, &rect);
                hdc = GetDC(hWnd);

                menu = GetMenu(hWnd);

                switch (menu)
                {
                case LOGIN_USER:
                case MODIFY_CLIENT_FORM:
                case CREATE_CLIENT_FORM:
                        GetWindowTextA(hWnd, text, 100);
                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN_HOVER), COLOR_WHITE, text);
                        break;
                case CLOSE_WINDOW:
                case CLOSE_CLIENT_FORM:
                        GetWindowTextA(hWnd, text, 100);
                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED_HOVER), COLOR_WHITE, text);
                        break;
                }

                ReleaseDC(hWnd, hdc);
                break;
        case WM_PAINT:
                GetClientRect(hWnd, &rect);

                menu = GetMenu(hWnd);

                switch (menu)
                {
                case LOGIN_USER:
                case CREATE_CLIENT_FORM:
                case MODIFY_CLIENT_FORM:
                        hdc = BeginPaint(hWnd, &ps);
                        GetWindowTextA(hWnd, text, 100);

                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN), COLOR_BLACK, text);
                        break;
                case CLOSE_WINDOW:
                case CLOSE_CLIENT_FORM:
                        hdc = BeginPaint(hWnd, &ps);
                        GetWindowTextA(hWnd, text, 100);

                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED), COLOR_BLACK, text);
                        break;
                }

                EndPaint(hWnd, &ps);
                return 0;
                break;
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                menu = GetMenu(hWnd);
                switch (menu)
                {
                case LOGIN_USER:
                        SendMessageA(hLogin, WM_COMMAND, CLOSE_WINDOW, NULL);
                        break;
                case CLOSE_WINDOW:
                        DestroyWindow(hWnd);
                        break;
                case CREATE_CLIENT_FORM:
                case CLOSE_CLIENT_FORM:
                case MODIFY_CLIENT_FORM:
                        DestroyWindow(hFormClient.container);
                        break;
                }
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
                if (!mouseTranking)
                {
                        TRACKMOUSEEVENT mouse;
                        mouse.cbSize = sizeof(mouse);
                        mouse.hwndTrack = hWnd;
                        mouse.dwFlags = TME_HOVER | TME_LEAVE;
                        mouse.dwHoverTime = 10;
                        TrackMouseEvent(&mouse);
                        mouseTranking = 1;
                }
                break;
        case WM_MOUSELEAVE:
                mouseTranking = 0;

                GetClientRect(hWnd, &rect);

                hdc = GetDC(hWnd);
                GetWindowTextA(hWnd, text, 100);

                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED), COLOR_BLACK, text);

                ReleaseDC(hWnd, hdc);
                break;
        case WM_LBUTTONDOWN:
                if (mouseTranking)
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

LRESULT CALLBACK HeaderCellWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
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

                FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 255, 255)));

                SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
                DrawTextA(hdc, text, -1, &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

                draw_border_bottom(rect, hdc, CreateSolidBrush(RGB(0, 0, 0)), 2);
                draw_border_top(rect, hdc, CreateSolidBrush(RGB(0, 0, 0)), 2);
                draw_border_left(rect, hdc, CreateSolidBrush(RGB(0, 0, 0)), 2);
                draw_border_right(rect, hdc, CreateSolidBrush(RGB(0, 0, 0)), 2);

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

LRESULT CALLBACK CellWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rect;
        char text[100];
        int menu;
        switch (msg)
        {
        case WM_LBUTTONDOWN:
                menu = GetMenu(hWnd);
                if (hTableCurrentRow == hTableCliente[menu].container)
                        return 0;
                if (hTableCurrentRow != NULL)
                {
                        GetClientRect(hTableCurrentRow, &rect);
                        InvalidateRect(hTableCurrentRow, &rect, TRUE);
                        hTableCurrentRow = NULL;
                }
                hTableCurrentRow = hTableCliente[menu].container;
                SendMessageA(hTableCliente[menu].container, WM_PRINT, NULL, PRF_CHECKVISIBLE);
                break;
        case WM_PAINT:
                GetClientRect(hWnd, &rect);

                hdc = BeginPaint(hWnd, &ps);

                SetTextColor(hdc, RGB(0, 0, 0));
                SetBkMode(hdc, TRANSPARENT);

                GetWindowTextA(hWnd, text, 100);

                FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 255, 255)));

                SetRect(&rect, rect.left + 10, rect.top, rect.right, rect.bottom);
                DrawTextA(hdc, text, -1, &rect, DT_SINGLELINE | DT_VCENTER);

                draw_border_bottom(rect, hdc, CreateSolidBrush(RGB(47, 54, 64)), 2);
                draw_border_top(rect, hdc, CreateSolidBrush(RGB(47, 54, 64)), 2);
                draw_border_left(rect, hdc, CreateSolidBrush(RGB(47, 54, 64)), 2);
                draw_border_right(rect, hdc, CreateSolidBrush(RGB(47, 54, 64)), 2);

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

LRESULT CALLBACK BodyRowCellWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rect;
        char text[100];
        int menu;
        switch (msg)
        {
        case WM_PRINT:
                hdc = GetDC(hWnd);
                GetClientRect(hWnd, &rect);

                draw_border_top(rect, hdc, CreateSolidBrush(RGB(251, 197, 49)), 1);
                draw_border_bottom(rect, hdc, CreateSolidBrush(RGB(251, 197, 49)), 1);
                draw_border_left(rect, hdc, CreateSolidBrush(RGB(251, 197, 49)), 1);
                draw_border_right(rect, hdc, CreateSolidBrush(RGB(251, 197, 49)), 1);

                ReleaseDC(hWnd, hdc);
                break;
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK BodyClientWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rect;
        char text[100];
        int menu;
        switch (msg)
        {
        case WM_LBUTTONDOWN:
                if (hTableCurrentRow != NULL)
                {
                        GetClientRect(hTableCurrentRow, &rect);
                        InvalidateRect(hTableCurrentRow, &rect, TRUE);
                        hTableCurrentRow = NULL;
                }
                break;
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}