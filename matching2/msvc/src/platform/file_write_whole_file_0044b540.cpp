#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435370..0x004353AC: FileHandle_OpenRetail
// Naked body preserves the retail register/stack ABI.

// 0x0044B540..0x0044B619: ?File_WriteWholeFile@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_File_WriteWholeFile_0044b540() {
    __asm {
    L_0044b540:
        push ecx
    L_0044b541:
        push esi
    L_0044b542:
        push 4922A4h
    L_0044b547:
        call dword ptr [data_004660b0]
    L_0044b54d:
        mov al,byte ptr [data_0049231e]
    L_0044b552:
        push 0
    L_0044b554:
        push 80h
    L_0044b559:
        push 2
    L_0044b55b:
        push 0
    L_0044b55d:
        inc al
    L_0044b55f:
        push 1
    L_0044b561:
        mov byte ptr [data_0049231e],al
    L_0044b566:
        mov eax,dword ptr [esp+20h]
    L_0044b56a:
        push 40000000h
    L_0044b56f:
        push eax
    L_0044b570:
        call dword ptr [data_004660c4]
    L_0044b576:
        mov esi,eax
    L_0044b578:
        cmp esi,0FFFFFFFFh
    L_0044b57b:
        push 0
    L_0044b57d:
        jne short L_0044b5c2
    L_0044b57f:
        push 0
    L_0044b581:
        lea ecx,[esp+14h]
    L_0044b585:
        push ecx
    L_0044b586:
        push 400h
    L_0044b58b:
        call dword ptr [data_0046610c]
    L_0044b591:
        push eax
    L_0044b592:
        push 0
    L_0044b594:
        push 1300h
    L_0044b599:
        call dword ptr [data_00466124]
    L_0044b59f:
        mov edx,dword ptr [esp+0Ch]
    L_0044b5a3:
        push edx
    L_0044b5a4:
        call dword ptr [data_00466128]
    L_0044b5aa:
        push 4922A4h
    L_0044b5af:
        call dword ptr [data_004660b4]
    L_0044b5b5:
        dec byte ptr [data_0049231e]
    L_0044b5bb:
        mov eax,esi
    L_0044b5bd:
        pop esi
    L_0044b5be:
        pop ecx
    L_0044b5bf:
        ret 8
    L_0044b5c2:
        mov ecx,dword ptr [esp+14h]
    L_0044b5c6:
        lea eax,[esp+8]
    L_0044b5ca:
        push eax
    L_0044b5cb:
        push edi
    L_0044b5cc:
        push ecx
    L_0044b5cd:
        push esi
    L_0044b5ce:
        call dword ptr [data_004660d4]
    L_0044b5d4:
        cmp edi,dword ptr [esp+4]
    L_0044b5d8:
        push esi
    L_0044b5d9:
        je short L_0044b5fc
    L_0044b5db:
        call dword ptr [data_004660cc]
    L_0044b5e1:
        push 4922A4h
    L_0044b5e6:
        call dword ptr [data_004660b4]
    L_0044b5ec:
        dec byte ptr [data_0049231e]
    L_0044b5f2:
        mov eax,0FFFFFFFEh
    L_0044b5f7:
        pop esi
    L_0044b5f8:
        pop ecx
    L_0044b5f9:
        ret 8
    L_0044b5fc:
        call dword ptr [data_004660cc]
    L_0044b602:
        push 4922A4h
    L_0044b607:
        call dword ptr [data_004660b4]
    L_0044b60d:
        dec byte ptr [data_0049231e]
    L_0044b613:
        xor eax,eax
    L_0044b615:
        pop esi
    L_0044b616:
        pop ecx
    L_0044b617:
        ret 8
    }
}
