#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463A5C..0x00463AA9: __CxxUnhandledExceptionFilter
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CxxUnhandledExceptionFilter_00463a5c() {
    __asm {
    L_00463a5c:
        push esi
    L_00463a5d:
        mov esi,dword ptr [esp+8]
    L_00463a61:
        mov eax,dword ptr [esi]
    L_00463a63:
        cmp dword ptr [eax],0E06D7363h
    L_00463a69:
        jne short L_00463a87
    L_00463a6b:
        cmp dword ptr [eax+10h],3
    L_00463a6f:
        jne short L_00463a87
    L_00463a71:
        mov eax,dword ptr [eax+14h]
    L_00463a74:
        cmp eax,19930520h
    L_00463a79:
        je short L_00463a82
    L_00463a7b:
        cmp eax,19930521h
    L_00463a80:
        jne short L_00463a87
    L_00463a82:
        call asm_terminate_00455693
    L_00463a87:
        mov eax,dword ptr [data_004776d8]
    L_00463a8c:
        test eax,eax
    L_00463a8e:
        je short L_00463aa4
    L_00463a90:
        push eax
    L_00463a91:
        call asm_ValidateExecute_00463b02
    L_00463a96:
        test eax,eax
    L_00463a98:
        pop ecx
    L_00463a99:
        je short L_00463aa4
    L_00463a9b:
        push esi
    L_00463a9c:
        call dword ptr [data_004776d8]
    L_00463aa2:
        jmp short L_00463aa6
    L_00463aa4:
        xor eax,eax
    L_00463aa6:
        pop esi
    L_00463aa7:
        ret 4
    }
}
