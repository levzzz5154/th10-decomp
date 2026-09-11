#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435370..0x004353AC: FileHandle_OpenRetail
// Naked body preserves the retail register/stack ABI.

// 0x0044B740..0x0044B78B: ?File_WriteShared@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_File_WriteShared_0044b740() {
    __asm {
    L_0044b740:
        push ecx
    L_0044b741:
        mov eax,dword ptr [data_00474c38]
    L_0044b746:
        cmp eax,0FFFFFFFFh
    L_0044b749:
        jne short L_0044b74f
    L_0044b74b:
        or eax,eax
    L_0044b74d:
        pop ecx
    L_0044b74e:
        ret
    L_0044b74f:
        push 0
    L_0044b751:
        lea ecx,[esp+4]
    L_0044b755:
        push ecx
    L_0044b756:
        push esi
    L_0044b757:
        push edx
    L_0044b758:
        push eax
    L_0044b759:
        call dword ptr [data_004660d4]
    L_0044b75f:
        cmp esi,dword ptr [esp]
    L_0044b762:
        je short L_0044b788
    L_0044b764:
        mov eax,dword ptr [data_00474c38]
    L_0044b769:
        push eax
    L_0044b76a:
        call dword ptr [data_004660cc]
    L_0044b770:
        push 4922A4h
    L_0044b775:
        call dword ptr [data_004660b4]
    L_0044b77b:
        dec byte ptr [data_0049231e]
    L_0044b781:
        mov eax,0FFFFFFFEh
    L_0044b786:
        pop ecx
    L_0044b787:
        ret
    L_0044b788:
        xor eax,eax
    L_0044b78a:
        pop ecx
    L_0044b78b:
        ret
    }
}
