// 00450190: FUN_00450190
// Original size: 32 bytes, actual code: 12 instructions

extern "C" __declspec(naked) void FUN_00450190(void) {
    __asm {
        mov  eax,DWORD PTR [eax+0x1034]
        xor  edx,edx
        cmp  eax,edx
        je loc_004501AE
        nop
    loc_004501A0:
        mov  ecx,DWORD PTR [eax+0x4]
        cmp  ecx,edx
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [eax+0x4],edx
        mov  eax,ecx
        jne loc_004501A0
    loc_004501AE:
        ret
    }
}
