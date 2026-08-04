#include "th10/platform/gdi_font_cache.hpp"

#ifdef _MSC_VER
extern "C" void sub_436A30(void*);
extern "C" void* __imp_DeleteObject;
extern "C" void* __imp_SelectObject;
extern "C" void* __imp_DeleteDC;
#endif

// GDI font/bitmap handle table (retail 0x00491868..0x004918A0).
void* DAT_00491868[15];

// 0x00436A30 - Flush the cached GDI font surface. When the cached DC at
// +0x114 is live, restore the old bitmap, delete the DC and font object,
// clear the six cache slots, and mark the cache stale (-1 at +0x100).
#ifdef _MSC_VER
__declspec(naked) void FontCache_FlushRetail() {
    __asm {
        mov eax, [esi+114h]
        push edi
        xor edi, edi
        cmp eax, edi
        jz loc_436A97
        mov ecx, [esi+118h]
        push ecx
        push eax
        call dword ptr [__imp_SelectObject]
        mov edx, [esi+114h]
        push edx
        call dword ptr [__imp_DeleteDC]
        mov eax, [esi+11Ch]
        push eax
        call dword ptr [__imp_DeleteObject]
        mov [esi+104h], edi
        mov [esi+108h], edi
        mov [esi+114h], edi
        mov [esi+11Ch], edi
        mov [esi+118h], edi
        mov [esi+120h], edi
        mov dword ptr [esi+100h], 0FFFFFFFFh
        mov al, 1
        pop edi
        ret
loc_436A97:
        xor al, al
        pop edi
        ret
    }
}
#endif

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
