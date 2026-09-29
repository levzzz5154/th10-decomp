#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// The typed resource-opener candidate passes 97 retail comparisons and full
// DAT lifecycle tests. See reference/recovery_notes/dat_archive_open_00434c30_00434ca0.md.
// The production body retains its exact assembly pending ABI/MSVC recovery.

// 0x00434CA0..0x00434D03: DatArchive_OpenResource
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_OpenResource_00434ca0() {
    __asm {
    L_00434ca0:
        push esi
    L_00434ca1:
        push edi
    L_00434ca2:
        mov esi,ecx
    L_00434ca4:
        mov edi,eax
    L_00434ca6:
        call asm_DatArchive_Close_00434d10
    L_00434cab:
        push 10h
    L_00434cad:
        call asm_operator_new_00452493
    L_00434cb2:
        add esp,4
    L_00434cb5:
        test eax,eax
    L_00434cb7:
        je short L_00434cd6
    L_00434cb9:
        mov dword ptr [eax+4],0
    L_00434cc0:
        mov dword ptr [eax+8],0
    L_00434cc7:
        mov dword ptr [eax+0Ch],0
    L_00434cce:
        mov dword ptr [eax],46F328h
    L_00434cd4:
        jmp short L_00434cd8
    L_00434cd6:
        xor eax,eax
    L_00434cd8:
        test eax,eax
    L_00434cda:
        mov dword ptr [esi+0Ch],eax
    L_00434cdd:
        je short L_00434cff
    L_00434cdf:
        push edi
    L_00434ce0:
        call asm_DatArchive_LoadIndex_00434f70
    L_00434ce5:
        test al,al
    L_00434ce7:
        je short L_00434cfa
    L_00434ce9:
        call asm_LegacyString_Duplicate_00435220
    L_00434cee:
        test eax,eax
    L_00434cf0:
        mov dword ptr [esi+8],eax
    L_00434cf3:
        je short L_00434cfa
    L_00434cf5:
        pop edi
    L_00434cf6:
        mov al,1
    L_00434cf8:
        pop esi
    L_00434cf9:
        ret
    L_00434cfa:
        call asm_DatArchive_Close_00434d10
    L_00434cff:
        pop edi
    L_00434d00:
        xor al,al
    L_00434d02:
        pop esi
    L_00434d03:
        ret
    }
}
