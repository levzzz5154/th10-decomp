// 00438350: FUN_00438350
// Original size: 48 bytes, actual code: 18 instructions
extern "C" void FUN_00438420(void);

extern "C" __declspec(naked) void FUN_00438350(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [esp+0x8]
        mov  eax,esi
        push  edi
        lea  edi,[eax+0x1]
        jmp loc_00438360
        nop
    loc_00438360:
        mov  dl,BYTE PTR [eax]
        inc  eax
        test  dl,dl
        jne loc_00438360
        sub  eax,edi
        push  eax
        push  esi
        call FUN_00438420
        pop  edi
        pop  esi
        ret  0x4
    }
}
