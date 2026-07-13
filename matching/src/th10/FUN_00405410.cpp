// 00405410: FUN_00405410
// Original size: 160 bytes, actual code: 19 instructions

extern "C" __declspec(naked) void FUN_00405410(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x10]
        test  cl,0x1
        push  esi
        mov  esi,DWORD PTR [esp+0x8]
        jne loc_00405438
        xor  edx,edx
        or   ecx,0x1
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [eax],0xfff0bdc1
        mov  DWORD PTR [eax+0x8],edx
        mov  DWORD PTR [eax+0xc],0x476f78
        mov  DWORD PTR [eax+0x10],ecx
    loc_00405438:
        fild  DWORD PTR [esp+0x8]
        mov  DWORD PTR [eax+0x4],esi
        dec  esi
        mov  DWORD PTR [eax],esi
        fstp  DWORD PTR [eax+0x8]
        pop  esi
        ret  0x4
    }
}
