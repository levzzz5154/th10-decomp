#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459F39..0x00459F7C: __getbuf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_getbuf_00459f39() {
    __asm {
    L_00459f39:
        inc dword ptr [data_00477614]
    L_00459f3f:
        push 1000h
    L_00459f44:
        call asm_malloc_00452706
    L_00459f49:
        test eax,eax
    L_00459f4b:
        pop ecx
    L_00459f4c:
        mov ecx,dword ptr [esp+4]
    L_00459f50:
        mov dword ptr [ecx+8],eax
    L_00459f53:
        je short L_00459f62
    L_00459f55:
        or dword ptr [ecx+0Ch],8
    L_00459f59:
        mov dword ptr [ecx+18h],1000h
    L_00459f60:
        jmp short L_00459f73
    L_00459f62:
        or dword ptr [ecx+0Ch],4
    L_00459f66:
        lea eax,[ecx+14h]
    L_00459f69:
        mov dword ptr [ecx+8],eax
    L_00459f6c:
        mov dword ptr [ecx+18h],2
    L_00459f73:
        mov eax,dword ptr [ecx+8]
    L_00459f76:
        and dword ptr [ecx+4],0
    L_00459f7a:
        mov dword ptr [ecx],eax
    L_00459f7c:
        ret
    }
}
