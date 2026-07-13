// 00407E40: FUN_00407e40
// Original size: 176 bytes, actual code: 45 instructions
extern "C" void FUN_004061d0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0044bf40(void);

extern "C" __declspec(naked) void FUN_00407e40(void) {
    __asm {
        mov  edx,DWORD PTR [ebx+0x39c]
        mov  eax,DWORD PTR [edx+0x30]
        mov  ecx,DWORD PTR [edx+0x34]
        push  eax
        push  ecx
        lea  ecx,[ebx+0x3b4]
        call FUN_004061d0
        test  eax,eax
        je loc_00407EEB
        fld  DWORD PTR [ebx+0x3b8]
        push  esi
        fcomp QWORD PTR ds:0x470b70
        push  edi
        fnstsw ax
        test  ah,0x5
        jp loc_00407E87
        fld  DWORD PTR [edx+0x30]
        fadd  DWORD PTR [ebx+0x3b8]
        fadd  DWORD PTR ds:0x470b38
        jmp loc_00407EA9
    loc_00407E87:
        fld  DWORD PTR [ebx+0x3b8]
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x41
        jne loc_00407ED5
        fld  DWORD PTR [edx+0x30]
        fadd  DWORD PTR ds:0x470b38
        fsubr DWORD PTR [ebx+0x3b8]
    loc_00407EA9:
        lea  esi,[ebx+0x780]
        fstp  DWORD PTR [ebx+0x3b8]
        push  0xbf800000
        call FUN_0044bf40
        mov  edi,DWORD PTR [ebx+0x458]
        test  edi,edi
        jl loc_00407ED5
        mov  ecx,0x492590
        push  0x0
        call FUN_0043dc90
    loc_00407ED5:
        mov  eax,DWORD PTR [ebx+0x784]
        test  eax,eax
        pop  edi
        pop  esi
        jg loc_00407EEB
        xor  DWORD PTR [ebx+0x43c],0x200000
    loc_00407EEB:
        ret
    }
}
