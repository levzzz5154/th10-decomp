#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B2A0..0x0040B303: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b2a0() {
    __asm {
    L_0040b2a0:
        push esi
    L_0040b2a1:
        push edi
    L_0040b2a2:
        mov edi,eax
    L_0040b2a4:
        mov esi,dword ptr [edi+358h]
    L_0040b2aa:
        test byte ptr [esi+28h],1
    L_0040b2ae:
        jne short L_0040b2c9
    L_0040b2b0:
        mov eax,dword ptr [esi+18h]
    L_0040b2b3:
        mov ecx,dword ptr [esi+1Ch]
    L_0040b2b6:
        push eax
    L_0040b2b7:
        push ecx
    L_0040b2b8:
        lea ecx,[esi+0Ch]
    L_0040b2bb:
        call asm_Recovery_PolarToVectorRetail_0044c5d0
    L_0040b2c0:
        mov dword ptr [esi+14h],0
    L_0040b2c7:
        jmp short L_0040b2e4
    L_0040b2c9:
        fld dword ptr [esi+24h]
    L_0040b2cc:
        push ecx
    L_0040b2cd:
        fadd dword ptr [esi+20h]
    L_0040b2d0:
        fstp dword ptr [esi+20h]
    L_0040b2d3:
        fld dword ptr [esi+18h]
    L_0040b2d6:
        fadd dword ptr [esi+1Ch]
    L_0040b2d9:
        fstp dword ptr [esp]
    L_0040b2dc:
        call asm_Angle_Normalize_0044bc70
    L_0040b2e1:
        fstp dword ptr [esi+1Ch]
    L_0040b2e4:
        call asm_Recovery_AdvancePolarMotion_0044c2a0
    L_0040b2e9:
        mov edx,dword ptr [esi]
    L_0040b2eb:
        add edi,340h
    L_0040b2f1:
        mov dword ptr [edi],edx
    L_0040b2f3:
        mov eax,dword ptr [esi+4]
    L_0040b2f6:
        mov dword ptr [edi+4],eax
    L_0040b2f9:
        mov ecx,dword ptr [esi+8]
    L_0040b2fc:
        mov dword ptr [edi+8],ecx
    L_0040b2ff:
        pop edi
    L_0040b300:
        xor eax,eax
    L_0040b302:
        pop esi
    L_0040b303:
        ret
    }
}
