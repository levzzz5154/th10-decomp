// 0044D300: FUN_0044d300
// Original size: 112 bytes, actual code: 42 instructions

extern "C" __declspec(naked) void FUN_0044d300(void) {
    __asm {
        push  ecx
        test  esi,esi
        jne loc_0044D30C
        mov  eax,0x800401f0
        pop  ecx
        ret
    loc_0044D30C:
        test  ebx,ebx
        je loc_0044D316
        mov  DWORD PTR [ebx],0x0
    loc_0044D316:
        mov  eax,DWORD PTR [esi]
        lea  ecx,[esp]
        push  ecx
        push  esi
        call  DWORD PTR [eax+0x24]
        test  eax,eax
        jl loc_0044D360
        test  BYTE PTR [esp],0x2
        je loc_0044D35B
        push  edi
        mov  edi,DWORD PTR ds:0x4660ac
    loc_0044D331:
        mov  edx,DWORD PTR [esi]
        push  esi
        call  DWORD PTR [edx+0x50]
        cmp  eax,0x88780096
        jne loc_0044D342
        push  0xa
        call  edi
    loc_0044D342:
        mov  eax,DWORD PTR [esi]
        push  esi
        call  DWORD PTR [eax+0x50]
        test  eax,eax
        jne loc_0044D331
        test  ebx,ebx
        pop  edi
        je loc_0044D357
        mov  DWORD PTR [ebx],0x1
    loc_0044D357:
        xor  eax,eax
        pop  ecx
        ret
    loc_0044D35B:
        mov  eax,0x1
    loc_0044D360:
        pop  ecx
        ret
    }
}
