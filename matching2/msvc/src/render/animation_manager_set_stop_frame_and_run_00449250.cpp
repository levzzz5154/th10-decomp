#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449250..0x0044929B: ?AnimationManager_SetStopFrameAndRun@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetStopFrameAndRun_00449250() {
    __asm {
    L_00449250:
        mov eax,dword ptr [esp+4]
    L_00449254:
        push esi
    L_00449255:
        push eax
    L_00449256:
        call asm_AnimationManager_Find_004491c0
    L_0044925b:
        mov esi,eax
    L_0044925d:
        test esi,esi
    L_0044925f:
        je short L_00449298
    L_00449261:
        push esi
    L_00449262:
        mov word ptr [esi+304h],di
    L_00449269:
        call asm_FUN_0043ee30_0043ee30
    L_0044926e:
        mov eax,dword ptr [esi+18h]
    L_00449271:
        test eax,eax
    L_00449273:
        jne short L_00449298
    L_00449275:
        mov esi,dword ptr [esi+14h]
    L_00449278:
        test esi,esi
    L_0044927a:
        je short L_00449298
    L_0044927c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00449280:
        mov ecx,dword ptr [esi]
    L_00449282:
        mov word ptr [ecx+304h],di
    L_00449289:
        mov edx,dword ptr [esi]
    L_0044928b:
        push edx
    L_0044928c:
        call asm_FUN_0043ee30_0043ee30
    L_00449291:
        mov esi,dword ptr [esi+4]
    L_00449294:
        test esi,esi
    L_00449296:
        jne short L_00449280
    L_00449298:
        pop esi
    L_00449299:
        ret 4
    }
}
