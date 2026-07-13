// 00434C30: FUN_00434c30
// Original size: 112 bytes, actual code: 41 instructions
extern "C" void FUN_00434d10(void);
extern "C" void FUN_00434f70(void);
extern "C" void FUN_00435220(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_00434c30(void) {
    __asm {
        push  esi
        push  edi
        mov  esi,ecx
        mov  edi,eax
        call FUN_00434d10
        push  0xc
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_00434C5F
        mov  DWORD PTR [eax],0x46f230
        mov  DWORD PTR [eax+0x4],0xffffffff
        mov  DWORD PTR [eax+0x8],0x0
        jmp loc_00434C61
    loc_00434C5F:
        xor  eax,eax
    loc_00434C61:
        test  eax,eax
        mov  DWORD PTR [esi+0xc],eax
        je loc_00434C97
        push  edi
        call FUN_00434f70
        test  al,al
        je loc_00434C92
        call FUN_00435220
        test  eax,eax
        mov  DWORD PTR [esi+0x8],eax
        je loc_00434C92
        mov  ecx,DWORD PTR [esi+0xc]
        mov  esi,DWORD PTR ds:0x474908
        mov  edx,DWORD PTR [ecx]
        push  esi
        push  eax
        call  DWORD PTR [edx]
        pop  edi
        mov  al,0x1
        pop  esi
        ret
    loc_00434C92:
        call FUN_00434d10
    loc_00434C97:
        pop  edi
        xor  al,al
        pop  esi
        ret
    }
}
