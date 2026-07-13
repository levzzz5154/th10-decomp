// 0043E5A0: FUN_0043e5a0
// Original size: 368 bytes, actual code: 80 instructions

extern "C" __declspec(naked) void FUN_0043e5a0(void) {
    __asm {
        push  esi
        mov  esi,ecx
        push  edi
        mov  edi,DWORD PTR [esi+0x108]
        xor  ecx,ecx
        cmp  edi,ecx
        je loc_0043E6FE
        cmp  DWORD PTR [esi+0x124],ecx
        jne loc_0043E6FE
        mov  WORD PTR [eax+0x384],dx
        imul  edx,edx,0x44
        mov  DWORD PTR [eax+0x308],esi
        mov  esi,DWORD PTR [esi+0x118]
        add  edx,esi
        mov  DWORD PTR [eax+0x394],edx
        mov  edx,DWORD PTR [edx+0x34]
        mov  DWORD PTR [eax+0x4c],edx
        mov  edx,DWORD PTR [eax+0x394]
        mov  edx,DWORD PTR [edx+0x30]
        mov  DWORD PTR [eax+0x50],edx
        mov  DWORD PTR [eax+0x274],ecx
        mov  DWORD PTR [eax+0x270],ecx
        mov  DWORD PTR [eax+0x26c],ecx
        mov  DWORD PTR [eax+0x268],ecx
        mov  DWORD PTR [eax+0x260],ecx
        mov  DWORD PTR [eax+0x25c],ecx
        mov  DWORD PTR [eax+0x258],ecx
        mov  DWORD PTR [eax+0x254],ecx
        mov  DWORD PTR [eax+0x24c],ecx
        mov  DWORD PTR [eax+0x248],ecx
        mov  DWORD PTR [eax+0x244],ecx
        mov  DWORD PTR [eax+0x240],ecx
        lea  esi,[eax+0x23c]
        mov  edx,0x3f800000
        mov  DWORD PTR [esi+0x3c],edx
        mov  DWORD PTR [esi+0x28],edx
        mov  DWORD PTR [esi+0x14],edx
        mov  DWORD PTR [esi],edx
        mov  DWORD PTR [eax+0x2f4],ecx
        mov  DWORD PTR [eax+0x2f0],ecx
        mov  DWORD PTR [eax+0x2ec],ecx
        mov  DWORD PTR [eax+0x2e8],ecx
        mov  DWORD PTR [eax+0x2e0],ecx
        mov  DWORD PTR [eax+0x2dc],ecx
        mov  DWORD PTR [eax+0x2d8],ecx
        mov  DWORD PTR [eax+0x2d4],ecx
        mov  DWORD PTR [eax+0x2cc],ecx
        mov  DWORD PTR [eax+0x2c8],ecx
        mov  DWORD PTR [eax+0x2c4],ecx
        mov  DWORD PTR [eax+0x2c0],ecx
        mov  DWORD PTR [eax+0x2f8],edx
        mov  DWORD PTR [eax+0x2e4],edx
        mov  DWORD PTR [eax+0x2d0],edx
        mov  DWORD PTR [eax+0x2bc],edx
        mov  ecx,DWORD PTR [eax+0x394]
        fld  DWORD PTR [eax+0x4c]
        lea  edi,[eax+0x27c]
        fmul  DWORD PTR ds:0x470b7c
        fstp  DWORD PTR [esi]
        fld  DWORD PTR [eax+0x50]
        fmul  DWORD PTR ds:0x470b7c
        fstp  DWORD PTR [eax+0x250]
        fld  DWORD PTR [ecx+0x38]
        fdiv  DWORD PTR [ecx+0x1c]
        fmul  DWORD PTR [eax+0x4c]
        fstp  DWORD PTR [eax+0x2bc]
        fld  DWORD PTR [ecx+0x3c]
        fdiv  DWORD PTR [ecx+0x18]
        mov  ecx,0x10
        rep movsd
        pop  edi
        pop  esi
        fmul  DWORD PTR [eax+0x50]
        fstp  DWORD PTR [eax+0x2d0]
        xor  eax,eax
        ret
    loc_0043E6FE:
        pop  edi
        or   eax,0xffffffff
        pop  esi
        ret
    }
}
