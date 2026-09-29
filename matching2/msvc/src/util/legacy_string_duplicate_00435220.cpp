// Current candidate passes 276 string-copy cases and complete DAT lifecycle
// comparisons with both callers. See
// reference/recovery_notes/dat_archive_open_00434c30_00434ca0.md. Native MSVC
// matching remains outstanding; the historical probe below predates this model.
// BLOCKED (D3802): closest_byte_count=63/47; first_diff=0x00435220;
// residual_class=private EDI string receiver, malloc/copy loop register
// lifetime, and the undecorated no-stack-argument entry ABI. Live Ghidra
// decompilation confirms the null-inclusive length calculation and
// destination-minus-source copy idiom.
// variants_tested=live Ghidra decompile with callers 0x00434C30 and
// 0x00434CE0; archived LegacyString_Duplicate semantic source; MSVC 13.10
// readable cdecl candidate (63-byte body, stack argument in place of EDI);
// no candidate retained because the callers remain assembly-only edges.
// next_lever=make both archive callers and this duplicate routine
// compiler-visible in one cluster, preserving the callers' real ABI, then
// compare the complete 47-byte body before replacing the exact assembly.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/util/heap.hpp"

// 0x00418150..0x00418161: ?Heap_DestroyOwned@@
// Naked body preserves the retail register/stack ABI.

// 0x00435220..0x0043524E: ?LegacyString_Duplicate@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_LegacyString_Duplicate_00435220() {
    __asm {
    L_00435220:
        mov eax,edi
    L_00435222:
        lea edx,[eax+1]
    L_00435225:
        mov cl,byte ptr [eax]
    L_00435227:
        inc eax
    L_00435228:
        test cl,cl
    L_0043522a:
        jne short L_00435225
    L_0043522c:
        sub eax,edx
    L_0043522e:
        inc eax
    L_0043522f:
        push eax
    L_00435230:
        call asm_malloc_00452706
    L_00435235:
        add esp,4
    L_00435238:
        test eax,eax
    L_0043523a:
        je short L_0043524e
    L_0043523c:
        push esi
    L_0043523d:
        mov esi,eax
    L_0043523f:
        mov ecx,edi
    L_00435241:
        sub esi,edi
    L_00435243:
        mov dl,byte ptr [ecx]
    L_00435245:
        mov byte ptr [esi+ecx],dl
    L_00435248:
        inc ecx
    L_00435249:
        test dl,dl
    L_0043524b:
        jne short L_00435243
    L_0043524d:
        pop esi
    L_0043524e:
        ret
    }
}
