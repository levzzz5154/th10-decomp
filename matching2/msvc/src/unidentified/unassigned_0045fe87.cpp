#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FE87..0x00460027: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045fe87() {
    __asm {
    L_0045fe87:
        push 0Ch
    L_0045fe89:
        push 46C920h
    L_0045fe8e:
        call asm_SEH_prolog_00454bbc
    L_0045fe93:
        mov ebx,dword ptr [ebp+0Ch]
    L_0045fe96:
        cmp ebx,4
    L_0045fe99:
        je asm_target_0045ffcd
    L_0045fe9f:
        cmp ebx,3
    L_0045fea2:
        je asm_target_0045ffcd
    L_0045fea8:
        mov esi,dword ptr [ebp+8]
    L_0045feab:
        cmp esi,2
    L_0045feae:
        je asm_target_0045ff59
    L_0045feb4:
        cmp esi,15h
    L_0045feb7:
        je asm_target_0045ff59
    L_0045febd:
        cmp esi,16h
    L_0045fec0:
        je asm_target_0045ff59
    L_0045fec6:
        cmp esi,0Fh
    L_0045fec9:
        je asm_target_0045ff59
    L_0045fecf:
        cmp esi,8
    L_0045fed2:
        je short L_0045fee2
    L_0045fed4:
        cmp esi,4
    L_0045fed7:
        je short L_0045fee2
    L_0045fed9:
        cmp esi,0Bh
    L_0045fedc:
        jne asm_target_0045ffcd
    L_0045fee2:
        call asm_getptd_00456357
    L_0045fee7:
        mov edi,eax
    L_0045fee9:
        mov ebx,4735D0h
    L_0045feee:
        cmp dword ptr [edi+54h],ebx
    L_0045fef1:
        jne short L_0045ff1a
    L_0045fef3:
        push dword ptr [data_00473650]
    L_0045fef9:
        call asm_malloc_00452706
    L_0045fefe:
        pop ecx
    L_0045feff:
        mov dword ptr [edi+54h],eax
    L_0045ff02:
        test eax,eax
    L_0045ff04:
        je asm_target_0045ffcd
    L_0045ff0a:
        push dword ptr [data_00473650]
    L_0045ff10:
        push ebx
    L_0045ff11:
        push eax
    L_0045ff12:
        call asm_memcpy_0045bfc0
    L_0045ff17:
        add esp,0Ch
    L_0045ff1a:
        mov edx,dword ptr [edi+54h]
    L_0045ff1d:
        call asm_siglookup_0045fe47
    L_0045ff22:
        test eax,eax
    L_0045ff24:
        je asm_target_0045ffcd
    L_0045ff2a:
        mov edx,dword ptr [eax+8]
    L_0045ff2d:
        jmp short L_0045ff4f
    L_0045ff2f:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045ff32:
        mov dword ptr [eax+8],ecx
    L_0045ff35:
        add eax,0Ch
    L_0045ff38:
        mov ecx,dword ptr [data_00473654]
    L_0045ff3e:
        lea ecx,[ecx+ecx*2]
    L_0045ff41:
        mov ebx,dword ptr [edi+54h]
    L_0045ff44:
        lea ecx,[ebx+ecx*4]
    L_0045ff47:
        cmp eax,ecx
    L_0045ff49:
        jae asm_target_0046001b
    L_0045ff4f:
        cmp dword ptr [eax+4],esi
    L_0045ff52:
        je short L_0045ff2f
    L_0045ff54:
        jmp asm_target_0046001b
    L_0045ff59:
        xor edi,edi
    L_0045ff5b:
        push edi
    L_0045ff5c:
        call asm_lock_00453c0c
    L_0045ff61:
        pop ecx
    L_0045ff62:
        mov dword ptr [ebp-4],edi
    L_0045ff65:
        cmp esi,2
    L_0045ff68:
        je short L_0045ff6f
    L_0045ff6a:
        cmp esi,15h
    L_0045ff6d:
        jne short L_0045ff90
    L_0045ff6f:
        cmp dword ptr [data_004776c0],edi
    L_0045ff75:
        jne short L_0045ff90
    L_0045ff77:
        xor edi,edi
    L_0045ff79:
        inc edi
    L_0045ff7a:
        push edi
    L_0045ff7b:
        push 45FDB8h
    L_0045ff80:
        call dword ptr [data_004661c0]
    L_0045ff86:
        cmp eax,edi
    L_0045ff88:
        jne short L_0045ffb1
    L_0045ff8a:
        mov dword ptr [data_004776c0],edi
    L_0045ff90:
        dec esi
    L_0045ff91:
        dec esi
    L_0045ff92:
        je short L_00460001
    L_0045ff94:
        sub esi,0Dh
    L_0045ff97:
        je short L_0045fff1
    L_0045ff99:
        sub esi,6
    L_0045ff9c:
        je short L_0045ffe1
    L_0045ff9e:
        dec esi
    L_0045ff9f:
        jne short L_0046000f
    L_0045ffa1:
        mov eax,dword ptr [data_004776b8]
    L_0045ffa6:
        mov dword ptr [ebp-1Ch],eax
    L_0045ffa9:
        mov dword ptr [data_004776b8],ebx
    L_0045ffaf:
        jmp short L_0046000f
    L_0045ffb1:
        call asm_FUN_00456afb_00456afb
    L_0045ffb6:
        mov esi,eax
    L_0045ffb8:
        call dword ptr [data_0046610c]
    L_0045ffbe:
        mov dword ptr [esi],eax
    L_0045ffc0:
        push 0FFFFFFFFh
    L_0045ffc2:
        lea eax,[ebp-10h]
    L_0045ffc5:
        push eax
    L_0045ffc6:
        call asm_local_unwind2_004598de
    L_0045ffcb:
        pop ecx
    L_0045ffcc:
        pop ecx
    L_0045ffcd:
        call asm_FUN_00456af2_00456af2
    L_0045ffd2:
        mov dword ptr [eax],16h
    L_0045ffd8:
        or eax,0FFFFFFFFh
    L_0045ffdb:
        call asm_SEH_epilog_00454bf7
    L_0045ffe0:
        ret
    L_0045ffe1:
        mov eax,dword ptr [data_004776b4]
    L_0045ffe6:
        mov dword ptr [ebp-1Ch],eax
    L_0045ffe9:
        mov dword ptr [data_004776b4],ebx
    L_0045ffef:
        jmp short L_0046000f
    L_0045fff1:
        mov eax,dword ptr [data_004776bc]
    L_0045fff6:
        mov dword ptr [ebp-1Ch],eax
    L_0045fff9:
        mov dword ptr [data_004776bc],ebx
    L_0045ffff:
        jmp short L_0046000f
    L_00460001:
        mov eax,dword ptr [data_004776b0]
    L_00460006:
        mov dword ptr [ebp-1Ch],eax
    L_00460009:
        mov dword ptr [data_004776b0],ebx
    L_0046000f:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00460013:
        call asm_target_0046001f
    L_00460018:
        mov edx,dword ptr [ebp-1Ch]
    L_0046001b:
        mov eax,edx
    L_0046001d:
        jmp short L_0045ffdb
    L_0046001f:
        push 0
    L_00460021:
        call asm_FUN_00453b3f_00453b3f
    L_00460026:
        pop ecx
    L_00460027:
        ret
    }
}
