#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D2FC..0x0045D348: __IncMan
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_IncMan_0045d2fc() {
    __asm {
    L_0045d2fc:
        mov eax,dword ptr [esp+8]
    L_0045d300:
        push esi
    L_0045d301:
        push edi
    L_0045d302:
        push 20h
    L_0045d304:
        pop ecx
    L_0045d305:
        cdq
    L_0045d306:
        idiv ecx
    L_0045d308:
        mov edi,dword ptr [esp+0Ch]
    L_0045d30c:
        mov esi,eax
    L_0045d30e:
        lea eax,[edi+esi*4]
    L_0045d311:
        push eax
    L_0045d312:
        push 1Fh
    L_0045d314:
        pop ecx
    L_0045d315:
        sub ecx,edx
    L_0045d317:
        xor edx,edx
    L_0045d319:
        inc edx
    L_0045d31a:
        shl edx,cl
    L_0045d31c:
        push edx
    L_0045d31d:
        push dword ptr [eax]
    L_0045d31f:
        call asm_addl_00460798
    L_0045d324:
        add esp,0Ch
    L_0045d327:
        dec esi
    L_0045d328:
        js short L_0045d346
    L_0045d32a:
        lea edi,[edi+esi*4]
    L_0045d32d:
        test eax,eax
    L_0045d32f:
        je short L_0045d346
    L_0045d331:
        push edi
    L_0045d332:
        push 1
    L_0045d334:
        push dword ptr [edi]
    L_0045d336:
        call asm_addl_00460798
    L_0045d33b:
        add esp,0Ch
    L_0045d33e:
        dec esi
    L_0045d33f:
        sub edi,4
    L_0045d342:
        test esi,esi
    L_0045d344:
        jge short L_0045d32d
    L_0045d346:
        pop edi
    L_0045d347:
        pop esi
    L_0045d348:
        ret
    }
}
