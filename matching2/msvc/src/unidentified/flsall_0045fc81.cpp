#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FC81..0x0045FD1B: flsall
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_flsall_0045fc81() {
    __asm {
    L_0045fc81:
        push 14h
    L_0045fc83:
        push 46C8E8h
    L_0045fc88:
        call asm_SEH_prolog_00454bbc
    L_0045fc8d:
        xor edi,edi
    L_0045fc8f:
        mov dword ptr [ebp-1Ch],edi
    L_0045fc92:
        mov dword ptr [ebp-24h],edi
    L_0045fc95:
        push 1
    L_0045fc97:
        call asm_lock_00453c0c
    L_0045fc9c:
        pop ecx
    L_0045fc9d:
        mov dword ptr [ebp-4],edi
    L_0045fca0:
        xor esi,esi
    L_0045fca2:
        mov dword ptr [ebp-20h],esi
    L_0045fca5:
        cmp esi,dword ptr [data_004991e0]
    L_0045fcab:
        jge asm_flsall_part_0045fd32
    L_0045fcb1:
        mov eax,dword ptr [data_004981d4]
    L_0045fcb6:
        mov eax,dword ptr [eax+esi*4]
    L_0045fcb9:
        cmp eax,edi
    L_0045fcbb:
        je short L_0045fd19
    L_0045fcbd:
        test byte ptr [eax+0Ch],83h
    L_0045fcc1:
        je short L_0045fd19
    L_0045fcc3:
        push eax
    L_0045fcc4:
        push esi
    L_0045fcc5:
        call asm_lock_file2_0045a099
    L_0045fcca:
        pop ecx
    L_0045fccb:
        pop ecx
    L_0045fccc:
        xor edx,edx
    L_0045fcce:
        inc edx
    L_0045fccf:
        mov dword ptr [ebp-4],edx
    L_0045fcd2:
        mov eax,dword ptr [data_004981d4]
    L_0045fcd7:
        mov eax,dword ptr [eax+esi*4]
    L_0045fcda:
        mov ecx,dword ptr [eax+0Ch]
    L_0045fcdd:
        test cl,83h
    L_0045fce0:
        je short L_0045fd11
    L_0045fce2:
        cmp dword ptr [ebp+8],edx
    L_0045fce5:
        jne short L_0045fcf8
    L_0045fce7:
        push eax
    L_0045fce8:
        call asm_fflush_lk_0045fc53
    L_0045fced:
        pop ecx
    L_0045fcee:
        cmp eax,0FFFFFFFFh
    L_0045fcf1:
        je short L_0045fd11
    L_0045fcf3:
        inc dword ptr [ebp-1Ch]
    L_0045fcf6:
        jmp short L_0045fd11
    L_0045fcf8:
        cmp dword ptr [ebp+8],edi
    L_0045fcfb:
        jne short L_0045fd11
    L_0045fcfd:
        test cl,2
    L_0045fd00:
        je short L_0045fd11
    L_0045fd02:
        push eax
    L_0045fd03:
        call asm_fflush_lk_0045fc53
    L_0045fd08:
        pop ecx
    L_0045fd09:
        cmp eax,0FFFFFFFFh
    L_0045fd0c:
        jne short L_0045fd11
    L_0045fd0e:
        or dword ptr [ebp-24h],eax
    L_0045fd11:
        mov dword ptr [ebp-4],edi
    L_0045fd14:
        call asm_FUN_0045fd21_0045fd21
    L_0045fd19:
        inc esi
    L_0045fd1a:
        jmp short L_0045fca2
    }
}

// 0x0045FD32..0x0045FD4C: flsall
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_flsall_part_0045fd32() {
    __asm {
    L_0045fd32:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045fd36:
        call asm_FUN_0045fd4d_0045fd4d
    L_0045fd3b:
        cmp dword ptr [ebp+8],1
    L_0045fd3f:
        mov eax,dword ptr [ebp-1Ch]
    L_0045fd42:
        je short L_0045fd47
    L_0045fd44:
        mov eax,dword ptr [ebp-24h]
    L_0045fd47:
        call asm_SEH_epilog_00454bf7
    L_0045fd4c:
        ret
    }
}
