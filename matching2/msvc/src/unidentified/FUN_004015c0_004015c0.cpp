// BLOCKED (H2701): closest_byte_count=109; first_diff=unmeasured;
// residual_class=abi/source_shape: retail receives formatted text in ECX,
// the record source in EBX, and the table/context in ESI, then appends a
// 0x68-byte entry with a byte-copy loop and three dword field stores; the
// four-register private contract is not expressible as a normal declaration.
// variants_tested=exact retail naked wrapper, the 0x00401700 formatted-text
// caller model, and an explicit 0x68-byte record-struct reconstruction; no
// compiler-readable candidate was byte-measured.
// next_lever=co-compile the formatter caller and owning record type in a
// native-LTCG cluster that makes ECX/EBX/ESI live at this entry.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004015C0..0x0040162C: FUN_004015c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004015c0_004015c0() {
    __asm {
    L_004015c0:
        mov edx,dword ptr [esi+8970h]
    L_004015c6:
        cmp edx,40h
    L_004015c9:
        jge short L_0040162c
    L_004015cb:
        mov eax,edx
    L_004015cd:
        imul eax,68h
    L_004015d0:
        push edi
    L_004015d1:
        lea eax,[eax+esi+6F6Ch]
    L_004015d8:
        inc edx
    L_004015d9:
        mov edi,eax
    L_004015db:
        mov dword ptr [esi+8970h],edx
    L_004015e1:
        sub edi,ecx
    L_004015e3:
        mov dl,byte ptr [ecx]
    L_004015e5:
        mov byte ptr [edi+ecx],dl
    L_004015e8:
        inc ecx
    L_004015e9:
        test dl,dl
    L_004015eb:
        jne short L_004015e3
    L_004015ed:
        mov edx,dword ptr [ebx]
    L_004015ef:
        lea ecx,[eax+40h]
    L_004015f2:
        mov dword ptr [ecx],edx
    L_004015f4:
        mov edx,dword ptr [ebx+4]
    L_004015f7:
        mov dword ptr [ecx+4],edx
    L_004015fa:
        mov edx,dword ptr [ebx+8]
    L_004015fd:
        mov dword ptr [ecx+8],edx
    L_00401600:
        mov ecx,dword ptr [esi+8974h]
    L_00401606:
        mov dword ptr [eax+4Ch],ecx
    L_00401609:
        mov edx,dword ptr [esi+8978h]
    L_0040160f:
        mov dword ptr [eax+50h],edx
    L_00401612:
        mov ecx,dword ptr [esi+897Ch]
    L_00401618:
        mov dword ptr [eax+54h],ecx
    L_0040161b:
        mov edx,dword ptr [esi+8980h]
    L_00401621:
        mov dword ptr [eax+5Ch],edx
    L_00401624:
        mov dword ptr [eax+60h],0
    L_0040162b:
        pop edi
    L_0040162c:
        ret
    }
}
