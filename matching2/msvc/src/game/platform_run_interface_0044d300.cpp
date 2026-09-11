#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0044D300..0x0044D361: ?Platform_RunInterface@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_RunInterface_0044d300() {
    __asm {
    L_0044d300:
        push ecx
    L_0044d301:
        test esi,esi
    L_0044d303:
        jne short L_0044d30c
    L_0044d305:
        mov eax,800401F0h
    L_0044d30a:
        pop ecx
    L_0044d30b:
        ret
    L_0044d30c:
        test ebx,ebx
    L_0044d30e:
        je short L_0044d316
    L_0044d310:
        mov dword ptr [ebx],0
    L_0044d316:
        mov eax,dword ptr [esi]
    L_0044d318:
        lea ecx,[esp]
    L_0044d31b:
        push ecx
    L_0044d31c:
        push esi
    L_0044d31d:
        call dword ptr [eax+24h]
    L_0044d320:
        test eax,eax
    L_0044d322:
        jl short L_0044d360
    L_0044d324:
        test byte ptr [esp],2
    L_0044d328:
        je short L_0044d35b
    L_0044d32a:
        push edi
    L_0044d32b:
        mov edi,dword ptr [data_004660ac]
    L_0044d331:
        mov edx,dword ptr [esi]
    L_0044d333:
        push esi
    L_0044d334:
        call dword ptr [edx+50h]
    L_0044d337:
        cmp eax,88780096h
    L_0044d33c:
        jne short L_0044d342
    L_0044d33e:
        push 0Ah
    L_0044d340:
        call edi
    L_0044d342:
        mov eax,dword ptr [esi]
    L_0044d344:
        push esi
    L_0044d345:
        call dword ptr [eax+50h]
    L_0044d348:
        test eax,eax
    L_0044d34a:
        jne short L_0044d331
    L_0044d34c:
        test ebx,ebx
    L_0044d34e:
        pop edi
    L_0044d34f:
        je short L_0044d357
    L_0044d351:
        mov dword ptr [ebx],1
    L_0044d357:
        xor eax,eax
    L_0044d359:
        pop ecx
    L_0044d35a:
        ret
    L_0044d35b:
        mov eax,1
    L_0044d360:
        pop ecx
    L_0044d361:
        ret
    }
}
