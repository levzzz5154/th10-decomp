// 00427C70: FUN_00427c70
// Original size: 272 bytes, actual code: 20 instructions

extern "C" __declspec(naked) void FUN_00427c70(void) {
    __asm {
        mov  eax,DWORD PTR [ecx+0x4]
        cmp  eax,DWORD PTR [ecx]
        je loc_00427C88
        cdq
        idiv  DWORD PTR [esp+0x4]
        test  edx,edx
        jne loc_00427C88
        mov  eax,0x1
        ret  0x4
    loc_00427C88:
        xor  eax,eax
        ret  0x4
    }
}
