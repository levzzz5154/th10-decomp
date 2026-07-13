// 00450690: FUN_00450690
// Original size: 64 bytes, actual code: 18 instructions

extern "C" __declspec(naked) void FUN_00450690(void) {
    __asm {
        mov  edx,DWORD PTR [eax+0x1000]
        add  ecx,edx
        cmp  ecx,0x1000
        jl loc_004506A4
        or   eax,0xffffffff
        ret
    loc_004506A4:
        push  esi
        lea  esi,[ecx+0x4]
        cmp  esi,0x1000
        mov  DWORD PTR [eax+0x1000],ecx
        jge loc_004506C6
        mov  esi,DWORD PTR [eax+0x1004]
        mov  DWORD PTR [ecx+eax*1],esi
        add  DWORD PTR [eax+0x1000],0x4
    loc_004506C6:
        mov  DWORD PTR [eax+0x1004],edx
        xor  eax,eax
        pop  esi
        ret
    }
}
