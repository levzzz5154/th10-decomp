#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436400..0x0043642D: FUN_00436400
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436400_00436400() {
    __asm {
    L_00436400:
        push esi
    L_00436401:
        push edi
    L_00436402:
        mov edi,dword ptr [esp+0Ch]
    L_00436406:
        mov esi,ecx
    L_00436408:
        push 0
    L_0043640a:
        mov ecx,edi
    L_0043640c:
        call asm_FUN_00435800_00435800
    L_00436411:
        mov ecx,edi
    L_00436413:
        mov dword ptr [esi+0Ch],eax
    L_00436416:
        call asm_Resource_GetFileSizeRetail_004358e0
    L_0043641b:
        mov dword ptr [esi+4],eax
    L_0043641e:
        mov eax,dword ptr [esi+0Ch]
    L_00436421:
        mov dword ptr [esi+8],eax
    L_00436424:
        test eax,eax
    L_00436426:
        pop edi
    L_00436427:
        setne al
    L_0043642a:
        pop esi
    L_0043642b:
        ret 8
    }
}
