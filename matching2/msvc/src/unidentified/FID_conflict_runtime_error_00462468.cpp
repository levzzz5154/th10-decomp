#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462468..0x004624AA: FID_conflict:runtime_error
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FID_conflict_runtime_error_00462468() {
    __asm {
    L_00462468:
        mov eax,4651BCh
    L_0046246d:
        call asm_FUN_00462adc_00462adc
    L_00462472:
        push ecx
    L_00462473:
        push esi
    L_00462474:
        push edi
    L_00462475:
        mov edi,dword ptr [ebp+8]
    L_00462478:
        mov esi,ecx
    L_0046247a:
        push edi
    L_0046247b:
        mov dword ptr [ebp-10h],esi
    L_0046247e:
        call asm_FUN_00462c5a_00462c5a
    L_00462483:
        and dword ptr [ebp-4],0
    L_00462487:
        add edi,0Ch
    L_0046248a:
        push edi
    L_0046248b:
        lea ecx,[esi+0Ch]
    L_0046248e:
        mov dword ptr [esi],46C9E8h
    L_00462494:
        call asm_basic_string_char_std_char_traits_char_std_allocator_char_00462301
    L_00462499:
        mov ecx,dword ptr [ebp-0Ch]
    L_0046249c:
        pop edi
    L_0046249d:
        mov eax,esi
    L_0046249f:
        pop esi
    L_004624a0:
        mov dword ptr fs:[0],ecx
    L_004624a7:
        leave
    L_004624a8:
        ret 4
    }
}
