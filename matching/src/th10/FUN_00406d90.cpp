// 00406D90: FUN_00406d90
// Original size: 1616 bytes, actual code: 409 instructions
extern "C" void FUN_00404f30(void);
extern "C" void FUN_00405410(void);
extern "C" void FUN_004073e0(void);
extern "C" void FUN_00408030(void);
extern "C" void FUN_00408750(void);
extern "C" void FUN_00426660(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0043dd10(void);

extern "C" __declspec(naked) void FUN_00406d90(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        and  esp,0xfffffff8
        sub  esp,0x210
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  ebp,ecx
        cmp  DWORD PTR [ebp+0x45c],0x12
        jge loc_00407336
        nop
    loc_00406DB0:
        mov  edx,DWORD PTR [ebp+0x45c]
        lea  eax,[edx+edx*2]
        mov  ecx,DWORD PTR [ebp+eax*8+0x474]
        lea  esi,[ebp+eax*8+0x464]
        xor  edi,edi
        cmp  ecx,edi
        je loc_00407336
        cmp  DWORD PTR [esi+0x14],edi
        jne loc_00406DE2
        cmp  DWORD PTR [ebp+0x43c],edi
        jne loc_00407336
    loc_00406DE2:
        cmp  ecx,0x80000000
        jne loc_00406DF6
        inc  edx
        mov  DWORD PTR [ebp+0x45c],edx
        jmp loc_00407329
    loc_00406DF6:
        mov  eax,ecx
        cmp  eax,0x4000
        ja loc_004070B2
        je loc_00407089
        cmp  eax,0x100
        ja loc_0040703A
        je loc_00406F64
        dec  eax
        cmp  eax,0x7f
        ja loc_0040731C
        movzx edx,BYTE PTR [eax+0x407354]
        jmp  DWORD PTR [edx*4+0x407340]
        mov  ecx,DWORD PTR [ebp+0x43c]
        or   ecx,0x1
        push  edi
        lea  eax,[ebp+0x614]
        mov  DWORD PTR [ebp+0x43c],ecx
        call FUN_00405410
        mov  DWORD PTR [ebp+0x638],0x0
        jmp loc_0040731C
        or   DWORD PTR [ebp+0x43c],0x10
        mov  eax,DWORD PTR [esi]
        mov  DWORD PTR [ebp+0x65c],eax
        fld  DWORD PTR [esi+0x4]
        fcomp DWORD PTR ds:0x470b50
        fnstsw ax
        test  ah,0x41
        jp loc_00406E83
        fld  DWORD PTR [ebp+0x3e4]
        jmp loc_00406EA9
    loc_00406E83:
        fld  DWORD PTR [esi+0x4]
        fcomp DWORD PTR ds:0x470ccc
        fnstsw ax
        test  ah,0x1
        jne loc_00406EA6
        mov  ecx,DWORD PTR ds:0x477834
        lea  eax,[ebp+0x3b4]
        call FUN_00426660
        jmp loc_00406EA9
    loc_00406EA6:
        fld  DWORD PTR [esi+0x4]
    loc_00406EA9:
        push  edi
        fstp  DWORD PTR [ebp+0x660]
        lea  eax,[ebp+0x648]
        call FUN_00405410
        mov  ecx,DWORD PTR [esi+0x8]
        mov  edx,DWORD PTR [ebp+0x65c]
        mov  eax,DWORD PTR [ebp+0x660]
        push  edx
        mov  DWORD PTR [ebp+0x670],ecx
        push  eax
        lea  ecx,[ebp+0x664]
        call FUN_00408750
        mov  eax,DWORD PTR [ebp+0x45c]
        test  eax,eax
        je loc_0040731C
        mov  edi,DWORD PTR [ebp+0x458]
        test  edi,edi
        jl loc_0040731C
        push  0x0
        mov  ecx,0x492590
        call FUN_0043dc90
        jmp loc_0040731C
        or   DWORD PTR [ebp+0x43c],0x20
        mov  ecx,DWORD PTR [esi]
        mov  DWORD PTR [ebp+0x690],ecx
        mov  edx,DWORD PTR [esi+0x4]
        push  edi
        lea  eax,[ebp+0x67c]
        mov  DWORD PTR [ebp+0x694],edx
        call FUN_00405410
        mov  eax,DWORD PTR [esi+0x8]
        mov  DWORD PTR [ebp+0x6a4],eax
        mov  eax,DWORD PTR [ebp+0x45c]
        test  eax,eax
        je loc_0040731C
        mov  edi,DWORD PTR [ebp+0x458]
        test  edi,edi
        jl loc_0040731C
        push  0x0
        mov  ecx,0x492590
        call FUN_0043dc90
        jmp loc_0040731C
    loc_00406F64:
        mov  eax,DWORD PTR [ebp+0x43c]
        or   eax,ecx
        mov  DWORD PTR [ebp+0x43c],eax
        fld  DWORD PTR [esi]
        fcomp DWORD PTR ds:0x470b50
        fnstsw ax
        test  ah,0x41
        jp loc_00406F89
        fld  DWORD PTR [ebp+0x3e4]
        jmp loc_00406FAD
    loc_00406F89:
        fld  DWORD PTR [esi]
        fcomp DWORD PTR ds:0x470ccc
        fnstsw ax
        test  ah,0x1
        jne loc_00406FAB
        mov  ecx,DWORD PTR ds:0x477834
        lea  eax,[ebp+0x3b4]
        call FUN_00426660
        jmp loc_00406FAD
    loc_00406FAB:
        fld  DWORD PTR [esi]
    loc_00406FAD:
        fstp  DWORD PTR [ebp+0x6c8]
        fld  DWORD PTR [esi+0x4]
        fcomp DWORD PTR ds:0x470cc8
        fnstsw ax
        test  ah,0x41
        jne loc_00406FC8
        fld  DWORD PTR [esi+0x4]
        jmp loc_00406FCE
    loc_00406FC8:
        fld  DWORD PTR [ebp+0x3d8]
    loc_00406FCE:
        fstp  DWORD PTR [ebp+0x6c4]
        mov  eax,DWORD PTR [ebp+0x6c0]
        test  al,0x1
        jne loc_00407007
        or   eax,0x1
        mov  DWORD PTR [ebp+0x6b4],edi
        mov  DWORD PTR [ebp+0x6b0],0xfff0bdc1
        mov  DWORD PTR [ebp+0x6b8],edi
        mov  DWORD PTR [ebp+0x6bc],0x476f78
        mov  DWORD PTR [ebp+0x6c0],eax
    loc_00407007:
        mov  DWORD PTR [ebp+0x6b4],edi
        mov  DWORD PTR [ebp+0x6b8],edi
        mov  DWORD PTR [ebp+0x6b0],0xffffffff
        mov  ecx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [ebp+0x6d8],ecx
        mov  edx,DWORD PTR [esi+0xc]
        mov  DWORD PTR [ebp+0x6dc],edx
        mov  DWORD PTR [ebp+0x6e0],edi
        jmp loc_0040731C
    loc_0040703A:
        cmp  eax,0x1000
        ja loc_00407069
        je loc_0040705E
        cmp  eax,0x400
        je loc_004072FF
        cmp  eax,0x800
        je loc_004072FF
        jmp loc_0040731C
    loc_0040705E:
        mov  eax,DWORD PTR [esi+0x8]
        mov  DWORD PTR [ebp+0x4],eax
        jmp loc_0040731C
    loc_00407069:
        cmp  eax,0x2000
        jne loc_0040731C
        mov  ecx,DWORD PTR [esi+0x8]
        inc  edx
        mov  DWORD PTR [ebp+0x434],ecx
        mov  DWORD PTR [ebp+0x45c],edx
        jmp loc_00407329
    loc_00407089:
        mov  edx,DWORD PTR [esi+0x8]
        mov  eax,DWORD PTR [edx*4+0x474170]
        mov  edx,DWORD PTR [esi+0xc]
        mov  ecx,DWORD PTR ds:0x4776f0
        add  eax,edx
        mov  edx,DWORD PTR [ecx+0x3e0b50]
        lea  esi,[ebp+0x8]
        push  edx
        call FUN_00404f30
        jmp loc_0040731C
    loc_004070B2:
        cmp  eax,0x400000
        ja loc_0040724D
        je loc_00407163
        cmp  eax,0x20000
        ja loc_0040711D
        je loc_00407104
        cmp  eax,0x8000
        je loc_004070EA
        cmp  eax,0x10000
        jne loc_0040731C
        mov  esi,ebp
        call FUN_00408030
        jmp loc_0040731C
    loc_004070EA:
        or   DWORD PTR [ebp+0x43c],ecx
        mov  eax,DWORD PTR [esi+0x8]
        push  eax
        lea  eax,[ebp+0x718]
        call FUN_00405410
        jmp loc_0040731C
    loc_00407104:
        mov  ecx,DWORD PTR [ebp+0x3b4]
        mov  ebx,DWORD PTR [esi+0x8]
        push  ecx
        mov  esi,0x492590
        call FUN_0043dd10
        jmp loc_0040731C
    loc_0040711D:
        cmp  eax,0x100000
        je loc_00407149
        cmp  eax,0x200000
        jne loc_0040731C
        or   DWORD PTR [ebp+0x43c],ecx
        mov  edx,DWORD PTR [esi+0x8]
        push  edx
        lea  eax,[ebp+0x780]
        call FUN_00405410
        jmp loc_0040731C
    loc_00407149:
        or   DWORD PTR [ebp+0x43c],ecx
        mov  eax,DWORD PTR [esi+0x8]
        push  eax
        lea  eax,[ebp+0x74c]
        call FUN_00405410
        jmp loc_0040731C
    loc_00407163:
        xor  eax,eax
        mov  ecx,0x84
        lea  edi,[esp+0x10]
        rep stosd
        lea  ecx,[ebp+0x3b4]
        mov  eax,DWORD PTR [ecx]
        mov  DWORD PTR [esp+0x14],eax
        mov  eax,DWORD PTR [ecx+0x4]
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esp+0x18],eax
        mov  eax,DWORD PTR [esi+0x8]
        mov  DWORD PTR [esp+0x1c],ecx
        xor  ecx,ecx
        mov  ebx,eax
        mov  WORD PTR [esp+0x208],cx
        mov  WORD PTR [esp+0x10],cx
        movsx cx,BYTE PTR [esi+0x9]
        and  eax,0xff
        mov  DWORD PTR [esp+0x218],eax
        mov  ax,WORD PTR [esi+0xc]
        mov  WORD PTR [esp+0x12],cx
        mov  ecx,DWORD PTR [esi]
        mov  WORD PTR [esp+0x204],ax
        mov  eax,DWORD PTR [esi+0x4]
        add  esi,0x18
        mov  DWORD PTR [esp+0x28],ecx
        and  ebx,0x80000000
        inc  edx
        mov  DWORD PTR [ebp+0x45c],edx
        mov  cx,WORD PTR [esi+0x8]
        mov  edx,DWORD PTR [esi+0xc]
        mov  WORD PTR [esp+0x206],cx
        mov  ecx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [esp+0x2c],eax
        mov  eax,DWORD PTR [esi]
        mov  DWORD PTR [esp+0x20c],edx
        mov  edx,DWORD PTR ds:0x4776f0
        mov  DWORD PTR [esp+0x24],ecx
        mov  DWORD PTR [esp+0x20],eax
        mov  DWORD PTR [esp+0x214],0xffffffff
        lea  esi,[ebp+0x464]
        mov  ecx,0x6c
        lea  edi,[esp+0x30]
        push  edx
        lea  eax,[esp+0x14]
        rep movsd
        call FUN_004073e0
        mov  ecx,DWORD PTR [ebp+0x45c]
        inc  ecx
        test  ebx,ebx
        mov  DWORD PTR [ebp+0x45c],ecx
        je loc_00407329
        mov  esi,ebp
        call FUN_00408030
        jmp loc_0040731C
    loc_0040724D:
        cmp  eax,0x4000000
        ja loc_004072F8
        je loc_00407289
        cmp  eax,0x1000000
        je loc_00407274
        cmp  eax,0x2000000
        jne loc_0040731C
        mov  eax,DWORD PTR [esi+0x8]
        jmp loc_00407323
    loc_00407274:
        mov  ecx,DWORD PTR [esi+0x8]
        inc  edx
        mov  DWORD PTR [ebp+0x420],ecx
        mov  DWORD PTR [ebp+0x45c],edx
        jmp loc_00407329
    loc_00407289:
        or   DWORD PTR [ebp+0x43c],0x4000000
        mov  edx,DWORD PTR [esi]
        mov  DWORD PTR [ebp+0x7c8],edx
        mov  eax,DWORD PTR [esi+0x4]
        mov  DWORD PTR [ebp+0x7cc],eax
        mov  eax,DWORD PTR [ebp+0x7c4]
        test  al,0x1
        jne loc_004072D7
        or   eax,0x1
        mov  DWORD PTR [ebp+0x7b8],edi
        mov  DWORD PTR [ebp+0x7b4],0xfff0bdc1
        mov  DWORD PTR [ebp+0x7bc],edi
        mov  DWORD PTR [ebp+0x7c0],0x476f78
        mov  DWORD PTR [ebp+0x7c4],eax
    loc_004072D7:
        mov  DWORD PTR [ebp+0x7b8],edi
        mov  DWORD PTR [ebp+0x7bc],edi
        mov  DWORD PTR [ebp+0x7b4],0xffffffff
        mov  ecx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [ebp+0x7dc],ecx
        jmp loc_0040731C
    loc_004072F8:
        cmp  eax,0x8000000
        jne loc_0040731C
    loc_004072FF:
        or   DWORD PTR [ebp+0x43c],ecx
        mov  edx,DWORD PTR [esi]
        mov  DWORD PTR [ebp+0x6f8],edx
        mov  eax,DWORD PTR [esi+0x8]
        mov  DWORD PTR [ebp+0x710],eax
        mov  DWORD PTR [ebp+0x70c],edi
    loc_0040731C:
        mov  eax,DWORD PTR [ebp+0x45c]
        inc  eax
    loc_00407323:
        mov  DWORD PTR [ebp+0x45c],eax
    loc_00407329:
        cmp  DWORD PTR [ebp+0x45c],0x12
        jl loc_00406DB0
    loc_00407336:
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        mov  esp,ebp
        pop  ebp
        ret
        mov  edi,edi
        xor  ch,BYTE PTR [esi+0x40]
        add  BYTE PTR [esi+ebp*2+0x40],bl
        add  BYTE PTR [edx],cl
        outs  dx,DWORD PTR ds:[esi]
        inc  eax
        add  BYTE PTR [edi+ebp*2+0x40],ah
        add  BYTE PTR [ebx+esi*2],bl
        inc  eax
        add  BYTE PTR [eax],al
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  DWORD PTR [esp+eax*1],eax
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x2
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x3
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x3
    }
}
