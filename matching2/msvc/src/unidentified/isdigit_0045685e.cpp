#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045685E..0x00456897: _isdigit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_isdigit_0045685e() {
    __asm {
    L_0045685e:
        call asm_getptd_00456357
    L_00456863:
        mov eax,dword ptr [eax+64h]
    L_00456866:
        cmp eax,dword ptr [data_0047320c]
    L_0045686c:
        je short L_00456873
    L_0045686e:
        call asm_updatetlocinfo_00455ade
    L_00456873:
        cmp dword ptr [eax+28h],1
    L_00456877:
        jle short L_00456889
    L_00456879:
        push 4
    L_0045687b:
        push dword ptr [esp+8]
    L_0045687f:
        push eax
    L_00456880:
        call asm_isctype_mt_00455752
    L_00456885:
        add esp,0Ch
    L_00456888:
        ret
    L_00456889:
        mov eax,dword ptr [eax+48h]
    L_0045688c:
        mov ecx,dword ptr [esp+4]
    L_00456890:
        movzx eax,byte ptr [eax+ecx*2]
    L_00456894:
        and eax,4
    L_00456897:
        ret
    }
}
