#include <windows.h>
#include <windowsx.h>
#include <wchar.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <wingdi.h>
#include <math.h>

#include "handlers/colors.h"
#include "handlers/productos.h"
#include "handlers/ventas.h"
#include "handlers/user.h"
#include "handlers/winProc.h"
#include "handlers/windows.h"
#include "handlers/draw.h"
#include "handlers/error.h"
#include "handlers/struct.h"
#include "handlers/caracteres.h"
#include "handlers/clientes.h"
#include "handlers/facturas.h"

int destroyingWindow = 0;
int mouseTranking = 0;
int mouseTrack = 0;
int display_scrollbar = 0;

LRESULT CALLBACK DivWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        char text[100];

        int newPos;
        int oldPos;

        SCROLLINFO scrollInfo;
        RECT rect;
        RECT rectMainWindow;
        RECT rectContainer;
        RECT rectBodyClientes;
        int cxClient, cyClient;
        SCROLLINFO sbInfo;

        int menu;

        PAINTSTRUCT ps;
        HDC hdc;
        int inicio, fin, y;

        switch (msg)
        {
        case WM_CREATE:
                menu = GetMenu(hWnd);
                if (hCurrentBody == hBodyClientes)
                {
                        GetClientRect(hBodyClientes, &rectBodyClientes);
                        GetClientRect(hMain, &rectMainWindow);
                        if (rows_clients_table > (rectMainWindow.bottom - HeaderHeight) / ROW_TABLE_HEIGHT)
                                cxColumnTable = (rectBodyClientes.right - SCROLLBAR_WIDTH) / nColumnsTable;
                        else
                                cxColumnTable = rectBodyClientes.right / nColumnsTable;
                }
                else if (menu == LIST_CLIENTS)
                {
                        GetClientRect(hWnd, &rect);
                        if (rows_clients_table > rect.bottom / ROW_TABLE_HEIGHT)
                                cxColumnTable = (rect.right - SCROLLBAR_WIDTH + 15) / nColumnsTable;
                        else
                                cxColumnTable = (rect.right - 15) / nColumnsTable;
                }
                else if (menu == LIST_PRODUCTS)
                {
                        GetClientRect(hWnd, &rect);

                        if (rows_product_table > rect.bottom / ROW_TABLE_HEIGHT)
                                cxColumnTableProduct = (rect.right - SCROLLBAR_WIDTH) / 6;
                        else
                                cxColumnTableProduct = (rect.right) / 6;
                }
                else if (menu == LIST_CURRENT_PRODUCTS)
                {
                        GetClientRect(hWnd, &rect);

                        if (rows_currentProduct_table > rect.bottom / ROW_TABLE_HEIGHT)
                                cxColumnTableCurrentProduct = (rect.right - SCROLLBAR_WIDTH) / 6;
                        else
                                cxColumnTableCurrentProduct = (rect.right) / 6;
                }
                else if (menu == LIST_VENTAS)
                {
                        GetClientRect(hWnd, &rect);
                        if (rows_ventas_table > rect.bottom / ROW_TABLE_HEIGHT)
                                cxColumnTableVentas = (rect.right - 15) / 5;
                        else
                                cxColumnTableVentas = (rect.right / 5);
                }
                else if (menu == LIST_PRODUCTS_VENTAS)
                {
                        GetClientRect(hWnd, &rect);

                        int position = GetMenu(hTableCurrentRow);

                        char ID_venta[20];
                        STRUCTVENTASDATA data = dataVentas[position];

                        int cantidadDeProductos = get_amounts_products_venta(data.ID);

                        if (cantidadDeProductos > rect.bottom / ROW_TABLE_HEIGHT)
                                cxColumnTableProductsVentas = (rect.right - SCROLLBAR_WIDTH) / 4;
                        else
                                cxColumnTableProductsVentas = (rect.right / 4);
                }
                break;
        case WM_SIZE:

                cxClient = LOWORD(lp);
                cyClient = HIWORD(lp);

                menu = GetMenu(hWnd);

                if (hCurrentBody == hBodyClientes)
                {
                        GetClientRect(hMain, &rectMainWindow);

                        sbInfo.nPos = 0;
                        sbInfo.nMin = 0;
                        sbInfo.cbSize = sizeof(SCROLLINFO);

                        if (rows_clients_table > cyClient / ROW_TABLE_HEIGHT)
                        {
                                sbInfo.nMax = rows_clients_table - 1;
                                sbInfo.nPage = (cyClient / 20);
                                sbInfo.fMask = SIF_ALL;
                                SetScrollInfo(hWnd, SB_VERT, &sbInfo, TRUE);
                                display_scrollbar = 1;
                        }
                }
                else if (menu == LIST_CLIENTS)
                {
                        sbInfo.nPos = 0;
                        sbInfo.nMin = 0;
                        sbInfo.cbSize = sizeof(SCROLLINFO);

                        if (rows_clients_table > cyClient / ROW_TABLE_HEIGHT)
                        {
                                sbInfo.nMax = rows_clients_table - 1;
                                sbInfo.nPage = (cyClient / 20);
                                sbInfo.fMask = SIF_ALL;
                                SetScrollInfo(hWnd, SB_VERT, &sbInfo, TRUE);
                                display_scrollbar = 1;
                        }
                }
                else if (menu == LIST_PRODUCTS)
                {
                        sbInfo.nPos = 0;
                        sbInfo.nMin = 0;
                        sbInfo.cbSize = sizeof(SCROLLINFO);

                        if (rows_product_table > cyClient / ROW_TABLE_HEIGHT)
                        {
                                sbInfo.nMax = rows_product_table - 1;
                                sbInfo.nPage = (cyClient / ROW_TABLE_HEIGHT);
                                sbInfo.fMask = SIF_ALL;
                                SetScrollInfo(hWnd, SB_VERT, &sbInfo, TRUE);
                                display_scrollbar = 1;
                        }
                }
                else if (menu == LIST_CURRENT_PRODUCTS)
                {
                        sbInfo.nPos = 0;
                        sbInfo.nMin = 0;
                        sbInfo.cbSize = sizeof(SCROLLINFO);

                        if (rows_currentProduct_table > cyClient / ROW_TABLE_HEIGHT)
                        {
                                sbInfo.nMax = rows_currentProduct_table - 1;
                                sbInfo.nPage = (cyClient / ROW_TABLE_HEIGHT);
                                sbInfo.fMask = SIF_ALL;
                                SetScrollInfo(hWnd, SB_VERT, &sbInfo, TRUE);
                                display_scrollbar = 1;
                        }
                }
                else if (menu == LIST_VENTAS)
                {
                        sbInfo.nPos = 0;
                        sbInfo.nMin = 0;
                        sbInfo.cbSize = sizeof(SCROLLINFO);

                        if (rows_ventas_table > cyClient / ROW_TABLE_HEIGHT)
                        {
                                sbInfo.nMax = rows_ventas_table - 1;
                                sbInfo.nPage = (cyClient / ROW_TABLE_HEIGHT);
                                sbInfo.fMask = SIF_ALL;
                                SetScrollInfo(hWnd, SB_VERT, &sbInfo, TRUE);
                                display_scrollbar = 1;
                        }
                }
                else if (menu == LIST_PRODUCTS_VENTAS)
                {
                        menu = GetMenu(hTableCurrentRow);

                        char ID_venta[20];
                        STRUCTVENTASDATA data = dataVentas[menu];

                        int cantidadDeProductos = get_amounts_products_venta(data.ID);

                        sbInfo.nPos = 0;
                        sbInfo.nMin = 0;
                        sbInfo.cbSize = sizeof(SCROLLINFO);

                        if (cantidadDeProductos > cyClient / ROW_TABLE_HEIGHT)
                        {
                                sbInfo.nMax = cantidadDeProductos - 1;
                                sbInfo.nPage = (cyClient / ROW_TABLE_HEIGHT);
                                sbInfo.fMask = SIF_ALL;
                                SetScrollInfo(hWnd, SB_VERT, &sbInfo, TRUE);
                                display_scrollbar = 1;
                        }
                }
                break;
        case WM_VSCROLL:

                scrollInfo.cbSize = sizeof(SCROLLINFO);
                scrollInfo.fMask = SIF_POS | SIF_RANGE | SIF_TRACKPOS | SIF_PAGE;

                GetScrollInfo(hWnd, SB_VERT, &scrollInfo);

                oldPos = scrollInfo.nPos;

                switch (LOWORD(wp))
                {
                case SB_PAGEUP:
                        scrollInfo.nPos -= scrollInfo.nPage;
                        break;
                case SB_PAGEDOWN:
                        GetClientRect(hMain, &rect);
                        scrollInfo.nPos += scrollInfo.nPage;
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

                        if (scrollInfo.nPos < scrollInfo.nMax - (scrollInfo.nPage - 1))
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
                        ScrollWindow(hWnd, 0, ROW_TABLE_HEIGHT * (oldPos - newPos), NULL, NULL);
                        UpdateWindow(hWnd);
                }
                break;
        case WM_PAINT:
                hdc = BeginPaint(hWnd, &ps);

                scrollInfo.cbSize = sizeof(SCROLLINFO);
                scrollInfo.fMask = SIF_ALL;

                menu = GetMenu(hWnd);

                GetScrollInfo(hWnd, SB_VERT, &scrollInfo);

                if (menu == LIST_CLIENTS)
                {
                        inicio = max((long)0, scrollInfo.nPos + ps.rcPaint.top / ROW_TABLE_HEIGHT);
                        fin = min((long)rows_clients_table - 1, scrollInfo.nPos + ps.rcPaint.bottom / ROW_TABLE_HEIGHT);

                        for (int i = inicio; i <= fin; i++)
                        {
                                y = ROW_TABLE_HEIGHT * (i - scrollInfo.nPos);
                                InvalidateRect(hTableCliente[i].container, NULL, FALSE);
                        }
                }
                else if (menu == LIST_PRODUCTS)
                {
                        inicio = max((long)0, scrollInfo.nPos + ps.rcPaint.top / ROW_TABLE_HEIGHT);
                        fin = min((long)rows_product_table - 1, scrollInfo.nPos + ps.rcPaint.bottom / ROW_TABLE_HEIGHT);

                        for (int i = inicio; i <= fin; i++)
                        {
                                y = ROW_TABLE_HEIGHT * (i - scrollInfo.nPos);
                                InvalidateRect(h_rows_product_table[i], NULL, TRUE);
                        }
                }
                else if (menu == LIST_CURRENT_PRODUCTS)
                {

                        inicio = max((long)0, scrollInfo.nPos + ps.rcPaint.top / ROW_TABLE_HEIGHT);
                        fin = min((long)rows_currentProduct_table - 1, scrollInfo.nPos + ps.rcPaint.bottom / ROW_TABLE_HEIGHT);

                        for (int i = inicio; i <= fin; i++)
                        {
                                y = ROW_TABLE_HEIGHT * (i - scrollInfo.nPos);
                                InvalidateRect(h_rows_currentProduct_table[i], NULL, TRUE);
                        }
                }
                else if (menu == LIST_VENTAS)
                {

                        inicio = max((long)0, scrollInfo.nPos + ps.rcPaint.top / ROW_TABLE_HEIGHT);
                        fin = min((long)rows_ventas_table - 1, scrollInfo.nPos + ps.rcPaint.bottom / ROW_TABLE_HEIGHT);

                        for (int i = inicio; i <= fin; i++)
                        {
                                y = ROW_TABLE_HEIGHT * (i - scrollInfo.nPos);
                                InvalidateRect(h_rows_ventas_table[i], NULL, TRUE);
                        }
                }
                else if (menu == LIST_PRODUCTS_VENTAS)
                {
                        int position = GetMenu(hTableCurrentRow);

                        char ID_venta[20];
                        STRUCTVENTASDATA data = dataVentas[position];

                        int row = search_venta_ID_venta(data.ID);
                        int lenColProductos = get_len_col_ventas(row, 2);
                        int cantidadDeProductos = get_amounts_products_venta(data.ID);

                        char productos[lenColProductos + 4];

                        get_productos_venta(row, productos);

                        GetClientRect(hWnd, &rect);

                        int nPos = 0;

                        if (cantidadDeProductos > rect.bottom / ROW_TABLE_HEIGHT)
                                nPos = scrollInfo.nPos;

                        inicio = max((long)0, nPos + ps.rcPaint.top / ROW_TABLE_HEIGHT);
                        fin = min((long)cantidadDeProductos - 1, nPos + ps.rcPaint.bottom / ROW_TABLE_HEIGHT);

                        int width = cxColumnTableProductsVentas;
                        FillRect(hdc, &rect, CreateSolidBrush(COLOR_WHITE));

                        STRUCTCURRENTPRODUCTOSDATA productosVenta[cantidadDeProductos + 1];

                        char subProducto[50];
                        int x = 0;
                        int w = 0;
                        char comprobacionDeCaracter[2];

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

                                        x = -1;
                                        w++;
                                }
                                x++;
                        }
                        w = 0;

                        for (int i = inicio; i <= fin; i++)
                        {
                                y = ROW_TABLE_HEIGHT * (i - nPos);

                                char precio[20];
                                char nombre[20];
                                char descuento[20];
                                char amount[20];

                                int rowProducto = search_product(productosVenta[i].ID);

                                get_name_product(rowProducto, nombre);
                                get_discount_product(rowProducto, descuento);
                                get_price_product(rowProducto, precio);

                                sprintf(amount, "%d", productosVenta[i].amount);
                                sprintf(descuento, "%s%%", descuento);
                                sprintf(precio, "%s Bs", precio);

                                int lenName = strlen(nombre);
                                int lenDescuento = strlen(descuento) + 1;
                                int lenPrecio = strlen(precio) + 1;
                                int lenAmount = strlen(amount) + 1;

                                draw_cell(nombre, hdc, 0, y, width, ROW_TABLE_HEIGHT);
                                draw_cell(amount, hdc, width, y, width, ROW_TABLE_HEIGHT);
                                draw_cell(descuento, hdc, width * 2, y, width, ROW_TABLE_HEIGHT);
                                draw_cell(precio, hdc, width * 3, y, width, ROW_TABLE_HEIGHT);

                                SetRect(&rect, 0, y, 2, y + ROW_TABLE_HEIGHT);
                                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                                SetRect(&rect, width, y, width + 1, y + ROW_TABLE_HEIGHT);
                                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                                SetRect(&rect, (width * 2), y, (width * 2) + 1, y + ROW_TABLE_HEIGHT);
                                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                                SetRect(&rect, (width * 3), y, (width * 3) + 1, y + ROW_TABLE_HEIGHT);
                                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                                SetRect(&rect, (width * 4) - 1, y, (width * 4) + 2, y + ROW_TABLE_HEIGHT);
                                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                                SetRect(&rect, 0, y, width * 4, y + 1);
                                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                                SetRect(&rect, 0, y + ROW_TABLE_HEIGHT - 1, width * 4, y + ROW_TABLE_HEIGHT);
                                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));
                        }
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

LRESULT CALLBACK ClientFacturaWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

        int cxClient;
        int cyClient;
        int totalHeight;

        int newPos;
        int oldPos;

        char text[100];

        SCROLLINFO sbInfo;
        RECT rect;
        int cantidadDeProductos = 1;
        STRUCTVENTASDATA data;

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
        case WM_SIZE:
                cxClient = LOWORD(lp);
                cyClient = HIWORD(lp);

                data = dataVentas[(int)GetMenu(hTableCurrentRow)];

                cantidadDeProductos = get_amounts_products_venta(data.ID);

                totalHeight = cantidadDeProductos + (200 / ROW_TABLE_HEIGHT);

                sbInfo.nPos = 0;
                sbInfo.nMin = 0;
                sbInfo.cbSize = sizeof(SCROLLINFO);

                if (totalHeight > cyClient / ROW_TABLE_HEIGHT)
                {
                        sbInfo.nMax = totalHeight - 1;
                        sbInfo.nPage = (cyClient / ROW_TABLE_HEIGHT);
                        sbInfo.fMask = SIF_ALL;
                        SetScrollInfo(hWnd, SB_VERT, &sbInfo, TRUE);
                        display_scrollbar = 1;
                }
                break;
        case WM_VSCROLL:
                sbInfo.cbSize = sizeof(SCROLLINFO);
                sbInfo.fMask = SIF_POS | SIF_RANGE | SIF_TRACKPOS | SIF_PAGE;

                GetScrollInfo(hWnd, SB_VERT, &sbInfo);

                oldPos = sbInfo.nPos;

                switch (LOWORD(wp))
                {
                case SB_PAGEUP:
                        sbInfo.nPos -= sbInfo.nPage;
                        break;
                case SB_PAGEDOWN:
                        GetClientRect(hMain, &rect);
                        sbInfo.nPos += sbInfo.nPage;
                        break;
                case SB_BOTTOM:
                        sbInfo.nPos = sbInfo.nMax;
                        break;
                case SB_TOP:
                        sbInfo.nPos = sbInfo.nMin;
                        break;
                case SB_LINEUP:
                        if (sbInfo.nPos > 0)
                                sbInfo.nPos -= 1;
                        break;
                case SB_LINEDOWN:
                        if (sbInfo.nPos < sbInfo.nMax - (sbInfo.nPage - 1))
                                sbInfo.nPos += 1;
                        break;
                case SB_THUMBTRACK:
                case SB_THUMBPOSITION:
                        sbInfo.nPos = HIWORD(wp);
                        break;
                }

                sbInfo.fMask = SIF_POS;
                SetScrollInfo(hWnd, SB_VERT, &sbInfo, TRUE);

                newPos = sbInfo.nPos;

                if (newPos != oldPos)
                {
                        GetClientRect(hWnd, &rect);
                        ScrollWindow(hWnd, 0, ROW_TABLE_HEIGHT * (oldPos - newPos), NULL, NULL);
                        UpdateWindow(hWnd);
                }
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
        HBRUSH menu;

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
                                CreateBodyProductos();
                        }
                        break;
                case NAV_CLIENTES:
                        if (hToolBarActual != hToolBarClientes)
                        {
                                ShowWindow(hToolBarActual, SW_HIDE);
                                ShowWindow(hToolBarClientes, SW_SHOW);
                                hToolBarActual = hToolBarClientes;
                                DestroyWindow(hCurrentBody);
                                CreateBodyClienteMainWindow();
                        }
                        break;
                case NAV_VENTAS:
                        if (hToolBarActual != hToolBarVentas)
                        {
                                ShowWindow(hToolBarActual, SW_HIDE);
                                ShowWindow(hToolBarVentas, SW_SHOW);
                                hToolBarActual = hToolBarVentas;
                                DestroyWindow(hCurrentBody);
                                CreateBodyVentasMainWindow(TRUE);
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
        int row;

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
                        CreateBodyClienteMainWindow();
                        break;
                case TOOLBAR_IMAGE_MODIFY_CLIENTE:
                        if (hTableCurrentRow != NULL)
                        {
                                if (hTableCurrentRow == NULL)
                                        return 0;
                                while (hTableCurrentRow != hTableCliente[i].container)
                                        i++;
                                CreateFormClient(FALSE, i, FALSE);
                        }
                        break;
                case TOOLBAR_IMAGE_NEW_CLIENTE:
                        CreateFormClient(TRUE, -1, FALSE);
                        break;

                case TOOLBAR_IMAGE_NEW_INVENTARIO:
                        CreateFormProduct(TRUE, -1);
                        break;
                case TOOLBAR_IMAGE_MODIFY_INVENTARIO:
                        if (hTableCurrentRow == NULL)
                                return 0;
                        while (hTableCurrentRow != h_rows_product_table[i])
                                i++;
                        CreateFormProduct(FALSE, i);
                        break;
                case TOOLBAR_IMAGE_DELETE_INVENTARIO:
                        if (hTableCurrentRow == NULL)
                                return 0;
                        while (hTableCurrentRow != h_rows_product_table[i])
                                i++;
                        row = search_product(dataProductos[i].ID);

                        hTableCurrentRow = NULL;
                        hide_product(row);

                        DestroyWindow(hBodyInventario);

                        CreateBodyProductos();
                        break;

                case TOOLBAR_IMAGE_HISTORIAL_VENTAS:
                        i = get_jumplines_venta_file();
                        if (i == 0)
                        {
                                MessageBox(NULL, "Error: Debe Registrar una venta", NULL, MB_ICONERROR);
                                return 0;
                        }
                        DestroyWindow(hBodyVentas);
                        hTableCurrentRow == NULL;
                        CreateBodyVentasMainWindow(FALSE);
                        break;
                case TOOLBAR_IMAGE_NEW_VENTAS:
                        DestroyWindow(hBodyVentas);
                        hTableCurrentRow == NULL;
                        CreateBodyVentasMainWindow(TRUE);
                        break;
                case TOOLBAR_IMAGE_VER_VENTAS:
                        if (hTableCurrentRow == NULL)
                                return 0;
                        CreateWindowViewVenta();
                        break;
                }
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
                case TOOLBAR_IMAGE_HISTORIAL_VENTAS:
                        hHistorialVentaImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 45 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_MODIFY_INVENTARIO, NULL, NULL);
                        break;
                case TOOLBAR_IMAGE_VER_VENTAS:
                        hVerVentaImage = CreateWindowA("STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 45 - 15, 5, 30, 30, hWnd, TOOLBAR_IMAGE_MODIFY_INVENTARIO, NULL, NULL);
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
                case TOOLBAR_IMAGE_HISTORIAL_VENTAS:
                        InvalidateRect(hHistorialVentaImage, NULL, TRUE);
                        break;
                case TOOLBAR_IMAGE_VER_VENTAS:
                        InvalidateRect(hVerVentaImage, NULL, TRUE);
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
                case TOOLBAR_IMAGE_HISTORIAL_VENTAS:
                        loadImagesHistorial();
                        SendMessageA(hHistorialVentaImage, STM_SETIMAGE, IMAGE_BITMAP, hImageHistorial);
                        break;
                case TOOLBAR_IMAGE_VER_VENTAS:
                        loadImagesView();
                        SendMessageA(hVerVentaImage, STM_SETIMAGE, IMAGE_BITMAP, hImageVer);
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
        int menu;

        switch (msg)
        {
        case WM_PAINT:
                GetClientRect(hWnd, &rect);

                hdc = BeginPaint(hWnd, &ps);

                menu = GetMenu(hWnd);
                SetTextColor(hdc, RGB(0, 0, 0));

                SetBkMode(hdc, TRANSPARENT);

                GetWindowTextA(hWnd, text, 100);

                if (menu == SS_CENTER)
                        DrawTextA(hdc, text, -1, &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
                else
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
        char amount[100];

        int menu;
        int row = 0;
        int productLen = 0;

        STRUCTCLIENTESDATA dataC;
        STRUCTPRODUCTOSDATA dataP;
        STRUCTPRODUCTOSDATA newDataP;
        STRUCTVENTASDATA dataV;
        STRUCTUSERDATA dataUserSingup;
        char *productos;

        switch (msg)
        {
        case WM_COMMAND:
                switch (wp)
                {
                case SINGUP_USER:
                        GetWindowTextA(hName, dataUserSingup.username, 100);
                        GetWindowTextA(hPassword, dataUserSingup.password, 100);
                        GetWindowTextA(hRifCompany, dataUserSingup.rif_company, 100);
                        GetWindowTextA(hDireccionCompany, dataUserSingup.direccion, 100);

                        if (!strcmp(dataUserSingup.username, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte un Usuario", NULL, MB_ICONERROR);
                                return 0;
                        }

                        if (search_user(dataUserSingup.username) >= 0)
                        {
                                MessageBoxA(NULL, "Error, Usuario Ya Existente", NULL, MB_ICONERROR);
                                return 0;
                        }

                        if (!strcmp(dataUserSingup.password, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte una contraseña", NULL, MB_ICONERROR);
                        }

                        if (!strcmp(dataUserSingup.direccion, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte una direccion", NULL, MB_ICONERROR);
                                return 0;
                        }

                        if (!strcmp(dataUserSingup.rif_company, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte un RIF", NULL, MB_ICONERROR);
                                return 0;
                        }

                        if (solo_number(dataUserSingup.rif_company))
                        {
                                MessageBoxA(NULL, "Error, Solo se aceptan numeros en el RIF", NULL, MB_ICONERROR);
                                return 0;
                        }

                        if (create_new_user(dataUserSingup.username, dataUserSingup.password, "USER",
                                            dataUserSingup.rif_company, dataUserSingup.direccion) == 1)
                        {
                                MessageBox(NULL, "Usuario a sido creado Existosamente", NULL, MB_OK);
                        }
                        else
                        {
                                MessageBox(NULL, "Error, user.txt no encontrado", NULL, MB_ICONERROR);
                                return 0;
                        }
                        ShowWindow(hSingUp, SW_HIDE);
                        ShowWindow(hLogin, SW_SHOW);
                        break;
                case OPEN_SINGUP_USER_WINDOW:
                        CreateSingupWindow();
                        ShowWindow(hLogin, SW_HIDE);
                        break;
                case VIEW_FACTURA:
                        CreateWindowFactura();
                        break;
                case CREATE_CLIENT_FORM_VENTAS:
                        GetWindowTextA(hFormClient.name, dataC.name, 100);
                        GetWindowTextA(hFormClient.phone, dataC.phone, 20);
                        GetWindowTextA(hFormClient.TdP, dataC.TdP, 2);
                        GetWindowTextA(hFormClient.dni, dataC.dni, 20);
                        GetWindowTextA(hFormClient.zone, dataC.zone, 100);

                        if (!strcmp(dataC.name, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte un nombre", NULL, MB_ICONERROR);
                                return 0;
                        }
                        if (!strcmp(dataC.phone, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte un Telefono", NULL, MB_ICONERROR);
                                return 0;
                        }
                        if (!strcmp(dataC.TdP, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte una Naturaleza", NULL, MB_ICONERROR);
                                return 0;
                        }
                        if (!strcmp(dataC.dni, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte un DNI", NULL, MB_ICONERROR);
                                return 0;
                        }
                        if (!strcmp(dataC.zone, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte una Direccion", NULL, MB_ICONERROR);
                                return 0;
                        }

                        create_ID(dataC.ID);

                        new_client(dataC.ID, dataC.name, dataC.dni, dataC.phone, dataC.TdP);
                        create_new_invoices(dataC.zone, currentUser.rif_company, dataC.ID, currentUser.direccion);

                        DestroyWindow(hFormClient.container);
                        DestroyWindow(hBodyClientes);
                        hTableCurrentRow = NULL;

                        SetWindowTextA(hCurrentClientVentas.name, dataC.name);
                        SetWindowTextA(hCurrentClientVentas.phone, dataC.phone);
                        SetWindowTextA(hCurrentClientVentas.dni, dataC.dni);
                        SetWindowTextA(hCurrentClientVentas.TdP, dataC.TdP);
                        strcpy(CurrentClientVentas.ID, dataC.ID);
                        break;
                case OPEN_FORM_CLIENTS_VENTAS:
                        CreateFormClient(TRUE, -1, TRUE);
                        break;
                case ADD_CLIENT_VENTAS:
                        if (hTableCurrentRow == NULL)
                                return 0;
                        menu = GetMenu(hTableCurrentRow);

                        dataC = dataClient[menu];
                        CurrentClientVentas = dataClient[menu];

                        SetWindowTextA(hCurrentClientVentas.name, dataC.name);
                        SetWindowTextA(hCurrentClientVentas.phone, dataC.phone);
                        SetWindowTextA(hCurrentClientVentas.dni, dataC.dni);
                        SetWindowTextA(hCurrentClientVentas.TdP, dataC.TdP);

                        DestroyWindow(hBodyClientes);
                        hTableCurrentRow = NULL;
                        break;
                case CLOSE_WINDOW_CLIENTS_VENTAS:
                        DestroyWindow(hBodyClientes);
                        hTableCurrentRow = NULL;
                        break;
                case SELECT_CLIENT_VENTAS:
                        CreateWindowClients();
                        break;
                case NEW_VENTA:
                        if (rows_currentProduct_table > 0)
                        {
                                int i;
                                for (i = 0; i < rows_currentProduct_table; i++)
                                {
                                        productLen += strlen(CurrentProducts[i].ID);
                                        sprintf(text, "%d", CurrentProducts[i].amount);

                                        row = search_product(CurrentProducts[i].ID);
                                        get_stock_product(row, amount);

                                        if (atoi(amount) - CurrentProducts[i].amount < 0)
                                        {
                                                sprintf(text, "Error. No hay suficiente inventario de %s", CurrentProducts[i].name);
                                                MessageBox(NULL, text, NULL, MB_ICONERROR);
                                                return 0;
                                        }
                                        productLen += strlen(text);
                                        productLen += strlen(CurrentProducts[i].discount);
                                        productLen += 3;
                                }
                                productLen += i;

                                productos = (char *)malloc(sizeof(char));
                                productos = (char *)realloc(NULL, sizeof(char) * (productLen));

                                productos[0] = '\0';
                                for (i = 0; i < rows_currentProduct_table; i++)
                                {
                                        sprintf(text, "%s=%d?%s", CurrentProducts[i].ID, CurrentProducts[i].amount, CurrentProducts[i].discount);
                                        if (i != rows_currentProduct_table - 1)
                                                strcat(text, "/");
                                        strcat(productos, text);
                                }

                                if (!strcmp(CurrentClientVentas.ID, ""))
                                {
                                        MessageBox(NULL, "Error, Elija al cliente al que se vendera", "Error", MB_OK);
                                        return 0;
                                }

                                for (i = 0; i < rows_currentProduct_table; i++)
                                {
                                        row = search_product(CurrentProducts[i].ID);
                                        reduce_stock(row, CurrentProducts[i].amount);
                                }

                                create_ID(dataV.ID);
                                new_ventas(dataV.ID, productos, CurrentClientVentas.ID, "0");

                                rows_currentProduct_table = 0;

                                h_rows_currentProduct_table = (HWND *)realloc(NULL, sizeof(HWND));
                                CurrentProducts = (STRUCTCURRENTPRODUCTOSDATA *)realloc(NULL, sizeof(STRUCTCURRENTPRODUCTOSDATA));

                                DestroyWindow(hBodyVentas);

                                CreateBodyVentasMainWindow(TRUE);

                                free(productos);
                        }
                        break;
                case CLOSE_FORM_PRODUCT:
                        DestroyWindow(hFormProduct.container);
                        break;
                case CLOSE_WINDOW_PRODUCT_VENTAS:
                        DestroyWindow(hWindowProduct);
                        break;
                case WINDOW_PRODUCT_VENTAS:
                        Window_product_is_open = 1;
                        CreateWindowProducts();
                        break;
                case ADD_PRODUCT_VENTAS:
                        if (hTableCurrentRow != NULL)
                        {
                                menu = GetMenu(hTableCurrentRow);
                                int repeat = 0;

                                int i;

                                for (i = 0; i < rows_currentProduct_table; i++)
                                {
                                        if (!strcmp(dataProductos[menu].ID, CurrentProducts[i].ID))
                                        {
                                                repeat = 1;
                                                break;
                                        }
                                }

                                if (repeat)
                                {
                                        CurrentProducts[i].amount++;
                                        sprintf(CurrentProducts[i].price, "%d", (atoi(CurrentProducts[i].price) / (CurrentProducts[i].amount - 1)) * CurrentProducts[i].amount);
                                }
                                else
                                {

                                        STRUCTCURRENTPRODUCTOSDATA copyData[rows_currentProduct_table];

                                        for (i = 0; i < rows_currentProduct_table; i++)
                                        {
                                                copyData[i] = CurrentProducts[i];
                                        }

                                        rows_currentProduct_table++;

                                        h_rows_currentProduct_table = (HWND *)realloc(NULL, sizeof(HWND) * (rows_currentProduct_table + 1));
                                        CurrentProducts = (STRUCTCURRENTPRODUCTOSDATA *)realloc(CurrentProducts, sizeof(STRUCTCURRENTPRODUCTOSDATA) * (rows_currentProduct_table + 1));

                                        for (i = 0; i < rows_currentProduct_table; i++)
                                        {
                                                CurrentProducts[i] = copyData[i];
                                        }

                                        CurrentProducts[rows_currentProduct_table - 1].amount = 1;
                                        strcpy(CurrentProducts[rows_currentProduct_table - 1].category, dataProductos[menu].category);
                                        strcpy(CurrentProducts[rows_currentProduct_table - 1].discount, dataProductos[menu].discount);
                                        strcpy(CurrentProducts[rows_currentProduct_table - 1].name, dataProductos[menu].name);
                                        strcpy(CurrentProducts[rows_currentProduct_table - 1].ID, dataProductos[menu].ID);
                                        strcpy(CurrentProducts[rows_currentProduct_table - 1].price, dataProductos[menu].price);
                                }

                                DestroyWindow(hWindowProduct);
                                DestroyWindow(hTableCurrentProduct);

                                CreateTableListOfProducts(pTableCurrentProduct.x, pTableCurrentProduct.y, pTableCurrentProduct.cx, pTableCurrentProduct.cy);
                        }
                        break;
                case ADD_PRODUCT_FORM:
                        GetWindowTextA(hFormProduct.name, dataP.name, 100);
                        GetWindowTextA(hFormProduct.category, dataP.category, 100);
                        GetWindowTextA(hFormProduct.discount, dataP.discount, 20);
                        GetWindowTextA(hFormProduct.price, dataP.price, 20);
                        GetWindowTextA(hFormProduct.stock, dataP.stock, 20);

                        if (strlen(dataP.name) == 0)
                        {
                                MessageBoxA(NULL, "Inserte un Nombre", NULL, MB_ICONERROR);
                                return 0;
                        }

                        if (strlen(dataP.category) == 0)
                        {
                                MessageBoxA(NULL, "Inserte una Categoria", NULL, MB_ICONERROR);
                                return 0;
                        }

                        if (strlen(dataP.discount) == 0)
                        {
                                strcpy(dataP.discount, "0");
                        }

                        if (strlen(dataP.price) == 0)
                        {
                                MessageBoxA(NULL, "Inserte un Precio", NULL, MB_ICONERROR);
                                return 0;
                        }

                        if (strlen(dataP.stock) == 0)
                        {
                                MessageBoxA(NULL, "Inserte un Stock", NULL, MB_ICONERROR);
                                return 0;
                        }

                        create_ID(dataP.ID);

                        new_product(dataP.ID, dataP.name, dataP.price, dataP.discount, dataP.stock, dataP.category);

                        DestroyWindow(hFormProduct.container);
                        DestroyWindow(hBodyInventario);
                        hTableCurrentRow = NULL;

                        CreateBodyProductos();
                        break;

                case MODIFY_PRODUCT_FORM:
                        GetWindowTextA(hFormProduct.name, dataP.name, 100);
                        GetWindowTextA(hFormProduct.category, dataP.category, 100);
                        GetWindowTextA(hFormProduct.discount, dataP.discount, 20);
                        GetWindowTextA(hFormProduct.price, dataP.price, 20);
                        GetWindowTextA(hFormProduct.stock, dataP.stock, 20);

                        if (!strcmp(dataP.name, currentDataP.name))
                                strcpy(newDataP.name, currentDataP.name);
                        else
                                strcpy(newDataP.name, dataP.name);

                        if (!strcmp(dataP.category, currentDataP.category))
                                strcpy(newDataP.category, currentDataP.category);
                        else
                                strcpy(newDataP.category, dataP.category);

                        if (!strcmp(dataP.discount, currentDataP.discount))
                                strcpy(newDataP.discount, currentDataP.discount);
                        else
                                strcpy(newDataP.discount, dataP.discount);

                        if (!strcmp(dataP.price, currentDataP.price))
                                strcpy(newDataP.price, currentDataP.price);
                        else
                                strcpy(newDataP.price, dataP.price);

                        if (!strcmp(dataP.stock, currentDataP.stock))
                                strcpy(newDataP.stock, currentDataP.stock);
                        else
                                strcpy(newDataP.stock, dataP.stock);

                        hTableCurrentRow = NULL;

                        modify_product(currentDataP.ID, currentDataP.date, newDataP.name, newDataP.price, newDataP.discount, newDataP.stock, newDataP.category);

                        DestroyWindow(hFormProduct.container);
                        DestroyWindow(hBodyInventario);

                        CreateBodyProductos();
                        break;
                case DELETE_PRODUCT_VENTAS:
                        if (hTableCurrentRow != NULL && rows_currentProduct_table > 0)
                        {

                                menu = GetMenu(hTableCurrentRow);

                                STRUCTCURRENTPRODUCTOSDATA copyData[rows_currentProduct_table - 1];

                                int i;
                                int x = 0;

                                for (i = 0; i < rows_currentProduct_table; i++)
                                {
                                        if (i != menu)
                                        {
                                                copyData[x] = CurrentProducts[i];
                                                x++;
                                        }
                                }

                                h_rows_currentProduct_table = (HWND *)realloc(NULL, sizeof(HWND) * (rows_currentProduct_table - 1));
                                CurrentProducts = (STRUCTCURRENTPRODUCTOSDATA *)realloc(NULL, sizeof(STRUCTCURRENTPRODUCTOSDATA) * (rows_currentProduct_table - 1));
                                rows_currentProduct_table--;

                                if (i > 0)
                                {
                                        for (i = 0; i < rows_currentProduct_table; i++)
                                        {
                                                CurrentProducts[i] = copyData[i];
                                        }
                                }

                                DestroyWindow(hWindowProduct);
                                DestroyWindow(hTableCurrentProduct);
                                hTableCurrentRow = NULL;

                                CreateTableListOfProducts(pTableCurrentProduct.x, pTableCurrentProduct.y, pTableCurrentProduct.cx, pTableCurrentProduct.cy);
                        }
                        break;
                case MODIFY_CLIENT_FORM:
                        GetWindowTextA(hFormClient.name, dataC.name, 100);
                        GetWindowTextA(hFormClient.phone, dataC.phone, 20);
                        GetWindowTextA(hFormClient.TdP, dataC.TdP, 2);
                        GetWindowTextA(hFormClient.dni, dataC.dni, 20);
                        GetWindowTextA(hFormClient.zone, dataC.zone, 100);

                        int row;

                        if (strcmp(dataC.name, currentDataC.name))
                        {
                                row = search_clients(currentDataC.ID);
                                modify_name_clients(row, dataC.name);
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

                        char direccion[100];

                        int rowFactura = search_invoice_id_client(currentDataC.ID);

                        get_zone_invoice(rowFactura, direccion);

                        if (strcmp(dataC.zone, direccion))
                        {
                                char ID_factura[20];
                                char rif_company[100];
                                char date[20];
                                char direccion_company[100];

                                get_ID_invoice(rowFactura, ID_factura);
                                get_rif_company_invoice(rowFactura, rif_company);
                                get_date_invoice(rowFactura, date);
                                get_direction_company_invoice(rowFactura, direccion_company);

                                modify_invoices(ID_factura, dataC.zone, rif_company, date, currentDataC.ID, direccion_company);
                        }

                        DestroyWindow(hFormClient.container);
                        DestroyWindow(hBodyClientes);
                        hTableCurrentRow = NULL;
                        CreateBodyClienteMainWindow();

                        break;
                case CREATE_CLIENT_FORM:
                        GetWindowTextA(hFormClient.name, dataC.name, 100);
                        GetWindowTextA(hFormClient.phone, dataC.phone, 20);
                        GetWindowTextA(hFormClient.TdP, dataC.TdP, 2);
                        GetWindowTextA(hFormClient.dni, dataC.dni, 20);
                        GetWindowTextA(hFormClient.zone, dataC.zone, 100);

                        if (!strcmp(dataC.name, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte un nombre", NULL, MB_ICONERROR);
                                return 0;
                        }
                        if (!strcmp(dataC.phone, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte un Telefono", NULL, MB_ICONERROR);
                                return 0;
                        }
                        if (!strcmp(dataC.TdP, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte una Naturaleza", NULL, MB_ICONERROR);
                                return 0;
                        }
                        if (!strcmp(dataC.dni, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte un DNI", NULL, MB_ICONERROR);
                                return 0;
                        }
                        if (!strcmp(dataC.zone, ""))
                        {
                                MessageBoxA(NULL, "Error, Inserte una Direccion", NULL, MB_ICONERROR);
                                return 0;
                        }

                        create_ID(dataC.ID);

                        new_client(dataC.ID, dataC.name, dataC.dni, dataC.phone, dataC.TdP);
                        create_new_invoices(dataC.zone, currentUser.rif_company, dataC.ID, currentUser.direccion);

                        DestroyWindow(hFormClient.container);
                        DestroyWindow(hBodyClientes);
                        hTableCurrentRow = NULL;
                        CreateBodyClienteMainWindow();
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
                                get_data_user(log, currentUser.ID, currentUser.username, currentUser.password,
                                              currentUser.range, currentUser.rif_company, currentUser.direccion);
                                CreateMainWindow();
                                destroyingWindow = 1;
                                DestroyWindow(hLogin);
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
                InvalidateRect(hWnd, NULL, FALSE);
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
                case NEW_VENTA:
                case SELECT_CLIENT_VENTAS:
                case ADD_CLIENT_VENTAS:
                case VIEW_FACTURA:
                case OPEN_SINGUP_USER_WINDOW:
                case SINGUP_USER:
                        InvalidateRect(hWnd, NULL, FALSE);
                        break;
                case LOGIN_USER:
                case CREATE_CLIENT_FORM:
                case MODIFY_CLIENT_FORM:
                case ADD_PRODUCT_VENTAS:
                case ADD_PRODUCT_FORM:
                case WINDOW_PRODUCT_VENTAS:
                case MODIFY_PRODUCT_FORM:
                case OPEN_FORM_CLIENTS_VENTAS:
                case CREATE_CLIENT_FORM_VENTAS:
                        InvalidateRect(hWnd, NULL, FALSE);
                        break;
                case CLOSE_WINDOW:
                case CLOSE_CLIENT_FORM:
                case CLOSE_WINDOW_PRODUCT_VENTAS:
                case DELETE_PRODUCT_VENTAS:
                case CLOSE_FORM_PRODUCT:
                case CLOSE_WINDOW_CLIENTS_VENTAS:
                        InvalidateRect(hWnd, NULL, FALSE);
                        break;
                }

                ReleaseDC(hWnd, hdc);
                break;
        case WM_LBUTTONDOWN:
                if (mouseTranking)
                {
                        hdc = GetDC(hWnd);
                        menu = GetMenu(hWnd);
                        GetClientRect(hWnd, &rect);
                        GetWindowTextA(hWnd, text, 100);
                        switch (menu)
                        {
                        case NEW_VENTA:
                        case SELECT_CLIENT_VENTAS:
                        case ADD_CLIENT_VENTAS:
                        case VIEW_FACTURA:
                        case OPEN_SINGUP_USER_WINDOW:
                        case SINGUP_USER:
                                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_BLUE_CLICK), COLOR_BLACK, text);
                                break;
                        case LOGIN_USER:
                        case CREATE_CLIENT_FORM:
                        case MODIFY_CLIENT_FORM:
                        case ADD_PRODUCT_VENTAS:
                        case WINDOW_PRODUCT_VENTAS:
                        case ADD_PRODUCT_FORM:
                        case MODIFY_PRODUCT_FORM:
                        case OPEN_FORM_CLIENTS_VENTAS:
                        case CREATE_CLIENT_FORM_VENTAS:
                                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN_CLICK), COLOR_WHITE, text);
                                break;
                        case CLOSE_WINDOW:
                        case DELETE_PRODUCT_VENTAS:
                        case CLOSE_CLIENT_FORM:
                        case CLOSE_WINDOW_PRODUCT_VENTAS:
                        case CLOSE_FORM_PRODUCT:
                        case CLOSE_WINDOW_CLIENTS_VENTAS:
                                draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED_CLICK), COLOR_WHITE, text);
                                break;
                                ReleaseDC(hWnd, hdc);
                        }
                }
                break;
        case WM_MOUSEHOVER:
                GetClientRect(hWnd, &rect);
                hdc = GetDC(hWnd);

                menu = GetMenu(hWnd);
                GetWindowTextA(hWnd, text, 100);

                switch (menu)
                {
                case NEW_VENTA:
                case SELECT_CLIENT_VENTAS:
                case ADD_CLIENT_VENTAS:
                case VIEW_FACTURA:
                case OPEN_SINGUP_USER_WINDOW:
                case SINGUP_USER:
                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_BLUE_HOVER), COLOR_BLACK, text);
                        break;

                case LOGIN_USER:
                case MODIFY_CLIENT_FORM:
                case CREATE_CLIENT_FORM:
                case ADD_PRODUCT_VENTAS:
                case ADD_PRODUCT_FORM:
                case WINDOW_PRODUCT_VENTAS:
                case MODIFY_PRODUCT_FORM:
                case OPEN_FORM_CLIENTS_VENTAS:
                case CREATE_CLIENT_FORM_VENTAS:
                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN_HOVER), COLOR_WHITE, text);
                        break;
                case CLOSE_WINDOW:
                case CLOSE_CLIENT_FORM:
                case DELETE_PRODUCT_VENTAS:
                case CLOSE_WINDOW_PRODUCT_VENTAS:
                case CLOSE_FORM_PRODUCT:
                case CLOSE_WINDOW_CLIENTS_VENTAS:
                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_RED_HOVER), COLOR_WHITE, text);
                        break;
                }

                ReleaseDC(hWnd, hdc);
                break;
        case WM_PAINT:
                GetClientRect(hWnd, &rect);

                menu = GetMenu(hWnd);
                hdc = BeginPaint(hWnd, &ps);
                GetWindowTextA(hWnd, text, 100);

                switch (menu)
                {
                case NEW_VENTA:
                case SELECT_CLIENT_VENTAS:
                case ADD_CLIENT_VENTAS:
                case VIEW_FACTURA:
                case OPEN_SINGUP_USER_WINDOW:
                case SINGUP_USER:
                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_BLUE), COLOR_BLACK, text);
                        break;
                case LOGIN_USER:
                case CREATE_CLIENT_FORM:
                case ADD_PRODUCT_VENTAS:
                case ADD_PRODUCT_FORM:
                case MODIFY_CLIENT_FORM:
                case WINDOW_PRODUCT_VENTAS:
                case MODIFY_PRODUCT_FORM:
                case OPEN_FORM_CLIENTS_VENTAS:
                case CREATE_CLIENT_FORM_VENTAS:
                        draw_bg_button(hdc, rect, CreateSolidBrush(COLOR_GREEN), COLOR_BLACK, text);
                        break;
                case CLOSE_WINDOW:
                case CLOSE_CLIENT_FORM:
                case DELETE_PRODUCT_VENTAS:
                case CLOSE_WINDOW_PRODUCT_VENTAS:
                case CLOSE_FORM_PRODUCT:
                case CLOSE_WINDOW_CLIENTS_VENTAS:
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
                case SINGUP_USER:
                case CLOSE_WINDOW:
                case WINDOW_PRODUCT_VENTAS:
                case CLOSE_WINDOW_PRODUCT_VENTAS:
                case ADD_PRODUCT_FORM:
                case MODIFY_PRODUCT_FORM:
                case CLOSE_FORM_PRODUCT:
                case SELECT_CLIENT_VENTAS:
                case ADD_CLIENT_VENTAS:
                case CLOSE_WINDOW_CLIENTS_VENTAS:
                case CREATE_CLIENT_FORM_VENTAS:
                case VIEW_FACTURA:
                case OPEN_SINGUP_USER_WINDOW:
                        DestroyWindow(hWnd);
                        break;
                case CREATE_CLIENT_FORM:
                case CLOSE_CLIENT_FORM:
                case MODIFY_CLIENT_FORM:
                        DestroyWindow(hFormClient.container);
                        break;
                default:
                        DestroyWindow(hWnd);
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

LRESULT CALLBACK BodyRowCellHistorialVentasWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rect;
        char text[100];
        char amount[20];
        char discount[5];
        char precio[20];
        char precioIVA[20];

        char *productos;
        char productoSeparado[100];
        int colLenProducts;

        float precioTotal = 0;
        char name[100];
        int menu;
        int width;
        int row;
        int x = 0;

        HWND temp;

        STRUCTVENTASDATA data;

        switch (msg)
        {
        case WM_LBUTTONDOWN:
                menu = GetMenu(hWnd);
                if (hTableCurrentRow == h_rows_ventas_table[menu])
                        return 0;
                if (hTableCurrentRow != NULL)
                {
                        temp = hTableCurrentRow;
                        hTableCurrentRow = NULL;
                        GetClientRect(temp, &rect);
                        InvalidateRect(temp, &rect, TRUE);
                }
                GetClientRect(hWnd, &rect);
                hTableCurrentRow = h_rows_ventas_table[menu];
                InvalidateRect(hTableCurrentRow, &rect, TRUE);
                break;
        case WM_PAINT:
                hdc = BeginPaint(hWnd, &ps);

                GetClientRect(hWnd, &rect);
                menu = GetMenu(hWnd);

                data = dataVentas[menu];

                width = rect.right / 5;

                // Obtener el nombre del cliente
                row = search_clients(data.ID_cliente);
                get_name_clients(row, name);

                // Obtener la lista de productos comprados
                row = search_venta_ID_venta(data.ID);
                colLenProducts = get_len_col_ventas(row, 2);
                productos = (char *)malloc((colLenProducts + 1) * sizeof(char));
                get_productos_venta(row, productos);

                for (int i = 0; i < colLenProducts + 1; i++)
                {
                        if (productos[i] != '/' && productos[i] != '\0')
                                productoSeparado[x] = productos[i];
                        else
                        {
                                productoSeparado[x] = '\0';

                                char strCantidad[20];
                                char strDescuento[20];
                                char ID_producto[20];
                                char strPrecio[20];
                                int precio;
                                int descuento;
                                int cantidad;

                                // Estas variable se encargan de marcar cuando termina ID, precio y descuento
                                int fID;
                                int fCantidad;
                                int fDescuento;

                                for (int j = 0; j < x + 1; j++)
                                {
                                        if (productoSeparado[j] == '=')
                                                fID = j;
                                        if (productoSeparado[j] == '?')
                                                fCantidad = j;
                                        if (productoSeparado[j] == '\0')
                                                fDescuento = j;
                                }

                                substr(ID_producto, productoSeparado, 0, fID);
                                substr(strCantidad, productoSeparado, fID + 1, fCantidad);
                                substr(strDescuento, productoSeparado, fCantidad + 1, fDescuento);

                                row = search_product(ID_producto);

                                get_price_product(row, strPrecio);

                                precio = atoi(strPrecio);
                                descuento = atoi(strDescuento);
                                cantidad = atoi(strCantidad);

                                precioTotal += (precio - (precio * (descuento / 100))) * cantidad;

                                x = -1;
                        }
                        x++;
                }

                sprintf(precio, "%.2f Bs", precioTotal);
                sprintf(precioIVA, "%.2f Bs", precioTotal * 1.16);
                sprintf(discount, "%s%%", data.discount);

                draw_cell(name, hdc, 0, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(discount, hdc, width, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(precio, hdc, width * 2, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(precioIVA, hdc, width * 3, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(data.date, hdc, width * 4, 0, width, ROW_TABLE_HEIGHT);

                free(productos);

                if (hTableCurrentRow != hWnd)
                        draw_border(hdc, rect, CreateSolidBrush(RGB(0, 0, 0)), 2);
                else
                {
                        draw_border(hdc, rect, CreateSolidBrush(COLOR_YELLOW), 3);
                }

                SetRect(&rect, width - 1, 0, width + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 2) - 1, 0, (width * 2) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 3) - 1, 0, (width * 3) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 4) - 1, 0, (width * 4) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 5) - 1, 0, (width * 5) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                EndPaint(hWnd, &ps);
                break;
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK BodyRowCellCurrentProductWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rect;
        char text[100];
        char amount[20];
        char discount[5];
        char precioTotal[25];
        char precio[20];
        int menu;
        int width;

        HWND temp;

        STRUCTCURRENTPRODUCTOSDATA data;

        switch (msg)
        {
        case WM_LBUTTONDOWN:
                menu = GetMenu(hWnd);
                if (hTableCurrentRow == h_rows_currentProduct_table[menu])
                        return 0;
                if (hTableCurrentRow != NULL)
                {
                        temp = hTableCurrentRow;
                        hTableCurrentRow = NULL;
                        GetClientRect(temp, &rect);
                        InvalidateRect(temp, &rect, TRUE);
                }
                GetClientRect(hWnd, &rect);
                hTableCurrentRow = h_rows_currentProduct_table[menu];
                InvalidateRect(hTableCurrentRow, &rect, TRUE);
                break;
        case WM_PAINT:
                hdc = BeginPaint(hWnd, &ps);

                GetClientRect(hWnd, &rect);
                menu = GetMenu(hWnd);

                data = CurrentProducts[menu];

                width = rect.right / 6;

                sprintf(precioTotal, "%.2f Bs", (float)atoi(data.price) - (atoi(data.price) * (atoi(data.discount) * 0.01)));
                sprintf(precio, "%.2f Bs", data.price);
                sprintf(amount, "%d", data.amount);
                sprintf(discount, "%s%%", data.discount);

                draw_cell(data.name, hdc, 0, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(data.category, hdc, width, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(amount, hdc, width * 2, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(discount, hdc, width * 3, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(precio, hdc, width * 4, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(precioTotal, hdc, width * 5, 0, width, ROW_TABLE_HEIGHT);

                if (hTableCurrentRow != hWnd)
                        draw_border(hdc, rect, CreateSolidBrush(RGB(0, 0, 0)), 2);
                else
                {
                        draw_border(hdc, rect, CreateSolidBrush(COLOR_YELLOW), 3);
                }

                SetRect(&rect, width - 1, 0, width + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 2) - 1, 0, (width * 2) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 3) - 1, 0, (width * 3) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 4) - 1, 0, (width * 4) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 5) - 1, 0, (width * 5) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                EndPaint(hWnd, &ps);
                break;
        case WM_DESTROY:
                DeleteDC(hdc);
                DestroyWindow(hWnd);
                break;
        default:
                DefWindowProcA(hWnd, msg, wp, lp);
        }
}

LRESULT CALLBACK BodyRowCellProductWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rect;
        char text[100];
        int menu;
        int width;
        char discount[5];
        char price[25];

        HWND temp;

        STRUCTPRODUCTOSDATA data;

        switch (msg)
        {
        case WM_LBUTTONDOWN:
                menu = GetMenu(hWnd);
                if (hTableCurrentRow == h_rows_product_table[menu])
                        return 0;
                if (hTableCurrentRow != NULL)
                {
                        temp = hTableCurrentRow;
                        hTableCurrentRow = NULL;
                        GetClientRect(temp, &rect);
                        InvalidateRect(temp, &rect, TRUE);
                }
                GetClientRect(hWnd, &rect);
                hTableCurrentRow = h_rows_product_table[menu];
                InvalidateRect(hTableCurrentRow, &rect, TRUE);
                break;
        case WM_PAINT:
                hdc = BeginPaint(hWnd, &ps);

                GetClientRect(hWnd, &rect);
                menu = GetMenu(hWnd);

                data = dataProductos[menu];
                width = rect.right / 6;

                sprintf(discount, "%s%%", data.discount);
                sprintf(price, "%s Bs", data.price);

                draw_cell(data.name, hdc, 0, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(data.category, hdc, width, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(data.stock, hdc, width * 2, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(discount, hdc, width * 3, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(price, hdc, width * 4, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(data.date, hdc, width * 5, 0, width, ROW_TABLE_HEIGHT);

                if (hTableCurrentRow != hWnd)
                        draw_border(hdc, rect, CreateSolidBrush(RGB(0, 0, 0)), 2);
                else
                {
                        draw_border(hdc, rect, CreateSolidBrush(COLOR_YELLOW), 3);
                }

                SetRect(&rect, width - 1, 0, width + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 2) - 1, 0, (width * 2) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 3) - 1, 0, (width * 3) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 4) - 1, 0, (width * 4) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 5) - 1, 0, (width * 5) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                EndPaint(hWnd, &ps);
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
        int width;

        HWND temp;

        STRUCTCLIENTESDATA data;

        switch (msg)
        {
        case WM_LBUTTONDOWN:
                menu = GetMenu(hWnd);
                if (hTableCurrentRow == hTableCliente[menu].container)
                        return 0;
                if (hTableCurrentRow != NULL)
                {
                        temp = hTableCurrentRow;
                        hTableCurrentRow = NULL;
                        GetClientRect(temp, &rect);
                        InvalidateRect(temp, &rect, TRUE);
                }
                GetClientRect(hWnd, &rect);
                hTableCurrentRow = hTableCliente[menu].container;
                InvalidateRect(hTableCurrentRow, &rect, TRUE);
                ;
                break;
        case WM_PAINT:
                hdc = BeginPaint(hWnd, &ps);

                GetClientRect(hWnd, &rect);
                menu = GetMenu(hWnd);

                data = dataClient[menu];
                width = rect.right / 5;

                char TipoDePersona[20];

                if (data.TdP[0] == 'V')
                        strcpy(TipoDePersona, "Venezolano");
                else if (data.TdP[0] == 'G')
                        strcpy(TipoDePersona, "Gubernamental");
                else if (data.TdP[0] == 'E')
                        strcpy(TipoDePersona, "Extranjero");
                else
                        strcpy(TipoDePersona, "Juridico");

                draw_cell(data.name, hdc, 0, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(data.dni, hdc, width, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(data.phone, hdc, width * 2, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(TipoDePersona, hdc, width * 3, 0, width, ROW_TABLE_HEIGHT);
                draw_cell(data.date, hdc, width * 4, 0, width, ROW_TABLE_HEIGHT);

                if (hTableCurrentRow != hWnd)
                        draw_border(hdc, rect, CreateSolidBrush(RGB(0, 0, 0)), 2);
                else
                {
                        draw_border(hdc, rect, CreateSolidBrush(COLOR_YELLOW), 3);
                }

                SetRect(&rect, width - 1, 0, width + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 2) - 1, 0, (width * 2) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 3) - 1, 0, (width * 3) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 4) - 1, 0, (width * 4) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                SetRect(&rect, (width * 5) - 1, 0, (width * 5) + 2, ROW_TABLE_HEIGHT);
                FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));

                EndPaint(hWnd, &ps);
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

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
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