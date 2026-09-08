#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436970..0x004369BA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436970() {
    __asm {
    L_00436970:
        mov eax,dword ptr [esi]
    L_00436972:
        test eax,eax
    L_00436974:
        je short L_00436983
    L_00436976:
        push eax
    L_00436977:
        call dword ptr [data_00466030]
    L_0043697d:
        mov dword ptr [esi],0
    L_00436983:
        cmp dword ptr [esi+24h],10h
    L_00436987:
        jb short L_0043698e
    L_00436989:
        mov eax,dword ptr [esi+10h]
    L_0043698c:
        jmp short L_00436991
    L_0043698e:
        lea eax,[esi+10h]
    L_00436991:
        push eax
    L_00436992:
        mov eax,dword ptr [esi+28h]
    L_00436995:
        mov ecx,dword ptr [esi+4]
    L_00436998:
        push 30h
    L_0043699a:
        mov edx,dword ptr [esi+8]
    L_0043699d:
        push 0
    L_0043699f:
        push 0
    L_004369a1:
        push 0
    L_004369a3:
        push 1
    L_004369a5:
        push 0
    L_004369a7:
        push 0
    L_004369a9:
        push 0
    L_004369ab:
        push eax
    L_004369ac:
        push 0
    L_004369ae:
        push 0
    L_004369b0:
        push ecx
    L_004369b1:
        push edx
    L_004369b2:
        call dword ptr [data_00466034]
    L_004369b8:
        mov dword ptr [esi],eax
    L_004369ba:
        ret
    }
}
