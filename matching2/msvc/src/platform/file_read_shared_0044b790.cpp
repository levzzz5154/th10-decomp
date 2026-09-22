#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED (D3304): closest_byte_count=74/74; first_diff=none;
// residual_class=private EDI byte-count plus opaque ECX caller context cannot
// be expressed by a standalone readable MSVC declaration without an ABI
// adapter. variants_tested=live Ghidra decompilation, callers/callees/xrefs
// and variable audit (caller 0x0042A200; callees 0x00452706, CloseHandle,
// ReadFile), plus MSVC 13.10 exact baseline probe. next_lever=native-LTCG
// cluster containing the real 0x0042A200 caller and this body so LTCG can
// preserve the observed EDI/ECX handoff; current overlay remains exact.

// 0x00435370..0x004353AC: FileHandle_OpenRetail
// Naked body preserves the retail register/stack ABI.

// 0x0044B790..0x0044B7D9: ?File_ReadShared@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_File_ReadShared_0044b790() {
    __asm {
    L_0044b790:
        push ecx
    L_0044b791:
        cmp dword ptr [data_00474c38],0FFFFFFFFh
    L_0044b798:
        jne short L_0044b79e
    L_0044b79a:
        xor eax,eax
    L_0044b79c:
        pop ecx
    L_0044b79d:
        ret
    L_0044b79e:
        push esi
    L_0044b79f:
        push edi
    L_0044b7a0:
        call asm_malloc_00452706
    L_0044b7a5:
        mov esi,eax
    L_0044b7a7:
        add esp,4
    L_0044b7aa:
        test esi,esi
    L_0044b7ac:
        jne short L_0044b7bf
    L_0044b7ae:
        mov eax,dword ptr [data_00474c38]
    L_0044b7b3:
        push eax
    L_0044b7b4:
        call dword ptr [data_004660cc]
    L_0044b7ba:
        xor eax,eax
    L_0044b7bc:
        pop esi
    L_0044b7bd:
        pop ecx
    L_0044b7be:
        ret
    L_0044b7bf:
        mov edx,dword ptr [data_00474c38]
    L_0044b7c5:
        push 0
    L_0044b7c7:
        lea ecx,[esp+8]
    L_0044b7cb:
        push ecx
    L_0044b7cc:
        push edi
    L_0044b7cd:
        push esi
    L_0044b7ce:
        push edx
    L_0044b7cf:
        call dword ptr [data_004660d0]
    L_0044b7d5:
        mov eax,esi
    L_0044b7d7:
        pop esi
    L_0044b7d8:
        pop ecx
    L_0044b7d9:
        ret
    }
}
