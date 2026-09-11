#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.

// 0x00450190..0x004501AE: ?ECL_ResetVariableBindings@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResetVariableBindings_00450190() {
    __asm {
    L_00450190:
        mov eax,dword ptr [eax+1034h]
    L_00450196:
        xor edx,edx
    L_00450198:
        cmp eax,edx
    L_0045019a:
        je short L_004501ae
    L_0045019c:
        TH10_NOP_LEA_ESP_DISP8()
    L_004501a0:
        mov ecx,dword ptr [eax+4]
    L_004501a3:
        cmp ecx,edx
    L_004501a5:
        mov eax,dword ptr [eax]
    L_004501a7:
        mov dword ptr [eax+4],edx
    L_004501aa:
        mov eax,ecx
    L_004501ac:
        jne short L_004501a0
    L_004501ae:
        ret
    }
}
