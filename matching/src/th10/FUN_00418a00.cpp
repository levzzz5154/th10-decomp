// 00418A00: FUN_00418a00
// Original size: 144 bytes, actual code: 24 instructions
extern "C" void FUN_0044bf40(void);

extern "C" __declspec(naked) void FUN_00418a00(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        push  esi
        jle loc_00418A17
        push  0xbf800000
        lea  esi,[eax+0x14]
        call FUN_0044bf40
        pop  esi
        ret
    loc_00418A17:
        mov  ecx,DWORD PTR [eax+0xc]
        mov  esi,0x1388
        cmp  ecx,esi
        jle loc_00418A3F
        mov  edx,DWORD PTR [eax+0x10]
        sub  ecx,edx
        cmp  edx,0x12
        mov  DWORD PTR [eax+0xc],ecx
        jge loc_00418A37
        mov  DWORD PTR [eax+0x10],0x12
    loc_00418A37:
        cmp  DWORD PTR [eax+0xc],esi
        jge loc_00418A3F
        mov  DWORD PTR [eax+0xc],esi
    loc_00418A3F:
        pop  esi
        ret
    }
}
