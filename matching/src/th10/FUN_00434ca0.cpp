// 00434CA0: FUN_00434ca0
// Original size: 112 bytes, actual code: 36 instructions
extern "C" void FUN_00434d10(void);
extern "C" void FUN_00434f70(void);
extern "C" void FUN_00435220(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_00434ca0(void) {
    __asm {
        push  esi
        push  edi
        mov  esi,ecx
        mov  edi,eax
        call FUN_00434d10
        push  0x10
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_00434CD6
        mov  DWORD PTR [eax+0x4],0x0
        mov  DWORD PTR [eax+0x8],0x0
        mov  DWORD PTR [eax+0xc],0x0
        mov  DWORD PTR [eax],0x46f328
        jmp loc_00434CD8
    loc_00434CD6:
        xor  eax,eax
    loc_00434CD8:
        test  eax,eax
        mov  DWORD PTR [esi+0xc],eax
        je loc_00434CFF
        push  edi
        call FUN_00434f70
        test  al,al
        je loc_00434CFA
        call FUN_00435220
        test  eax,eax
        mov  DWORD PTR [esi+0x8],eax
        je loc_00434CFA
        pop  edi
        mov  al,0x1
        pop  esi
        ret
    loc_00434CFA:
        call FUN_00434d10
    loc_00434CFF:
        pop  edi
        xor  al,al
        pop  esi
        ret
    }
}
