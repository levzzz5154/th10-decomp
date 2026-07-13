// 00405BE0: FUN_00405be0
// Original size: 288 bytes, actual code: 39 instructions

extern "C" __declspec(naked) void FUN_00405be0(void) {
    __asm {
        xor  edx,edx
        mov  WORD PTR [eax+0x446],dx
        mov  ecx,DWORD PTR [eax+0x408]
        test  cl,0x1
        jne loc_00405C1D
        or   ecx,0x1
        mov  DWORD PTR [eax+0x3fc],edx
        mov  DWORD PTR [eax+0x3f8],0xfff0bdc1
        mov  DWORD PTR [eax+0x400],edx
        mov  DWORD PTR [eax+0x404],0x476f78
        mov  DWORD PTR [eax+0x408],ecx
    loc_00405C1D:
        mov  DWORD PTR [eax+0x3fc],edx
        mov  DWORD PTR [eax+0x400],edx
        mov  DWORD PTR [eax+0x3f8],0xffffffff
        mov  ecx,DWORD PTR [eax+0x41c]
        test  cl,0x1
        jne loc_00405C67
        or   ecx,0x1
        mov  DWORD PTR [eax+0x410],edx
        mov  DWORD PTR [eax+0x40c],0xfff0bdc1
        mov  DWORD PTR [eax+0x414],edx
        mov  DWORD PTR [eax+0x418],0x476f78
        mov  DWORD PTR [eax+0x41c],ecx
    loc_00405C67:
        mov  DWORD PTR [eax+0x410],edx
        mov  DWORD PTR [eax+0x414],edx
        mov  DWORD PTR [eax+0x40c],0xffffffff
        ret
    }
}
