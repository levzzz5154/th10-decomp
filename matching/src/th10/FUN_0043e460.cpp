// 0043E460: FUN_0043e460
// Original size: 320 bytes, actual code: 32 instructions

extern "C" __declspec(naked) void FUN_0043e460(void) {
    __asm {
        push  esi
        mov  esi,eax
        xor  eax,eax
        lea  ecx,[esi+0x1f88]
        jmp loc_0043E470
        nop
    loc_0043E470:
        cmp  DWORD PTR [ecx],0x0
        je loc_0043E485
        inc  eax
        add  ecx,0x10c
        cmp  eax,0x1f
        jl loc_0043E470
        pop  esi
        ret  0x8
    loc_0043E485:
        imul  eax,eax,0x10c
        lea  ecx,[eax+esi*1]
        mov  eax,DWORD PTR [esp+0x8]
        mov  DWORD PTR [ecx+0x1f88],eax
        mov  eax,DWORD PTR [esp+0xc]
        lea  esi,[ecx+0x1f94]
        mov  DWORD PTR [ecx+0x1f8c],eax
        mov  eax,edx
        sub  esi,edx
        nop
    loc_0043E4B0:
        mov  dl,BYTE PTR [eax]
        mov  BYTE PTR [esi+eax*1],dl
        inc  eax
        test  dl,dl
        jne loc_0043E4B0
        mov  DWORD PTR [ecx+0x1f90],0x0
        pop  esi
        ret  0x8
    }
}
