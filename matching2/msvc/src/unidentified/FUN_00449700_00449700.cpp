// Semantic model: take the address of a texture pointer in EAX, fetch texture
// level zero, query its surface description, lock the full surface, clear
// pitch*height bytes at the returned bits pointer, unlock, and Release the
// temporary surface. HRESULTs are ignored. EAX is the private input register;
// on the non-null path the return value left in EAX is Release's refcount.
//
// BLOCKED: Ghidra currently has no function at 0x00449700 and reports no xrefs
// to the entry. The 111-byte span nevertheless has a balanced local frame,
// returns at 0x0044976E, and is followed by an INT3 and the next 16-byte
// boundary at 0x00449770, strongly supporting a complete function body. The
// EAX-only input is not expressible by an ordinary MSVC x86 C++ function
// signature, so retain the byte-exact wrapper until an ABI-aware caller/cluster
// route is available. See recovery_notes/texture_surface_clear_00449700.md.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449700..0x0044976E: FUN_00449700
// The naked body preserves the retail private EAX-input ABI. The C declaration
// is only the linker-facing shell; it does not describe that register input.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449700_00449700() {
    __asm {
    L_00449700:
        mov eax,dword ptr [eax]
    L_00449702:
        mov ecx,dword ptr [eax]
    L_00449704:
        sub esp,2Ch
    L_00449707:
        push edi
    L_00449708:
        lea edx,[esp+4]
    L_0044970c:
        push edx
    L_0044970d:
        push 0
    L_0044970f:
        push eax
    L_00449710:
        call dword ptr [ecx+48h]
    L_00449713:
        mov eax,dword ptr [esp+4]
    L_00449717:
        mov ecx,dword ptr [eax]
    L_00449719:
        lea edx,[esp+10h]
    L_0044971d:
        push edx
    L_0044971e:
        push eax
    L_0044971f:
        call dword ptr [ecx+30h]
    L_00449722:
        mov eax,dword ptr [esp+4]
    L_00449726:
        mov ecx,dword ptr [eax]
    L_00449728:
        push 0
    L_0044972a:
        push 0
    L_0044972c:
        lea edx,[esp+10h]
    L_00449730:
        push edx
    L_00449731:
        push eax
    L_00449732:
        call dword ptr [ecx+34h]
    L_00449735:
        mov ecx,dword ptr [esp+2Ch]
    L_00449739:
        imul ecx,dword ptr [esp+8]
    L_0044973e:
        mov edi,dword ptr [esp+0Ch]
    L_00449742:
        mov edx,ecx
    L_00449744:
        shr ecx,2
    L_00449747:
        xor eax,eax
    L_00449749:
        rep stosd
    L_0044974b:
        mov ecx,edx
    L_0044974d:
        and ecx,3
    L_00449750:
        rep stosb
    L_00449752:
        mov eax,dword ptr [esp+4]
    L_00449756:
        mov ecx,dword ptr [eax]
    L_00449758:
        push eax
    L_00449759:
        call dword ptr [ecx+38h]
    L_0044975c:
        mov eax,dword ptr [esp+4]
    L_00449760:
        test eax,eax
    L_00449762:
        pop edi
    L_00449763:
        je short L_0044976b
    L_00449765:
        mov edx,dword ptr [eax]
    L_00449767:
        push eax
    L_00449768:
        call dword ptr [edx+8]
    L_0044976b:
        add esp,2Ch
    L_0044976e:
        ret
    }
}
