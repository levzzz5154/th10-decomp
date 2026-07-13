// 00421E00: FUN_00421e00
// Original size: 256 bytes, actual code: 83 instructions
extern "C" void FUN_0044d4e0(void);

extern "C" __declspec(naked) void FUN_00421e00(void) {
    __asm {
        push  esi
        push  edi
        mov  edi,eax
        mov  ecx,DWORD PTR [edi+0x5208]
        xor  esi,esi
        cmp  ecx,esi
        je loc_00421EDE
        cmp  DWORD PTR [ecx+0x1c],0x1
        jne loc_00421E4C
        mov  eax,DWORD PTR [ecx+0x14]
        dec  eax
        cmp  eax,esi
        mov  DWORD PTR [ecx+0x14],eax
        jg loc_00421E35
        mov  eax,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [ecx+0x1c],esi
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        jmp loc_00421E4C
    loc_00421E35:
        imul  eax,eax,0x1388
        cdq
        idiv  DWORD PTR [ecx+0x18]
        sub  eax,0x1388
        push  eax
        mov  eax,ecx
        call FUN_0044d4e0
    loc_00421E4C:
        mov  ecx,DWORD PTR [edi+0x5208]
        cmp  DWORD PTR [ecx+0x1c],0x2
        jne loc_00421E7A
        mov  eax,DWORD PTR [ecx+0x14]
        dec  eax
        cmp  eax,esi
        mov  DWORD PTR [ecx+0x14],eax
        jg loc_00421E68
        mov  DWORD PTR [ecx+0x1c],esi
        jmp loc_00421E7A
    loc_00421E68:
        imul  eax,eax,0xffffec78
        cdq
        idiv  DWORD PTR [ecx+0x18]
        push  eax
        mov  eax,ecx
        call FUN_0044d4e0
    loc_00421E7A:
        mov  ecx,DWORD PTR [edi+0x5208]
        cmp  DWORD PTR [ecx+0x1c],0x4
        jne loc_00421EAD
        mov  eax,DWORD PTR [ecx+0x14]
        dec  eax
        cmp  eax,esi
        mov  DWORD PTR [ecx+0x14],eax
        jg loc_00421E96
        mov  DWORD PTR [ecx+0x1c],esi
        jmp loc_00421EAD
    loc_00421E96:
        imul  eax,eax,0x3e8
        cdq
        idiv  DWORD PTR [ecx+0x18]
        sub  eax,0x3e8
        push  eax
        mov  eax,ecx
        call FUN_0044d4e0
    loc_00421EAD:
        mov  ecx,DWORD PTR [edi+0x5208]
        cmp  DWORD PTR [ecx+0x1c],0x3
        jne loc_00421EDE
        mov  edi,DWORD PTR [ecx+0x14]
        dec  edi
        mov  eax,edi
        cmp  eax,esi
        mov  DWORD PTR [ecx+0x14],edi
        jg loc_00421ECC
        pop  edi
        mov  DWORD PTR [ecx+0x1c],esi
        pop  esi
        ret
    loc_00421ECC:
        imul  eax,eax,0xfffffc18
        cdq
        idiv  DWORD PTR [ecx+0x18]
        push  eax
        mov  eax,ecx
        call FUN_0044d4e0
    loc_00421EDE:
        pop  edi
        pop  esi
        ret
    }
}
