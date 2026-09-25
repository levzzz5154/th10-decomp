#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456720..0x004567AA: _strlen
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strlen_00456720() {
    __asm {
    L_00456720:
        mov ecx,dword ptr [esp+4]
    L_00456724:
        test ecx,3
    L_0045672a:
        je short L_00456750
    L_0045672c:
        mov al,byte ptr [ecx]
    L_0045672e:
        add ecx,1
    L_00456731:
        test al,al
    L_00456733:
        je short L_00456783
    L_00456735:
        test ecx,3
    L_0045673b:
        jne short L_0045672c
    L_0045673d:
        add eax,offset force_imm32_zero
    L_00456742:
        lea esp,[esp+force_disp32_zero]
    L_00456749:
        lea esp,[esp+force_disp32_zero]
    L_00456750:
        mov eax,dword ptr [ecx]
    L_00456752:
        mov edx,7EFEFEFFh
    L_00456757:
        add edx,eax
    L_00456759:
        xor eax,0FFFFFFFFh
    L_0045675c:
        xor eax,edx
    L_0045675e:
        add ecx,4
    L_00456761:
        test eax,81010100h
    L_00456766:
        je short L_00456750
    L_00456768:
        mov eax,dword ptr [ecx-4]
    L_0045676b:
        test al,al
    L_0045676d:
        je short L_004567a1
    L_0045676f:
        test ah,ah
    L_00456771:
        je short L_00456797
    L_00456773:
        test eax,0FF0000h
    L_00456778:
        je short L_0045678d
    L_0045677a:
        test eax,0FF000000h
    L_0045677f:
        je short L_00456783
    L_00456781:
        jmp short L_00456750
    L_00456783:
        lea eax,[ecx-1]
    L_00456786:
        mov ecx,dword ptr [esp+4]
    L_0045678a:
        sub eax,ecx
    L_0045678c:
        ret
    L_0045678d:
        lea eax,[ecx-2]
    L_00456790:
        mov ecx,dword ptr [esp+4]
    L_00456794:
        sub eax,ecx
    L_00456796:
        ret
    L_00456797:
        lea eax,[ecx-3]
    L_0045679a:
        mov ecx,dword ptr [esp+4]
    L_0045679e:
        sub eax,ecx
    L_004567a0:
        ret
    L_004567a1:
        lea eax,[ecx-4]
    L_004567a4:
        mov ecx,dword ptr [esp+4]
    L_004567a8:
        sub eax,ecx
    L_004567aa:
        ret
    }
}
