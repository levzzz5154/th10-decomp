#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D260..0x0040D27C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040d260() {
    __asm {
    L_0040d260:
        and dword ptr [edx+50h],0FFFFFFFEh
    L_0040d264:
        push edi
    L_0040d265:
        xor eax,eax
    L_0040d267:
        mov ecx,1Ah
    L_0040d26c:
        mov edi,edx
    L_0040d26e:
        rep stosd
    L_0040d270:
        or dword ptr [edx],2
    L_0040d273:
        mov dword ptr [data_00477704],edx
    L_0040d279:
        mov eax,edx
    L_0040d27b:
        pop edi
    L_0040d27c:
        ret
    }
}
