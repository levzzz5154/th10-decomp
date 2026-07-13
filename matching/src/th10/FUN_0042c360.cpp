// 0042C360: FUN_0042c360
// Original size: 608 bytes, actual code: 117 instructions
extern "C" void FUN_00401690(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0042c360(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        push  esi
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x46e8d4
        lea  ebx,[esp+0xc]
        mov  DWORD PTR [esp+0xc],0x0
        mov  DWORD PTR [esp+0x10],0x0
        mov  DWORD PTR [esp+0x14],0x0
        call FUN_00401690
        mov  eax,DWORD PTR [edi+0x30]
        add  esp,0x4
        dec  eax
        je loc_0042C474
        dec  eax
        je loc_0042C413
        dec  eax
        jne loc_0042C568
        mov  esi,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [esi+0x8974],0xffa0a0a0
        fld  DWORD PTR [edi+0x2c8]
        mov  DWORD PTR [esp+0x8],0x42000000
        mov  DWORD PTR [esp+0xc],0x41800000
        mov  DWORD PTR [esp+0x10],0x0
        call FUN_00463b2c
        fld  DWORD PTR [edi+0x2c4]
        push  eax
        call FUN_00463b2c
        push  eax
        push  0x46cdf4
        lea  ebx,[esp+0x14]
        call FUN_00401690
        mov  eax,ds:0x4776e0
        add  esp,0xc
        pop  esi
        mov  DWORD PTR [eax+0x8974],0xffffffff
        mov  eax,0x1
        pop  ebx
        add  esp,0xc
        ret
    loc_0042C413:
        mov  esi,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [esi+0x8974],0xffff4040
        mov  ecx,DWORD PTR [edi+0x114]
        mov  edx,DWORD PTR [edi+0x34]
        mov  eax,DWORD PTR [edx+ecx*4]
        push  eax
        push  0x46ce44
        lea  ebx,[esp+0x10]
        mov  DWORD PTR [esp+0x10],0x42000000
        mov  DWORD PTR [esp+0x14],0x41800000
        mov  DWORD PTR [esp+0x18],0x0
        call FUN_00401690
        mov  ecx,DWORD PTR ds:0x4776e0
        add  esp,0x8
        pop  esi
        mov  DWORD PTR [ecx+0x8974],0xffffffff
        mov  eax,0x1
        pop  ebx
        add  esp,0xc
        ret
    loc_0042C474:
        mov  eax,DWORD PTR [edi+0x38]
        test  eax,eax
        mov  esi,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [esp+0x8],0x42280000
        mov  DWORD PTR [esp+0xc],0x41800000
        mov  DWORD PTR [esp+0x10],0x0
        lea  ebx,[esp+0x8]
        je loc_0042C4B9
        mov  edx,DWORD PTR [edi+0x114]
        mov  eax,DWORD PTR [edi+0x34]
        mov  ecx,DWORD PTR [eax+edx*4]
        push  ecx
        push  0x46ce3c
        call FUN_00401690
        add  esp,0x8
        jmp loc_0042C4C6
    loc_0042C4B9:
        push  0x46ce2c
        call FUN_00401690
        add  esp,0x4
    loc_0042C4C6:
        mov  eax,DWORD PTR [edi+0x2d8]
        test  eax,eax
        mov  esi,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [esp+0xc],0x41d00000
        lea  ebx,[esp+0x8]
        je loc_0042C501
        mov  edx,DWORD PTR [edi+0x1ec]
        mov  eax,DWORD PTR [eax+0x8c]
        mov  ecx,DWORD PTR [eax+edx*8]
        push  ecx
        push  0x46ce24
        call FUN_00401690
        add  esp,0x8
        jmp loc_0042C50E
    loc_0042C501:
        push  0x46e8c4
        call FUN_00401690
        add  esp,0x4
    loc_0042C50E:
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x46ce14
        lea  ebx,[esp+0xc]
        mov  DWORD PTR [esp+0x10],0x42100000
        call FUN_00401690
        fild  DWORD PTR [edi+0x3c]
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x46ce10
        fmul  DWORD PTR ds:0x470c1c
        mov  DWORD PTR [esp+0x10],0x42000000
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esp+0x14]
        call FUN_00401690
        mov  edx,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [edx+0x8974],0xffffffff
        add  esp,0x8
    loc_0042C568:
        pop  esi
        mov  eax,0x1
        pop  ebx
        add  esp,0xc
        ret
    }
}
