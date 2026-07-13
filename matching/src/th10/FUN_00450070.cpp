// 00450070: FUN_00450070
// Original size: 96 bytes, actual code: 37 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00450070(void) {
    __asm {
        push  esi
        push  edi
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x4]
        movzx eax,WORD PTR [edx+0x8]
        mov  edi,0x1
        shl  edi,cl
        test  edi,eax
        je loc_004500C8
        fld  DWORD PTR [edx+ecx*4+0x10]
        fcomp DWORD PTR ds:0x470b04
        fld  DWORD PTR [edx+ecx*4+0x10]
        fnstsw ax
        test  ah,0x1
        jne loc_004500B2
        add  esi,0x8
        call FUN_00463b2c
        mov  ecx,eax
        mov  eax,DWORD PTR [esi+0x1004]
        add  eax,ecx
        pop  edi
        add  eax,esi
        pop  esi
        ret
    loc_004500B2:
        mov  esi,DWORD PTR [esi+0x1014]
        mov  edi,DWORD PTR [esi]
        call FUN_00463b2c
        push  eax
        mov  ecx,esi
        call  DWORD PTR [edi+0x10]
        pop  edi
        pop  esi
        ret
    loc_004500C8:
        pop  edi
        xor  eax,eax
        pop  esi
        ret
    }
}
