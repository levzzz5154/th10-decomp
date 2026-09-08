#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462327..0x00462362: FID_conflict:runtime_error
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FID_conflict_runtime_error_00462327() {
    __asm {
    L_00462327:
        mov eax,465198h
    L_0046232c:
        call asm_FUN_00462adc_00462adc
    L_00462331:
        push ecx
    L_00462332:
        push esi
    L_00462333:
        mov esi,ecx
    L_00462335:
        mov dword ptr [ebp-10h],esi
    L_00462338:
        call asm_exception_00462c01
    L_0046233d:
        push dword ptr [ebp+8]
    L_00462340:
        and dword ptr [ebp-4],0
    L_00462344:
        lea ecx,[esi+0Ch]
    L_00462347:
        mov dword ptr [esi],46C9E8h
    L_0046234d:
        call asm_basic_string_char_std_char_traits_char_std_allocator_char_00462301
    L_00462352:
        mov ecx,dword ptr [ebp-0Ch]
    L_00462355:
        mov eax,esi
    L_00462357:
        pop esi
    L_00462358:
        mov dword ptr fs:[0],ecx
    L_0046235f:
        leave
    L_00462360:
        ret 4
    }
}
