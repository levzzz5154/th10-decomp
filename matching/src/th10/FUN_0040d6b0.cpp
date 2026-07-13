// 0040D6B0: FUN_0040d6b0
// Original size: 160 bytes, actual code: 47 instructions
extern "C" void FUN_0040d280(void);
extern "C" void FUN_0040d530(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040d6b0(void) {
    __asm {
        push  ebx
        push  0x68
        call operator_new
        mov  edx,eax
        add  esp,0x4
        test  edx,edx
        je loc_0040D6DF
        and  DWORD PTR [edx+0x50],0xfffffffe
        push  edi
        xor  eax,eax
        mov  ecx,0x1a
        mov  edi,edx
        rep stosd
        or   DWORD PTR [edx],0x2
        mov  DWORD PTR ds:0x477704,edx
        mov  ebx,edx
        pop  edi
        jmp loc_0040D6E1
    loc_0040D6DF:
        xor  ebx,ebx
    loc_0040D6E1:
        mov  eax,DWORD PTR [esp+0x8]
        push  eax
        call FUN_0040d280
        test  eax,eax
        je loc_0040D709
        test  ebx,ebx
        je loc_0040D703
        mov  eax,ebx
        call FUN_0040d530
        push  ebx
        call _free
        add  esp,0x4
    loc_0040D703:
        xor  eax,eax
        pop  ebx
        ret  0x4
    loc_0040D709:
        mov  eax,ebx
        pop  ebx
        ret  0x4
    }
}
