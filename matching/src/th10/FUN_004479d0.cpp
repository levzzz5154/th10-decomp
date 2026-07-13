// 004479D0: FUN_004479d0
// Original size: 128 bytes, actual code: 45 instructions
extern "C" void FUN_00437db0(void);
extern "C" void FUN_00437fe0(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004479d0(void) {
    __asm {
        sub  esp,0x10
        push  ebp
        mov  ebp,DWORD PTR [esp+0x20]
        push  esi
        mov  esi,eax
        test  esi,esi
        jg loc_004479E6
        mov  esi,0x11
        jmp loc_004479EB
    loc_004479E6:
        cmp  esi,0x8
        jle loc_00447A47
    loc_004479EB:
        fld  DWORD PTR [edi+0x8]
        call FUN_00463b2c
        fld  DWORD PTR [edi+0xc]
        mov  DWORD PTR [esp+0x8],eax
        call FUN_00463b2c
        fld  DWORD PTR [edi+0x10]
        mov  DWORD PTR [esp+0xc],eax
        call FUN_00463b2c
        fld  DWORD PTR [edi+0x14]
        mov  DWORD PTR [esp+0x10],eax
        call FUN_00463b2c
        mov  ecx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x14],eax
        mov  eax,DWORD PTR [esp+0x28]
        test  eax,eax
        mov  eax,DWORD PTR [esp+0x1c]
        push  eax
        push  ebx
        push  ebp
        push  esi
        lea  edx,[esp+0x18]
        push  ecx
        push  edx
        jne loc_00447A42
        call FUN_00437db0
        pop  esi
        pop  ebp
        add  esp,0x10
        ret  0x10
    loc_00447A42:
        call FUN_00437fe0
    loc_00447A47:
        pop  esi
        pop  ebp
        add  esp,0x10
        ret  0x10
    }
}
