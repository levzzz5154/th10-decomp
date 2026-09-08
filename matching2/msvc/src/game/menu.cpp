#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044BEA0..0x0044BF1F: MenuCursor_Advance
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MenuCursor_Advance_0044bea0() {
    __asm {
    L_0044bea0:
        push esi
    L_0044bea1:
        mov esi,dword ptr [eax+8]
    L_0044bea4:
        test esi,esi
    L_0044bea6:
        jle short L_0044bf1a
    L_0044bea8:
        push ebx
    L_0044bea9:
        push ebp
    L_0044beaa:
        push edi
    L_0044beab:
        mov edi,dword ptr [eax+0D4h]
    L_0044beb1:
        lea ebx,[eax+90h]
    L_0044beb7:
        mov ecx,dword ptr [esp+14h]
    L_0044bebb:
        mov edx,dword ptr [eax]
    L_0044bebd:
        add edx,ecx
    L_0044bebf:
        mov ecx,edx
    L_0044bec1:
        cmp ecx,esi
    L_0044bec3:
        mov dword ptr [eax],edx
    L_0044bec5:
        jl short L_0044bee4
    L_0044bec7:
        mov ecx,dword ptr [eax+0D0h]
    L_0044becd:
        TH10_NOP_LEA_ECX_DISP8()
    L_0044bed0:
        test ecx,ecx
    L_0044bed2:
        je short L_0044beda
    L_0044bed4:
        mov edx,dword ptr [eax]
    L_0044bed6:
        sub edx,esi
    L_0044bed8:
        jmp short L_0044bedd
    L_0044beda:
        lea edx,[esi-1]
    L_0044bedd:
        mov dword ptr [eax],edx
    L_0044bedf:
        cmp edx,dword ptr [eax+8]
    L_0044bee2:
        jge short L_0044bed0
    L_0044bee4:
        cmp dword ptr [eax],0
    L_0044bee7:
        jge short L_0044bf03
    L_0044bee9:
        mov ecx,dword ptr [eax+0D0h]
    L_0044beef:
        nop
    L_0044bef0:
        test ecx,ecx
    L_0044bef2:
        je short L_0044bef8
    L_0044bef4:
        add dword ptr [eax],esi
    L_0044bef6:
        jmp short L_0044befe
    L_0044bef8:
        mov dword ptr [eax],0
    L_0044befe:
        cmp dword ptr [eax],0
    L_0044bf01:
        jl short L_0044bef0
    L_0044bf03:
        xor ecx,ecx
    L_0044bf05:
        mov edx,ebx
    L_0044bf07:
        cmp ecx,edi
    L_0044bf09:
        jge short L_0044bf17
    L_0044bf0b:
        mov ebp,dword ptr [edx]
    L_0044bf0d:
        cmp ebp,dword ptr [eax]
    L_0044bf0f:
        je short L_0044beb7
    L_0044bf11:
        inc ecx
    L_0044bf12:
        add edx,4
    L_0044bf15:
        jmp short L_0044bf07
    L_0044bf17:
        pop edi
    L_0044bf18:
        pop ebp
    L_0044bf19:
        pop ebx
    L_0044bf1a:
        mov eax,dword ptr [eax]
    L_0044bf1c:
        pop esi
    L_0044bf1d:
        ret 4
    }
}
