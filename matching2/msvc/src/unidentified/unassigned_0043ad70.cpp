#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043AD70..0x0043AE16: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043ad70() {
    __asm {
    L_0043ad70:
        push edi
    L_0043ad71:
        mov edi,eax
    L_0043ad73:
        mov eax,dword ptr [edi+138h]
    L_0043ad79:
        test eax,eax
    L_0043ad7b:
        jne short L_0043ad82
    L_0043ad7d:
        or eax,0FFFFFFFFh
    L_0043ad80:
        pop edi
    L_0043ad81:
        ret
    L_0043ad82:
        push esi
    L_0043ad83:
        call asm_FUN_0043ace0_0043ace0
    L_0043ad88:
        mov eax,dword ptr [edi+13Ch]
    L_0043ad8e:
        test eax,eax
    L_0043ad90:
        lea esi,[edi+13Ch]
    L_0043ad96:
        je short L_0043adb4
    L_0043ad98:
        cmp dword ptr [esi+4],0FFFFFFFFh
    L_0043ad9c:
        je short L_0043add2
    L_0043ad9e:
        push eax
    L_0043ad9f:
        call dword ptr [data_004662a8]
    L_0043ada5:
        mov eax,dword ptr [esi]
    L_0043ada7:
        push eax
    L_0043ada8:
        call dword ptr [data_004662a4]
    L_0043adae:
        mov dword ptr [esi],0
    L_0043adb4:
        push 10000h
    L_0043adb9:
        push 0
    L_0043adbb:
        mov dword ptr [esi+4],0FFFFFFFFh
    L_0043adc2:
        mov ecx,dword ptr [data_00491c70]
    L_0043adc8:
        push ecx
    L_0043adc9:
        push 0FFFFFFFFh
    L_0043adcb:
        push esi
    L_0043adcc:
        call dword ptr [data_004662ac]
    L_0043add2:
        mov eax,dword ptr [edi+4]
    L_0043add5:
        test eax,eax
    L_0043add7:
        pop esi
    L_0043add8:
        je short L_0043ade1
    L_0043adda:
        push eax
    L_0043addb:
        call dword ptr [data_00466288]
    L_0043ade1:
        mov edx,dword ptr [edi+8]
    L_0043ade4:
        push edx
    L_0043ade5:
        call dword ptr [data_00466274]
    L_0043adeb:
        mov eax,dword ptr [edi+8]
    L_0043adee:
        push eax
    L_0043adef:
        mov dword ptr [edi+4],0
    L_0043adf6:
        call dword ptr [data_00466278]
    L_0043adfc:
        mov ecx,dword ptr [edi+8]
    L_0043adff:
        push 1
    L_0043ae01:
        push edi
    L_0043ae02:
        push 43A6E0h
    L_0043ae07:
        push ecx
    L_0043ae08:
        push 1
    L_0043ae0a:
        call dword ptr [data_0046628c]
    L_0043ae10:
        mov dword ptr [edi+4],eax
    L_0043ae13:
        xor eax,eax
    L_0043ae15:
        pop edi
    L_0043ae16:
        ret
    }
}
