#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436900..0x00436937: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436900() {
    __asm {
    L_00436900:
        mov eax,dword ptr [esi]
    L_00436902:
        test eax,eax
    L_00436904:
        je short L_00436913
    L_00436906:
        push eax
    L_00436907:
        call dword ptr [data_00466030]
    L_0043690d:
        mov dword ptr [esi],0
    L_00436913:
        cmp dword ptr [esi+24h],10h
    L_00436917:
        jb short L_00436925
    L_00436919:
        mov eax,dword ptr [esi+10h]
    L_0043691c:
        push eax
    L_0043691d:
        call asm_free_004524a1
    L_00436922:
        add esp,4
    L_00436925:
        mov dword ptr [esi+24h],0Fh
    L_0043692c:
        mov dword ptr [esi+20h],0
    L_00436933:
        mov byte ptr [esi+10h],0
    L_00436937:
        ret
    }
}
