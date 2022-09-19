#include <windows.h>

void draw_border_top(RECT rect, HDC hdc, HBRUSH hbrush, int px);
void draw_border_left(RECT rect, HDC hdc, HBRUSH hbrush, int px);
void draw_border_right(RECT rect, HDC hdc, HBRUSH hbrush, int px);
void draw_border_bottom(RECT rect, HDC hdc, HBRUSH hbrush, int px);
void draw_border(HDC hdc, RECT rect, HBRUSH hbrush, int px);

void draw_bg_button(HDC, RECT, HBRUSH, COLORREF, char*);
void draw_bg_button_multiline(HDC, RECT, HBRUSH, COLORREF, char*);

void draw_cell(char *text, HDC hdc, int x, int y, int cx, int cy);

void MouseTrack(HWND hWnd);