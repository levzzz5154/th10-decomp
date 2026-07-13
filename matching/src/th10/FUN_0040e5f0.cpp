// 0040E5F0: FUN_0040e5f0
// Original size: 176 bytes, actual code: 48 instructions
extern "C" void FUN_0040c9d0(void);
extern "C" void FUN_00412ff0(void);
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_0043dd10(void);
extern "C" void FUN_00448db0(void);

extern "C" __declspec(naked) void FUN_0040e5f0(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        mov  ebx,DWORD PTR [ebp+0x2444]
        test  ebx,ebx
        push  esi
        push  edi
        jl loc_0040E613
        mov  eax,DWORD PTR [ebp+0x1068]
        push  eax
        mov  esi,0x492590
        call FUN_0043dd10
    loc_0040E613:
        mov  eax,DWORD PTR [ebp+0x2448]
        test  eax,eax
        jl loc_0040E63E
        mov  edx,DWORD PTR [ebp+0x244c]
        push  eax
        mov  eax,ds:0x477704
        lea  ecx,[esp+0x18]
        push  ecx
        mov  ecx,DWORD PTR [eax+edx*4+0x30]
        lea  edi,[ebp+0x1068]
        push  ecx
        call FUN_00448db0
    loc_0040E63E:
        mov  eax,DWORD PTR [ebp+0x2408]
        lea  esi,[ebp+0x1068]
        add  ebp,0x2408
        test  eax,eax
        jle loc_0040E66D
        push  0x400ccccd
        push  0xbfc90fdb
        push  0xffffffff
        push  eax
        mov  eax,ds:0x477818
        mov  ecx,esi
        call FUN_0041bb00
    loc_0040E66D:
        push  ebp
        call FUN_0040c9d0
        push  0xa
        mov  edi,0x474c40
        mov  DWORD PTR [ebp+0x0],0x0
        call FUN_00412ff0
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret  0x4
    }
}
