// 00407DA0: FUN_00407da0
// Original size: 160 bytes, actual code: 45 instructions
extern "C" void FUN_004061d0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0044bf40(void);

extern "C" __declspec(naked) void FUN_00407da0(void) {
    __asm {
        mov  edx,DWORD PTR [ebx+0x39c]
        mov  eax,DWORD PTR [edx+0x30]
        push  eax
        mov  eax,DWORD PTR [edx+0x34]
        lea  ecx,[ebx+0x3b4]
        push  eax
        call FUN_004061d0
        test  eax,eax
        je loc_00407E33
        fld  DWORD PTR [ecx]
        push  esi
        fcomp DWORD PTR ds:0x470b40
        push  edi
        fnstsw ax
        test  ah,0x5
        jp loc_00407DDB
        fld  DWORD PTR [edx+0x34]
        fadd  DWORD PTR [ecx]
        fadd  DWORD PTR ds:0x470b54
        jmp loc_00407DF5
    loc_00407DDB:
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x41
        jne loc_00407E1D
        fld  DWORD PTR [edx+0x34]
        fadd  DWORD PTR ds:0x470b54
        fsubr DWORD PTR [ecx]
    loc_00407DF5:
        lea  esi,[ebx+0x74c]
        fstp  DWORD PTR [ecx]
        push  0xbf800000
        call FUN_0044bf40
        mov  edi,DWORD PTR [ebx+0x458]
        test  edi,edi
        jl loc_00407E1D
        mov  ecx,0x492590
        push  0x0
        call FUN_0043dc90
    loc_00407E1D:
        mov  eax,DWORD PTR [ebx+0x750]
        test  eax,eax
        pop  edi
        pop  esi
        jg loc_00407E33
        xor  DWORD PTR [ebx+0x43c],0x100000
    loc_00407E33:
        ret
    }
}
