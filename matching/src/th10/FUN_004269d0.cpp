// 004269D0: FUN_004269d0
// Original size: 800 bytes, actual code: 211 instructions
extern "C" void FUN_00413790(void);
extern "C" void FUN_00424650(void);
extern "C" void FUN_0043e710(void);

extern "C" __declspec(naked) void FUN_004269d0(void) {
    __asm {
        push  ecx
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR ds:0x474c4c
        push  edi
        lea  edi,[esi-0x1388]
        mov  eax,0x55555555
        imul  edi
        sub  edx,edi
        sar  edx,1
        mov  ecx,DWORD PTR ds:0x474c70
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  ebp,DWORD PTR [esp+0x18]
        lea  edx,[eax+eax*4]
        shl  edx,1
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        add  esi,eax
        dec  ecx
        cmp  esi,0x1388
        mov  DWORD PTR ds:0x474c70,ecx
        mov  DWORD PTR ds:0x474c4c,esi
        jge loc_00426A34
        mov  DWORD PTR ds:0x474c4c,0x1388
    loc_00426A34:
        xor  edi,edi
        cmp  ecx,edi
        jl loc_00426A44
        mov  eax,ds:0x47770c
        call FUN_00413790
    loc_00426A44:
        mov  DWORD PTR [ebp+0x458],0x2
        mov  eax,DWORD PTR [ebp+0x484]
        test  al,0x1
        mov  edx,0xfff0bdc1
        mov  ecx,0x476f78
        jne loc_00426A83
        or   eax,0x1
        mov  DWORD PTR [ebp+0x478],edi
        mov  DWORD PTR [ebp+0x474],edx
        mov  DWORD PTR [ebp+0x47c],edi
        mov  DWORD PTR [ebp+0x480],ecx
        mov  DWORD PTR [ebp+0x484],eax
    loc_00426A83:
        mov  DWORD PTR [ebp+0x478],edi
        mov  DWORD PTR [ebp+0x47c],edi
        mov  DWORD PTR [ebp+0x474],0xffffffff
        mov  eax,DWORD PTR [ebp+0x431c]
        test  al,0x1
        jne loc_00426AC4
        or   eax,0x1
        mov  DWORD PTR [ebp+0x4310],edi
        mov  DWORD PTR [ebp+0x430c],edx
        mov  DWORD PTR [ebp+0x4314],edi
        mov  DWORD PTR [ebp+0x4318],ecx
        mov  DWORD PTR [ebp+0x431c],eax
    loc_00426AC4:
        mov  DWORD PTR [ebp+0x4310],0xb4
        mov  DWORD PTR [ebp+0x4314],0x43340000
        mov  DWORD PTR [ebp+0x430c],0xb3
        mov  ecx,DWORD PTR [ebp+0x10]
        lea  eax,[ebp+0x14]
        xor  ebx,ebx
        call FUN_0043e710
        mov  esi,DWORD PTR ds:0x491c10
        lea  ebx,[ebp+0x3308]
        mov  DWORD PTR [esp+0x18],ebx
        mov  DWORD PTR [esp+0x10],0x4
    loc_00426B07:
        mov  ecx,DWORD PTR [ebx]
        cmp  ecx,edi
        mov  DWORD PTR [ebx-0x68],edi
        je loc_00426B44
        mov  eax,DWORD PTR [esi+0x72dad4]
        cmp  eax,edi
        je loc_00426B2D
        lea  ebx,[ebx+0x0]
    loc_00426B20:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00426B86
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00426B20
    loc_00426B2D:
        mov  eax,DWORD PTR [esi+0x72dadc]
        cmp  eax,edi
        je loc_00426B44
    loc_00426B37:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00426B86
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00426B37
    loc_00426B44:
        mov  edx,0x1
    loc_00426B49:
        mov  ecx,DWORD PTR [ebx+0x4]
        cmp  ecx,edi
        je loc_00426BE0
        mov  eax,DWORD PTR [esi+0x72dad4]
        cmp  eax,edi
        je loc_00426B6D
        mov  edi,edi
    loc_00426B60:
        mov  ebx,DWORD PTR [eax]
        cmp  DWORD PTR [ebx],ecx
        je loc_00426BB6
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00426B60
    loc_00426B6D:
        mov  eax,DWORD PTR [esi+0x72dadc]
        cmp  eax,edi
        je loc_00426BE0
    loc_00426B77:
        mov  ebx,DWORD PTR [eax]
        cmp  DWORD PTR [ebx],ecx
        je loc_00426BB6
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00426B77
        jmp loc_00426BE0
    loc_00426B86:
        mov  eax,DWORD PTR [eax]
        cmp  eax,edi
        je loc_00426B44
        cmp  DWORD PTR [eax+0x18],edi
        mov  edx,0x1
        mov  WORD PTR [eax+0x304],dx
        jne loc_00426B49
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,edi
        je loc_00426B49
    loc_00426BA4:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],dx
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00426BA4
        jmp loc_00426B49
    loc_00426BB6:
        mov  eax,DWORD PTR [eax]
        cmp  eax,edi
        je loc_00426BE0
        cmp  DWORD PTR [eax+0x18],edi
        mov  WORD PTR [eax+0x304],dx
        jne loc_00426BE0
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,edi
        je loc_00426BE0
        nop
    loc_00426BD0:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],dx
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00426BD0
    loc_00426BE0:
        mov  ebx,DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x10]
        add  ebx,0x98
        dec  eax
        mov  DWORD PTR [esp+0x18],ebx
        mov  DWORD PTR [esp+0x10],eax
        jne loc_00426B07
        mov  edx,DWORD PTR ds:0x477838
        mov  DWORD PTR [ebp+0x3500],edi
        cmp  DWORD PTR [edx+0x10],0x1
        je loc_00426C26
        mov  esi,DWORD PTR ds:0x477814
        add  ebp,0x3c0
        push  ebp
        push  0x46e360
        call FUN_00424650
    loc_00426C26:
        mov  eax,ds:0x4776f4
        cmp  DWORD PTR [eax+0x3738],0x3c
        jl loc_00426CAF
        mov  DWORD PTR [eax+0x3790],edi
        mov  edi,DWORD PTR [eax+0x378c]
        mov  ecx,0xfffffffd
        and  edi,ecx
        mov  DWORD PTR [eax+0x378c],edi
        mov  esi,DWORD PTR [eax+0xad4]
        mov  edx,DWORD PTR [eax+0xe80]
        mov  ebp,DWORD PTR [eax+0x15d8]
        mov  ebx,DWORD PTR [eax+0x1984]
        mov  edi,DWORD PTR [eax+0x1d30]
        and  esi,ecx
        and  edx,ecx
        mov  DWORD PTR [eax+0xad4],esi
        mov  esi,DWORD PTR [eax+0x20dc]
        mov  DWORD PTR [eax+0xe80],edx
        mov  edx,DWORD PTR [eax+0x2488]
        and  ebp,ecx
        and  ebx,ecx
        and  edi,ecx
        and  esi,ecx
        and  edx,ecx
        mov  DWORD PTR [eax+0x15d8],ebp
        mov  DWORD PTR [eax+0x1984],ebx
        mov  DWORD PTR [eax+0x1d30],edi
        mov  DWORD PTR [eax+0x20dc],esi
        mov  DWORD PTR [eax+0x2488],edx
    loc_00426CAF:
        mov  eax,ds:0x474c98
        pop  edi
        pop  esi
        sub  eax,0x400
        cmp  eax,0x400
        pop  ebp
        mov  ds:0x474c98,eax
        pop  ebx
        jle loc_00426CD7
        mov  DWORD PTR ds:0x474c98,0x400
        pop  ecx
        ret  0x4
    loc_00426CD7:
        cmp  eax,0xfffffc00
        jge loc_00426CE8
        mov  DWORD PTR ds:0x474c98,0xfffffc00
    loc_00426CE8:
        pop  ecx
        ret  0x4
    }
}
