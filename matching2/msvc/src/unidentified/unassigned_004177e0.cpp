// BLOCKED (M2703): closest_byte_count=25; first_diff=0x004177F2;
// residual_class=abi: seven source spellings reached the 25-byte extent,
// but the second field load/store base landed in ECX (the member receiver)
// instead of retail's required EAX destination;
// variants_tested=7 source spellings and the exact retail naked wrapper;
// next_lever=use a caller/anchor native-LTCG context that forces the second
// destination pointer into EAX while retaining the ECX receiver.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004177E0..0x004177F8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004177e0() {
    __asm {
    L_004177e0:
        mov eax,dword ptr [ecx+8]
    L_004177e3:
        push esi
    L_004177e4:
        mov esi,dword ptr [eax+4]
    L_004177e7:
        mov edx,2
    L_004177ec:
        or esi,edx
    L_004177ee:
        mov dword ptr [eax+4],esi
    L_004177f1:
        mov eax,dword ptr [ecx+0Ch]
    L_004177f4:
        or dword ptr [eax+4],edx
    L_004177f7:
        pop esi
    L_004177f8:
        ret
    }
}
