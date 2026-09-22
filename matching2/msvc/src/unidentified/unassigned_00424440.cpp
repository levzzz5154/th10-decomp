#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424440..0x00424450: unassigned code fragment
// BLOCKED (M2703): closest_byte_count=14/17; first_diff=0x00424441;
// residual_class=private ABI/register allocation: the readable pair compare
// emits the same three-way result sequence and RET, but a natural member uses
// ECX as the receiver while retail enters with the pair in EAX.  Ghidra has no
// containing function or xrefs from this unresolved fragment.
// variants_tested=natural Pair::IsDifferent member and equivalent inequality
// forms; all retained the ECX receiver, differing in the three base-register
// encodings.
// next_lever=native-LTCG caller topology proving the private EAX receiver;
// no legal caller was available for this unresolved region.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00424440() {
    __asm {
    L_00424440:
        mov ecx,dword ptr [eax+4]
    L_00424443:
        push esi
    L_00424444:
        mov esi,dword ptr [eax]
    L_00424446:
        xor edx,edx
    L_00424448:
        cmp ecx,esi
    L_0042444a:
        setne dl
    L_0042444d:
        pop esi
    L_0042444e:
        mov eax,edx
    L_00424450:
        ret
    }
}
