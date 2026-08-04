#include "th10/platform/gdi_font_cache.hpp"

#ifdef _MSC_VER
extern "C" void sub_436A30(void*);
extern "C" void* __imp_DeleteObject;
#endif

// GDI font/bitmap handle table (retail 0x00491868..0x004918A0).
void* DAT_00491868[15];

// 0x00437D10 - Delete the fifteen cached GDI objects. Retail flushes
// the font cache first (0x00436A30) and then calls DeleteObject on each
// handle starting from the highest slot (0x004918A0) down to the lowest
// (0x00491868), leaving the slots untouched.
#ifdef _MSC_VER
__declspec(naked) void FontCache_DeleteGdiObjectsRetail() {
    __asm {
        push esi
        mov esi, 474CB0h
        call sub_436A30
        mov eax, dword ptr [DAT_00491868+38h]
        mov esi, dword ptr [__imp_DeleteObject]
        push eax
        call esi
        mov ecx, dword ptr [DAT_00491868+34h]
        push ecx
        call esi
        mov edx, dword ptr [DAT_00491868+30h]
        push edx
        call esi
        mov eax, dword ptr [DAT_00491868+2Ch]
        push eax
        call esi
        mov ecx, dword ptr [DAT_00491868+28h]
        push ecx
        call esi
        mov edx, dword ptr [DAT_00491868+24h]
        push edx
        call esi
        mov eax, dword ptr [DAT_00491868+20h]
        push eax
        call esi
        mov ecx, dword ptr [DAT_00491868+1Ch]
        push ecx
        call esi
        mov edx, dword ptr [DAT_00491868+18h]
        push edx
        call esi
        mov eax, dword ptr [DAT_00491868+14h]
        push eax
        call esi
        mov ecx, dword ptr [DAT_00491868+10h]
        push ecx
        call esi
        mov edx, dword ptr [DAT_00491868+0Ch]
        push edx
        call esi
        mov eax, dword ptr [DAT_00491868+8]
        push eax
        call esi
        mov ecx, dword ptr [DAT_00491868+4]
        push ecx
        call esi
        mov edx, dword ptr [DAT_00491868]
        push edx
        call esi
        pop esi
        ret
    }
}
#endif

void FontCache_DeleteGdiObjects(void (*flush)(),
                                void (*delete_object)(void*)) {
    if (flush != 0) {
        flush();
    }
    if (delete_object == 0) {
        return;
    }
    for (int slot = 14; slot >= 0; --slot) {
        delete_object(DAT_00491868[slot]);
    }
}
