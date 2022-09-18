#include <windows.h>
#include <stdio.h>
#include <wingdi.h>

#include "../handlers/draw.h"
#include "../handlers/winProc.h"

void draw_border_top(RECT rect, HDC hdc, HBRUSH hbrush, int px)
{
        RECT rect_temp;

        SetRect(&rect_temp, 0, 0, rect.right, px);
        FillRect(hdc, &rect_temp, hbrush);
}

void draw_border_left(RECT rect, HDC hdc, HBRUSH hbrush, int px)
{
        RECT rect_temp;

        SetRect(&rect_temp, 0, 0, px, rect.bottom);
        FillRect(hdc, &rect_temp, hbrush);
}

void draw_border_right(RECT rect, HDC hdc, HBRUSH hbrush, int px)
{
        RECT rect_temp;

        SetRect(&rect_temp, rect.right - px, 0, rect.right, rect.bottom);
        FillRect(hdc, &rect_temp, hbrush);
}

void draw_border_bottom(RECT rect, HDC hdc, HBRUSH hbrush, int px)
{
        RECT rect_temp;

        SetRect(&rect_temp, 0, rect.bottom - px, rect.right, rect.bottom);
        FillRect(hdc, &rect_temp, hbrush);
}

void draw_border(HDC hdc, RECT rect, HBRUSH hbrush, int px)
{
        draw_border_bottom(rect, hdc, hbrush, px);
        draw_border_right(rect, hdc, hbrush, px);
        draw_border_top(rect, hdc, hbrush, px);
        draw_border_left(rect, hdc, hbrush, px);
}

void draw_bg_button(HDC hdc, RECT rect, HBRUSH bgBrush, COLORREF textBrush, char *text)
{
        SetBkMode(hdc, TRANSPARENT);

        FillRect(hdc, &rect, bgBrush);

        // Draw Text
        SetTextColor(hdc, (COLORREF)textBrush);
        DrawTextA(hdc, text, -1, &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

void draw_bg_button_multiline(HDC hdc, RECT rect, HBRUSH bgBrush, COLORREF textBrush, char *text)
{
        SetBkMode(hdc, TRANSPARENT);

        FillRect(hdc, &rect, bgBrush);

        // Draw Text
        SetTextColor(hdc, (COLORREF)textBrush);
        DrawTextA(hdc, text, -1, &rect, DT_WORDBREAK | DT_CENTER);
}

void MouseTrack(HWND hWnd)
{
        TRACKMOUSEEVENT mouse;
        mouse.cbSize = sizeof(mouse);
        mouse.hwndTrack = hWnd;
        mouse.dwFlags = TME_HOVER | TME_LEAVE;
        mouse.dwHoverTime = 5;
        TrackMouseEvent(&mouse);
}

void draw_cell(char *text, HDC hdc, int x, int y, int cx, int cy)
{
        SetBkMode(hdc, TRANSPARENT);
        RECT rect;

        SetRect(&rect, x, y, x + cx, y + cy);
        FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 255, 255)));

        SetRect(&rect, x + 10, y, x + cx - 5, y + cy);
        DrawTextA(hdc, text, -1, &rect, DT_SINGLELINE | DT_VCENTER);
}