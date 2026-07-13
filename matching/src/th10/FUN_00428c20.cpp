// 00428C20: FUN_00428c20
// Original size: 336 bytes, actual code: 52 instructions

extern "C" __declspec(naked) void FUN_00428c20(void) {
    __asm {
        sub  esp,0xc
        push  esi
        mov  esi,DWORD PTR [edx+0x58]
        movsx eax,BYTE PTR [esi+0x1c]
        imul  eax,eax,0x98
        fild  DWORD PTR [eax+ecx*1+0x3244]
        fmul  DWORD PTR ds:0x470b00
        fstp  DWORD PTR [esp+0x4]
        fild  DWORD PTR [eax+ecx*1+0x3248]
        lea  eax,[eax+ecx*1+0x3244]
        push  edi
        mov  edi,DWORD PTR [esp+0x8]
        fmul  DWORD PTR ds:0x470b00
        lea  eax,[edx+0x14]
        mov  ecx,eax
        mov  DWORD PTR [ecx],edi
        fstp  DWORD PTR [esp+0xc]
        mov  edi,DWORD PTR [esp+0xc]
        mov  DWORD PTR [ecx+0x4],edi
        mov  DWORD PTR [esp+0x10],0x0
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ecx+0x8],edi
        pop  edi
        fld  DWORD PTR [esi+0x4]
        pop  esi
        fsub  DWORD PTR [edx+0x20]
        fadd  DWORD PTR [eax]
        fstp  DWORD PTR [eax]
        mov  eax,DWORD PTR [edx+0x58]
        fld  DWORD PTR [eax+0x8]
        xor  eax,eax
        fsub  DWORD PTR [edx+0x24]
        fadd  DWORD PTR [edx+0x18]
        fstp  DWORD PTR [edx+0x18]
        add  esp,0xc
        ret
    }
}
