// 0040B9F0: FUN_0040b9f0
// Original size: 160 bytes, actual code: 42 instructions
extern "C" void FUN_0040bd20(void);

extern "C" __declspec(naked) void FUN_0040b9f0(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [edi+0x18]
        call FUN_0040bd20
        test  eax,eax
        je loc_0040BA1D
        mov  eax,ds:0x491ff4
        and  eax,0x1000
        neg  eax
        sbb  eax,eax
        and  eax,0xfffffff3
        add  eax,0xf
        mov  ds:0x491fb8,eax
        mov  eax,0x1
        pop  esi
        ret
    loc_0040BA1D:
        mov  esi,DWORD PTR [edi+0x24]
        mov  ecx,DWORD PTR [edi+0x18]
        inc  esi
        mov  DWORD PTR [edi+0x24],esi
        mov  ecx,DWORD PTR [ecx+0x74]
        test  cl,0x4
        mov  eax,esi
        jne loc_0040BA58
        test  BYTE PTR [edi+0x20],0x2
        jne loc_0040BA58
        test  cl,0x2
        je loc_0040BA58
        mov  ecx,DWORD PTR ds:0x474e30
        test  ch,0x1
        je loc_0040BA58
        cdq
        mov  ecx,0xc
        idiv  ecx
        mov  eax,0x6
        test  edx,edx
        jne loc_0040BA5D
    loc_0040BA58:
        mov  eax,0x1
    loc_0040BA5D:
        pop  esi
        ret
    }
}
