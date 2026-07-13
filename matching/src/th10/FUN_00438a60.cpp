// 00438A60: FUN_00438a60
// Original size: 112 bytes, actual code: 49 instructions
extern "C" void FUN_00448270(void);
extern "C" void FUN_00448450(void);

extern "C" __declspec(naked) void FUN_00438a60(void) {
    __asm {
        push  ebx
        mov  ebx,DWORD PTR [esi+0x4]
        test  ebx,ebx
        jl loc_00438A99
        mov  eax,DWORD PTR [esi+0x24]
        mov  ecx,DWORD PTR [esi+0x20]
        mov  edx,DWORD PTR [esi+0x1c]
        push  eax
        mov  eax,DWORD PTR [esi+0x18]
        push  ecx
        mov  ecx,DWORD PTR [esi+0x14]
        push  edx
        mov  edx,DWORD PTR [esi+0x10]
        push  eax
        mov  eax,DWORD PTR [esi+0xc]
        push  ecx
        mov  ecx,DWORD PTR [esi+0x8]
        push  edx
        push  eax
        mov  eax,DWORD PTR [esi+0x28]
        push  ecx
        mov  ecx,esi
        call FUN_00448270
        mov  DWORD PTR [esi+0x4],0xffffffff
    loc_00438A99:
        mov  eax,DWORD PTR [esi]
        test  eax,eax
        pop  ebx
        jl loc_00438ACE
        mov  edx,DWORD PTR [esi+0x48]
        mov  ecx,DWORD PTR [esi+0x44]
        push  edx
        mov  edx,DWORD PTR [esi+0x40]
        push  ecx
        mov  ecx,DWORD PTR [esi+0x3c]
        push  edx
        mov  edx,DWORD PTR [esi+0x38]
        push  ecx
        mov  ecx,DWORD PTR [esi+0x34]
        push  edx
        mov  edx,DWORD PTR [esi+0x30]
        push  ecx
        mov  ecx,DWORD PTR [esi+0x2c]
        push  edx
        push  ecx
        push  eax
        mov  eax,esi
        call FUN_00448450
        mov  DWORD PTR [esi],0xffffffff
    loc_00438ACE:
        ret
    }
}
