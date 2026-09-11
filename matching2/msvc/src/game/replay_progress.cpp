#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412FF0..0x0041304C: FUN_00412ff0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412ff0_00412ff0() {
    __asm {
    L_00412ff0:
        cmp dword ptr [edi+18h],82h
    L_00412ff7:
        jge short L_0041304a
    L_00412ff9:
        fild dword ptr [esp+4]
    L_00412ffd:
        push esi
    L_00412ffe:
        push ecx
    L_00412fff:
        lea esi,[edi+14h]
    L_00413002:
        fstp dword ptr [esp]
    L_00413005:
        call asm_FrameTimer_Advance_0044bf40
    L_0041300a:
        cmp dword ptr [edi+18h],82h
    L_00413011:
        jle short L_00413049
    L_00413013:
        mov eax,dword ptr [esi+10h]
    L_00413016:
        test al,1
    L_00413018:
        jne short L_00413035
    L_0041301a:
        xor ecx,ecx
    L_0041301c:
        or eax,1
    L_0041301f:
        mov dword ptr [esi+4],ecx
    L_00413022:
        mov dword ptr [esi],0FFF0BDC1h
    L_00413028:
        mov dword ptr [esi+8],ecx
    L_0041302b:
        mov dword ptr [esi+0Ch],476F78h
    L_00413032:
        mov dword ptr [esi+10h],eax
    L_00413035:
        mov dword ptr [esi+4],82h
    L_0041303c:
        mov dword ptr [esi+8],43020000h
    L_00413043:
        mov dword ptr [esi],81h
    L_00413049:
        pop esi
    L_0041304a:
        ret 4
    }
}

