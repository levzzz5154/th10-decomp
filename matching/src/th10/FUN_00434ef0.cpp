// 00434EF0: FUN_00434ef0
// Original size: 64 bytes, actual code: 28 instructions
extern "C" void __stricmp(void);

extern "C" __declspec(naked) void FUN_00434ef0(void) {
    __asm {
        push  esi
        push  edi
        mov  edi,DWORD PTR [eax]
        test  edi,edi
        je loc_00434F18
        mov  esi,DWORD PTR [eax+0x4]
        test  esi,esi
        jle loc_00434F18
        nop
    loc_00434F00:
        mov  eax,DWORD PTR [edi]
        push  eax
        push  ebx
        call __stricmp
        add  esp,0x8
        test  eax,eax
        je loc_00434F1D
        dec  esi
        add  edi,0x10
        test  esi,esi
        jg loc_00434F00
    loc_00434F18:
        pop  edi
        xor  eax,eax
        pop  esi
        ret
    loc_00434F1D:
        mov  eax,DWORD PTR [edi+0x8]
        pop  edi
        pop  esi
        ret
    }
}
