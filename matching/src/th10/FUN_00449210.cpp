// 00449210: FUN_00449210
// Original size: 64 bytes, actual code: 18 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00449210(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        push  eax
        call FUN_004491c0
        test  eax,eax
        je loc_00449243
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        mov  WORD PTR [eax+0x304],si
        jne loc_00449243
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00449243
    loc_00449233:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],si
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00449233
    loc_00449243:
        ret  0x4
    }
}
