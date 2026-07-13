// 00443F80: FUN_00443f80
// Original size: 48 bytes, actual code: 11 instructions
extern "C" void FUN_00442670(void);
extern "C" void FUN_00443b60(void);

extern "C" __declspec(naked) void FUN_00443f80(void) {
    __asm {
        mov  eax,esi
        call FUN_00443b60
        test  eax,eax
        je loc_00443F91
        or   eax,0xffffffff
        ret  0x4
    loc_00443F91:
        mov  ecx,DWORD PTR [esp+0x4]
        push  0x0
        mov  eax,esi
        call FUN_00442670
        ret  0x4
    }
}
