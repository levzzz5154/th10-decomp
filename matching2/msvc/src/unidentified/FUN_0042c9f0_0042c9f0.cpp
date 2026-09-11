#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C9F0..0x0042CA3C: FUN_0042c9f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042c9f0_0042c9f0() {
    __asm {
    L_0042c9f0:
        push ebx
    L_0042c9f1:
        mov ebx,dword ptr [data_0047784c]
    L_0042c9f7:
        call asm_Title_RegisterTasksRetail_0042caa0
    L_0042c9fc:
        test eax,eax
    L_0042c9fe:
        je short L_0042ca19
    L_0042ca00:
        mov eax,dword ptr [data_00491ff4]
    L_0042ca05:
        shr eax,0Ch
    L_0042ca08:
        not eax
    L_0042ca0a:
        and eax,1
    L_0042ca0d:
        or eax,2
    L_0042ca10:
        mov dword ptr [data_00491fb8],eax
    L_0042ca15:
        xor eax,eax
    L_0042ca17:
        pop ebx
    L_0042ca18:
        ret
    L_0042ca19:
        mov eax,dword ptr [data_00477820]
    L_0042ca1e:
        test eax,eax
    L_0042ca20:
        TH10_REL8(0x74, 0x0042ca20, VA_asm_target_0042ca88)
    L_0042ca22:
        mov ecx,dword ptr [eax+3ECh]
    L_0042ca28:
        push esi
    L_0042ca29:
        push edi
    L_0042ca2a:
        mov edi,12Ch
    L_0042ca2f:
        cmp ecx,edi
    L_0042ca31:
        TH10_REL8(0x7d, 0x0042ca31, VA_asm_target_0042ca5a)
    L_0042ca33:
        mov esi,dword ptr [data_004660ac]
    L_0042ca39:
        mov bl,80h
    L_0042ca3b:
        TH10_REL8(0xeb, 0x0042ca3b, VA_asm_FUN_0042c9f0_part_0042ca40)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042ca40:
        test byte ptr [data_00491ff4],bl
    L_0042ca46:
        jne short L_0042ca5a
    L_0042ca48:
        push 10h
    L_0042ca4a:
        call esi
    L_0042ca4c:
        mov ecx,dword ptr [data_00477820]
    L_0042ca52:
        cmp dword ptr [ecx+3ECh],edi
    L_0042ca58:
        jl short L_0042ca40
    L_0042ca5a:
        mov esi,dword ptr [data_00491c10]
    L_0042ca60:
        mov edi,dword ptr [esi+3AD070h]
    L_0042ca66:
        add esi,3AD070h
    L_0042ca6c:
        test edi,edi
    L_0042ca6e:
        je short L_0042ca86
    L_0042ca70:
        call asm_FUN_00447810_00447810
    L_0042ca75:
        mov edx,dword ptr [esi]
    L_0042ca77:
        push edx
    L_0042ca78:
        call asm_free_004524a1
    L_0042ca7d:
        add esp,4
    L_0042ca80:
        mov dword ptr [esi],0
    L_0042ca86:
        pop edi
    L_0042ca87:
        pop esi
    L_0042ca88:
        mov eax,dword ptr [data_0047784c]
    L_0042ca8d:
        mov eax,dword ptr [eax+0Ch]
    L_0042ca90:
        or dword ptr [eax+4],2
    L_0042ca94:
        xor eax,eax
    L_0042ca96:
        pop ebx
    L_0042ca97:
        ret
    }
}
