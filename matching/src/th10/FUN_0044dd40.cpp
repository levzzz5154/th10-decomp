// 0044DD40: FUN_0044dd40
// Original size: 208 bytes, actual code: 65 instructions

extern "C" __declspec(naked) void FUN_0044dd40(void) {
    __asm {
        push  ebx
        mov  bl,al
        mov  eax,DWORD PTR [esi+0x7c]
        test  eax,eax
        je loc_0044DD88
        mov  edx,DWORD PTR [esi+0x80]
        mov  ecx,DWORD PTR [esi+0x90]
        mov  DWORD PTR [esi+0x84],edx
        mov  eax,DWORD PTR [ecx+0x1c]
        test  eax,eax
        jle loc_0044DD69
        mov  DWORD PTR [esi+0x88],eax
    loc_0044DD69:
        test  bl,bl
        je loc_0044DDFE
        mov  ecx,DWORD PTR [ecx+0x18]
        test  ecx,ecx
        jle loc_0044DDFE
        add  ecx,edx
        mov  DWORD PTR [esi+0x84],ecx
        xor  eax,eax
        pop  ebx
        ret
    loc_0044DD88:
        mov  edx,DWORD PTR [esi+0x8c]
        test  edx,edx
        jne loc_0044DD99
        mov  eax,0x800401f0
        pop  ebx
        ret
    loc_0044DD99:
        test  bl,bl
        je loc_0044DDD6
        mov  eax,DWORD PTR [esi+0x90]
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        jle loc_0044DDD6
        mov  eax,DWORD PTR [eax+0x10]
        mov  ebx,DWORD PTR ds:0x4977a4
        push  0x0
        add  eax,ecx
        push  0x0
        add  eax,ebx
        push  eax
        push  edx
        call  DWORD PTR ds:0x4660c8
        mov  eax,DWORD PTR [esi+0x90]
        mov  ecx,DWORD PTR [eax+0x1c]
        sub  ecx,DWORD PTR [eax+0x18]
        mov  DWORD PTR [esi+0x8],ecx
        xor  eax,eax
        pop  ebx
        ret
    loc_0044DDD6:
        mov  eax,DWORD PTR [esi+0x90]
        mov  ecx,DWORD PTR [eax+0x10]
        mov  eax,ds:0x4977a4
        push  0x0
        push  0x0
        add  ecx,eax
        push  ecx
        push  edx
        call  DWORD PTR ds:0x4660c8
        mov  edx,DWORD PTR [esi+0x90]
        mov  eax,DWORD PTR [edx+0x1c]
        mov  DWORD PTR [esi+0x8],eax
    loc_0044DDFE:
        xor  eax,eax
        pop  ebx
        ret
    }
}
