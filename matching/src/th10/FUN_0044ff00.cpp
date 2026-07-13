// 0044FF00: FUN_0044ff00
// Original size: 128 bytes, actual code: 39 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0044ff00(void) {
    __asm {
        mov  ecx,DWORD PTR [edx+0x4]
        mov  eax,DWORD PTR [esp+0x8]
        push  esi
        movzx esi,WORD PTR [ecx+0x8]
        mov  ecx,DWORD PTR [esp+0x8]
        push  edi
        mov  edi,0x1
        shl  edi,cl
        test  edi,esi
        pop  edi
        pop  esi
        je loc_0044FF79
        test  eax,eax
        jl loc_0044FF33
        lea  ecx,[edx+0x8]
        mov  edx,DWORD PTR [ecx+0x1004]
        add  edx,ecx
        mov  eax,DWORD PTR [edx+eax*1]
        ret  0x8
    loc_0044FF33:
        cmp  eax,0xffffffff
        jne loc_0044FF6D
        mov  ecx,DWORD PTR [edx+0x1008]
        add  ecx,0xfffffffc
        js loc_0044FF79
        mov  DWORD PTR [edx+0x1008],ecx
        mov  eax,DWORD PTR [ecx+edx*1+0x8]
        add  ecx,0xfffffffc
        mov  DWORD PTR [edx+0x1008],ecx
        cmp  BYTE PTR [ecx+edx*1+0x8],0x66
        mov  DWORD PTR [esp+0x8],eax
        jne loc_0044FF79
        fld  DWORD PTR [esp+0x8]
        call FUN_00463b2c
        ret  0x8
    loc_0044FF6D:
        mov  ecx,DWORD PTR [edx+0x1014]
        mov  edx,DWORD PTR [ecx]
        push  eax
        call  DWORD PTR [edx+0x4]
    loc_0044FF79:
        ret  0x8
    }
}
