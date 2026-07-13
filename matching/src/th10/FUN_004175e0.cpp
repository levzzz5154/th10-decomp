// 004175E0: FUN_004175e0
// Original size: 400 bytes, actual code: 15 instructions

extern "C" __declspec(naked) void FUN_004175e0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x3c]
        cmp  ecx,0x7
        jge loc_004175EC
        inc  ecx
        mov  DWORD PTR [eax+0x3c],ecx
    loc_004175EC:
        mov  eax,DWORD PTR [eax+0x3c]
        lea  eax,[eax+eax*2]
        shl  eax,0x4
        add  eax,0x474788
        mov  ds:0x477848,eax
        ret
        mov  eax,DWORD PTR [eax+0x60]
        shr  eax,0x4
        and  eax,0x1
        ret
    }
}
