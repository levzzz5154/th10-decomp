#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3306): closest_byte_count=0/54; first_diff=0x00449210
// residual_class=private ECX/EDX lookup inputs, SI stop-frame live-in, and
// private caller/callee convention for AnimationManager_Find.
// variants_tested=readable opaque-layout cdecl candidate (65-byte standalone
// extent; disassembly compared against 54-byte retail body) plus the existing
// naked baseline.
// next_lever=caller 0x004250B0 plus callee 0x004491C0 in a native-LTCG
// cluster so MSVC can select the retail private register convention.

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
