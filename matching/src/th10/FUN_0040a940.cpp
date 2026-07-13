// 0040A940: FUN_0040a940
// Original size: 736 bytes, actual code: 159 instructions
extern "C" void FUN_00401690(void);
extern "C" void FUN_0040A450(void);
extern "C" void FUN_00443080(void);
extern "C" void FUN_00463b2c(void);
extern "C" void FUN_8840EC76(void);

extern "C" __declspec(naked) void FUN_0040a940(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        push  esi
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x46ce50
        lea  ebx,[esp+0xc]
        mov  DWORD PTR [esp+0xc],0x0
        mov  DWORD PTR [esp+0x10],0x0
        mov  DWORD PTR [esp+0x14],0x0
        call FUN_00401690
        mov  eax,DWORD PTR [edi+0x30]
        add  esp,0x4
        dec  eax
        cmp  eax,0x3
        ja loc_0040ABBC
        jmp  DWORD PTR [eax*4+0x40abc8]
        mov  esi,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [esi+0x8974],0xffff4040
        mov  eax,DWORD PTR [edi+0x114]
        mov  ecx,DWORD PTR [edi+0x34]
        mov  edx,DWORD PTR [ecx+eax*4]
        push  edx
        push  0x46ce44
        lea  ebx,[esp+0x10]
        mov  DWORD PTR [esp+0x10],0x42000000
        mov  DWORD PTR [esp+0x14],0x41800000
        mov  DWORD PTR [esp+0x18],0x0
        call FUN_00401690
        mov  eax,ds:0x4776e0
        add  esp,0x8
        pop  esi
        mov  DWORD PTR [eax+0x8974],0xffffffff
        mov  eax,0x1
        pop  ebx
        add  esp,0xc
        ret
        mov  eax,DWORD PTR [edi+0x38]
        test  eax,eax
        mov  esi,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [esp+0x8],0x42280000
        mov  DWORD PTR [esp+0xc],0x41800000
        mov  DWORD PTR [esp+0x10],0x0
        lea  ebx,[esp+0x8]
        je loc_0040AA2D
        mov  ecx,DWORD PTR [edi+0x114]
        mov  edx,DWORD PTR [edi+0x34]
        mov  eax,DWORD PTR [edx+ecx*4]
        push  eax
        push  0x46ce3c
        call FUN_00401690
        add  esp,0x8
        jmp loc_0040AA3A
    loc_0040AA2D:
        push  0x46ce2c
        call FUN_00401690
        add  esp,0x4
    loc_0040AA3A:
        mov  eax,ds:0x477704
        test  eax,eax
        mov  esi,DWORD PTR ds:0x4776e0
        mov  edx,DWORD PTR [edi+0x1ec]
        mov  DWORD PTR [esp+0xc],0x41d00000
        lea  ebx,[esp+0x8]
        je loc_0040AA6F
        mov  ecx,DWORD PTR [eax+0x54]
        mov  eax,DWORD PTR [ecx+0x8c]
        mov  ecx,DWORD PTR [eax+edx*8]
        push  ecx
        push  0x46ce24
        jmp loc_0040AA75
    loc_0040AA6F:
        push  edx
        push  0x46ce1c
    loc_0040AA75:
        call FUN_00401690
        mov  esi,DWORD PTR ds:0x4776e0
        add  esp,0x8
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
        add  esp,0x8
        jmp loc_0040AB61
        mov  ecx,DWORD PTR ds:0x477704
        mov  edx,DWORD PTR [ecx+0x60]
        mov  esi,DWORD PTR ds:0x4776e0
        push  edx
        push  0x46ce04
        lea  ebx,[esp+0x10]
        mov  DWORD PTR [esp+0x10],0x43fa0000
        mov  DWORD PTR [esp+0x14],0x43700000
        mov  DWORD PTR [esp+0x18],0x0
        call FUN_00401690
        add  esp,0x8
        pop  esi
        mov  eax,0x1
        pop  ebx
        add  esp,0xc
        ret
        mov  esi,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [esi+0x8974],0xffa0a0a0
        fld  DWORD PTR [edi+0x678]
        mov  DWORD PTR [esp+0x8],0x42000000
        mov  DWORD PTR [esp+0xc],0x41800000
        mov  DWORD PTR [esp+0x10],0x0
        call FUN_00463b2c
        fld  DWORD PTR [edi+0x674]
        push  eax
        call FUN_00463b2c
        push  eax
        push  0x46cdf4
        lea  ebx,[esp+0x14]
        call FUN_00401690
        add  esp,0xc
    loc_0040AB61:
        mov  eax,ds:0x4776e0
        mov  DWORD PTR [eax+0x8974],0xffffffff
        test  BYTE PTR [edi+0x684],0x2
        je loc_0040ABBC
        mov  DWORD PTR [esp+0x8],0x43a00000
        mov  edx,DWORD PTR [esp+0x8]
        lea  ecx,[edi+0x5fc]
        mov  DWORD PTR [ecx],edx
        mov  DWORD PTR [esp+0xc],0x43700000
        mov  eax,DWORD PTR [esp+0xc]
        mov  DWORD PTR [ecx+0x4],eax
        mov  eax,ds:0x491c10
        mov  DWORD PTR [esp+0x10],0x0
        mov  edx,DWORD PTR [esp+0x10]
        lea  esi,[edi+0x2c8]
        push  eax
        mov  DWORD PTR [ecx+0x8],edx
        call FUN_00443080
    loc_0040ABBC:
        pop  esi
        mov  eax,0x1
        pop  ebx
        add  esp,0xc
        ret
    }
}
