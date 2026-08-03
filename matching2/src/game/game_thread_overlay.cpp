// MSVC-only exact overlay for the main game-thread constructor (retail
// 0x00401000). The readable semantic reconstruction lives in
// game_thread.cpp for host builds; this translation unit keeps the overlay
// free of C++11 so the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"

extern "C" void* PTR_LAB_0046cb14;
extern "C" void* g_pGameThread;

__declspec(naked) void* GameThread_ConstructOverlay() {
    __asm {
        mov dword ptr [esi], offset PTR_LAB_0046cb14
        mov eax, [esi+80h]
        lea edx, [esi+14h]
        push ebx
        mov ebx, 0FFFFFFFEh
        push edi
        and eax, ebx
        mov [edx+6Ch], eax
        and [edx+0B0h], ebx
        and [edx+0FCh], ebx
        and [edx+128h], ebx
        and [edx+174h], ebx
        and [edx+1B0h], ebx
        and [edx+1FCh], ebx
        and [edx+228h], ebx
        and [edx+378h], ebx
        xor eax, eax
        mov edi, edx
        mov ecx, 0EBh
        rep stosd
        mov word ptr [edx+384h], 0FFFFh
        mov eax, [esi+42Ch]
        lea edx, [esi+3C0h]
        and eax, ebx
        mov [edx+6Ch], eax
        and [edx+0B0h], ebx
        and [edx+0FCh], ebx
        and [edx+128h], ebx
        and [edx+174h], ebx
        and [edx+1B0h], ebx
        and [edx+1FCh], ebx
        and [edx+228h], ebx
        and [edx+378h], ebx
        xor eax, eax
        mov ecx, 0EBh
        mov edi, edx
        rep stosd
        mov word ptr [edx+384h], 0FFFFh
        mov ecx, 226Bh
        mov edi, esi
        rep stosd
        or dword ptr [esi+4], 2
        mov eax, 3F800000h
        mov dword ptr [g_pGameThread], esi
        mov dword ptr [esi+8974h], 0FFFFFFFFh
        mov [esi+8978h], eax
        mov [esi+897Ch], eax
        pop edi
        mov dword ptr [esi+8984h], 0
        mov dword ptr [esi+898Ch], 9
        mov eax, esi
        pop ebx
        ret
    }
}
#endif
