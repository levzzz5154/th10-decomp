#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043D050..0x0043D076: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043d050() {
    __asm {
    L_0043d050:
        mov eax,dword ptr [esi]
    L_0043d052:
        test eax,eax
    L_0043d054:
        je short L_0043d062
    L_0043d056:
        mov ecx,dword ptr [eax]
    L_0043d058:
        push eax
    L_0043d059:
        call dword ptr [ecx+8]
    L_0043d05c:
        mov dword ptr [esi],0
    L_0043d062:
        test byte ptr [esp+4],1
    L_0043d067:
        je short L_0043d072
    L_0043d069:
        push esi
    L_0043d06a:
        call asm_free_004524a1
    L_0043d06f:
        add esp,4
    L_0043d072:
        mov eax,esi
    L_0043d074:
        ret 4
    }
}
