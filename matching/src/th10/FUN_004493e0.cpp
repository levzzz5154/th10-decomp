// 004493E0: FUN_004493e0
// Original size: 112 bytes, actual code: 32 instructions

extern "C" __declspec(naked) void FUN_004493e0(void) {
    __asm {
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        push  edi
        mov  edi,0x4000000
        je loc_0044940C
    loc_004493F3:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax]
        cmp  DWORD PTR [eax+0x308],edx
        jne loc_00449406
        or   DWORD PTR [eax+0x35c],edi
    loc_00449406:
        test  ecx,ecx
        mov  eax,ecx
        jne loc_004493F3
    loc_0044940C:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_00449439
        jmp loc_00449420
        nop
        nop
    loc_00449420:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax]
        cmp  DWORD PTR [eax+0x308],edx
        jne loc_00449433
        or   DWORD PTR [eax+0x35c],edi
    loc_00449433:
        test  ecx,ecx
        mov  eax,ecx
        jne loc_00449420
    loc_00449439:
        pop  edi
        pop  esi
        ret
    }
}
