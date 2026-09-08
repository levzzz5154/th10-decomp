#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041ACF0..0x0041AD57: FUN_0041acf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041acf0_0041acf0() {
    __asm {
    L_0041acf0:
        mov edx,ecx
    L_0041acf2:
        mov eax,dword ptr [edx+6Ch]
    L_0041acf5:
        push esi
    L_0041acf6:
        mov esi,0FFFFFFFEh
    L_0041acfb:
        and eax,esi
    L_0041acfd:
        mov dword ptr [edx+6Ch],eax
    L_0041ad00:
        push edi
    L_0041ad01:
        and dword ptr [edx+0B0h],esi
    L_0041ad07:
        and dword ptr [edx+0FCh],esi
    L_0041ad0d:
        and dword ptr [edx+128h],esi
    L_0041ad13:
        and dword ptr [edx+174h],esi
    L_0041ad19:
        and dword ptr [edx+1B0h],esi
    L_0041ad1f:
        and dword ptr [edx+1FCh],esi
    L_0041ad25:
        and dword ptr [edx+228h],esi
    L_0041ad2b:
        and dword ptr [edx+378h],esi
    L_0041ad31:
        xor eax,eax
    L_0041ad33:
        mov ecx,0EBh
    L_0041ad38:
        mov edi,edx
    L_0041ad3a:
        rep stosd
    L_0041ad3c:
        mov word ptr [edx+384h],0FFFFh
    L_0041ad45:
        mov eax,dword ptr [edx+3D8h]
    L_0041ad4b:
        and eax,esi
    L_0041ad4d:
        pop edi
    L_0041ad4e:
        mov dword ptr [edx+3D8h],eax
    L_0041ad54:
        mov eax,edx
    L_0041ad56:
        pop esi
    L_0041ad57:
        ret
    }
}
