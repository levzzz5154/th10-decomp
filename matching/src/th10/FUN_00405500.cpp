// 00405500: FUN_00405500
// Original size: 192 bytes, actual code: 15 instructions

extern "C" __declspec(naked) void FUN_00405500(void) {
    __asm {
        cmp  DWORD PTR [eax+0x3738],0x3c
        jl loc_00405550
        mov  edx,DWORD PTR [eax+0x378c]
        mov  DWORD PTR [eax+0x3790],0x0
        mov  ecx,0xfffffffd
        and  edx,ecx
        mov  DWORD PTR [eax+0x378c],edx
        and  DWORD PTR [eax+0xad4],ecx
        and  DWORD PTR [eax+0xe80],ecx
        and  DWORD PTR [eax+0x15d8],ecx
        and  DWORD PTR [eax+0x1984],ecx
        and  DWORD PTR [eax+0x1d30],ecx
        and  DWORD PTR [eax+0x20dc],ecx
        and  DWORD PTR [eax+0x2488],ecx
    loc_00405550:
        ret
    }
}
