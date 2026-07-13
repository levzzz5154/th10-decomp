// 00419120: FUN_00419120
// Original size: 1328 bytes, actual code: 348 instructions
extern "C" void FUN_0041ab70(void);
extern "C" void FUN_00447a50(void);
extern "C" void FUN_00447ae0(void);
extern "C" void FUN_00447bb0(void);
extern "C" void FUN_00448db0(void);
extern "C" void FUN_004491c0(void);
extern "C" void _free(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00419120(void) {
    __asm {
        sub  esp,0x3c
        test  eax,eax
        push  ebp
        mov  ebp,DWORD PTR [esp+0x44]
        je loc_0041963C
        push  ebx
        mov  ebx,DWORD PTR ds:0x491c10
        push  esi
        push  edi
        nop
    loc_00419140:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edi,DWORD PTR [eax]
        mov  eax,DWORD PTR [edi+0x68]
        test  eax,eax
        mov  DWORD PTR [esp+0x50],ecx
        je loc_00419158
        cmp  eax,DWORD PTR ds:0x474c84
        jne loc_0041915B
    loc_00419158:
        dec  DWORD PTR [edi+0x60]
    loc_0041915B:
        mov  eax,DWORD PTR [edi+0x60]
        test  eax,eax
        jg loc_0041962D
        mov  edx,DWORD PTR [ebp+0x1a4]
        mov  ecx,DWORD PTR [ebp+edx*4+0xdc]
        test  ecx,ecx
        lea  esi,[ebp+edx*4+0xdc]
        je loc_004191EF
        mov  eax,DWORD PTR [ebx+0x72dad4]
        test  eax,eax
        je loc_00419195
    loc_00419188:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_004191AF
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00419188
    loc_00419195:
        mov  eax,DWORD PTR [ebx+0x72dadc]
        test  eax,eax
        je loc_004191EF
        nop
    loc_004191A0:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_004191AF
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004191A0
        jmp loc_004191EF
    loc_004191AF:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_004191EF
        mov  ebx,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        mov  edx,0x4000000
        or   ebx,edx
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],ebx
        jne loc_004191EF
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_004191EF
        jmp loc_004191E0
        nop
        nop
    loc_004191E0:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],edx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004191E0
    loc_004191EF:
        mov  DWORD PTR [esi],0x0
        fld  DWORD PTR [edi+0x7c]
        fmul  DWORD PTR ds:0x470bd0
        fadd  DWORD PTR [edi+0x4]
        fstp  DWORD PTR [edi+0x4]
        mov  ecx,DWORD PTR [ebp+0x1a4]
        fld  DWORD PTR [edi+0x7c]
        fcomp DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x41
        jp loc_004192E8
        mov  eax,ds:0x4776e0
        mov  eax,DWORD PTR [eax+0x899c]
        add  ecx,0x2
        push  ecx
        lea  edx,[esp+0x14]
        push  edx
        push  eax
        call FUN_00448db0
        mov  edx,DWORD PTR [eax]
        mov  ecx,DWORD PTR [ebp+0x1a4]
        mov  ebx,DWORD PTR ds:0x491c10
        mov  DWORD PTR [ebp+ecx*4+0xdc],edx
        mov  eax,DWORD PTR [ebp+0x1a4]
        mov  ecx,DWORD PTR [ebp+eax*4+0xdc]
        test  ecx,ecx
        lea  edx,[ebp+eax*4+0xdc]
        jne loc_00419269
    loc_00419265:
        xor  eax,eax
        jmp loc_004192A5
    loc_00419269:
        mov  eax,DWORD PTR [ebx+0x72dad4]
        test  eax,eax
        je loc_00419280
    loc_00419273:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_0041929F
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00419273
    loc_00419280:
        mov  eax,DWORD PTR [ebx+0x72dadc]
        test  eax,eax
        je loc_00419265
        lea  ebx,[ebx+0x0]
    loc_00419290:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_0041929F
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00419290
        jmp loc_004192A5
    loc_0041929F:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        jne loc_004192AB
    loc_004192A5:
        mov  DWORD PTR [edx],0x0
    loc_004192AB:
        mov  BYTE PTR [eax+0x3a1],0xf
        mov  BYTE PTR [eax+0x3a0],0xf
        fld  DWORD PTR [edi+0x7c]
        mov  ecx,DWORD PTR [edi+0x7c]
        fmul  DWORD PTR ds:0x470ca8
        mov  edx,ecx
        mov  DWORD PTR [esp+0x1c],ecx
        mov  DWORD PTR [esp+0x20],edx
        fstp  DWORD PTR [esp+0x24]
        mov  DWORD PTR [esp+0x28],0x0
        lea  ecx,[esp+0x1c]
        lea  edx,[esp+0x24]
        jmp loc_00419435
    loc_004192E8:
        fld  DWORD PTR [edi+0x7c]
        add  ecx,0xc
        fcomp DWORD PTR ds:0x470b08
        push  ecx
        fnstsw ax
        test  ah,0x41
        jp loc_004193AB
        mov  eax,ds:0x4776e0
        mov  eax,DWORD PTR [eax+0x899c]
        lea  edx,[esp+0x18]
        push  edx
        push  eax
        call FUN_00448db0
        mov  edx,DWORD PTR [eax]
        mov  ecx,DWORD PTR [ebp+0x1a4]
        mov  DWORD PTR [ebp+ecx*4+0xdc],edx
        mov  eax,DWORD PTR [ebp+0x1a4]
        mov  ecx,DWORD PTR [ebp+eax*4+0xdc]
        mov  edx,DWORD PTR ds:0x491c10
        lea  ebx,[ebp+eax*4+0xdc]
        push  ecx
        call FUN_004491c0
        mov  esi,eax
        test  esi,esi
        jne loc_0041934D
        mov  DWORD PTR [ebx],eax
    loc_0041934D:
        fld  DWORD PTR [edi+0x7c]
        fmul  DWORD PTR ds:0x470c08
        call FUN_00463b2c
        mov  BYTE PTR [esi+0x3a1],al
        mov  BYTE PTR [esi+0x3a0],al
        fld  DWORD PTR [edi+0x7c]
        fmul  DWORD PTR ds:0x470ce4
        push  0x4
        push  0x8
        lea  ecx,[esp+0x34]
        fstp  DWORD PTR [esp+0x3c]
        lea  edx,[esp+0x3c]
        fld  DWORD PTR [edi+0x7c]
        mov  eax,esi
        fmul  DWORD PTR ds:0x470b0c
        mov  DWORD PTR [esp+0x40],0x0
        fst  DWORD PTR [esp+0x34]
        fstp  DWORD PTR [esp+0x38]
        call FUN_0041ab70
        mov  ebx,DWORD PTR ds:0x491c10
        jmp loc_00419440
    loc_004193AB:
        mov  edx,DWORD PTR ds:0x4776e0
        mov  eax,DWORD PTR [edx+0x899c]
        lea  edx,[esp+0x1c]
        push  edx
        push  eax
        call FUN_00448db0
        mov  edx,DWORD PTR [eax]
        mov  ecx,DWORD PTR [ebp+0x1a4]
        mov  ebx,DWORD PTR ds:0x491c10
        mov  DWORD PTR [ebp+ecx*4+0xdc],edx
        mov  eax,DWORD PTR [ebp+0x1a4]
        mov  ecx,DWORD PTR [ebp+eax*4+0xdc]
        lea  esi,[ebp+eax*4+0xdc]
        push  ecx
        mov  edx,ebx
        call FUN_004491c0
        test  eax,eax
        jne loc_004193F9
        mov  DWORD PTR [esi],eax
    loc_004193F9:
        mov  BYTE PTR [eax+0x3a1],0x1e
        mov  BYTE PTR [eax+0x3a0],0x1e
        fld  DWORD PTR [edi+0x7c]
        fmul  DWORD PTR ds:0x470ce4
        mov  DWORD PTR [esp+0x48],0x0
        lea  ecx,[esp+0x3c]
        lea  edx,[esp+0x44]
        fstp  DWORD PTR [esp+0x44]
        fld  DWORD PTR [edi+0x7c]
        fmul  DWORD PTR ds:0x470b0c
        fst  DWORD PTR [esp+0x3c]
        fstp  DWORD PTR [esp+0x40]
    loc_00419435:
        push  0x4
        push  0x8
        mov  esi,eax
        call FUN_0041ab70
    loc_00419440:
        mov  eax,DWORD PTR [edi+0x64]
        sub  eax,0x0
        je loc_00419567
        dec  eax
        je loc_004194E2
        dec  eax
        jne loc_004195B8
        mov  eax,DWORD PTR [ebp+0x1a4]
        lea  eax,[eax+eax*2]
        lea  ecx,[ebp+eax*4+0x104]
        lea  edx,[esi+0x340]
        mov  eax,DWORD PTR [edx]
        mov  DWORD PTR [ecx],eax
        mov  eax,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ecx+0x4],eax
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ecx+0x8],edx
        fld  DWORD PTR [edi+0x80]
        mov  eax,DWORD PTR [ebp+0x1a4]
        fmul  DWORD PTR ds:0x470b0c
        lea  eax,[eax+eax*2]
        lea  eax,[ebp+eax*4+0x104]
        fsubr DWORD PTR [eax]
        fstp  DWORD PTR [eax]
        mov  ecx,DWORD PTR [ebp+0x1a4]
        mov  edx,DWORD PTR [edi+0x80]
        lea  eax,[edi+0x1c]
        push  eax
        push  0xffffff
        push  ebx
        mov  DWORD PTR [ebp+ecx*4+0x17c],edx
        call FUN_00447ae0
        mov  ecx,DWORD PTR [esi+0x35c]
        and  ecx,0xfffbffff
        add  esp,0xc
        or   ecx,0x80000
        mov  DWORD PTR [esi+0x35c],ecx
        jmp loc_004195B2
    loc_004194E2:
        mov  eax,DWORD PTR [ebp+0x1a4]
        lea  eax,[eax+eax*2]
        lea  ecx,[ebp+eax*4+0x104]
        lea  edx,[esi+0x340]
        mov  eax,DWORD PTR [edx]
        mov  DWORD PTR [ecx],eax
        mov  eax,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ecx+0x4],eax
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ecx+0x8],edx
        fld  DWORD PTR [edi+0x80]
        mov  eax,DWORD PTR [ebp+0x1a4]
        fmul  DWORD PTR ds:0x470b0c
        lea  eax,[eax+eax*2]
        lea  eax,[ebp+eax*4+0x104]
        fadd  DWORD PTR [eax]
        fstp  DWORD PTR [eax]
        mov  ecx,DWORD PTR [ebp+0x1a4]
        mov  edx,DWORD PTR [edi+0x80]
        lea  eax,[edi+0x1c]
        push  eax
        push  0xffffff
        push  ebx
        mov  DWORD PTR [ebp+ecx*4+0x17c],edx
        call FUN_00447a50
        mov  ecx,DWORD PTR [esi+0x35c]
        and  ecx,0xfff7ffff
        add  esp,0xc
        or   ecx,0x40000
        mov  DWORD PTR [esi+0x35c],ecx
        jmp loc_004195B2
    loc_00419567:
        mov  eax,DWORD PTR [ebp+0x1a4]
        lea  eax,[eax+eax*2]
        lea  ecx,[ebp+eax*4+0x104]
        lea  edx,[esi+0x340]
        mov  eax,DWORD PTR [edx]
        mov  DWORD PTR [ecx],eax
        mov  eax,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ecx+0x4],eax
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ecx+0x8],edx
        mov  eax,DWORD PTR [ebp+0x1a4]
        mov  ecx,DWORD PTR [edi+0x80]
        lea  edx,[edi+0x1c]
        push  edx
        push  0xffffff
        push  ebx
        mov  DWORD PTR [ebp+eax*4+0x17c],ecx
        call FUN_00447bb0
        add  esp,0xc
    loc_004195B2:
        mov  ebx,DWORD PTR ds:0x491c10
    loc_004195B8:
        mov  eax,DWORD PTR [edi+0x84]
        mov  DWORD PTR [esi+0x2fc],eax
        mov  BYTE PTR [esi+0x2ff],0x0
        mov  ecx,DWORD PTR [edi+0x6c]
        mov  DWORD PTR [esi+0x30c],ecx
        movzx edx,BYTE PTR [edi+0x87]
        mov  DWORD PTR [esi+0x310],edx
        mov  eax,DWORD PTR [ebp+0x1a4]
        inc  eax
        cdq
        mov  ecx,0xa
        idiv  ecx
        xor  ecx,ecx
        mov  DWORD PTR [ebp+0x1a4],edx
        mov  eax,DWORD PTR [edi+0x10]
        cmp  eax,ecx
        je loc_00419605
        mov  edx,DWORD PTR [edi+0x14]
        mov  DWORD PTR [eax+0x8],edx
    loc_00419605:
        mov  eax,DWORD PTR [edi+0x14]
        cmp  eax,ecx
        je loc_00419612
        mov  edx,DWORD PTR [edi+0x10]
        mov  DWORD PTR [eax+0x4],edx
    loc_00419612:
        cmp  DWORD PTR [esp+0x54],ecx
        mov  DWORD PTR [edi+0x10],ecx
        mov  DWORD PTR [edi+0x14],ecx
        je loc_0041962D
        push  edi
        call _free
        mov  ebx,DWORD PTR ds:0x491c10
        add  esp,0x4
    loc_0041962D:
        mov  eax,DWORD PTR [esp+0x50]
        test  eax,eax
        jne loc_00419140
        pop  edi
        pop  esi
        pop  ebx
    loc_0041963C:
        xor  eax,eax
        pop  ebp
        add  esp,0x3c
        ret  0x8
    }
}
