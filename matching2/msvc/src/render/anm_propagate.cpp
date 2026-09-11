#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409E50..0x00409E90: FUN_00409e50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409e50_00409e50() {
    __asm {
    L_00409e50:
        mov eax,dword ptr [eax]
    L_00409e52:
        mov edx,dword ptr [data_00491c10]
    L_00409e58:
        push eax
    L_00409e59:
        call asm_AnimationManager_Find_004491c0
    L_00409e5e:
        test eax,eax
    L_00409e60:
        je short L_00409e90
    L_00409e62:
        mov edx,dword ptr [eax+18h]
    L_00409e65:
        test edx,edx
    L_00409e67:
        mov ecx,1
    L_00409e6c:
        mov word ptr [eax+304h],cx
    L_00409e73:
        jne short L_00409e90
    L_00409e75:
        mov eax,dword ptr [eax+14h]
    L_00409e78:
        test eax,eax
    L_00409e7a:
        je short L_00409e90
    L_00409e7c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00409e80:
        mov edx,dword ptr [eax]
    L_00409e82:
        mov word ptr [edx+304h],cx
    L_00409e89:
        mov eax,dword ptr [eax+4]
    L_00409e8c:
        test eax,eax
    L_00409e8e:
        jne short L_00409e80
    L_00409e90:
        ret
    }
}

