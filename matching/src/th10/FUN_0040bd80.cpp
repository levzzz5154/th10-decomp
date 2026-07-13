// 0040BD80: FUN_0040bd80
// Original size: 1600 bytes, actual code: 481 instructions
extern "C" void FUN_00405410(void);
extern "C" void FUN_0040b480(void);
extern "C" void FUN_0040c480(void);
extern "C" void FUN_0040c4d0(void);
extern "C" void FUN_0040c540(void);
extern "C" void FUN_00417010(void);
extern "C" void FUN_00420a90(void);
extern "C" void FUN_00420b10(void);
extern "C" void FUN_00420c30(void);
extern "C" void FUN_0043c8b0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_004477d0(void);
extern "C" void FUN_00447a50(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_004492a0(void);
extern "C" void FUN_00449450(void);
extern "C" void FUN_00449630(void);
extern "C" void FUN_0044bf40(void);
extern "C" void FUN_0044c1c0(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0040bd80(void) {
    __asm {
        sub  esp,0xc
        push  ebp
        mov  ebp,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [ebp+0x74]
        test  al,0x4
        je loc_0040BD98
        xor  eax,eax
        pop  ebp
        add  esp,0xc
        ret  0x4
    loc_0040BD98:
        mov  ecx,DWORD PTR ds:0x477700
        test  BYTE PTR [ecx+0x20],0x1
        jne loc_0040BDC6
        test  al,0x2
        jne loc_0040BDC6
        mov  ecx,DWORD PTR ds:0x474e30
        test  ch,0x1
        je loc_0040BDC6
        test  al,0x1
        je loc_0040BDC6
        mov  edx,DWORD PTR [ebp+0x54]
        movzx eax,WORD PTR [edx]
        push  eax
        lea  eax,[ebp+0x18]
        call FUN_00405410
    loc_0040BDC6:
        mov  ecx,DWORD PTR [ebp+0x54]
        movzx edx,WORD PTR [ecx]
        cmp  DWORD PTR [ebp+0x1c],edx
        push  ebx
        push  esi
        push  edi
        jl loc_0040C27C
        jmp loc_0040BDE0
        lea  ebx,[ebx+0x0]
    loc_0040BDE0:
        mov  eax,DWORD PTR [ebp+0x54]
        movzx ecx,BYTE PTR [eax+0x2]
        cmp  ecx,0x11
        ja loc_0040C25F
        jmp  DWORD PTR [ecx*4+0x40c358]
        mov  ecx,DWORD PTR [ebp+0x78]
        test  ecx,ecx
        jne loc_0040BE8C
        lea  edi,[ebp+0x40]
        mov  ebx,0x5
        lea  ebx,[ebx+0x0]
    loc_0040BE10:
        mov  eax,DWORD PTR [edi]
        mov  esi,DWORD PTR ds:0x491c10
        push  eax
        mov  edx,esi
        call FUN_004491c0
        test  eax,eax
        jne loc_0040BE26
        mov  DWORD PTR [edi],eax
    loc_0040BE26:
        push  0x46cfd4
        push  0xffffff
        push  esi
        mov  esi,eax
        call FUN_00447a50
        add  esp,0xc
        mov  eax,edi
        call FUN_0040c4d0
        add  edi,0x4
        dec  ebx
        jne loc_0040BE10
        mov  ecx,DWORD PTR [ebp+0x40]
        mov  ebx,DWORD PTR ds:0x491c10
        lea  edi,[ebp+0x40]
        push  ecx
        mov  edx,ebx
        call FUN_004491c0
        mov  esi,eax
        test  esi,esi
        jne loc_0040BE64
        mov  DWORD PTR [edi],eax
    loc_0040BE64:
        mov  eax,DWORD PTR [ebp+0x54]
        add  eax,0x4
        call FUN_00417010
        mov  edx,DWORD PTR [ebp+0x7c]
        push  eax
        push  edx
        push  ebx
        call FUN_00447a50
        add  esp,0xc
        mov  eax,edi
        call FUN_0040c480
        inc  DWORD PTR [ebp+0x78]
        jmp loc_0040C25F
    loc_0040BE8C:
        add  eax,0x4
        call FUN_00417010
        mov  ecx,DWORD PTR [ebp+0x78]
        push  eax
        mov  eax,DWORD PTR [ebp+0x7c]
        push  eax
        lea  esi,[ebp+ecx*4+0x40]
        call FUN_00449450
        mov  edx,DWORD PTR ds:0x491c10
        push  edx
        mov  esi,eax
        call FUN_00447a50
        mov  eax,DWORD PTR [ebp+0x78]
        add  esp,0xc
        lea  eax,[ebp+eax*4+0x40]
        call FUN_0040c480
        mov  ecx,DWORD PTR [ebp+0x78]
        inc  ecx
        mov  eax,ecx
        cmp  eax,0x5
        mov  DWORD PTR [ebp+0x78],ecx
        jl loc_0040C25F
        mov  DWORD PTR [ebp+0x78],0x0
        jmp loc_0040C25F
        lea  esi,[ebp+0x40]
        mov  edi,0x5
    loc_0040BEE8:
        mov  eax,esi
        call FUN_0040c4d0
        add  esi,0x4
        dec  edi
        jne loc_0040BEE8
        jmp loc_0040C25F
        mov  ecx,DWORD PTR [ebp+0x30]
        test  ecx,ecx
        jg loc_0040BF0D
        mov  ecx,DWORD PTR [eax+0x4]
        push  ecx
        lea  eax,[ebp+0x2c]
        call FUN_00405410
    loc_0040BF0D:
        lea  esi,[ebp+0x2c]
        push  0xbf800000
        call FUN_0044bf40
        mov  edx,DWORD PTR [ebp+0x54]
        mov  eax,DWORD PTR [edx+0x4]
        test  eax,eax
        jge loc_0040BF30
        push  0x3e7
        mov  eax,esi
        call FUN_00405410
    loc_0040BF30:
        test  DWORD PTR ds:0x474e36,0x1001
        jne loc_0040BF7F
        mov  eax,DWORD PTR [ebp+0x30]
        test  eax,eax
        jle loc_0040BF7F
        mov  ecx,DWORD PTR ds:0x477700
        test  BYTE PTR [ecx+0x20],0x1
        jne loc_0040C34A
        mov  ecx,DWORD PTR ds:0x474e30
        test  ch,0x1
        je loc_0040C34A
        cdq
        mov  ecx,0x6
        idiv  ecx
        test  edx,edx
        jne loc_0040C34A
        push  edx
        mov  eax,esi
        call FUN_00405410
        jmp loc_0040C25F
    loc_0040BF7F:
        push  0x0
        xor  edi,edi
        mov  ecx,0x492590
        call FUN_0043dc90
        push  edi
        mov  eax,esi
        call FUN_00405410
        jmp loc_0040C25F
        mov  ecx,DWORD PTR [ebp+0x30]
        xor  ebx,ebx
        cmp  ecx,ebx
        jg loc_0040BFAF
        mov  edx,DWORD PTR [eax+0x4]
        push  edx
        lea  eax,[ebp+0x2c]
        call FUN_00405410
    loc_0040BFAF:
        lea  esi,[ebp+0x2c]
        push  0xbf800000
        call FUN_0044bf40
        test  DWORD PTR ds:0x474e36,0x1001
        jne loc_0040C000
        mov  eax,DWORD PTR [ebp+0x30]
        cmp  eax,ebx
        jle loc_0040C000
        mov  ecx,DWORD PTR ds:0x477700
        test  BYTE PTR [ecx+0x20],0x1
        jne loc_0040C34A
        mov  ecx,DWORD PTR ds:0x474e30
        test  ch,0x1
        je loc_0040C34A
        cdq
        mov  ecx,0x6
        idiv  ecx
        test  edx,edx
        jne loc_0040C34A
        jmp loc_0040C00D
    loc_0040C000:
        push  ebx
        xor  edi,edi
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_0040C00D:
        push  ebx
        mov  eax,esi
        call FUN_00405410
        mov  DWORD PTR [ebp+0x78],ebx
        mov  DWORD PTR ds:0x4918a4,ebx
        jmp loc_0040C25F
        mov  edx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [ebp+edx*4+0x90]
        lea  esi,[ebp+edx*4+0x90]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004492a0
        mov  DWORD PTR [esi],0x0
        mov  eax,DWORD PTR [ebp+0x54]
        mov  ecx,DWORD PTR [eax+0xc]
        mov  edx,DWORD PTR [eax+0x8]
        mov  eax,DWORD PTR [ebp+edx*4+0x80]
        push  0xf
        push  ecx
        push  eax
        lea  edi,[esp+0x2c]
        call FUN_00448d00
        mov  ecx,DWORD PTR [ebp+0x54]
        mov  edx,DWORD PTR [ecx+0x4]
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [ebp+edx*4+0x90],eax
        jmp loc_0040C25F
        cmp  DWORD PTR ds:0x474c74,0x1
        jne loc_0040C25F
        mov  ecx,DWORD PTR [eax+0x4]
        lea  esi,[ebp+ecx*4+0x90]
        call FUN_00449630
        mov  eax,DWORD PTR [ebp+0x54]
        mov  edx,DWORD PTR [eax+0xc]
        mov  eax,DWORD PTR [eax+0x8]
        mov  ecx,DWORD PTR [ebp+eax*4+0x80]
        push  0xf
        push  edx
        push  ecx
        lea  edi,[esp+0x1c]
        call FUN_00448d00
        mov  edx,DWORD PTR [ebp+0x54]
        mov  ecx,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+ecx*4+0x90],edx
        jmp loc_0040C25F
        cmp  DWORD PTR ds:0x474c74,0x2
        jne loc_0040C25F
        mov  eax,DWORD PTR [eax+0x4]
        lea  esi,[ebp+eax*4+0x90]
        call FUN_00449630
        mov  eax,DWORD PTR [ebp+0x54]
        mov  ecx,DWORD PTR [eax+0xc]
        mov  edx,DWORD PTR [eax+0x8]
        mov  eax,DWORD PTR [ebp+edx*4+0x80]
        push  0xf
        push  ecx
        push  eax
        lea  edi,[esp+0x20]
        call FUN_00448d00
        mov  ecx,DWORD PTR [ebp+0x54]
        mov  edx,DWORD PTR [ecx+0x4]
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [ebp+edx*4+0x90],eax
        jmp loc_0040C25F
        cmp  DWORD PTR ds:0x474c74,0x3
        jne loc_0040C25F
        mov  ecx,DWORD PTR [eax+0x4]
        lea  esi,[ebp+ecx*4+0x90]
        call FUN_00449630
        mov  eax,DWORD PTR [ebp+0x54]
        mov  edx,DWORD PTR [eax+0xc]
        mov  eax,DWORD PTR [eax+0x8]
        mov  ecx,DWORD PTR [ebp+eax*4+0x80]
        push  0xf
        push  edx
        push  ecx
        lea  edi,[esp+0x24]
        call FUN_00448d00
        mov  edx,DWORD PTR [ebp+0x54]
        mov  ecx,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+ecx*4+0x90],edx
        jmp loc_0040C25F
        mov  eax,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ebp+0x7c],eax
        jmp loc_0040C25F
        add  eax,0x4
        push  eax
        push  0x0
        call FUN_00420a90
        mov  esi,DWORD PTR [ebp+0x54]
        add  esi,0x4
        mov  edi,0x46cfc4
        mov  ecx,0x10
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_0040C197
        push  0xf
        push  edx
        call FUN_00420b10
        jmp loc_0040C25F
    loc_0040C197:
        push  0x10
        push  0x0
        call FUN_00420b10
        jmp loc_0040C25F
        push  0x40400000
        call FUN_00420c30
        and  DWORD PTR [ebp+0x74],0xfffffffe
        jmp loc_0040C25F
        mov  ebx,DWORD PTR ds:0x491c10
        lea  esi,[ebp+0x40]
        mov  edi,0x5
    loc_0040C1C6:
        mov  eax,DWORD PTR [esi]
        push  eax
        mov  edx,ebx
        call FUN_004492a0
        mov  DWORD PTR [esi],0x0
        add  esi,0x4
        dec  edi
        jne loc_0040C1C6
        mov  eax,DWORD PTR [ebp+0x54]
        mov  ecx,DWORD PTR ds:0x477700
        add  eax,0x4
        push  ecx
        call FUN_0040b480
        mov  edx,eax
        test  edx,edx
        je loc_0040C2C7
        xor  eax,eax
        mov  ecx,0x3b
        mov  edi,ebp
        rep stosd
        mov  eax,DWORD PTR [edx+0x4]
        add  eax,edx
        mov  DWORD PTR [ebp+0x54],eax
        push  0x0
        lea  eax,[ebp+0x4]
        call FUN_00405410
        push  0x0
        lea  eax,[ebp+0x18]
        call FUN_00405410
        push  0x0
        lea  eax,[ebp+0x2c]
        call FUN_00405410
        mov  eax,DWORD PTR [ebp+0x74]
        or   eax,0x2
        mov  DWORD PTR [ebp+0x7c],0xffffff
        mov  DWORD PTR [ebp+0x74],eax
        jmp loc_0040C26D
        mov  ecx,DWORD PTR [eax+0x4]
        push  0x0
        push  0x0
        push  0x0
        push  ecx
        push  0x0
        jmp loc_0040C255
        mov  edx,DWORD PTR [eax+0x4]
        push  0x0
        push  0x0
        push  0x0
        push  edx
        push  0x5
    loc_0040C255:
        mov  ebx,0x31
        call FUN_0043c8b0
    loc_0040C25F:
        mov  eax,DWORD PTR [ebp+0x54]
        movzx ecx,BYTE PTR [eax+0x3]
        lea  edx,[ecx+eax*1+0x4]
        mov  DWORD PTR [ebp+0x54],edx
    loc_0040C26D:
        mov  eax,DWORD PTR [ebp+0x54]
        movzx ecx,WORD PTR [eax]
        cmp  DWORD PTR [ebp+0x1c],ecx
        jge loc_0040BDE0
    loc_0040C27C:
        mov  edx,DWORD PTR [ebp+0x1c]
        mov  ecx,DWORD PTR [ebp+0x24]
        mov  DWORD PTR [ebp+0x18],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0040C33A
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0040C33A
        fld  DWORD PTR [ebp+0x20]
        pop  edi
        fadd  DWORD PTR ds:0x470afc
        pop  esi
        inc  edx
        pop  ebx
        fstp  DWORD PTR [ebp+0x20]
        mov  DWORD PTR [ebp+0x1c],edx
        xor  eax,eax
        pop  ebp
        add  esp,0xc
        ret  0x4
    loc_0040C2C7:
        pop  edi
        pop  esi
        pop  ebx
        or   eax,0xffffffff
        pop  ebp
        add  esp,0xc
        ret  0x4
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x43c40000
        push  0x43f00000
        call FUN_0040c540
        mov  edx,DWORD PTR [ebp+0x54]
        mov  esi,DWORD PTR [edx+0x4]
        mov  ebx,DWORD PTR ds:0x491c10
        add  esi,0x1d
        call FUN_004477d0
        mov  eax,DWORD PTR [ebp+0x54]
        mov  edx,DWORD PTR [ebp+0x74]
        add  eax,0x8
        or   edx,0x4
        mov  DWORD PTR [ebp+0x70],eax
        push  ebp
        lea  eax,[ebp+0xd0]
        mov  edi,0x40c3a0
        mov  DWORD PTR [ebp+0x74],edx
        call FUN_0044c1c0
        mov  eax,DWORD PTR [ebp+0x54]
        movzx ecx,BYTE PTR [eax+0x3]
        pop  edi
        pop  esi
        lea  edx,[ecx+eax*1+0x4]
        pop  ebx
        mov  DWORD PTR [ebp+0x54],edx
        xor  eax,eax
        pop  ebp
        add  esp,0xc
        ret  0x4
    loc_0040C33A:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [ebp+0x20]
        fst  DWORD PTR [ebp+0x20]
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x1c],eax
    loc_0040C34A:
        pop  edi
        pop  esi
        pop  ebx
        xor  eax,eax
        pop  ebp
        add  esp,0xc
        ret  0x4
    loc_0040C356:
        mov  edi,edi
        mov  edx,0xc25f0040
        inc  eax
        add  BYTE PTR [edi-0x3e],bl
        inc  eax
        add  bh,dh
        mov  ebp,0xbee00040
        inc  eax
        add  dl,bh
        mov  esi,0xbf9a0040
        inc  eax
        add  ah,dl
        ret  0x40
        and  eax,eax
        inc  eax
        add  BYTE PTR [esi-0x3f],bl
        inc  eax
        add  BYTE PTR [ecx-0x3f],ch
        inc  eax
        add  BYTE PTR [ebp-0x47ffbf3f],ah
        rol  DWORD PTR [eax+0x0],0x3b
        ret  0x40
        dec  ecx
        ret  0x40
        ja loc_0040C356
        inc  eax
        add  ah,al
        rol  BYTE PTR [eax+0x0],0x11
        rol  DWORD PTR [eax+0x0],0xa1
        add  BYTE PTR [edi+0x47],dh
        add  BYTE PTR [ebx-0x75],dl
        pop  eax
        sbb  al,ch
        adc  al,BYTE PTR [eax]
        add  BYTE PTR [eax],al
        xor  eax,eax
        pop  ebx
        ret
    }
}
