// 00434F30: FUN_00434f30
// Original size: 64 bytes, actual code: 30 instructions
extern "C" void __stricmp(void);

extern "C" __declspec(naked) void FUN_00434f30(void) {
    __asm {
        push  edi
        mov  edi,DWORD PTR [eax]
        test  edi,edi
        jne loc_00434F3B
        xor  eax,eax
        pop  edi
        ret
    loc_00434F3B:
        push  esi
        mov  esi,DWORD PTR [eax+0x4]
        test  esi,esi
        jle loc_00434F5B
    loc_00434F43:
        mov  eax,DWORD PTR [edi]
        push  eax
        push  ebx
        call __stricmp
        add  esp,0x8
        test  eax,eax
        je loc_00434F60
        dec  esi
        add  edi,0x10
        test  esi,esi
        jg loc_00434F43
    loc_00434F5B:
        pop  esi
        xor  eax,eax
        pop  edi
        ret
    loc_00434F60:
        pop  esi
        mov  eax,edi
        pop  edi
        ret
    }
}
