// Current semantic candidate passes 256 retail comparisons and complete DAT
// lifecycle tests with the real vector-destructor helper. See
// reference/recovery_notes/archive_cleanup_00434c20_00434d10.md. Private ABI
// and native MSVC byte recovery remain outstanding; the probe below is history.
// BLOCKED (D3406): closest_byte_count=0/86; first_diff=unmeasured;
// residual_class=__usercall ESI archive receiver, vector-destructor element
// count/allocator ABI, and the virtual-release call through [object]+0x1C.
// variants_tested=live Ghidra complete decompilation with all callers,
// callees, xrefs and variable/storage audit; no compiler-readable candidate
// was byte-measured, so the exact naked overlay remains intact.
// next_lever=schema2/native-LTCG cluster containing the real archive open/
// reset callers at 0x00434C20 and 0x00434CA0, this close body, the vector
// destructor helper, and FileHandle::Release with ESI preserved as receiver.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.

// 0x00434D10..0x00434D65: ?DatArchive_Close@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_Close_00434d10() {
    __asm {
    L_00434d10:
        mov eax,dword ptr [esi+8]
    L_00434d13:
        push edi
    L_00434d14:
        xor edi,edi
    L_00434d16:
        cmp eax,edi
    L_00434d18:
        je short L_00434d26
    L_00434d1a:
        push eax
    L_00434d1b:
        call asm_free_00452422
    L_00434d20:
        add esp,4
    L_00434d23:
        mov dword ptr [esi+8],edi
    L_00434d26:
        mov eax,dword ptr [esi]
    L_00434d28:
        cmp eax,edi
    L_00434d2a:
        mov dword ptr [esi+8],edi
    L_00434d2d:
        je short L_00434d4e
    L_00434d2f:
        mov ecx,dword ptr [eax-4]
    L_00434d32:
        push ebx
    L_00434d33:
        lea ebx,[eax-4]
    L_00434d36:
        push 435250h
    L_00434d3b:
        push ecx
    L_00434d3c:
        push 10h
    L_00434d3e:
        push eax
    L_00434d3f:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00434d44:
        push ebx
    L_00434d45:
        call asm_free_004524a1
    L_00434d4a:
        add esp,4
    L_00434d4d:
        pop ebx
    L_00434d4e:
        mov ecx,dword ptr [esi+0Ch]
    L_00434d51:
        cmp ecx,edi
    L_00434d53:
        mov dword ptr [esi],edi
    L_00434d55:
        je short L_00434d5e
    L_00434d57:
        mov edx,dword ptr [ecx]
    L_00434d59:
        push 1
    L_00434d5b:
        call dword ptr [edx+1Ch]
    L_00434d5e:
        mov dword ptr [esi+0Ch],edi
    L_00434d61:
        mov dword ptr [esi+4],edi
    L_00434d64:
        pop edi
    L_00434d65:
        ret
    }
}
