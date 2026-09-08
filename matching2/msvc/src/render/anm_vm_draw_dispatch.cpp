#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004451C0..0x0044526C: FUN_004451c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004451c0_004451c0() {
    __asm {
    L_004451c0:
        mov edx,dword ptr [eax+35Ch]
    L_004451c6:
        test dl,1
    L_004451c9:
        je short L_004451dc
    L_004451cb:
        test dl,2
    L_004451ce:
        je short L_004451dc
    L_004451d0:
        push ebx
    L_004451d1:
        mov bl,byte ptr [eax+2FFh]
    L_004451d7:
        test bl,bl
    L_004451d9:
        pop ebx
    L_004451da:
        jne short L_004451e0
    L_004451dc:
        or eax,0FFFFFFFFh
    L_004451df:
        ret
    L_004451e0:
        shr edx,16h
    L_004451e3:
        and edx,0Fh
    L_004451e6:
        cmp edx,9
    L_004451e9:
        push esi
    L_004451ea:
        push edi
    L_004451eb:
        ja short L_00445268
    L_004451ed:
        jmp dword ptr [edx*4+445270h]
    L_004451f4:
        push ecx
    L_004451f5:
        mov esi,eax
    L_004451f7:
        call asm_FUN_00443080_00443080
    L_004451fc:
        pop edi
    L_004451fd:
        pop esi
    L_004451fe:
        ret
    L_004451ff:
        pop edi
    L_00445200:
        mov edx,eax
    L_00445202:
        pop esi
    L_00445203:
        jmp asm_FUN_004436c0_004436c0
    L_00445208:
        push ecx
    L_00445209:
        mov esi,eax
    L_0044520b:
        call asm_FUN_00443f80_00443f80
    L_00445210:
        pop edi
    L_00445211:
        pop esi
    L_00445212:
        ret
    L_00445213:
        mov esi,eax
    L_00445215:
        mov edi,ecx
    L_00445217:
        call asm_FUN_00444580_00444580
    L_0044521c:
        pop edi
    L_0044521d:
        pop esi
    L_0044521e:
        ret
    L_0044521f:
        mov edi,eax
    L_00445221:
        mov esi,ecx
    L_00445223:
        call asm_FUN_00443fb0_00443fb0
    L_00445228:
        pop edi
    L_00445229:
        pop esi
    L_0044522a:
        ret
    L_0044522b:
        push eax
    L_0044522c:
        push ecx
    L_0044522d:
        call asm_FUN_004445c0_004445c0
    L_00445232:
        pop edi
    L_00445233:
        pop esi
    L_00445234:
        ret
    L_00445235:
        push ecx
    L_00445236:
        call asm_FUN_00444760_00444760
    L_0044523b:
        pop edi
    L_0044523c:
        pop esi
    L_0044523d:
        ret
    L_0044523e:
        mov edx,dword ptr [eax+30Ch]
    L_00445244:
        shl edx,1
    L_00445246:
        push edx
    L_00445247:
        mov edx,dword ptr [eax+358h]
    L_0044524d:
        push edx
    L_0044524e:
        call asm_FUN_00444ce0_00444ce0
    L_00445253:
        pop edi
    L_00445254:
        pop esi
    L_00445255:
        ret
    L_00445256:
        push ecx
    L_00445257:
        call asm_FUN_00443290_00443290
    L_0044525c:
        pop edi
    L_0044525d:
        pop esi
    L_0044525e:
        ret
    L_0044525f:
        pop edi
    L_00445260:
        mov edx,eax
    L_00445262:
        pop esi
    L_00445263:
        jmp asm_FUN_00443910_00443910
    L_00445268:
        pop edi
    L_00445269:
        xor eax,eax
    L_0044526b:
        pop esi
    L_0044526c:
        ret
    }
}
