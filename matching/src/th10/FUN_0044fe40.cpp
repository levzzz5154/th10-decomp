// 0044FE40: FUN_0044fe40
// Original size: 192 bytes, actual code: 68 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0044fe40(void) {
    __asm {
        push  ecx
        push  esi
        push  edi
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x4]
        movzx eax,WORD PTR [edx+0x8]
        mov  edi,0x1
        shl  edi,cl
        test  edi,eax
        je loc_0044FEEF
        fld  DWORD PTR [edx+ecx*4+0x10]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_0044FE83
        fld  DWORD PTR [edx+ecx*4+0x10]
        call FUN_00463b2c
        add  eax,DWORD PTR [esi+0x100c]
        fld  DWORD PTR [eax+esi*1+0x8]
        pop  edi
        pop  esi
        pop  ecx
        ret
    loc_0044FE83:
        fld  DWORD PTR ds:0x470b60
        fld  DWORD PTR [edx+ecx*4+0x10]
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0044FED4
        mov  eax,DWORD PTR [esi+0x1008]
        add  eax,0xfffffffc
        js loc_0044FECC
        mov  DWORD PTR [esi+0x1008],eax
        mov  ecx,DWORD PTR [eax+esi*1+0x8]
        add  eax,0xfffffffc
        mov  DWORD PTR [esi+0x1008],eax
        mov  al,BYTE PTR [eax+esi*1+0x8]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x8],ecx
        je loc_0044FECC
        cmp  al,0x69
        jne loc_0044FECC
        fild  DWORD PTR [esp+0x8]
        pop  edi
        pop  esi
        pop  ecx
        ret
    loc_0044FECC:
        fld  DWORD PTR [esp+0x8]
        pop  edi
        pop  esi
        pop  ecx
        ret
    loc_0044FED4:
        mov  esi,DWORD PTR [esi+0x1014]
        fld  DWORD PTR [edx+ecx*4+0x10]
        mov  edi,DWORD PTR [esi]
        call FUN_00463b2c
        push  eax
        mov  ecx,esi
        call  DWORD PTR [edi+0xc]
        pop  edi
        pop  esi
        pop  ecx
        ret
    loc_0044FEEF:
        fld  DWORD PTR [edx+ecx*4+0x10]
        pop  edi
        pop  esi
        pop  ecx
        ret
    }
}
