// 004198C0: FUN_004198c0
// Original size: 160 bytes, actual code: 47 instructions

extern "C" __declspec(naked) void FUN_004198c0(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x8]
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        push  esi
        push  edi
        xor  edi,edi
        test  eax,eax
        jle loc_0041990E
    loc_004198D2:
        mov  esi,DWORD PTR [ebp+edi*8+0x0]
        mov  eax,edx
    loc_004198D8:
        mov  bl,BYTE PTR [eax]
        mov  cl,bl
        cmp  bl,BYTE PTR [esi]
        jne loc_004198FC
        test  cl,cl
        je loc_004198F8
        mov  bl,BYTE PTR [eax+0x1]
        mov  cl,bl
        cmp  bl,BYTE PTR [esi+0x1]
        jne loc_004198FC
        add  eax,0x2
        add  esi,0x2
        test  cl,cl
        jne loc_004198D8
    loc_004198F8:
        xor  eax,eax
        jmp loc_00419901
    loc_004198FC:
        sbb  eax,eax
        sbb  eax,0xffffffff
    loc_00419901:
        test  eax,eax
        je loc_00419917
        mov  eax,DWORD PTR [esp+0x18]
        inc  edi
        cmp  edi,eax
        jl loc_004198D2
    loc_0041990E:
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        ret  0x8
    loc_00419917:
        mov  eax,DWORD PTR [ebp+edi*8+0x4]
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x8
    }
}
