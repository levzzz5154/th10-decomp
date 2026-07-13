// 00447940: FUN_00447940
// Original size: 144 bytes, actual code: 43 instructions

extern "C" __declspec(naked) void FUN_00447940(void) {
    __asm {
        imul  eax,eax,0x44
        push  esi
        push  edi
        mov  edi,DWORD PTR [edx+0x118]
        add  edi,eax
        mov  ecx,0x11
        mov  esi,ebx
        rep movsd
        mov  ecx,DWORD PTR [edx+0x118]
        add  ecx,eax
        pop  edi
        pop  esi
        fld  DWORD PTR [ecx+0x8]
        fdiv  DWORD PTR [ecx+0x1c]
        fstp  DWORD PTR [ecx+0x20]
        mov  ecx,DWORD PTR [edx+0x118]
        fld  DWORD PTR [ecx+eax*1+0x10]
        fdiv  DWORD PTR [ecx+eax*1+0x1c]
        add  ecx,eax
        fstp  DWORD PTR [ecx+0x28]
        mov  ecx,DWORD PTR [edx+0x118]
        fld  DWORD PTR [ecx+eax*1+0xc]
        fdiv  DWORD PTR [ecx+eax*1+0x18]
        add  ecx,eax
        fstp  DWORD PTR [ecx+0x24]
        mov  ecx,DWORD PTR [edx+0x118]
        fld  DWORD PTR [ecx+eax*1+0x14]
        fdiv  DWORD PTR [ecx+eax*1+0x18]
        add  ecx,eax
        fstp  DWORD PTR [ecx+0x2c]
        mov  ecx,DWORD PTR [edx+0x118]
        fld  DWORD PTR [ecx+eax*1+0x10]
        fsub  DWORD PTR [ecx+eax*1+0x8]
        add  ecx,eax
        fdiv  DWORD PTR [ebx+0x38]
        fstp  DWORD PTR [ecx+0x34]
        mov  edx,DWORD PTR [edx+0x118]
        fld  DWORD PTR [eax+edx*1+0x14]
        fsub  DWORD PTR [eax+edx*1+0xc]
        add  eax,edx
        fdiv  DWORD PTR [ebx+0x3c]
        fstp  DWORD PTR [eax+0x30]
        ret
    }
}
