// 00426520: FUN_00426520
// Original size: 240 bytes, actual code: 67 instructions
extern "C" void FUN_0044b360(void);

extern "C" __declspec(naked) void FUN_00426520(void) {
    __asm {
        push  0x0
        push  0x0
        call FUN_0044b360
        test  eax,eax
        mov  DWORD PTR [esi+0x45c],eax
        jne loc_00426537
        or   eax,0xffffffff
        ret
    loc_00426537:
        fld  QWORD PTR ds:0x470c50
        xor  edx,edx
        fsin
        fld  st(0)
        fmul  DWORD PTR [eax+0x10]
        fstp  DWORD PTR [eax+0x18]
        mov  eax,DWORD PTR [esi+0x45c]
        fld  st(0)
        fmul  DWORD PTR [eax+0x14]
        fstp  DWORD PTR [eax+0x1c]
        mov  eax,DWORD PTR [esi+0x45c]
        fld  st(0)
        fmul  DWORD PTR [eax+0x10]
        fstp  DWORD PTR [eax+0x18]
        mov  eax,DWORD PTR [esi+0x45c]
        fmul  DWORD PTR [eax+0x14]
        fstp  DWORD PTR [eax+0x1c]
        mov  eax,DWORD PTR [esi+0x45c]
        cmp  WORD PTR [eax+0x2],dx
        jbe loc_00426602
        push  ebx
        mov  ecx,0x110
        push  edi
        jmp loc_00426590
        lea  ebx,[ebx+0x0]
    loc_00426590:
        mov  eax,DWORD PTR [esi+0x45c]
        add  DWORD PTR [ecx+eax*1],eax
        mov  eax,DWORD PTR [esi+0x45c]
        mov  eax,DWORD PTR [ecx+eax*1]
        cmp  BYTE PTR [eax],0x0
        jl loc_004265EE
        jmp loc_004265B0
        nop
    loc_004265B0:
        mov  edi,DWORD PTR [eax+0x24]
        mov  edi,DWORD PTR [edi*4+0x47476c]
        mov  DWORD PTR [eax+0x24],edi
        mov  edi,DWORD PTR [eax+0x28]
        mov  edi,DWORD PTR [edi*4+0x474778]
        mov  DWORD PTR [eax+0x28],edi
        mov  edi,DWORD PTR [eax+0x2c]
        mov  edi,DWORD PTR [edi*4+0x491bf4]
        mov  DWORD PTR [eax+0x2c],edi
        mov  edi,DWORD PTR [eax+0x30]
        mov  edi,DWORD PTR [edi*4+0x491bf8]
        mov  DWORD PTR [eax+0x30],edi
        mov  bl,BYTE PTR [eax+0x34]
        add  eax,0x34
        test  bl,bl
        jge loc_004265B0
    loc_004265EE:
        mov  eax,DWORD PTR [esi+0x45c]
        movzx eax,WORD PTR [eax+0x2]
        inc  edx
        add  ecx,0x8
        cmp  edx,eax
        jl loc_00426590
        pop  edi
        pop  ebx
    loc_00426602:
        xor  eax,eax
        ret
    }
}
