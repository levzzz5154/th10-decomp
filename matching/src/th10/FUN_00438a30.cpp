// 00438A30: FUN_00438a30
// Original size: 48 bytes, actual code: 19 instructions

extern "C" __declspec(naked) void FUN_00438a30(void) {
    __asm {
        push  esi
        mov  esi,eax
        push  edi
        add  esi,0x3ad4e0
        mov  edi,0x20
        nop
    loc_00438A40:
        mov  eax,DWORD PTR [esi]
        test  eax,eax
        je loc_00438A52
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esi],0x0
    loc_00438A52:
        add  esi,0x4
        dec  edi
        jne loc_00438A40
        pop  edi
        pop  esi
        ret
    }
}
