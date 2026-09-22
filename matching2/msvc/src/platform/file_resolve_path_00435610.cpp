#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435370..0x004353AC: FileHandle_OpenRetail
// Naked body preserves the retail register/stack ABI.

// 0x00435610..0x00435688: ?File_ResolvePath@@
// Naked body preserves the retail register/stack ABI.
// BLOCKED (D3704): closest_byte_count=0/121; first_diff=0x00435610;
// residual_class=EAX/ECX usercall ABI, in-place path aliasing, and Win32
// buffer semantics; variants_tested=["live Ghidra decompile at 0x00435610",
// "live caller 0x00435370", "MSVC 13.10 schema-2 baseline probe"];
// next_lever=native-LTCG cluster co-compiling caller 0x00435370 with typed
// FileHandle/path declarations and the real FUN_00452730/strrchr callees.
extern "C" __declspec(naked) void __cdecl asm_File_ResolvePath_00435610() {
    __asm {
    L_00435610:
        push esi
    L_00435611:
        push edi
    L_00435612:
        mov esi,eax
    L_00435614:
        push 3Ah
    L_00435616:
        push esi
    L_00435617:
        mov edi,ecx
    L_00435619:
        call asm_FUN_00452730_00452730
    L_0043561e:
        add esp,8
    L_00435621:
        test eax,eax
    L_00435623:
        je short L_0043563d
    L_00435625:
        mov eax,esi
    L_00435627:
        sub edi,esi
    L_00435629:
        lea esp,[esp+force_disp32_zero]
    L_00435630:
        mov cl,byte ptr [eax]
    L_00435632:
        mov byte ptr [edi+eax],cl
    L_00435635:
        inc eax
    L_00435636:
        test cl,cl
    L_00435638:
        jne short L_00435630
    L_0043563a:
        pop edi
    L_0043563b:
        pop esi
    L_0043563c:
        ret
    L_0043563d:
        push 104h
    L_00435642:
        push edi
    L_00435643:
        push 0
    L_00435645:
        call dword ptr [data_004660dc]
    L_0043564b:
        push 5Ch
    L_0043564d:
        push edi
    L_0043564e:
        call asm_strrchr_00452930
    L_00435653:
        add esp,8
    L_00435656:
        test eax,eax
    L_00435658:
        jne short L_0043565c
    L_0043565a:
        mov byte ptr [edi],al
    L_0043565c:
        mov byte ptr [eax+1],0
    L_00435660:
        mov eax,esi
    L_00435662:
        mov ecx,esi
    L_00435664:
        mov dl,byte ptr [eax]
    L_00435666:
        inc eax
    L_00435667:
        test dl,dl
    L_00435669:
        jne short L_00435664
    L_0043566b:
        sub eax,ecx
    L_0043566d:
        mov esi,ecx
    L_0043566f:
        dec edi
    L_00435670:
        mov cl,byte ptr [edi+1]
    L_00435673:
        inc edi
    L_00435674:
        test cl,cl
    L_00435676:
        jne short L_00435670
    L_00435678:
        mov ecx,eax
    L_0043567a:
        shr ecx,2
    L_0043567d:
        rep movsd
    L_0043567f:
        mov ecx,eax
    L_00435681:
        and ecx,3
    L_00435684:
        rep movsb
    L_00435686:
        pop edi
    L_00435687:
        pop esi
    L_00435688:
        ret
    }
}
