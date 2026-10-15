// 0x004372A0, 0x00437380: text output onto a GDI surface.
#include "th10/render/gdi_font_state.hpp"
#include "th10/render/gdi_surface.hpp"

struct SIZE {
    long cx;
    long cy;
};

struct RECT {
    long left;
    long top;
    long right;
    long bottom;
};

extern "C" {
__declspec(dllimport) void* __stdcall SelectObject(void* dc, void* object);
__declspec(dllimport) int __stdcall SetBkMode(void* dc, int mode);
__declspec(dllimport) unsigned long __stdcall SetTextColor(void* dc, unsigned long color);
__declspec(dllimport) int __stdcall DrawTextA(void* dc, const char* text, int count,
                                              RECT* rect, unsigned int format);
}

// 0x004372A0. Nothing in the game calls this.
#pragma code_seg(".text$05sized")
bool GdiSurface::DrawTextSized(const char* text, int x, int y, int size,
                               unsigned long color, unsigned long shadow) {
    GdiFontState font;
    font.SetSize(0, size);
    font.Create();
    return DrawText(text, x, y, font.handle, color, shadow);
}

// 0x00437380
#pragma code_seg(".text$07draw")
bool GdiSurface::DrawText(const char* text, int x, int y, void* font,
                          unsigned long color, unsigned long shadow) {
    if (text == 0)
        return false;
    SIZE size = { width, height };
    void* hdc = dc;
    void* previous_font = SelectObject(hdc, font);
    SetBkMode(hdc, 1 /* TRANSPARENT */);
    if (shadow != 0xFFFFFFFF) {
        SetTextColor(hdc, shadow);
        RECT inner = { x, y, x + size.cx - 2, y + size.cy - 2 };
        DrawTextA(hdc, text, -1, &inner, 0);
        RECT around[5] = {
            { x + 2, y, x + size.cx + 2, y + size.cy },
            { x + 1, y + 2, x + size.cx + 1, y + size.cy + 2 },
            { x + 2, y, x + size.cx + 2, y + size.cy },
            { x, y + 2, x + size.cx, y + size.cy + 2 },
            { x + 2, y + 2, x + size.cx + 2, y + size.cy + 2 },
        };
        DrawTextA(hdc, text, -1, &around[0], 0);
        DrawTextA(hdc, text, -1, &around[1], 0);
        DrawTextA(hdc, text, -1, &around[2], 0);
        DrawTextA(hdc, text, -1, &around[3], 0);
        DrawTextA(hdc, text, -1, &around[4], 0);
    }
    SetTextColor(hdc, color);
    RECT rect = { x + 1, y + 1, x + size.cx + 1, y + size.cy + 1 };
    DrawTextA(hdc, text, -1, &rect, 0);
    SelectObject(hdc, previous_font);
    return true;
}
#pragma code_seg()
