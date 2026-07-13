// 0044BE70: FUN_0044be70
// Original size: 48 bytes, actual code: 13 instructions

extern "C" __declspec(naked) void FUN_0044be70(void) {
    __asm {
        dec  DWORD PTR [eax+0x8c]
        mov  edx,0x0
        jns loc_0044BE83
        mov  DWORD PTR [eax+0x8c],edx
    loc_0044BE83:
        mov  ecx,DWORD PTR [eax+0x8c]
        push  esi
        mov  esi,DWORD PTR [eax+ecx*4+0xc]
        mov  DWORD PTR [eax],esi
        mov  ecx,DWORD PTR [eax+ecx*4+0x4c]
        mov  DWORD PTR [eax+0x8],ecx
        mov  DWORD PTR [eax+0xd4],edx
        pop  esi
        ret
    }
}
