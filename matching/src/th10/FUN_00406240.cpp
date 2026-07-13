// 00406240: FUN_00406240
// Original size: 896 bytes, actual code: 228 instructions
extern "C" void FUN_00405be0(void);
extern "C" void FUN_00406160(void);
extern "C" void FUN_00406d90(void);
extern "C" void FUN_004074b0(void);
extern "C" void FUN_00407560(void);
extern "C" void FUN_004076a0(void);
extern "C" void FUN_00407780(void);
extern "C" void FUN_004078e0(void);
extern "C" void FUN_00407a30(void);
extern "C" void FUN_00407be0(void);
extern "C" void FUN_00407da0(void);
extern "C" void FUN_00407e40(void);
extern "C" void FUN_00407ef0(void);
extern "C" void FUN_004266b0(void);
extern "C" void FUN_0043dd10(void);
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_00448db0(void);
extern "C" void FUN_0044bf40(void);

extern "C" __declspec(naked) void FUN_00406240(void) {
    __asm {
        sub  esp,0x18
        push  ebp
        mov  ebp,DWORD PTR [esp+0x20]
        test  BYTE PTR [ebp+0x0],0x8
        je loc_0040625F
        mov  eax,ebp
        call FUN_00405be0
        or   eax,0xffffffff
        pop  ebp
        add  esp,0x18
        ret  0x4
    loc_0040625F:
        movzx eax,WORD PTR [ebp+0x446]
        dec  eax
        push  ebx
        mov  ebx,0x1
        je loc_00406373
        dec  eax
        je loc_004062F0
        dec  eax
        jne loc_0040651B
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x3c0]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x3c4]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x3c8]
        fstp  DWORD PTR [esp+0x10]
        fxch  st(1)
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x14]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [esp+0x10]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR [ebp+0x3b4]
        fstp  DWORD PTR [ebp+0x3b4]
        fxch  st(1)
        fadd  DWORD PTR [ebp+0x3b8]
        fstp  DWORD PTR [ebp+0x3b8]
        fadd  DWORD PTR [ebp+0x3bc]
        fstp  DWORD PTR [ebp+0x3bc]
        jmp loc_0040651B
    loc_004062F0:
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x3c0]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x3c4]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x3c8]
        fstp  DWORD PTR [esp+0x1c]
        fxch  st(1)
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x8]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [esp+0x1c]
        fmul  DWORD PTR ds:0x470b0c
        fld  DWORD PTR [esp+0x8]
        fadd  DWORD PTR [ebp+0x3b4]
        fstp  DWORD PTR [ebp+0x3b4]
        fxch  st(1)
        fadd  DWORD PTR [ebp+0x3b8]
        fstp  DWORD PTR [ebp+0x3b8]
        fadd  DWORD PTR [ebp+0x3bc]
        fstp  DWORD PTR [ebp+0x3bc]
        mov  eax,DWORD PTR [ebp+0x314]
        test  eax,eax
        je loc_0040651B
        mov  WORD PTR [ebp+0x446],bx
    loc_00406373:
        push  esi
        mov  ecx,ebp
        call FUN_00406d90
        mov  eax,DWORD PTR [ebp+0x43c]
        test  eax,eax
        je loc_0040643E
        test  bl,al
        je loc_00406394
        mov  esi,ebp
        call FUN_004074b0
    loc_00406394:
        test  BYTE PTR [ebp+0x43c],0x10
        je loc_004063A4
        mov  esi,ebp
        call FUN_00407560
    loc_004063A4:
        test  BYTE PTR [ebp+0x43c],0x20
        je loc_004063B4
        mov  esi,ebp
        call FUN_004076a0
    loc_004063B4:
        test  BYTE PTR [ebp+0x43c],0x40
        je loc_004063C4
        mov  esi,ebp
        call FUN_00407780
    loc_004063C4:
        mov  eax,DWORD PTR [ebp+0x43c]
        test  ah,0x1
        je loc_004063D6
        mov  esi,ebp
        call FUN_004078e0
    loc_004063D6:
        mov  al,BYTE PTR [ebp+0x43c]
        test  al,al
        jns loc_004063E7
        mov  esi,ebp
        call FUN_00407a30
    loc_004063E7:
        test  DWORD PTR [ebp+0x43c],0x8000c00
        je loc_004063FA
        mov  esi,ebp
        call FUN_00407be0
    loc_004063FA:
        test  DWORD PTR [ebp+0x43c],0x4000000
        je loc_0040640D
        mov  esi,ebp
        call FUN_00407ef0
    loc_0040640D:
        mov  eax,DWORD PTR [ebp+0x43c]
        test  ah,ah
        jns loc_0040643E
        mov  ecx,DWORD PTR [ebp+0x71c]
        test  ecx,ecx
        jg loc_0040642E
        xor  eax,0x8000
        mov  DWORD PTR [ebp+0x43c],eax
        jmp loc_0040643E
    loc_0040642E:
        push  0xbf800000
        lea  esi,[ebp+0x718]
        call FUN_0044bf40
    loc_0040643E:
        fld  DWORD PTR ds:0x476f78
        push  edi
        fmul  DWORD PTR [ebp+0x3c0]
        lea  edi,[ebp+0x3b4]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x3c4]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x3c8]
        fstp  DWORD PTR [esp+0x24]
        fxch  st(1)
        fadd  DWORD PTR [edi]
        fstp  DWORD PTR [edi]
        fadd  DWORD PTR [edi+0x4]
        fstp  DWORD PTR [edi+0x4]
        fld  DWORD PTR [esp+0x24]
        fadd  DWORD PTR [edi+0x8]
        fstp  DWORD PTR [edi+0x8]
        mov  al,BYTE PTR [ebp+0x0]
        test  al,0x2
        je loc_00406519
        mov  edx,DWORD PTR ds:0x477834
        lea  eax,[ebp+0x3f0]
        mov  ecx,edi
        call FUN_004266b0
        cmp  eax,ebx
        jne loc_004064D9
        mov  eax,DWORD PTR [ebp+0x438]
        test  eax,eax
        mov  WORD PTR [ebp+0x446],0x3
        mov  WORD PTR [ebp+0x30c],bx
        jl loc_00406519
        mov  ecx,DWORD PTR ds:0x4776f0
        mov  edx,DWORD PTR [ecx+0x3e0b50]
        push  eax
        lea  eax,[esp+0x30]
        push  eax
        push  edx
        call FUN_00448db0
        jmp loc_00406519
    loc_004064D9:
        cmp  eax,0x2
        jne loc_00406519
        mov  eax,DWORD PTR [ebp+0x0]
        test  al,0x4
        jne loc_00406519
        mov  ecx,DWORD PTR ds:0x4776f0
        or   eax,0x4
        mov  DWORD PTR [ebp+0x0],eax
        mov  edx,DWORD PTR [ecx+0x3e0b50]
        push  0x1b2
        lea  eax,[esp+0x30]
        push  eax
        push  edx
        call FUN_00448db0
        mov  eax,DWORD PTR [edi]
        push  eax
        mov  ebx,0x1c
        mov  esi,0x492590
        call FUN_0043dd10
    loc_00406519:
        pop  edi
        pop  esi
    loc_0040651B:
        mov  eax,DWORD PTR [ebp+0x39c]
        test  eax,eax
        je loc_00406584
        test  DWORD PTR [ebp+0x43c],0x100000
        je loc_00406538
        mov  ebx,ebp
        call FUN_00407da0
    loc_00406538:
        test  DWORD PTR [ebp+0x43c],0x200000
        je loc_0040654B
        mov  ebx,ebp
        call FUN_00407e40
    loc_0040654B:
        mov  eax,DWORD PTR [ebp+0x434]
        test  eax,eax
        jg loc_00406584
        mov  eax,DWORD PTR [ebp+0x39c]
        mov  ecx,DWORD PTR [eax+0x30]
        mov  edx,DWORD PTR [eax+0x34]
        push  ecx
        push  edx
        lea  ecx,[ebp+0x3b4]
        call FUN_00406160
        test  eax,eax
        je loc_00406584
    loc_00406572:
        mov  eax,ebp
        call FUN_00405be0
        pop  ebx
        or   eax,0xffffffff
        pop  ebp
        add  esp,0x18
        ret  0x4
    loc_00406584:
        mov  eax,DWORD PTR [ebp+0x4]
        test  eax,eax
        je loc_0040658F
        dec  eax
        mov  DWORD PTR [ebp+0x4],eax
    loc_0040658F:
        mov  eax,DWORD PTR [ebp+0x434]
        test  eax,eax
        jle loc_004065A0
        dec  eax
        mov  DWORD PTR [ebp+0x434],eax
    loc_004065A0:
        lea  eax,[ebp+0x8]
        push  eax
        call FUN_0043ee30
        test  eax,eax
        jne loc_00406572
        pop  ebx
        pop  ebp
        add  esp,0x18
        ret  0x4
    }
}
