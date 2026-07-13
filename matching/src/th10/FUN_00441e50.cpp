// 00441E50: FUN_00441e50
// Original size: 160 bytes, actual code: 20 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00441e50(void) {
    __asm {
        fild  DWORD PTR [edi+0x4]
        push  ebx
        push  ebp
        fmul  DWORD PTR [esp+0xc]
        call FUN_00463b2c
        fild  DWORD PTR [edi+0x8]
        mov  ebx,eax
        fmul  DWORD PTR [esp+0xc]
        call FUN_00463b2c
        fild  DWORD PTR [edi]
        mov  ebp,eax
        fmul  DWORD PTR [esp+0xc]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x8],ebp
        pop  ebp
        mov  DWORD PTR [esi],eax
        mov  DWORD PTR [esi+0x4],ebx
        mov  eax,esi
        pop  ebx
        ret  0x4
    }
}
