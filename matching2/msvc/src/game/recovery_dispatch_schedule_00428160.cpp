#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
 
// BLOCKED (D3405): closest_byte_count=31/105; first_diff=0x00428163;
// residual_class=hidden EDI/EBX/ESI register inputs, signed schedule-entry
// loop shape, and private 0x00427E90 call ABI;
// variants_tested=live Ghidra decompile/callers/callee (0x004281D0,
// 0x00427E90) and MSVC 13.10 readable state-layout cdecl candidate
// (120-byte extent, 31 matching bytes); next_lever=co-compile the real
// 0x004281D0 caller with 0x00427E90 in native LTCG to expose frame in EBX,
// owner in EDI, and schedule cursor in ESI.

// 0x004050D0..0x00405101: ?EmbeddedTimer_Reset@@
// Naked body preserves the retail register/stack ABI.

// 0x00428160..0x004281C8: Recovery_DispatchSchedule
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_DispatchSchedule_00428160() {
    __asm {
    L_00428160:
        movzx ecx,word ptr [data_00474c48]
    L_00428167:
        mov eax,66666667h
    L_0042816c:
        imul ecx
    L_0042816e:
        sar edx,3
    L_00428171:
        mov eax,edx
    L_00428173:
        shr eax,1Fh
    L_00428176:
        add eax,edx
    L_00428178:
        cmp eax,5
    L_0042817b:
        jl short L_00428182
    L_0042817d:
        mov eax,4
    L_00428182:
        mov ecx,dword ptr [edi+4474h]
    L_00428188:
        test ecx,ecx
    L_0042818a:
        je short L_0042818f
    L_0042818c:
        add eax,5
    L_0042818f:
        mov ecx,dword ptr [edi+45Ch]
    L_00428195:
        push esi
    L_00428196:
        mov esi,dword ptr [ecx+eax*8+110h]
    L_0042819d:
        mov al,byte ptr [esi]
    L_0042819f:
        test al,al
    L_004281a1:
        jl short L_004281c5
    L_004281a3:
        movsx ecx,al
    L_004281a6:
        mov eax,ebx
    L_004281a8:
        cdq
    L_004281a9:
        idiv ecx
    L_004281ab:
        movsx eax,byte ptr [esi+1]
    L_004281af:
        cmp edx,eax
    L_004281b1:
        jne short L_004281bb
    L_004281b3:
        push ebx
    L_004281b4:
        push esi
    L_004281b5:
        push edi
    L_004281b6:
        call asm_FUN_00427e90_00427e90
    L_004281bb:
        mov al,byte ptr [esi+34h]
    L_004281be:
        add esi,34h
    L_004281c1:
        test al,al
    L_004281c3:
        jge short L_004281a3
    L_004281c5:
        xor eax,eax
    L_004281c7:
        pop esi
    L_004281c8:
        ret
    }
}
