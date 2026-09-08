#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462301..0x00462326: basic_string<char,std::char_traits<char>,std::allocator<char>_>
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_basic_string_char_std_char_traits_char_std_allocator_char_00462301() {
    __asm {
    L_00462301:
        push esi
    L_00462302:
        mov esi,ecx
    L_00462304:
        push 0
    L_00462306:
        mov dword ptr [esi+18h],0Fh
    L_0046230d:
        call asm_SetLength_LegacyString_00438590
    L_00462312:
        push 0FFFFFFFFh
    L_00462314:
        push 0
    L_00462316:
        push dword ptr [esp+10h]
    L_0046231a:
        mov ecx,esi
    L_0046231c:
        call asm_AssignSubstring_LegacyString_00438260
    L_00462321:
        mov eax,esi
    L_00462323:
        pop esi
    L_00462324:
        ret 4
    }
}
