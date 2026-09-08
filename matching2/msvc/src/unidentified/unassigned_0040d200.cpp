#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D200..0x0040D251: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040d200() {
    __asm {
    L_0040d200:
        push esi
    L_0040d201:
        mov esi,dword ptr [ecx+58h]
    L_0040d204:
        lea eax,[edx+116Ch]
    L_0040d20a:
        cmp esi,eax
    L_0040d20c:
        push edi
    L_0040d20d:
        jne short L_0040d218
    L_0040d20f:
        mov esi,dword ptr [edx+1170h]
    L_0040d215:
        mov dword ptr [ecx+58h],esi
    L_0040d218:
        cmp dword ptr [ecx+5Ch],eax
    L_0040d21b:
        jne short L_0040d226
    L_0040d21d:
        mov edx,dword ptr [edx+1174h]
    L_0040d223:
        mov dword ptr [ecx+5Ch],edx
    L_0040d226:
        mov edx,dword ptr [eax+4]
    L_0040d229:
        xor esi,esi
    L_0040d22b:
        cmp edx,esi
    L_0040d22d:
        je short L_0040d235
    L_0040d22f:
        mov edi,dword ptr [eax+8]
    L_0040d232:
        mov dword ptr [edx+8],edi
    L_0040d235:
        mov edx,dword ptr [eax+8]
    L_0040d238:
        cmp edx,esi
    L_0040d23a:
        je short L_0040d242
    L_0040d23c:
        mov edi,dword ptr [eax+4]
    L_0040d23f:
        mov dword ptr [edx+4],edi
    L_0040d242:
        mov dword ptr [eax+4],esi
    L_0040d245:
        mov dword ptr [eax+8],esi
    L_0040d248:
        mov eax,dword ptr [ecx+60h]
    L_0040d24b:
        dec eax
    L_0040d24c:
        pop edi
    L_0040d24d:
        mov dword ptr [ecx+60h],eax
    L_0040d250:
        pop esi
    L_0040d251:
        ret
    }
}
