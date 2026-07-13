// 004506D0: FUN_004506d0
// Original size: 48 bytes, actual code: 10 instructions

extern "C" __declspec(naked) void FUN_004506d0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x1000]
        add  ecx,0xfffffffc
        mov  edx,DWORD PTR [eax+0x1004]
        js loc_004506F0
        mov  DWORD PTR [eax+0x1000],ecx
        mov  ecx,DWORD PTR [ecx+eax*1]
        mov  DWORD PTR [eax+0x1004],ecx
    loc_004506F0:
        mov  DWORD PTR [eax+0x1000],edx
        xor  eax,eax
        ret
    }
}
