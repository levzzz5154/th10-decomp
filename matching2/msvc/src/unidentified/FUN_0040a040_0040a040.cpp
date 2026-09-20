// BLOCKED (H2601): closest_byte_count=234; first_diff=unmeasured;
// residual_class=scheduler: MSVC store scheduling and mutually exclusive reset
// shapes: the supported readable initializer emits the retail 234-byte extent
// but retains the known 14-byte clear-block/pop-EDI placement delta;
// variants_tested=the exact retail wrapper, the prior RawState 0x688-byte
// semantic initializer, and its __fastcall(ignored-ECX, EDX-state) ABI shape;
// next_lever=obtain a compiler/source scheduling lever for the clear-block
// stores and pop-EDI placement, then rerun the existing initializer/factory
// cluster; retain this exact wrapper until that lever exists.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A040..0x0040A129: FUN_0040a040
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040a040_0040a040() {
    __asm {
    L_0040a040:
        mov dword ptr [edx+10h],4703E4h
    L_0040a047:
        xor eax,eax
    L_0040a049:
        mov dword ptr [edx+14h],eax
    L_0040a04c:
        mov dword ptr [edx+18h],eax
    L_0040a04f:
        mov dword ptr [edx+1Ch],eax
    L_0040a052:
        mov dword ptr [edx+20h],eax
    L_0040a055:
        mov dword ptr [edx+0C8h],eax
    L_0040a05b:
        mov dword ptr [edx+3Ch],eax
    L_0040a05e:
        mov dword ptr [edx+110h],eax
    L_0040a064:
        push esi
    L_0040a065:
        mov esi,1
    L_0040a06a:
        mov dword ptr [edx+10Ch],esi
    L_0040a070:
        mov ecx,3E7h
    L_0040a075:
        mov dword ptr [edx+44h],ecx
    L_0040a078:
        mov dword ptr [edx+11Ch],ecx
    L_0040a07e:
        mov dword ptr [edx+1A0h],eax
    L_0040a084:
        mov dword ptr [edx+114h],eax
    L_0040a08a:
        mov dword ptr [edx+1E8h],eax
    L_0040a090:
        mov dword ptr [edx+1E4h],esi
    L_0040a096:
        mov dword ptr [edx+1F4h],ecx
    L_0040a09c:
        mov dword ptr [edx+278h],eax
    L_0040a0a2:
        mov dword ptr [edx+1ECh],eax
    L_0040a0a8:
        mov dword ptr [edx+2C0h],eax
    L_0040a0ae:
        mov dword ptr [edx+2BCh],esi
    L_0040a0b4:
        mov ecx,dword ptr [edx+334h]
    L_0040a0ba:
        lea esi,[edx+2C8h]
    L_0040a0c0:
        push edi
    L_0040a0c1:
        mov eax,0FFFFFFFEh
    L_0040a0c6:
        and ecx,eax
    L_0040a0c8:
        mov dword ptr [esi+6Ch],ecx
    L_0040a0cb:
        and dword ptr [esi+0B0h],eax
    L_0040a0d1:
        and dword ptr [esi+0FCh],eax
    L_0040a0d7:
        and dword ptr [esi+128h],eax
    L_0040a0dd:
        and dword ptr [esi+174h],eax
    L_0040a0e3:
        and dword ptr [esi+1B0h],eax
    L_0040a0e9:
        and dword ptr [esi+1FCh],eax
    L_0040a0ef:
        and dword ptr [esi+228h],eax
    L_0040a0f5:
        and dword ptr [esi+378h],eax
    L_0040a0fb:
        xor eax,eax
    L_0040a0fd:
        mov edi,esi
    L_0040a0ff:
        mov ecx,0EBh
    L_0040a104:
        rep stosd
    L_0040a106:
        mov word ptr [esi+384h],0FFFFh
    L_0040a10f:
        mov ecx,1A2h
    L_0040a114:
        mov edi,edx
    L_0040a116:
        rep stosd
    L_0040a118:
        mov eax,dword ptr [edx]
    L_0040a11a:
        or eax,2
    L_0040a11d:
        pop edi
    L_0040a11e:
        mov dword ptr [edx],eax
    L_0040a120:
        mov dword ptr [data_004776f8],edx
    L_0040a126:
        mov eax,edx
    L_0040a128:
        pop esi
    L_0040a129:
        ret
    }
}
