// 00450030: FUN_00450030
// Original size: 64 bytes, actual code: 23 instructions

extern "C" __declspec(naked) void FUN_00450030(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x4]
        movzx edx,WORD PTR [eax+0x8]
        push  edi
        mov  edi,0x1
        shl  edi,cl
        test  edi,edx
        pop  edi
        je loc_00450067
        mov  edx,DWORD PTR [eax+ecx*4+0x10]
        test  edx,edx
        jl loc_0045005A
        mov  eax,DWORD PTR [esi+0x100c]
        lea  ecx,[esi+0x8]
        add  eax,edx
        add  eax,ecx
        ret
    loc_0045005A:
        mov  ecx,DWORD PTR [esi+0x1014]
        mov  eax,DWORD PTR [ecx]
        push  edx
        call  DWORD PTR [eax+0x8]
        ret
    loc_00450067:
        xor  eax,eax
        ret
    }
}
