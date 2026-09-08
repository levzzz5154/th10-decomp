#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A870..0x0042A899: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042a870() {
    __asm {
    L_0042a870:
        mov edx,dword ptr [ecx+5460h]
    L_0042a876:
        sub edx,ecx
    L_0042a878:
        mov eax,2AAAAAABh
    L_0042a87d:
        imul edx
    L_0042a87f:
        mov eax,edx
    L_0042a881:
        shr eax,1Fh
    L_0042a884:
        lea eax,[edx+eax+2AAA9C9Ah]
    L_0042a88b:
        lea edx,[eax+eax*2]
    L_0042a88e:
        mov eax,dword ptr [ecx+6274h]
    L_0042a894:
        lea eax,[eax+edx*2]
    L_0042a897:
        sub eax,ecx
    L_0042a899:
        ret
    }
}
