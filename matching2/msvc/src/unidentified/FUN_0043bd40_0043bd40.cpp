#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BD40..0x0043BD9C: FUN_0043bd40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043bd40_0043bd40() {
    __asm {
    L_0043bd40:
        push ecx
    L_0043bd41:
        mov eax,dword ptr [data_004918a4]
    L_0043bd46:
        test eax,eax
    L_0043bd48:
        push esi
    L_0043bd49:
        mov esi,ecx
    L_0043bd4b:
        jne short L_0043bd85
    L_0043bd4d:
        push edi
    L_0043bd4e:
        mov edi,dword ptr [esi+1Ch]
    L_0043bd51:
        test edi,edi
    L_0043bd53:
        mov dword ptr [esp+8],edi
    L_0043bd57:
        je short L_0043bd7f
    L_0043bd59:
        fld dword ptr [esi+38h]
    L_0043bd5c:
        fmul dword ptr [data_00470bf8]
    L_0043bd62:
        fidiv dword ptr [esp+8]
    L_0043bd66:
        fsubr dword ptr [data_00470bf8]
    L_0043bd6c:
        call asm_FUN_00463b2c_00463b2c
    L_0043bd71:
        test eax,eax
    L_0043bd73:
        mov dword ptr [esi+18h],eax
    L_0043bd76:
        jge short L_0043bd7f
    L_0043bd78:
        mov dword ptr [esi+18h],0
    L_0043bd7f:
        cmp dword ptr [esi+34h],edi
    L_0043bd82:
        pop edi
    L_0043bd83:
        jl short L_0043bd8d
    L_0043bd85:
        mov eax,7
    L_0043bd8a:
        pop esi
    L_0043bd8b:
        pop ecx
    L_0043bd8c:
        ret
    L_0043bd8d:
        add esi,30h
    L_0043bd90:
        call asm_FrameTimer_Tick_00404ed0
    L_0043bd95:
        mov eax,1
    L_0043bd9a:
        pop esi
    L_0043bd9b:
        pop ecx
    L_0043bd9c:
        ret
    }
}
