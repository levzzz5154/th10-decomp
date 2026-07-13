// 0044BEA0: FUN_0044bea0
// Original size: 160 bytes, actual code: 56 instructions

extern "C" __declspec(naked) void FUN_0044bea0(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [eax+0x8]
        test  esi,esi
        jle loc_0044BF1A
        push  ebx
        push  ebp
        push  edi
        mov  edi,DWORD PTR [eax+0xd4]
        lea  ebx,[eax+0x90]
    loc_0044BEB7:
        mov  ecx,DWORD PTR [esp+0x14]
        mov  edx,DWORD PTR [eax]
        add  edx,ecx
        mov  ecx,edx
        cmp  ecx,esi
        mov  DWORD PTR [eax],edx
        jl loc_0044BEE4
        mov  ecx,DWORD PTR [eax+0xd0]
        nop
    loc_0044BED0:
        test  ecx,ecx
        je loc_0044BEDA
        mov  edx,DWORD PTR [eax]
        sub  edx,esi
        jmp loc_0044BEDD
    loc_0044BEDA:
        lea  edx,[esi-0x1]
    loc_0044BEDD:
        mov  DWORD PTR [eax],edx
        cmp  edx,DWORD PTR [eax+0x8]
        jge loc_0044BED0
    loc_0044BEE4:
        cmp  DWORD PTR [eax],0x0
        jge loc_0044BF03
        mov  ecx,DWORD PTR [eax+0xd0]
        nop
    loc_0044BEF0:
        test  ecx,ecx
        je loc_0044BEF8
        add  DWORD PTR [eax],esi
        jmp loc_0044BEFE
    loc_0044BEF8:
        mov  DWORD PTR [eax],0x0
    loc_0044BEFE:
        cmp  DWORD PTR [eax],0x0
        jl loc_0044BEF0
    loc_0044BF03:
        xor  ecx,ecx
        mov  edx,ebx
    loc_0044BF07:
        cmp  ecx,edi
        jge loc_0044BF17
        mov  ebp,DWORD PTR [edx]
        cmp  ebp,DWORD PTR [eax]
        je loc_0044BEB7
        inc  ecx
        add  edx,0x4
        jmp loc_0044BF07
    loc_0044BF17:
        pop  edi
        pop  ebp
        pop  ebx
    loc_0044BF1A:
        mov  eax,DWORD PTR [eax]
        pop  esi
        ret  0x4
        and  DWORD PTR [eax+0x10],0xfffffffe
        ret
    }
}
