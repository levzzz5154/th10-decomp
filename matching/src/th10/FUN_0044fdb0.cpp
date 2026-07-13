// 0044FDB0: FUN_0044fdb0
// Original size: 144 bytes, actual code: 53 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0044fdb0(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        push  ebx
        push  esi
        mov  esi,DWORD PTR [edx+0x4]
        mov  ebx,0x1
        mov  ecx,eax
        push  edi
        movzx edi,WORD PTR [esi+0x8]
        shl  ebx,cl
        test  ebx,edi
        je loc_0044FE36
        mov  esi,DWORD PTR [esi+eax*4+0x10]
        test  esi,esi
        jl loc_0044FDE5
        mov  eax,DWORD PTR [edx+0x100c]
        pop  edi
        add  eax,esi
        mov  eax,DWORD PTR [eax+edx*1+0x8]
        pop  esi
        pop  ebx
        ret  0x4
    loc_0044FDE5:
        cmp  esi,0xffffffff
        jne loc_0044FE24
        mov  ecx,DWORD PTR [edx+0x1008]
        lea  esi,[ecx-0x4]
        test  esi,esi
        jl loc_0044FE3A
        mov  DWORD PTR [edx+0x1008],esi
        mov  eax,DWORD PTR [esi+edx*1+0x8]
        add  esi,0xfffffffc
        mov  DWORD PTR [edx+0x1008],esi
        cmp  BYTE PTR [esi+edx*1+0x8],0x66
        mov  DWORD PTR [esp+0x10],eax
        jne loc_0044FE3A
        fld  DWORD PTR [esp+0x10]
        call FUN_00463b2c
        pop  edi
        pop  esi
        pop  ebx
        ret  0x4
    loc_0044FE24:
        mov  ecx,DWORD PTR [edx+0x1014]
        mov  edx,DWORD PTR [ecx]
        push  esi
        call  DWORD PTR [edx+0x4]
        pop  edi
        pop  esi
        pop  ebx
        ret  0x4
    loc_0044FE36:
        mov  eax,DWORD PTR [esi+eax*4+0x10]
    loc_0044FE3A:
        pop  edi
        pop  esi
        pop  ebx
        ret  0x4
    }
}
