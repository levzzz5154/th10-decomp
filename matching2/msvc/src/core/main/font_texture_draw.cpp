#include <string.h>
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

typedef unsigned int DWORD;
typedef void* HGDIOBJ;
typedef const char* LPCSTR;
typedef void* HDC;
typedef unsigned int COLORREF;

// The shared font atlas object at 0x00474CB0: a 256-byte palette, 15 cached
// GDI fonts, the pixel buffer, its pitch, the source format and the DC the
// fonts are selected into.
extern "C" unsigned char data_00474cb0;

// GDI entry points, reached through the image's own import slots so the calls
// stay indirect exactly as the retail build issues them.
extern "C" __declspec(dllimport) HGDIOBJ __stdcall SelectObject(HDC dc, HGDIOBJ object);
extern "C" __declspec(dllimport) int __stdcall SetBkMode(HDC dc, int mode);
extern "C" __declspec(dllimport) COLORREF __stdcall SetTextColor(HDC dc, COLORREF color);
extern "C" __declspec(dllimport) int __stdcall TextOutA(HDC dc, int x, int y, LPCSTR text, int count);

// A four-byte value class: a __fastcall callee receives an aggregate argument
// on the stack, so this pointer type reproduces the retail call that keeps the
// atlas object in ECX and pushes its argument.
struct StackWord {
    int value;
};

typedef char (__fastcall* AtlasSetHeightFn)(void* atlas, StackWord height);
typedef void (__stdcall* AtlasRebuildFn)(void* atlas, int height);
typedef int (__stdcall* LoadSurfaceFromMemoryFn)(void* surface, void* destination_palette,
        const void* destination_rect, const void* source_memory, unsigned int source_pitch,
        unsigned int source_format, const void* source_palette, const void* source_rect,
        unsigned int filter, unsigned int color_key);
typedef void (__stdcall* SurfaceGetterFn)(void* owner, int index, void* out);
typedef int (__stdcall* ReleaseFn)(void* surface);

struct SrgbRect {
    int left;
    int top;
    int right;
    int bottom;
};

// 0x00437DB0: AtlasDrawText - stamp one line of text into the software font
// atlas and upload the touched rectangle to its D3D surface. The string is
// drawn twice: a black copy offset by (2,2) that forms the outline, then the
// caller's colour on top.
int __stdcall sub_437DB0(DWORD* destination_rect, int x, int size, COLORREF color,
                         LPCSTR text, void* surface_owner) {
    HGDIOBJ font;
    if (size <= 17)
        font = *(HGDIOBJ*)&data_004918a0;
    else if (size <= 18)
        font = *(HGDIOBJ*)&data_0049189c;
    else if (size <= 19)
        font = *(HGDIOBJ*)&data_00491898;
    else if (size <= 20)
        font = *(HGDIOBJ*)&data_00491894;
    else if (size <= 21)
        font = *(HGDIOBJ*)&data_00491890;
    else if (size <= 22)
        font = *(HGDIOBJ*)&data_0049188c;
    else if (size <= 23)
        font = *(HGDIOBJ*)&data_00491888;
    else if (size <= 24)
        font = *(HGDIOBJ*)&data_00491884;
    else if (size <= 25)
        font = *(HGDIOBJ*)&data_00491880;
    else if (size <= 26)
        font = *(HGDIOBJ*)&data_0049187c;
    else if (size <= 27)
        font = *(HGDIOBJ*)&data_00491878;
    else if (size <= 28)
        font = *(HGDIOBJ*)&data_00491874;
    else if (size <= 29)
        font = *(HGDIOBJ*)&data_00491870;
    else if (size <= 30)
        font = *(HGDIOBJ*)&data_0049186c;
    else
        font = *(HGDIOBJ*)&data_00491868;

    int selected_size = size;
    if (selected_size < 17) {
        size = 17;
        selected_size = *(volatile int*)&size;
    }

    memset(*(void**)&data_00474dd0, 0, *(int*)&data_00474dbc);
    HDC dc = *(HDC*)&data_00474dc4;
    HGDIOBJ previous = SelectObject(dc, font);
    int line_height = 2 * selected_size + 6;
    StackWord height;
    height.value = line_height;
    ((AtlasSetHeightFn)asm_FUN_00437160_00437160)(&data_00474cb0, height);
    SetBkMode(dc, 1);
    int length = strlen(text);
    SetTextColor(dc, 0);
    TextOutA(dc, 2 * x + 2, 2, text, length);
    SetTextColor(dc, color);
    TextOutA(dc, 2 * x, 0, text, length);
    SelectObject(dc, previous);
    height.value = line_height;
    ((AtlasSetHeightFn)asm_FUN_00437160_00437160)(&data_00474cb0, height);
    ((AtlasRebuildFn)asm_FUN_00436da0_00436da0)(&data_00474cb0, line_height);
    SelectObject(dc, previous);

    SrgbRect source_rect;
    source_rect.left = 0;
    source_rect.top = 0;
    source_rect.right = 2 * (destination_rect[2] - destination_rect[0]) + 22;
    source_rect.bottom = 2 * size + 2;
    if (source_rect.right > 1024)
        source_rect.right = 1024;

    // The owner hands its surface back through the stack word the dead size
    // parameter occupies; the retail build reuses that same slot.
    (*(SurfaceGetterFn*)(*(void***)surface_owner + 18))(surface_owner, 0, (void**)&size);
    void*& surface = *(void**)&size;
    (*(LoadSurfaceFromMemoryFn)asm_D3DXLoadSurfaceFromMemory_004521a6)(surface, 0,
            destination_rect, *(void**)&data_00474dd0, *(unsigned int*)&data_00474db0,
            *(unsigned int*)&data_00474dc0, 0, &source_rect, 4, 0);
    int result = (int)surface;
    if (surface)
        result = (*(ReleaseFn*)(*(void***)surface + 2))(surface);
    return result;
}

