// 0043DC90: FUN_0043dc90
// Original size: 128 bytes, actual code: 40 instructions

extern "C" __declspec(naked) void FUN_0043dc90(void) {
    __asm {
        push  ebx
        movsx ebx,WORD PTR [edi*8+0x4749ce]
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        push  esi
        xor  eax,eax
        lea  edx,[ecx+0x620]
    loc_0043DCA7:
        mov  esi,DWORD PTR [edx]
        test  esi,esi
        jl loc_0043DCDF
        cmp  esi,edi
        je loc_0043DCC0
        inc  eax
        add  edx,0x4
        cmp  eax,0xc
        jl loc_0043DCA7
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x4
    loc_0043DCC0:
        mov  edx,DWORD PTR [ecx+eax*4+0x650]
        cmp  edx,0x80
        jge loc_0043DD05
        mov  esi,eax
        shl  esi,0x7
        add  esi,edx
        mov  DWORD PTR [ecx+esi*4+0x680],ebp
        jmp loc_0043DCFE
    loc_0043DCDF:
        cmp  eax,0xc
        jge loc_0043DD05
        mov  edx,eax
        mov  DWORD PTR [ecx+eax*4+0x620],edi
        shl  edx,0x9
        mov  DWORD PTR [ecx+edi*4+0x408],ebx
        mov  DWORD PTR [edx+ecx*1+0x680],ebp
    loc_0043DCFE:
        inc  DWORD PTR [ecx+eax*4+0x650]
    loc_0043DD05:
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x4
    }
}
