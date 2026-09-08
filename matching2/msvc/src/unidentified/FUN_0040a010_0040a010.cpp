#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A010..0x0040A033: FUN_0040a010
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040a010_0040a010() {
    __asm {
    L_0040a010:
        mov ecx,dword ptr [eax+8]
    L_0040a013:
        push esi
    L_0040a014:
        mov esi,dword ptr [ecx+4]
    L_0040a017:
        mov edx,2
    L_0040a01c:
        or esi,edx
    L_0040a01e:
        mov dword ptr [ecx+4],esi
    L_0040a021:
        mov ecx,dword ptr [eax+0Ch]
    L_0040a024:
        mov esi,dword ptr [ecx+4]
    L_0040a027:
        or esi,edx
    L_0040a029:
        push eax
    L_0040a02a:
        mov dword ptr [ecx+4],esi
    L_0040a02d:
        call asm_FUN_00426f70_00426f70
    L_0040a032:
        pop esi
    L_0040a033:
        ret
    }
}
