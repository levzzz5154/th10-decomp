// BLOCKED (M2701): closest_byte_count=0; first_diff=0x0044DEE0;
// residual_class=private ABI: retail enters with its archive object in ESI,
// performs an indirect import call, and has two retail RET sites. The fixed C
// symbol cannot preserve the private receiver convention.
// variants_tested=extern-C cdecl readable cursor/import body (38-byte extent,
// first diff at byte 0), compiled with the project MSVC 13.10 profile and
// rejected. Exact naked baseline remains 33 bytes.
// next_lever=native-LTCG cluster with the real caller/import binding and ESI
// receiver, followed by semantic manifest ownership migration.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DEE0..0x0044DF00: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044dee0() {
    __asm {
    L_0044dee0:
        cmp dword ptr [esi+78h],1
    L_0044dee4:
        jne short L_0044defd
    L_0044dee6:
        mov eax,dword ptr [esi+8Ch]
    L_0044deec:
        push eax
    L_0044deed:
        call dword ptr [data_004660cc]
    L_0044def3:
        mov dword ptr [esi+8Ch],0FFFFFFFFh
    L_0044defd:
        xor eax,eax
    L_0044deff:
        ret
    L_0044df00:
        ret
    }
}
