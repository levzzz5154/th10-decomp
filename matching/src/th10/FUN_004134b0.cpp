// 004134B0: FUN_004134b0
// Original size: 288 bytes, actual code: 85 instructions
extern "C" void FUN_00439540(void);

extern "C" __declspec(naked) void FUN_004134b0(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        and  esp,0xfffffff8
        push  ecx
        push  edi
        call FUN_00439540
        fcom  QWORD PTR [esi+0x14]
        fnstsw ax
        test  ah,0x5
        jp loc_004134CA
        fst  QWORD PTR [esi+0x14]
    loc_004134CA:
        fsub  QWORD PTR [esi+0x14]
        fcom  QWORD PTR ds:0x470bc0
        fnstsw ax
        test  ah,0x1
        jne loc_004135BC
        mov  eax,DWORD PTR [esi+0x20]
        fld  st(0)
        test  eax,eax
        fadd  QWORD PTR [esi+0x14]
        fstp  QWORD PTR [esi+0x14]
        fild  DWORD PTR [esi+0x20]
        jge loc_004134F6
        fadd  QWORD PTR ds:0x470b30
    loc_004134F6:
        fdivrp st(1),st
        xor  edi,edi
        fst  DWORD PTR [esi+0x34]
        fcomp DWORD PTR ds:0x470bb8
        fnstsw ax
        test  ah,0x41
        jne loc_00413565
        mov  edx,DWORD PTR [esi+0x1c]
        inc  edx
        mov  eax,edx
        cmp  eax,0x2
        mov  DWORD PTR [esi+0x1c],edx
        jne loc_00413537
        call FUN_00439540
        fst  QWORD PTR ds:0x492540
        fst  QWORD PTR ds:0x492538
        fst  QWORD PTR ds:0x492528
        fstp  QWORD PTR ds:0x492530
        jmp loc_00413568
    loc_00413537:
        cmp  eax,0x4
        jne loc_00413568
        mov  DWORD PTR ds:0x492508,edi
        mov  DWORD PTR ds:0x49250c,edi
        call FUN_00439540
        fst  QWORD PTR ds:0x492540
        fst  QWORD PTR ds:0x492538
        fst  QWORD PTR ds:0x492528
        fstp  QWORD PTR ds:0x492530
    loc_00413565:
        mov  DWORD PTR [esi+0x1c],edi
    loc_00413568:
        mov  ecx,DWORD PTR ds:0x477810
        cmp  ecx,edi
        je loc_004135AF
        test  BYTE PTR [ecx+0x58],0x14
        jne loc_004135A8
        fld  QWORD PTR [esi+0x2c]
        fadd  QWORD PTR ds:0x470bb0
        fstp  QWORD PTR [esi+0x2c]
        fld  DWORD PTR [esi+0x34]
        fcomp DWORD PTR ds:0x470ba8
        fnstsw ax
        test  ah,0x41
        jne loc_0041359F
        fld  QWORD PTR [esi+0x24]
        fadd  QWORD PTR ds:0x470bb0
        jmp loc_004135A5
    loc_0041359F:
        fld  DWORD PTR [esi+0x34]
        fadd  QWORD PTR [esi+0x24]
    loc_004135A5:
        fstp  QWORD PTR [esi+0x24]
    loc_004135A8:
        and  DWORD PTR [ecx+0x58],0xffffff7f
    loc_004135AF:
        mov  DWORD PTR [esi+0x20],edi
        mov  eax,0x1
        pop  edi
        mov  esp,ebp
        pop  ebp
        ret
    loc_004135BC:
        fstp  st(0)
        mov  eax,0x1
        pop  edi
        mov  esp,ebp
        pop  ebp
        ret
    }
}
