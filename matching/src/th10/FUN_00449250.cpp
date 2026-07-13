// 00449250: FUN_00449250
// Original size: 80 bytes, actual code: 27 instructions
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00449250(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        push  esi
        push  eax
        call FUN_004491c0
        mov  esi,eax
        test  esi,esi
        je loc_00449298
        push  esi
        mov  WORD PTR [esi+0x304],di
        call FUN_0043ee30
        mov  eax,DWORD PTR [esi+0x18]
        test  eax,eax
        jne loc_00449298
        mov  esi,DWORD PTR [esi+0x14]
        test  esi,esi
        je loc_00449298
        nop
    loc_00449280:
        mov  ecx,DWORD PTR [esi]
        mov  WORD PTR [ecx+0x304],di
        mov  edx,DWORD PTR [esi]
        push  edx
        call FUN_0043ee30
        mov  esi,DWORD PTR [esi+0x4]
        test  esi,esi
        jne loc_00449280
    loc_00449298:
        pop  esi
        ret  0x4
    }
}
