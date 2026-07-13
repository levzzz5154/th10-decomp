// 00437160: FUN_00437160
// Original size: 1520 bytes, actual code: 438 instructions
extern "C" void FUN_00436890(void);
extern "C" void _free(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_00437160(void) {
    __asm {
        mov  eax,DWORD PTR [ecx+0x110]
        mov  edx,DWORD PTR [ecx+0x120]
        imul  eax,DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [ecx+0x100]
        sub  ecx,0x15
        push  esi
        je loc_004371DF
        sub  ecx,0x4
        je loc_004371A5
        dec  ecx
        je loc_0043718B
        xor  al,al
        pop  esi
        ret  0x4
    loc_0043718B:
        mov  ecx,0x1
        cmp  eax,ecx
        jle loc_004371F7
    loc_00437194:
        xor  BYTE PTR [ecx+edx*1],0xf0
        add  ecx,0x2
        cmp  ecx,eax
        jl loc_00437194
        mov  al,0x1
        pop  esi
        ret  0x4
    loc_004371A5:
        test  eax,eax
        jle loc_004371F7
        lea  esi,[eax-0x1]
        shr  esi,1
        inc  esi
        nop
    loc_004371B0:
        xor  ecx,ecx
        mov  cx,WORD PTR [edx]
        mov  eax,ecx
        not  eax
        xor  eax,ecx
        and  eax,0x7fff
        not  ecx
        xor  eax,ecx
        test  ah,ah
        mov  WORD PTR [edx],ax
        js loc_004371D3
        and  eax,0x8000
        mov  WORD PTR [edx],ax
    loc_004371D3:
        add  edx,0x2
        dec  esi
        jne loc_004371B0
        mov  al,0x1
        pop  esi
        ret  0x4
    loc_004371DF:
        mov  esi,0x3
        cmp  eax,esi
        jle loc_004371F7
    loc_004371E8:
        mov  cl,BYTE PTR [esi+edx*1]
        not  cl
        mov  BYTE PTR [esi+edx*1],cl
        add  esi,0x4
        cmp  esi,eax
        jl loc_004371E8
    loc_004371F7:
        mov  al,0x1
        pop  esi
        ret  0x4
    }
}
