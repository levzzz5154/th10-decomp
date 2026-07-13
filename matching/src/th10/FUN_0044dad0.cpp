// 0044DAD0: FUN_0044dad0
// Original size: 288 bytes, actual code: 81 instructions
extern "C" void FUN_0044d110(void);
extern "C" void FUN_0044d300(void);

extern "C" __declspec(naked) void FUN_0044dad0(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [edi+0x4]
        mov  ecx,DWORD PTR [eax]
        push  ebp
        xor  ebp,ebp
        cmp  ecx,ebp
        je loc_0044DB9D
        cmp  DWORD PTR [edi+0xc],ebp
        je loc_0044DB9D
        push  ebx
        push  esi
        mov  DWORD PTR [edi+0x5c],ebp
        mov  DWORD PTR [edi+0x60],ebp
        mov  DWORD PTR [edi+0x64],ebp
        mov  DWORD PTR [edi+0x68],ebp
        mov  esi,DWORD PTR [eax]
        lea  ebx,[esp+0xc]
        call FUN_0044d300
        cmp  eax,ebp
        jl loc_0044DB98
        cmp  DWORD PTR [esp+0xc],ebp
        je loc_0044DB23
        mov  eax,DWORD PTR [edi+0x4]
        mov  ecx,DWORD PTR [eax]
        push  ebp
        push  ecx
        mov  eax,edi
        call FUN_0044d110
        cmp  eax,ebp
        jl loc_0044DB98
    loc_0044DB23:
        mov  esi,DWORD PTR [edi+0xc]
        cmp  DWORD PTR [esi+0x7c],ebp
        je loc_0044DB5B
        mov  edx,DWORD PTR [esi+0x80]
        mov  eax,DWORD PTR [esi+0x90]
        mov  DWORD PTR [esi+0x84],edx
        mov  eax,DWORD PTR [eax+0x1c]
        cmp  eax,ebp
        jle loc_0044DB8C
        mov  DWORD PTR [esi+0x88],eax
        mov  edx,DWORD PTR [edi+0x4]
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [eax]
        push  ebp
        push  eax
        call  DWORD PTR [ecx+0x34]
        pop  esi
        pop  ebx
        pop  ebp
        pop  ecx
        ret
    loc_0044DB5B:
        mov  eax,DWORD PTR [esi+0x8c]
        cmp  eax,ebp
        je loc_0044DB8C
        mov  ecx,DWORD PTR [esi+0x90]
        mov  edx,DWORD PTR [ecx+0x10]
        mov  ecx,DWORD PTR ds:0x4977a4
        push  ebp
        push  ebp
        add  edx,ecx
        push  edx
        push  eax
        call  DWORD PTR ds:0x4660c8
        mov  eax,DWORD PTR [esi+0x90]
        mov  ecx,DWORD PTR [eax+0x1c]
        mov  DWORD PTR [esi+0x8],ecx
    loc_0044DB8C:
        mov  edx,DWORD PTR [edi+0x4]
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [eax]
        push  ebp
        push  eax
        call  DWORD PTR [ecx+0x34]
    loc_0044DB98:
        pop  esi
        pop  ebx
        pop  ebp
        pop  ecx
        ret
    loc_0044DB9D:
        mov  eax,0x800401f0
        pop  ebp
        pop  ecx
        ret
    }
}
