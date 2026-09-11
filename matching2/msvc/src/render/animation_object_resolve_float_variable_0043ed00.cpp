#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x0043ED00..0x0043ED6B: ?AnimationObject_ResolveFloatVariable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_ResolveFloatVariable_0043ed00() {
    __asm {
    L_0043ed00:
        mov eax,1
    L_0043ed05:
        shl eax,cl
    L_0043ed07:
        movzx ecx,word ptr [esp+4]
    L_0043ed0c:
        test eax,ecx
    L_0043ed0e:
        je short L_0043ed67
    L_0043ed10:
        fld dword ptr [edi]
    L_0043ed12:
        call asm_FUN_00463b2c_00463b2c
    L_0043ed17:
        add eax,0FFFFD8ECh
    L_0043ed1c:
        cmp eax,0Bh
    L_0043ed1f:
        ja short L_0043ed67
    L_0043ed21:
        jmp dword ptr [eax*4+43ED6Ch]
    L_0043ed28:
        lea eax,[esi+31Ch]
    L_0043ed2e:
        ret 4
    L_0043ed31:
        lea eax,[esi+320h]
    L_0043ed37:
        ret 4
    L_0043ed3a:
        lea eax,[esi+324h]
    L_0043ed40:
        ret 4
    L_0043ed43:
        lea eax,[esi+328h]
    L_0043ed49:
        ret 4
    L_0043ed4c:
        lea eax,[esi+334h]
    L_0043ed52:
        ret 4
    L_0043ed55:
        lea eax,[esi+338h]
    L_0043ed5b:
        ret 4
    L_0043ed5e:
        lea eax,[esi+33Ch]
    L_0043ed64:
        ret 4
    L_0043ed67:
        mov eax,edi
    L_0043ed69:
        ret 4
    }
}
