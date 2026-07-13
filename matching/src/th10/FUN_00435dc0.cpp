// 00435DC0: FUN_00435dc0
// Original size: 576 bytes, actual code: 175 instructions
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_00435dc0(void) {
    __asm {
        sub  esp,0xc
        mov  eax,DWORD PTR [esp+0x18]
        push  ebx
        push  ebp
        xor  ebp,ebp
        cmp  eax,ebp
        mov  bl,0x80
        mov  DWORD PTR [esp+0x8],ebp
        jne loc_00435DF4
        mov  eax,DWORD PTR [esp+0x24]
        push  eax
        call _malloc
        add  esp,0x4
        cmp  eax,ebp
        mov  DWORD PTR [esp+0x20],eax
        jne loc_00435DF4
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0xc
        ret  0x10
    loc_00435DF4:
        mov  edx,DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x20]
        push  esi
        push  edi
        mov  edi,edx
        mov  DWORD PTR [esp+0x2c],ecx
        mov  DWORD PTR [esp+0x14],0x1
        jmp loc_00435E14
    loc_00435E0E:
        xor  ebp,ebp
    loc_00435E10:
        mov  edx,DWORD PTR [esp+0x20]
    loc_00435E14:
        cmp  bl,0x80
        jne loc_00435E33
        movzx eax,BYTE PTR [edi]
        mov  ecx,edi
        mov  DWORD PTR [esp+0x10],eax
        mov  eax,DWORD PTR [esp+0x24]
        sub  ecx,edx
        cmp  ecx,eax
        jl loc_00435E32
        mov  DWORD PTR [esp+0x10],ebp
        jmp loc_00435E33
    loc_00435E32:
        inc  edi
    loc_00435E33:
        mov  eax,DWORD PTR [esp+0x10]
        movzx ecx,bl
        shr  bl,1
        and  ecx,eax
        test  bl,bl
        jne loc_00435E44
        mov  bl,0x80
    loc_00435E44:
        cmp  ecx,ebp
        mov  ecx,edi
        je loc_00435EAA
        xor  eax,eax
        mov  esi,0x80
        sub  ecx,edx
    loc_00435E53:
        cmp  bl,0x80
        jne loc_00435E6D
        movzx edx,BYTE PTR [edi]
        mov  DWORD PTR [esp+0x10],edx
        cmp  ecx,DWORD PTR [esp+0x24]
        jl loc_00435E6B
        mov  DWORD PTR [esp+0x10],ebp
        jmp loc_00435E6D
    loc_00435E6B:
        inc  edi
        inc  ecx
    loc_00435E6D:
        mov  dl,BYTE PTR [esp+0x10]
        test  dl,bl
        je loc_00435E77
        or   eax,esi
    loc_00435E77:
        shr  bl,1
        shr  esi,1
        test  bl,bl
        jne loc_00435E81
        mov  bl,0x80
    loc_00435E81:
        cmp  esi,ebp
        jne loc_00435E53
        mov  ecx,DWORD PTR [esp+0x2c]
        mov  BYTE PTR [ecx],al
        inc  ecx
        mov  DWORD PTR [esp+0x2c],ecx
        mov  ecx,DWORD PTR [esp+0x14]
        mov  BYTE PTR [ecx+0x48f868],al
        inc  ecx
        and  ecx,0x1fff
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_00435E10
    loc_00435EAA:
        mov  esi,0x1000
        sub  ecx,edx
    loc_00435EB1:
        cmp  bl,0x80
        jne loc_00435ECF
        movzx eax,BYTE PTR [edi]
        mov  DWORD PTR [esp+0x10],eax
        cmp  ecx,DWORD PTR [esp+0x24]
        jl loc_00435ECD
        mov  DWORD PTR [esp+0x10],0x0
        jmp loc_00435ECF
    loc_00435ECD:
        inc  edi
        inc  ecx
    loc_00435ECF:
        mov  al,BYTE PTR [esp+0x10]
        test  al,bl
        je loc_00435ED9
        or   ebp,esi
    loc_00435ED9:
        shr  bl,1
        shr  esi,1
        test  bl,bl
        jne loc_00435EE3
        mov  bl,0x80
    loc_00435EE3:
        test  esi,esi
        jne loc_00435EB1
        xor  eax,eax
        cmp  ebp,eax
        mov  DWORD PTR [esp+0x18],ebp
        je loc_00435F7D
        mov  ecx,edi
        xor  ebp,ebp
        mov  esi,0x8
        sub  ecx,edx
    loc_00435F00:
        cmp  bl,0x80
        jne loc_00435F1A
        movzx edx,BYTE PTR [edi]
        mov  DWORD PTR [esp+0x10],edx
        cmp  ecx,DWORD PTR [esp+0x24]
        jl loc_00435F18
        mov  DWORD PTR [esp+0x10],eax
        jmp loc_00435F1A
    loc_00435F18:
        inc  edi
        inc  ecx
    loc_00435F1A:
        mov  dl,BYTE PTR [esp+0x10]
        test  dl,bl
        je loc_00435F24
        or   ebp,esi
    loc_00435F24:
        shr  bl,1
        shr  esi,1
        test  bl,bl
        jne loc_00435F2E
        mov  bl,0x80
    loc_00435F2E:
        cmp  esi,eax
        jne loc_00435F00
        lea  esi,[ebp+0x2]
        xor  ecx,ecx
        cmp  esi,eax
        jl loc_00435E0E
        nop
    loc_00435F40:
        mov  eax,DWORD PTR [esp+0x18]
        lea  edx,[ecx+eax*1]
        mov  eax,DWORD PTR [esp+0x2c]
        and  edx,0x1fff
        movzx edx,BYTE PTR [edx+0x48f868]
        mov  BYTE PTR [eax],dl
        inc  eax
        mov  DWORD PTR [esp+0x2c],eax
        mov  eax,DWORD PTR [esp+0x14]
        mov  BYTE PTR [eax+0x48f868],dl
        inc  eax
        and  eax,0x1fff
        inc  ecx
        cmp  ecx,esi
        mov  DWORD PTR [esp+0x14],eax
        jle loc_00435F40
        jmp loc_00435E0E
    loc_00435F7D:
        cmp  bl,0x80
        pop  edi
        pop  esi
        je loc_00435F8F
    loc_00435F84:
        shr  bl,1
        test  bl,bl
        je loc_00435F8F
        cmp  bl,0x80
        jne loc_00435F84
    loc_00435F8F:
        mov  eax,DWORD PTR [esp+0x20]
        pop  ebp
        pop  ebx
        add  esp,0xc
        ret  0x10
    }
}
