#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046332A..0x00463398: FUN_0046332a
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0046332a_0046332a() {
    __asm {
    L_0046332a:
        mov eax,dword ptr [ebp-38h]
    L_0046332d:
        mov dword ptr [edi-4],eax
    L_00463330:
        push dword ptr [ebp-3Ch]
    L_00463333:
        call asm_FindAndUnlinkFrame_00462a34
    L_00463338:
        pop ecx
    L_00463339:
        call asm_getptd_00456357
    L_0046333e:
        mov ecx,dword ptr [ebp-40h]
    L_00463341:
        mov dword ptr [eax+7Ch],ecx
    L_00463344:
        call asm_getptd_00456357
    L_00463349:
        mov ecx,dword ptr [ebp-44h]
    L_0046334c:
        mov dword ptr [eax+80h],ecx
    L_00463352:
        cmp dword ptr [esi],0E06D7363h
    L_00463358:
        jne short L_00463398
    L_0046335a:
        cmp dword ptr [esi+10h],3
    L_0046335e:
        jne short L_00463398
    L_00463360:
        mov eax,dword ptr [esi+14h]
    L_00463363:
        cmp eax,19930520h
    L_00463368:
        je short L_00463371
    L_0046336a:
        cmp eax,19930521h
    L_0046336f:
        jne short L_00463398
    L_00463371:
        cmp dword ptr [ebp-48h],0
    L_00463375:
        jne short L_00463398
    L_00463377:
        cmp dword ptr [ebp-20h],0
    L_0046337b:
        je short L_00463398
    L_0046337d:
        push dword ptr [esi+18h]
    L_00463380:
        call asm_IsExceptionObjectToBeDestroyed_00462a13
    L_00463385:
        pop ecx
    L_00463386:
        test eax,eax
    L_00463388:
        je short L_00463398
    L_0046338a:
        call asm_abnormal_termination_00459946
    L_0046338f:
        push eax
    L_00463390:
        push esi
    L_00463391:
        call asm_DestructExceptionObject_00462f7c
    L_00463396:
        pop ecx
    L_00463397:
        pop ecx
    L_00463398:
        ret
    }
}
