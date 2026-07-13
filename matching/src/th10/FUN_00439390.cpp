// 00439390: FUN_00439390
// Original size: 432 bytes, actual code: 120 instructions
extern "C" void FUN_00420cd0(void);
extern "C" void FUN_00421480(void);
extern "C" void FUN_004391f0(void);
extern "C" void FUN_00439540(void);
extern "C" void FUN_0043ddf0(void);
extern "C" void FUN_00442f50(void);
extern "C" void FUN_00449c00(void);
extern "C" void FUN_00449d40(void);
extern "C" void FUN_0044c150(void);

extern "C" __declspec(naked) void FUN_00439390(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        push  esi
        push  edi
        call FUN_00439540
        fcom  QWORD PTR [ebp+0x40]
        fst  QWORD PTR [ebp+0x38]
        fnstsw ax
        test  ah,0x5
        jp loc_004393AC
        fst  QWORD PTR [ebp+0x48]
    loc_004393AC:
        fcom  QWORD PTR [ebp+0x48]
        fst  QWORD PTR [ebp+0x40]
        fnstsw ax
        test  ah,0x41
        jne loc_00439527
        fcomp QWORD PTR [ebp+0x48]
        fnstsw ax
        test  ah,0x41
        jne loc_004393E9
        jmp loc_004393D0
        nop
    loc_004393D0:
        fld  QWORD PTR [ebp+0x48]
        fadd  QWORD PTR ds:0x470c90
        fstp  QWORD PTR [ebp+0x48]
        fld  QWORD PTR [ebp+0x48]
        fcomp QWORD PTR [ebp+0x38]
        fnstsw ax
        test  ah,0x5
        jnp loc_004393D0
    loc_004393E9:
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  edi,0x491e94
        mov  DWORD PTR ds:0x491fac,edi
        call FUN_00421480
        mov  edx,DWORD PTR ds:0x491fac
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        add  edx,0xcc
        push  edx
        push  eax
        call  DWORD PTR [ecx+0xbc]
        mov  eax,ds:0x491be4
        push  eax
        mov  DWORD PTR ds:0x491fb0,0x1
        call FUN_00449c00
        push  0x492590
        mov  esi,eax
        call FUN_0043ddf0
        test  esi,esi
        jne loc_00439459
        mov  esi,0x492254
        call FUN_0044c150
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_00439459:
        cmp  esi,0xffffffff
        jne loc_00439473
        mov  esi,0x492254
        call FUN_0044c150
        pop  edi
        pop  esi
        mov  eax,0x2
        pop  ebp
        ret  0x4
    loc_00439473:
        mov  al,BYTE PTR [ebp+0x14]
        inc  al
        mov  BYTE PTR [ebp+0x14],al
        movzx ecx,BYTE PTR ds:0x491d66
        movsx edx,al
        inc  ecx
        cmp  ecx,edx
        jg loc_00439511
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0xa4]
        mov  eax,ds:0x491c10
        lea  ecx,[eax+0x3adacc]
        mov  DWORD PTR [eax+0x3adac8],0x0
        mov  DWORD PTR [eax+0x72dacc],ecx
        mov  DWORD PTR [eax+0x72dad0],ecx
        mov  edi,0x491c28
        mov  DWORD PTR ds:0x492378,0xff
        call FUN_00420cd0
        mov  edx,DWORD PTR ds:0x491be4
        push  edx
        call FUN_00449d40
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x104]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0xa8]
        mov  BYTE PTR [ebp+0x14],0x0
        call FUN_004391f0
    loc_00439511:
        call FUN_00439540
        fsub  QWORD PTR [ebp+0x38]
        pop  edi
        pop  esi
        fstp  QWORD PTR ds:0x4923a0
        xor  eax,eax
        pop  ebp
        ret  0x4
    loc_00439527:
        push  0x0
        fstp  st(0)
        call  DWORD PTR ds:0x4660ac
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        ret  0x4
    }
}
