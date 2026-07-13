// 00412FF0: FUN_00412ff0
// Original size: 384 bytes, actual code: 34 instructions
extern "C" void FUN_0044bf40(void);

extern "C" __declspec(naked) void FUN_00412ff0(void) {
    __asm {
        cmp  DWORD PTR [edi+0x18],0x82
        jge loc_0041304A
        fild  DWORD PTR [esp+0x4]
        push  esi
        push  ecx
        lea  esi,[edi+0x14]
        fstp  DWORD PTR [esp]
        call FUN_0044bf40
        cmp  DWORD PTR [edi+0x18],0x82
        jle loc_00413049
        mov  eax,DWORD PTR [esi+0x10]
        test  al,0x1
        jne loc_00413035
        xor  ecx,ecx
        or   eax,0x1
        mov  DWORD PTR [esi+0x4],ecx
        mov  DWORD PTR [esi],0xfff0bdc1
        mov  DWORD PTR [esi+0x8],ecx
        mov  DWORD PTR [esi+0xc],0x476f78
        mov  DWORD PTR [esi+0x10],eax
    loc_00413035:
        mov  DWORD PTR [esi+0x4],0x82
        mov  DWORD PTR [esi+0x8],0x43020000
        mov  DWORD PTR [esi],0x81
    loc_00413049:
        pop  esi
    loc_0041304A:
        ret  0x4
    }
}
