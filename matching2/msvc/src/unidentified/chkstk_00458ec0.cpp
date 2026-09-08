#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458EC0..0x00458EFC: __chkstk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_chkstk_00458ec0() {
    __asm {
    L_00458ec0:
        cmp eax,1000h
    L_00458ec5:
        jae short L_00458ed5
    L_00458ec7:
        neg eax
    L_00458ec9:
        add eax,esp
    L_00458ecb:
        add eax,4
    L_00458ece:
        test dword ptr [eax],eax
    L_00458ed0:
        xchg esp,eax
    L_00458ed1:
        mov eax,dword ptr [eax]
    L_00458ed3:
        push eax
    L_00458ed4:
        ret
    L_00458ed5:
        push ecx
    L_00458ed6:
        lea ecx,[esp+8]
    L_00458eda:
        sub ecx,1000h
    L_00458ee0:
        sub eax,1000h
    L_00458ee5:
        test dword ptr [ecx],eax
    L_00458ee7:
        cmp eax,1000h
    L_00458eec:
        jae short L_00458eda
    L_00458eee:
        sub ecx,eax
    L_00458ef0:
        mov eax,esp
    L_00458ef2:
        test dword ptr [ecx],eax
    L_00458ef4:
        mov esp,ecx
    L_00458ef6:
        mov ecx,dword ptr [eax]
    L_00458ef8:
        mov eax,dword ptr [eax+4]
    L_00458efb:
        push eax
    L_00458efc:
        ret
    }
}
