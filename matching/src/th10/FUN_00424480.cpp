// 00424480: FUN_00424480
// Original size: 464 bytes, actual code: 54 instructions
extern "C" void FUN_004491c0(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00424480(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [esp+0x8]
        mov  edx,DWORD PTR ds:0x491c10
        push  ebx
        push  ebp
        push  edi
        push  eax
        call FUN_004491c0
        mov  ebx,eax
        mov  edi,DWORD PTR [ebx+0x394]
        fld  DWORD PTR [edi+0x30]
        call FUN_00463b2c
        fld  DWORD PTR [edi+0x34]
        mov  ebp,eax
        call FUN_00463b2c
        fld  DWORD PTR [edi+0xc]
        mov  DWORD PTR [esp+0xc],eax
        call FUN_00463b2c
        fld  DWORD PTR [edi+0x8]
        mov  DWORD PTR [esp+0x14],eax
        call FUN_00463b2c
        mov  ecx,DWORD PTR [esi+0x4]
        test  ecx,ecx
        jl loc_004244D7
        pop  edi
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        pop  ecx
        ret  0x14
    loc_004244D7:
        mov  ecx,DWORD PTR [ebx+0x308]
        mov  edx,DWORD PTR [ecx]
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esi+0x4],edx
        mov  edx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esi+0x8],ecx
        mov  ecx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [esi+0x18],eax
        mov  eax,DWORD PTR [esp+0x14]
        pop  edi
        mov  DWORD PTR [esi+0xc],edx
        mov  edx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [esi+0x10],ecx
        mov  ecx,DWORD PTR [esp+0x8]
        mov  DWORD PTR [esi+0x24],ebp
        pop  ebp
        mov  DWORD PTR [esi+0x1c],eax
        mov  DWORD PTR [esi+0x14],edx
        mov  DWORD PTR [esi+0x20],ecx
        mov  DWORD PTR [esi+0x28],0x0
        xor  eax,eax
        pop  ebx
        pop  ecx
        ret  0x14
    }
}
