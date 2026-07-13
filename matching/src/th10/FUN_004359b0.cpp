// 004359B0: FUN_004359b0
// Original size: 1040 bytes, actual code: 313 instructions
extern "C" void FUN_00436000(void);
extern "C" void FUN_00436210(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_004359b0(void) {
    __asm {
        sub  esp,0x2c
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x3c]
        lea  eax,[ebp+ebp*1+0x0]
        push  eax
        mov  bl,0x80
        mov  DWORD PTR [esp+0x10],0x0
        call _malloc
        add  esp,0x4
        test  eax,eax
        mov  DWORD PTR [esp+0x30],eax
        jne loc_004359E0
        pop  ebp
        pop  ebx
        add  esp,0x2c
        ret  0xc
    loc_004359E0:
        mov  ecx,DWORD PTR [esp+0x38]
        mov  edx,DWORD PTR [esp+0x40]
        push  esi
        mov  esi,eax
        push  edi
        mov  DWORD PTR [esp+0x1c],ecx
        xor  eax,eax
        mov  ecx,0x800
        mov  edi,0x48f868
        mov  DWORD PTR [edx],0x0
        rep stosd
        mov  DWORD PTR [esp+0x18],esi
        mov  eax,0x47785c
        nop
    loc_00435A10:
        xor  ecx,ecx
        mov  DWORD PTR [eax-0x4],ecx
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x4],ecx
        add  eax,0xc
        cmp  eax,0x48f868
        jl loc_00435A10
        xor  eax,eax
        mov  DWORD PTR [esp+0x24],0x1
        xor  edx,edx
        jmp loc_00435A34
    loc_00435A32:
        xor  ecx,ecx
    loc_00435A34:
        cmp  edx,ebp
        jge loc_00435A58
        mov  edi,DWORD PTR [esp+0x1c]
        movzx ecx,BYTE PTR [edi]
        inc  edi
        inc  edx
        cmp  ecx,0xffffffff
        mov  DWORD PTR [esp+0x1c],edi
        je loc_00435A56
        mov  BYTE PTR [eax+0x48f869],cl
        inc  eax
        cmp  eax,0x12
        jl loc_00435A32
    loc_00435A56:
        xor  ecx,ecx
    loc_00435A58:
        xor  ebp,ebp
        cmp  eax,ecx
        mov  edx,eax
        mov  DWORD PTR [esp+0x28],edx
        mov  DWORD PTR ds:0x48f860,0x1
        mov  DWORD PTR ds:0x477864,0x2000
        mov  DWORD PTR ds:0x47786c,ecx
        mov  DWORD PTR ds:0x477868,ecx
        mov  DWORD PTR [esp+0x20],ebp
        mov  DWORD PTR [esp+0x30],ecx
        jle loc_00435D6E
    loc_00435A90:
        cmp  ebp,edx
        jle loc_00435A9A
        mov  DWORD PTR [esp+0x20],edx
        mov  ebp,edx
    loc_00435A9A:
        cmp  ebp,0x2
        jg loc_00435B0F
        mov  ebp,DWORD PTR [esp+0x14]
        movzx eax,bl
        or   ebp,eax
        shr  bl,1
        test  bl,bl
        mov  edi,0x1
        mov  DWORD PTR [esp+0x14],ebp
        jne loc_00435AC8
        mov  dl,BYTE PTR [esp+0x14]
        mov  BYTE PTR [esi],dl
        inc  esi
        mov  DWORD PTR [esp+0x18],esi
        mov  DWORD PTR [esp+0x14],ecx
        mov  bl,0x80
    loc_00435AC8:
        mov  eax,0x80
        nop
    loc_00435AD0:
        mov  edx,DWORD PTR [esp+0x24]
        test  BYTE PTR [edx+0x48f868],al
        je loc_00435AE9
        mov  ebp,DWORD PTR [esp+0x14]
        movzx edx,bl
        or   ebp,edx
        mov  DWORD PTR [esp+0x14],ebp
    loc_00435AE9:
        shr  bl,1
        test  bl,bl
        jne loc_00435AFC
        mov  dl,BYTE PTR [esp+0x14]
        mov  BYTE PTR [esi],dl
        inc  esi
        mov  DWORD PTR [esp+0x14],ecx
        mov  bl,0x80
    loc_00435AFC:
        shr  eax,1
        cmp  eax,ecx
        jne loc_00435AD0
        mov  DWORD PTR [esp+0x18],esi
        mov  BYTE PTR [esp+0x13],bl
        jmp loc_00435BB0
    loc_00435B0F:
        shr  bl,1
        test  bl,bl
        jne loc_00435B26
        mov  al,BYTE PTR [esp+0x14]
        mov  BYTE PTR [esi],al
        inc  esi
        mov  DWORD PTR [esp+0x18],esi
        mov  DWORD PTR [esp+0x14],ecx
        mov  bl,0x80
    loc_00435B26:
        mov  eax,0x1000
        jmp loc_00435B30
        nop
    loc_00435B30:
        mov  edx,DWORD PTR [esp+0x30]
        test  edx,eax
        je loc_00435B45
        mov  edi,DWORD PTR [esp+0x14]
        movzx edx,bl
        or   edi,edx
        mov  DWORD PTR [esp+0x14],edi
    loc_00435B45:
        shr  bl,1
        test  bl,bl
        jne loc_00435B58
        mov  dl,BYTE PTR [esp+0x14]
        mov  BYTE PTR [esi],dl
        inc  esi
        mov  DWORD PTR [esp+0x14],ecx
        mov  bl,0x80
    loc_00435B58:
        shr  eax,1
        cmp  eax,ecx
        jne loc_00435B30
        mov  DWORD PTR [esp+0x18],esi
        mov  eax,0x8
        lea  edi,[ebp-0x3]
        lea  ebx,[ebx+0x0]
    loc_00435B70:
        test  eax,edi
        je loc_00435B85
        mov  ebp,DWORD PTR [esp+0x14]
        movzx edx,bl
        or   ebp,edx
        mov  DWORD PTR [esp+0x14],ebp
        mov  ebp,DWORD PTR [esp+0x20]
    loc_00435B85:
        shr  bl,1
        test  bl,bl
        jne loc_00435B98
        mov  dl,BYTE PTR [esp+0x14]
        mov  BYTE PTR [esi],dl
        inc  esi
        mov  DWORD PTR [esp+0x14],ecx
        mov  bl,0x80
    loc_00435B98:
        shr  eax,1
        cmp  eax,ecx
        jne loc_00435B70
        cmp  ebp,ecx
        mov  DWORD PTR [esp+0x18],esi
        mov  BYTE PTR [esp+0x13],bl
        mov  edi,ebp
        jle loc_00435D62
    loc_00435BB0:
        mov  eax,DWORD PTR [esp+0x1c]
        sub  eax,DWORD PTR [esp+0x40]
        mov  DWORD PTR [esp+0x2c],eax
        mov  DWORD PTR [esp+0x34],edi
    loc_00435BC0:
        mov  ebp,DWORD PTR [esp+0x24]
        add  ebp,0x12
        and  ebp,0x1fff
        lea  eax,[ebp+ebp*2+0x0]
        shl  eax,0x2
        mov  ecx,DWORD PTR [eax+0x477858]
        test  ecx,ecx
        lea  edi,[eax+0x477858]
        je loc_00435CFB
        mov  edx,DWORD PTR [eax+0x477860]
        test  edx,edx
        mov  eax,DWORD PTR [eax+0x47785c]
        jne loc_00435C28
        lea  edx,[eax+eax*2]
        mov  DWORD PTR [edx*4+0x477858],ecx
        mov  ecx,DWORD PTR [edi]
        lea  ecx,[ecx+ecx*2]
        shl  ecx,0x2
        cmp  DWORD PTR [ecx+0x477860],ebp
        jne loc_00435C1D
        mov  DWORD PTR [ecx+0x477860],eax
        jmp loc_00435CF5
    loc_00435C1D:
        mov  DWORD PTR [ecx+0x47785c],eax
        jmp loc_00435CF5
    loc_00435C28:
        test  eax,eax
        jne loc_00435C5C
        lea  eax,[edx+edx*2]
        mov  DWORD PTR [eax*4+0x477858],ecx
        mov  eax,DWORD PTR [edi]
        lea  eax,[eax+eax*2]
        shl  eax,0x2
        cmp  DWORD PTR [eax+0x477860],ebp
        jne loc_00435C51
        mov  DWORD PTR [eax+0x477860],edx
        jmp loc_00435CF5
    loc_00435C51:
        mov  DWORD PTR [eax+0x47785c],edx
        jmp loc_00435CF5
    loc_00435C5C:
        mov  esi,eax
        lea  eax,[esi+esi*2]
        mov  ecx,DWORD PTR [eax*4+0x477860]
        test  ecx,ecx
        lea  eax,[eax*4+0x477860]
        je loc_00435C8A
    loc_00435C73:
        mov  esi,DWORD PTR [eax]
        lea  eax,[esi+esi*2]
        mov  ecx,DWORD PTR [eax*4+0x477860]
        test  ecx,ecx
        lea  eax,[eax*4+0x477860]
        jne loc_00435C73
    loc_00435C8A:
        mov  ecx,esi
        call FUN_00436210
        mov  eax,DWORD PTR [edi]
        lea  eax,[eax+eax*2]
        shl  eax,0x2
        cmp  DWORD PTR [eax+0x47785c],ebp
        jne loc_00435CA9
        mov  DWORD PTR [eax+0x47785c],esi
        jmp loc_00435CAF
    loc_00435CA9:
        mov  DWORD PTR [eax+0x477860],esi
    loc_00435CAF:
        lea  eax,[esi+esi*2]
        shl  eax,0x2
        lea  ecx,[eax+0x477858]
        mov  edx,edi
        mov  ebx,DWORD PTR [edx]
        mov  DWORD PTR [ecx],ebx
        mov  ebx,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ecx+0x4],ebx
        mov  edx,DWORD PTR [edx+0x8]
        mov  bl,BYTE PTR [esp+0x13]
        mov  DWORD PTR [ecx+0x8],edx
        mov  ecx,DWORD PTR [eax+0x47785c]
        lea  ecx,[ecx+ecx*2]
        mov  DWORD PTR [ecx*4+0x477858],esi
        mov  eax,DWORD PTR [eax+0x477860]
        lea  edx,[eax+eax*2]
        mov  DWORD PTR [edx*4+0x477858],esi
        mov  esi,DWORD PTR [esp+0x18]
    loc_00435CF5:
        mov  DWORD PTR [edi],0x0
    loc_00435CFB:
        mov  eax,DWORD PTR [esp+0x2c]
        cmp  eax,DWORD PTR [esp+0x44]
        jge loc_00435D1F
        mov  ecx,DWORD PTR [esp+0x1c]
        movzx eax,BYTE PTR [ecx]
        mov  edx,DWORD PTR [esp+0x2c]
        inc  ecx
        inc  edx
        cmp  eax,0xffffffff
        mov  DWORD PTR [esp+0x1c],ecx
        mov  DWORD PTR [esp+0x2c],edx
        jne loc_00435D25
    loc_00435D1F:
        dec  DWORD PTR [esp+0x28]
        jmp loc_00435D2B
    loc_00435D25:
        mov  BYTE PTR [ebp+0x48f868],al
    loc_00435D2B:
        mov  ecx,DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [esp+0x28]
        lea  edx,[ecx+0x1]
        and  edx,0x1fff
        test  eax,eax
        mov  DWORD PTR [esp+0x24],edx
        je loc_00435D52
        lea  eax,[esp+0x30]
        push  eax
        call FUN_00436000
        mov  DWORD PTR [esp+0x20],eax
    loc_00435D52:
        dec  DWORD PTR [esp+0x34]
        jne loc_00435BC0
        mov  ebp,DWORD PTR [esp+0x20]
        xor  ecx,ecx
    loc_00435D62:
        mov  edx,DWORD PTR [esp+0x28]
        cmp  edx,ecx
        jg loc_00435A90
    loc_00435D6E:
        shr  bl,1
        test  bl,bl
        jne loc_00435D81
        mov  dl,BYTE PTR [esp+0x14]
        mov  BYTE PTR [esi],dl
        inc  esi
        mov  DWORD PTR [esp+0x14],ecx
        mov  bl,0x80
    loc_00435D81:
        mov  eax,0x1000
    loc_00435D86:
        shr  bl,1
        test  bl,bl
        jne loc_00435D99
        mov  dl,BYTE PTR [esp+0x14]
        mov  BYTE PTR [esi],dl
        inc  esi
        mov  DWORD PTR [esp+0x14],ecx
        mov  bl,0x80
    loc_00435D99:
        shr  eax,1
        cmp  eax,ecx
        jne loc_00435D86
        mov  eax,DWORD PTR [esp+0x38]
        mov  ecx,DWORD PTR [esp+0x48]
        sub  esi,eax
        pop  edi
        mov  DWORD PTR [ecx],esi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0x2c
        ret  0xc
    }
}
