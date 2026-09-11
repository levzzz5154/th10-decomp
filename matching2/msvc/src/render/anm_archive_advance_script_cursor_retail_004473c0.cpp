#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446C70..0x00446D62: FUN_00446c70
// Naked body preserves the retail register/stack ABI.

// 0x004473C0..0x0044746D: AnmArchive_AdvanceScriptCursorRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnmArchive_AdvanceScriptCursorRetail_004473c0() {
    __asm {
    L_004473c0:
        push ecx
    L_004473c1:
        push ebx
    L_004473c2:
        push ebp
    L_004473c3:
        mov ebp,dword ptr [esp+14h]
    L_004473c7:
        push esi
    L_004473c8:
        mov esi,dword ptr [ebp+108h]
    L_004473ce:
        xor edx,edx
    L_004473d0:
        xor ecx,ecx
    L_004473d2:
        push edi
    L_004473d3:
        xor ebx,ebx
    L_004473d5:
        mov dword ptr [esp+10h],ecx
    L_004473d9:
        xor edi,edi
    L_004473db:
        mov dword ptr [esp+1Ch],edx
    L_004473df:
        nop
    L_004473e0:
        mov eax,dword ptr [ebp+124h]
    L_004473e6:
        dec eax
    L_004473e7:
        cmp ecx,eax
    L_004473e9:
        jne short L_0044740a
    L_004473eb:
        mov ecx,dword ptr [esp+18h]
    L_004473ef:
        mov eax,dword ptr [esp+1Ch]
    L_004473f3:
        push esi
    L_004473f4:
        push ebx
    L_004473f5:
        push edi
    L_004473f6:
        push ebp
    L_004473f7:
        push ecx
    L_004473f8:
        call asm_FUN_00447470_00447470
    L_004473fd:
        test eax,eax
    L_004473ff:
        jl short L_00447446
    L_00447401:
        mov ecx,dword ptr [esp+10h]
    L_00447405:
        mov edx,1
    L_0044740a:
        add edi,dword ptr [esi]
    L_0044740c:
        add ebx,dword ptr [esi+4]
    L_0044740f:
        inc dword ptr [esp+1Ch]
    L_00447413:
        mov eax,dword ptr [esi+38h]
    L_00447416:
        test eax,eax
    L_00447418:
        je short L_0044745a
    L_0044741a:
        add esi,eax
    L_0044741c:
        mov eax,dword ptr [ebp+124h]
    L_00447422:
        inc ecx
    L_00447423:
        cmp ecx,eax
    L_00447425:
        mov dword ptr [esp+10h],ecx
    L_00447429:
        je short L_0044742f
    L_0044742b:
        test edx,edx
    L_0044742d:
        je short L_004473e0
    L_0044742f:
        mov eax,dword ptr [ebp+124h]
    L_00447435:
        pop edi
    L_00447436:
        inc eax
    L_00447437:
        mov dword ptr [ebp+124h],eax
    L_0044743d:
        pop esi
    L_0044743e:
        mov eax,ebp
    L_00447440:
        pop ebp
    L_00447441:
        pop ebx
    L_00447442:
        pop ecx
    L_00447443:
        ret 8
    L_00447446:
        pop edi
    L_00447447:
        pop esi
    L_00447448:
        mov dword ptr [ebp+124h],0
    L_00447452:
        pop ebp
    L_00447453:
        xor eax,eax
    L_00447455:
        pop ebx
    L_00447456:
        pop ecx
    L_00447457:
        ret 8
    L_0044745a:
        pop edi
    L_0044745b:
        pop esi
    L_0044745c:
        mov dword ptr [ebp+124h],0
    L_00447466:
        mov eax,ebp
    L_00447468:
        pop ebp
    L_00447469:
        pop ebx
    L_0044746a:
        pop ecx
    L_0044746b:
        ret 8
    }
}
