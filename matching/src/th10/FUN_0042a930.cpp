// 0042A930: FUN_0042a930
// Original size: 288 bytes, actual code: 19 instructions

extern "C" __declspec(naked) void FUN_0042a930(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x24]
        test  cl,0x1
        push  esi
        mov  esi,DWORD PTR [esp+0x8]
        jne loc_0042A959
        xor  edx,edx
        or   ecx,0x1
        mov  DWORD PTR [eax+0x18],edx
        mov  DWORD PTR [eax+0x14],0xfff0bdc1
        mov  DWORD PTR [eax+0x1c],edx
        mov  DWORD PTR [eax+0x20],0x476f78
        mov  DWORD PTR [eax+0x24],ecx
    loc_0042A959:
        fild  DWORD PTR [esp+0x8]
        mov  DWORD PTR [eax+0x18],esi
        dec  esi
        mov  DWORD PTR [eax+0x14],esi
        fstp  DWORD PTR [eax+0x1c]
        pop  esi
        ret  0x4
    }
}
