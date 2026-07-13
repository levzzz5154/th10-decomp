// 00439540: FUN_00439540
// Original size: 496 bytes, actual code: 73 instructions

extern "C" __declspec(naked) void FUN_00439540(void) {
    __asm {
        sub  esp,0x14
        push  0x4922ec
        call  DWORD PTR ds:0x4660b0
        mov  dl,BYTE PTR ds:0x492321
        mov  eax,ds:0x492508
        mov  ecx,DWORD PTR ds:0x49250c
        inc  dl
        or   eax,ecx
        mov  BYTE PTR ds:0x492321,dl
        je loc_004395DF
        lea  ecx,[esp+0x8]
        push  ecx
        call  DWORD PTR ds:0x4660fc
        mov  eax,ds:0x492510
        mov  edx,DWORD PTR [esp+0x8]
        mov  ecx,DWORD PTR ds:0x492514
        sub  edx,eax
        mov  eax,DWORD PTR [esp+0xc]
        sbb  eax,ecx
        mov  DWORD PTR [esp+0x4],eax
        mov  DWORD PTR [esp],edx
        fild  QWORD PTR [esp]
        fild  QWORD PTR ds:0x492508
        fdivp st(1),st
        fst  QWORD PTR [esp]
        fld  QWORD PTR ds:0x492540
        fcomp st(1)
        fnstsw ax
        test  ah,0x41
        jne loc_004395B9
        fstp  QWORD PTR ds:0x492540
        jmp loc_004395BB
    loc_004395B9:
        fstp  st(0)
    loc_004395BB:
        push  0x4922ec
        call  DWORD PTR ds:0x4660b4
        fld  QWORD PTR [esp]
        mov  al,ds:0x492321
        fsub  QWORD PTR ds:0x492540
        dec  al
        mov  ds:0x492321,al
        add  esp,0x14
        ret
    loc_004395DF:
        push  0x1
        call  DWORD PTR ds:0x466278
        call  DWORD PTR ds:0x466270
        test  eax,eax
        mov  DWORD PTR [esp],eax
        fild  DWORD PTR [esp]
        jge loc_004395FD
        fadd  QWORD PTR ds:0x470b30
    loc_004395FD:
        push  0x1
        fstp  QWORD PTR [esp+0x4]
        call  DWORD PTR ds:0x466274
        fld  QWORD PTR ds:0x492540
        fcomp QWORD PTR [esp]
        fnstsw ax
        test  ah,0x41
        jne loc_00439622
        fld  QWORD PTR [esp]
        fstp  QWORD PTR ds:0x492540
    loc_00439622:
        fld  QWORD PTR ds:0x492540
        push  0x4922ec
        fmul  QWORD PTR ds:0x470b88
        fsubr QWORD PTR [esp+0x4]
        fmul  QWORD PTR ds:0x470b28
        fstp  QWORD PTR [esp+0x4]
        call  DWORD PTR ds:0x4660b4
        mov  al,ds:0x492321
        fld  QWORD PTR [esp]
        dec  al
        mov  ds:0x492321,al
        add  esp,0x14
        ret
    }
}
