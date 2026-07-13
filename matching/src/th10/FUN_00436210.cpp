// 00436210: FUN_00436210
// Original size: 80 bytes, actual code: 28 instructions
extern "C" void FUN_00436260(void);
extern "C" void FUN_004362b0(void);
extern "C" void FUN_00436330(void);

extern "C" __declspec(naked) void FUN_00436210(void) {
    __asm {
        push  esi
        mov  esi,ecx
        lea  eax,[esi+esi*2]
        shl  eax,0x2
        mov  ecx,DWORD PTR [eax+0x477858]
        test  ecx,ecx
        je loc_00436238
        mov  edx,DWORD PTR [eax+0x477860]
        test  edx,edx
        jne loc_0043623A
        mov  edx,DWORD PTR [eax+0x47785c]
    loc_00436233:
        call FUN_00436260
    loc_00436238:
        pop  esi
        ret
    loc_0043623A:
        mov  ecx,DWORD PTR [eax+0x47785c]
        test  ecx,ecx
        je loc_00436233
        push  edi
        mov  eax,esi
        call FUN_00436330
        mov  edi,eax
        mov  ecx,edi
        call FUN_00436210
        mov  ecx,edi
        pop  edi
        mov  eax,esi
        pop  esi
        jmp FUN_004362b0
    }
}
