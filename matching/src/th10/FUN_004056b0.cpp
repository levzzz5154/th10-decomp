// 004056B0: FUN_004056b0
// Original size: 160 bytes, actual code: 35 instructions
extern "C" void FUN_004055c0(void);
extern "C" void FUN_00405620(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_004056b0(void) {
    __asm {
        push  ebx
        push  0x48
        call operator_new
        mov  edx,eax
        add  esp,0x4
        test  edx,edx
        je loc_004056DF
        and  DWORD PTR [edx+0x24],0xfffffffe
        push  edi
        xor  eax,eax
        mov  ecx,0x12
        mov  edi,edx
        rep stosd
        or   DWORD PTR [edx],0x2
        mov  DWORD PTR ds:0x4776ec,edx
        mov  ebx,edx
        pop  edi
        jmp loc_004056E1
    loc_004056DF:
        xor  ebx,ebx
    loc_004056E1:
        call FUN_004055c0
        test  eax,eax
        je loc_00405701
        test  ebx,ebx
        je loc_004056FD
        push  ebx
        call FUN_00405620
        push  ebx
        call _free
        add  esp,0x4
    loc_004056FD:
        xor  eax,eax
        pop  ebx
        ret
    loc_00405701:
        mov  eax,ebx
        pop  ebx
        ret
    }
}
