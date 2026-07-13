// 0043ACE0: FUN_0043ace0
// Original size: 320 bytes, actual code: 42 instructions

extern "C" __declspec(naked) void FUN_0043ace0(void) {
    __asm {
        mov  ecx,DWORD PTR [edi+0x118]
        mov  eax,DWORD PTR [edi+0x138]
        push  ebx
        xor  ebx,ebx
        push  ebp
        xor  ebp,ebp
        cmp  ecx,ebx
        mov  DWORD PTR [edi+0x2c8],0x3f800000
        mov  DWORD PTR [edi+0x2dc],ebx
        mov  DWORD PTR [edi+0x2e0],ebx
        mov  DWORD PTR [edi+0x128],ebx
        mov  DWORD PTR [edi+0x12c],ebx
        mov  DWORD PTR [edi+0x130],ebx
        mov  DWORD PTR [edi+0x134],ebx
        jle loc_0043AD61
        push  esi
    loc_0043AD25:
        mov  ecx,DWORD PTR [eax+0x10]
        mov  DWORD PTR [eax+0x14],ecx
        mov  DWORD PTR [eax+0x18],ecx
        mov  DWORD PTR [eax],0x1
        xor  esi,esi
    loc_0043AD36:
        mov  ecx,DWORD PTR [eax+0x14]
        mov  dl,BYTE PTR [ecx]
        inc  ecx
        mov  DWORD PTR [eax+0x14],ecx
        xor  ecx,ecx
        mov  cl,dl
        shl  esi,0x7
        and  ecx,0x7f
        add  esi,ecx
        test  dl,dl
        js loc_0043AD36
        mov  DWORD PTR [eax+0x4],esi
        mov  ecx,DWORD PTR [edi+0x118]
        inc  ebp
        add  eax,0x20
        cmp  ebp,ecx
        jl loc_0043AD25
        pop  esi
    loc_0043AD61:
        pop  ebp
        pop  ebx
        ret
    }
}
