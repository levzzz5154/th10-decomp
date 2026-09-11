#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449210..0x00449245: ?AnimationManager_SetStopFrame@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetStopFrame_00449210() {
    __asm {
    L_00449210:
        mov eax,dword ptr [esp+4]
    L_00449214:
        push eax
    L_00449215:
        call asm_AnimationManager_Find_004491c0
    L_0044921a:
        test eax,eax
    L_0044921c:
        je short L_00449243
    L_0044921e:
        mov ecx,dword ptr [eax+18h]
    L_00449221:
        test ecx,ecx
    L_00449223:
        mov word ptr [eax+304h],si
    L_0044922a:
        jne short L_00449243
    L_0044922c:
        mov eax,dword ptr [eax+14h]
    L_0044922f:
        test eax,eax
    L_00449231:
        je short L_00449243
    L_00449233:
        mov ecx,dword ptr [eax]
    L_00449235:
        mov word ptr [ecx+304h],si
    L_0044923c:
        mov eax,dword ptr [eax+4]
    L_0044923f:
        test eax,eax
    L_00449241:
        jne short L_00449233
    L_00449243:
        ret 4
    }
}
