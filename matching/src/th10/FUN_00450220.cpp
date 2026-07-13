// 00450220: FUN_00450220
// Original size: 592 bytes, actual code: 198 instructions
extern "C" void _free(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_00450220(void) {
    __asm {
        sub  esp,0x10
        push  ebx
        mov  ebx,ecx
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [ebx+eax*4+0xc],ecx
        mov  edx,DWORD PTR [ebx+0x4]
        mov  ecx,DWORD PTR [ebx+edx*4+0xc]
        lea  eax,[ebx+edx*4+0xc]
        cmp  DWORD PTR [ecx],0x54504353
        jne loc_0045024B
        cmp  WORD PTR [ecx+0x4],0x1
        je loc_0045025B
    loc_0045024B:
        mov  DWORD PTR [eax],0x0
        or   eax,0xffffffff
        pop  ebx
        add  esp,0x10
        ret  0x4
    loc_0045025B:
        mov  eax,DWORD PTR [eax]
        movzx ecx,WORD PTR [eax+0x6]
        mov  edx,DWORD PTR [ebx+0x8]
        push  ebp
        mov  ebp,DWORD PTR [ebx+0x8c]
        push  esi
        push  edi
        lea  edi,[ecx+eax*1+0x24]
        movzx eax,WORD PTR [eax+0x10]
        add  edx,eax
        mov  DWORD PTR [esp+0x24],edi
        lea  edi,[edi+eax*4]
        mov  eax,edx
        shl  eax,0x3
        push  eax
        mov  DWORD PTR [esp+0x14],edi
        mov  DWORD PTR [ebx+0x8],edx
        call _malloc
        add  esp,0x4
        test  ebp,ebp
        mov  DWORD PTR [ebx+0x8c],eax
        jne loc_004502FE
        mov  eax,DWORD PTR [ebx+0x8]
        xor  esi,esi
        test  eax,eax
        jle loc_00450442
        jmp loc_004502B0
    loc_004502AC:
        mov  edi,DWORD PTR [esp+0x10]
    loc_004502B0:
        mov  edx,DWORD PTR [ebx+0x4]
        mov  eax,DWORD PTR [ebx+edx*4+0xc]
        mov  ecx,DWORD PTR [esp+0x24]
        add  eax,DWORD PTR [ecx]
        mov  edx,DWORD PTR [ebx+0x8c]
        mov  DWORD PTR [edx+esi*8+0x4],eax
        mov  eax,DWORD PTR [ebx+0x8c]
        mov  DWORD PTR [eax+esi*8],edi
        mov  eax,edi
        lea  edx,[eax+0x1]
    loc_004502D5:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_004502D5
        sub  eax,edx
        lea  ecx,[edi+eax*1+0x1]
        mov  eax,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [esp+0x10],ecx
        mov  ecx,DWORD PTR [esp+0x24]
        inc  esi
        add  ecx,0x4
        cmp  esi,eax
        mov  DWORD PTR [esp+0x24],ecx
        jl loc_004502AC
        jmp loc_00450442
    loc_004502FE:
        mov  edx,DWORD PTR [ebx+0x4]
        mov  ecx,DWORD PTR [ebx+edx*4+0xc]
        movzx ecx,WORD PTR [ecx+0x10]
        mov  edx,DWORD PTR [ebx+0x8]
        sub  edx,ecx
        test  ebp,ebp
        lea  ecx,[edx+edx*1]
        mov  esi,ebp
        mov  edi,eax
        mov  DWORD PTR [esp+0x14],edx
        rep movsd
        je loc_0045032C
        push  ebp
        call _free
        mov  edx,DWORD PTR [esp+0x18]
        add  esp,0x4
    loc_0045032C:
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,DWORD PTR [ebx+eax*4+0xc]
        cmp  WORD PTR [ecx+0x10],0x0
        mov  DWORD PTR [esp+0x1c],0x0
        jbe loc_00450442
        jmp loc_00450350
    loc_00450348:
        mov  edx,DWORD PTR [esp+0x14]
        nop
    loc_00450350:
        xor  ebp,ebp
        test  edx,edx
        jle loc_004503B3
        mov  edx,DWORD PTR [ebx+0x8c]
        mov  DWORD PTR [esp+0x18],edx
    loc_00450360:
        mov  eax,DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [esp+0x10]
        mov  edi,DWORD PTR [eax]
        mov  esi,edx
        nop
    loc_00450370:
        mov  cl,BYTE PTR [esi]
        mov  al,cl
        cmp  cl,BYTE PTR [edi]
        jne loc_00450394
        test  al,al
        je loc_00450390
        mov  cl,BYTE PTR [esi+0x1]
        mov  al,cl
        cmp  cl,BYTE PTR [edi+0x1]
        jne loc_00450394
        add  esi,0x2
        add  edi,0x2
        test  al,al
        jne loc_00450370
    loc_00450390:
        xor  eax,eax
        jmp loc_00450399
    loc_00450394:
        sbb  eax,eax
        sbb  eax,0xffffffff
    loc_00450399:
        test  eax,eax
        jle loc_004503B7
        mov  ecx,DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x14]
        inc  ebp
        add  ecx,0x8
        cmp  ebp,eax
        mov  DWORD PTR [esp+0x18],ecx
        jl loc_00450360
        jmp loc_004503B7
    loc_004503B3:
        mov  edx,DWORD PTR [esp+0x10]
    loc_004503B7:
        mov  ecx,DWORD PTR [ebx+0x8]
        dec  ecx
        cmp  ecx,ebp
        jle loc_004503DA
        nop
    loc_004503C0:
        mov  eax,DWORD PTR [ebx+0x8c]
        mov  esi,DWORD PTR [eax+ecx*8-0x8]
        lea  eax,[eax+ecx*8]
        mov  DWORD PTR [eax],esi
        mov  esi,DWORD PTR [eax-0x4]
        dec  ecx
        cmp  ecx,ebp
        mov  DWORD PTR [eax+0x4],esi
        jg loc_004503C0
    loc_004503DA:
        mov  ecx,DWORD PTR [ebx+0x4]
        mov  eax,DWORD PTR [ebx+ecx*4+0xc]
        mov  ecx,DWORD PTR [esp+0x24]
        mov  esi,DWORD PTR [ecx]
        mov  ecx,DWORD PTR [ebx+0x8c]
        add  eax,esi
        mov  DWORD PTR [ecx+ebp*8+0x4],eax
        mov  eax,DWORD PTR [ebx+0x8c]
        mov  DWORD PTR [eax+ebp*8],edx
        mov  eax,edx
        lea  esi,[eax+0x1]
    loc_00450401:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00450401
        mov  edi,DWORD PTR [esp+0x14]
        sub  eax,esi
        lea  ecx,[edx+eax*1+0x1]
        mov  edx,DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [esp+0x1c]
        add  edx,0x4
        mov  DWORD PTR [esp+0x24],edx
        mov  edx,DWORD PTR [ebx+0x4]
        mov  DWORD PTR [esp+0x10],ecx
        mov  ecx,DWORD PTR [ebx+edx*4+0xc]
        movzx edx,WORD PTR [ecx+0x10]
        inc  edi
        inc  eax
        cmp  eax,edx
        mov  DWORD PTR [esp+0x14],edi
        mov  DWORD PTR [esp+0x1c],eax
        jl loc_00450348
    loc_00450442:
        mov  esi,DWORD PTR [ebx+0x4]
        lea  eax,[esi+0x1]
        mov  DWORD PTR [ebx+0x4],eax
        mov  eax,DWORD PTR [ebx+esi*4+0xc]
        cmp  WORD PTR [eax+0x6],0x0
        je loc_00450461
        mov  edx,DWORD PTR [ebx]
        add  eax,0x24
        push  eax
        mov  ecx,ebx
        call  DWORD PTR [edx+0x4]
    loc_00450461:
        pop  edi
        mov  eax,esi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0x10
        ret  0x4
    }
}
