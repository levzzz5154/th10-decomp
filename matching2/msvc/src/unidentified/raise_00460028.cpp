#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460028..0x0046015A: _raise
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_raise_00460028() {
    __asm {
    L_00460028:
        push 20h
    L_0046002a:
        push 46C930h
    L_0046002f:
        call asm_SEH_prolog_00454bbc
    L_00460034:
        xor ecx,ecx
    L_00460036:
        mov dword ptr [ebp-1Ch],ecx
    L_00460039:
        mov eax,dword ptr [ebp+8]
    L_0046003c:
        dec eax
    L_0046003d:
        dec eax
    L_0046003e:
        je short L_004600aa
    L_00460040:
        dec eax
    L_00460041:
        dec eax
    L_00460042:
        je short L_0046008a
    L_00460044:
        sub eax,4
    L_00460047:
        je short L_0046008a
    L_00460049:
        sub eax,3
    L_0046004c:
        je short L_0046008a
    L_0046004e:
        sub eax,4
    L_00460051:
        je short L_0046007d
    L_00460053:
        sub eax,6
    L_00460056:
        je short L_00460070
    L_00460058:
        dec eax
    L_00460059:
        je short L_00460063
    L_0046005b:
        or eax,0FFFFFFFFh
    L_0046005e:
        jmp asm_target_0046019b
    L_00460063:
        mov esi,4776B8h
    L_00460068:
        mov edi,dword ptr [data_004776b8]
    L_0046006e:
        jmp short L_004600b5
    L_00460070:
        mov esi,4776B4h
    L_00460075:
        mov edi,dword ptr [data_004776b4]
    L_0046007b:
        jmp short L_004600b5
    L_0046007d:
        mov esi,4776BCh
    L_00460082:
        mov edi,dword ptr [data_004776bc]
    L_00460088:
        jmp short L_004600b5
    L_0046008a:
        call asm_getptd_00456357
    L_0046008f:
        mov ebx,eax
    L_00460091:
        mov dword ptr [ebp-24h],ebx
    L_00460094:
        mov edx,dword ptr [ebx+54h]
    L_00460097:
        mov esi,dword ptr [ebp+8]
    L_0046009a:
        call asm_siglookup_0045fe47
    L_0046009f:
        mov esi,eax
    L_004600a1:
        add esi,8
    L_004600a4:
        mov edi,dword ptr [esi]
    L_004600a6:
        xor ecx,ecx
    L_004600a8:
        jmp short L_004600bf
    L_004600aa:
        mov esi,4776B0h
    L_004600af:
        mov edi,dword ptr [data_004776b0]
    L_004600b5:
        mov dword ptr [ebp-1Ch],1
    L_004600bc:
        mov ebx,dword ptr [ebp-24h]
    L_004600bf:
        mov dword ptr [ebp-20h],edi
    L_004600c2:
        cmp edi,1
    L_004600c5:
        je asm_target_00460199
    L_004600cb:
        cmp edi,ecx
    L_004600cd:
        jne short L_004600d6
    L_004600cf:
        push 3
    L_004600d1:
        call asm_exit_004576fd
    L_004600d6:
        cmp dword ptr [ebp-1Ch],ecx
    L_004600d9:
        je short L_004600e4
    L_004600db:
        push ecx
    L_004600dc:
        call asm_lock_00453c0c
    L_004600e1:
        pop ecx
    L_004600e2:
        xor ecx,ecx
    L_004600e4:
        mov dword ptr [ebp-4],ecx
    L_004600e7:
        mov eax,dword ptr [ebp+8]
    L_004600ea:
        cmp eax,8
    L_004600ed:
        je short L_004600f9
    L_004600ef:
        cmp eax,0Bh
    L_004600f2:
        je short L_004600f9
    L_004600f4:
        cmp eax,4
    L_004600f7:
        jne short L_00460114
    L_004600f9:
        mov edx,dword ptr [ebx+58h]
    L_004600fc:
        mov dword ptr [ebp-2Ch],edx
    L_004600ff:
        mov dword ptr [ebx+58h],ecx
    L_00460102:
        cmp eax,8
    L_00460105:
        jne short L_00460140
    L_00460107:
        mov edx,dword ptr [ebx+5Ch]
    L_0046010a:
        mov dword ptr [ebp-30h],edx
    L_0046010d:
        mov dword ptr [ebx+5Ch],8Ch
    L_00460114:
        cmp eax,8
    L_00460117:
        jne short L_00460140
    L_00460119:
        mov eax,dword ptr [data_00473648]
    L_0046011e:
        mov dword ptr [ebp-28h],eax
    L_00460121:
        mov edx,dword ptr [data_0047364c]
    L_00460127:
        mov esi,dword ptr [data_00473648]
    L_0046012d:
        add edx,esi
    L_0046012f:
        cmp eax,edx
    L_00460131:
        jge short L_00460142
    L_00460133:
        lea edx,[eax+eax*2]
    L_00460136:
        mov esi,dword ptr [ebx+54h]
    L_00460139:
        mov dword ptr [esi+edx*4+8],ecx
    L_0046013d:
        inc eax
    L_0046013e:
        jmp short L_0046011e
    L_00460140:
        mov dword ptr [esi],ecx
    L_00460142:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00460146:
        call asm_FUN_00460163_00460163
    L_0046014b:
        cmp dword ptr [ebp+8],8
    L_0046014f:
        TH10_REL8(0x75, 0x0046014f, VA_asm_raise_part_00460170)
    L_00460151:
        push dword ptr [ebx+5Ch]
    L_00460154:
        push 8
    L_00460156:
        call edi
    L_00460158:
        pop ecx
    L_00460159:
        TH10_REL8(0xeb, 0x00460159, VA_asm_target_00460175)
    }
}

// 0x00460170..0x004601A0: _raise
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_raise_part_00460170() {
    __asm {
    L_00460170:
        push dword ptr [ebp+8]
    L_00460173:
        call edi
    L_00460175:
        pop ecx
    L_00460176:
        mov eax,dword ptr [ebp+8]
    L_00460179:
        cmp eax,8
    L_0046017c:
        je short L_00460188
    L_0046017e:
        cmp eax,0Bh
    L_00460181:
        je short L_00460188
    L_00460183:
        cmp eax,4
    L_00460186:
        jne short L_00460199
    L_00460188:
        mov ecx,dword ptr [ebp-2Ch]
    L_0046018b:
        mov dword ptr [ebx+58h],ecx
    L_0046018e:
        cmp eax,8
    L_00460191:
        jne short L_00460199
    L_00460193:
        mov eax,dword ptr [ebp-30h]
    L_00460196:
        mov dword ptr [ebx+5Ch],eax
    L_00460199:
        xor eax,eax
    L_0046019b:
        call asm_SEH_epilog_00454bf7
    L_004601a0:
        ret
    }
}
