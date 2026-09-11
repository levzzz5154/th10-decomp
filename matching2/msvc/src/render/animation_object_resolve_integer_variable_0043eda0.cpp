#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x0043EDA0..0x0043EDFB: ?AnimationObject_ResolveIntegerVariable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_ResolveIntegerVariable_0043eda0() {
    __asm {
    L_0043eda0:
        push esi
    L_0043eda1:
        mov esi,1
    L_0043eda6:
        shl esi,cl
    L_0043eda8:
        movzx ecx,word ptr [esp+8]
    L_0043edad:
        test esi,ecx
    L_0043edaf:
        pop esi
    L_0043edb0:
        je short L_0043edf9
    L_0043edb2:
        mov ecx,dword ptr [eax]
    L_0043edb4:
        add ecx,0FFFFD8F0h
    L_0043edba:
        cmp ecx,9
    L_0043edbd:
        ja short L_0043edf9
    L_0043edbf:
        jmp dword ptr [ecx*4+43EDFCh]
    L_0043edc6:
        lea eax,[edx+30Ch]
    L_0043edcc:
        ret 4
    L_0043edcf:
        lea eax,[edx+310h]
    L_0043edd5:
        ret 4
    L_0043edd8:
        lea eax,[edx+314h]
    L_0043edde:
        ret 4
    L_0043ede1:
        lea eax,[edx+318h]
    L_0043ede7:
        ret 4
    L_0043edea:
        lea eax,[edx+32Ch]
    L_0043edf0:
        ret 4
    L_0043edf3:
        lea eax,[edx+330h]
    L_0043edf9:
        ret 4
        _emit 0xc6
        _emit 0xed
        _emit 0x43
        _emit 0x00
        _emit 0xcf
        _emit 0xed
        _emit 0x43
        _emit 0x00
        _emit 0xd8
        _emit 0xed
        _emit 0x43
        _emit 0x00
        _emit 0xe1
        _emit 0xed
        _emit 0x43
        _emit 0x00
        _emit 0xf9
        _emit 0xed
        _emit 0x43
        _emit 0x00
        _emit 0xf9
        _emit 0xed
        _emit 0x43
        _emit 0x00
        _emit 0xf9
        _emit 0xed
        _emit 0x43
        _emit 0x00
        _emit 0xf9
        _emit 0xed
        _emit 0x43
        _emit 0x00
        _emit 0xea
        _emit 0xed
        _emit 0x43
        _emit 0x00
        _emit 0xf3
        _emit 0xed
        _emit 0x43
        _emit 0x00
    }
}
