// 0044FF80: FUN_0044ff80
// Original size: 176 bytes, actual code: 54 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0044ff80(void) {
    __asm {
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x4]
        movzx edx,WORD PTR [eax+0x8]
        mov  eax,0x1
        shl  eax,cl
        test  eax,edx
        je loc_00450006
        fld  DWORD PTR [esp+0x8]
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x1
        jne loc_0044FFBD
        fld  DWORD PTR [esp+0x8]
        call FUN_00463b2c
        add  eax,DWORD PTR [esi+0x100c]
        fld  DWORD PTR [eax+esi*1+0x8]
        pop  esi
        ret  0x4
    loc_0044FFBD:
        fld  DWORD PTR ds:0x470b60
        fld  DWORD PTR [esp+0x8]
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0045000E
        mov  eax,DWORD PTR [esi+0x1008]
        add  eax,0xfffffffc
        js loc_00450006
        mov  DWORD PTR [esi+0x1008],eax
        mov  ecx,DWORD PTR [eax+esi*1+0x8]
        add  eax,0xfffffffc
        mov  DWORD PTR [esi+0x1008],eax
        mov  al,BYTE PTR [eax+esi*1+0x8]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x8],ecx
        je loc_00450006
        cmp  al,0x69
        jne loc_00450006
        fild  DWORD PTR [esp+0x8]
        fstp  DWORD PTR [esp+0x8]
    loc_00450006:
        fld  DWORD PTR [esp+0x8]
        pop  esi
        ret  0x4
    loc_0045000E:
        mov  esi,DWORD PTR [esi+0x1014]
        fld  DWORD PTR [esp+0x8]
        push  edi
        mov  edi,DWORD PTR [esi]
        call FUN_00463b2c
        push  eax
        mov  ecx,esi
        call  DWORD PTR [edi+0xc]
        pop  edi
        pop  esi
        ret  0x4
    }
}
