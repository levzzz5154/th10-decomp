// 004497D0: FUN_004497d0
// Original size: 160 bytes, actual code: 25 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_004497d0(void) {
    __asm {
        mov  eax,DWORD PTR [esi]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        jne loc_004497E4
        mov  DWORD PTR [esi],eax
    loc_004497E4:
        add  eax,0x10
        je loc_00449804
        nop
    loc_004497F0:
        mov  ecx,DWORD PTR [eax]
        movsx edx,WORD PTR [ecx+0x38a]
        cmp  edx,ebx
        je loc_0044980D
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004497F0
    loc_00449804:
        mov  DWORD PTR [edi],0x0
        mov  eax,edi
        ret
    loc_0044980D:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [edi],ecx
        mov  eax,edi
        ret
    }
}
