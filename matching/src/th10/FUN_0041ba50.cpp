// 0041BA50: FUN_0041ba50
// Original size: 176 bytes, actual code: 55 instructions
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_00448db0(void);

extern "C" __declspec(naked) void FUN_0041ba50(void) {
    __asm {
        push  ecx
        push  ebp
        push  edi
        lea  edi,[esi+0x3c0]
        mov  ebp,0x96
        mov  edi,edi
    loc_0041BA60:
        mov  eax,DWORD PTR [edi+0x30]
        test  eax,eax
        je loc_0041BAE2
        mov  eax,DWORD PTR [edi+0x34]
        cmp  eax,0x1
        je loc_0041BA74
        cmp  eax,0x4
        jne loc_0041BAE2
    loc_0041BA74:
        cmp  eax,0x1
        mov  DWORD PTR [edi+0x30],0x0
        jne loc_0041BA90
        push  0x400ccccd
        push  0xbfc90fdb
        push  0xffffffff
        push  0x9
        jmp loc_0041BABD
    loc_0041BA90:
        cmp  eax,0x4
        jne loc_0041BAA5
        push  0x400ccccd
        push  0xbfc90fdb
        push  0xffffffff
        push  0x9
        jmp loc_0041BABD
    loc_0041BAA5:
        cmp  eax,0xa
        je loc_0041BAAF
        cmp  eax,0xb
        jne loc_0041BAE2
    loc_0041BAAF:
        push  0x400ccccd
        push  0xbfc90fdb
        push  0xffffffff
        push  0x5
    loc_0041BABD:
        mov  eax,esi
        mov  ecx,edi
        call FUN_0041bb00
        mov  ecx,DWORD PTR ds:0x4776f0
        mov  edx,DWORD PTR [ecx+0x3e0b50]
        push  0x189
        lea  eax,[esp+0xc]
        push  eax
        push  edx
        call FUN_00448db0
    loc_0041BAE2:
        add  edi,0x3f0
        dec  ebp
        jne loc_0041BA60
        pop  edi
        xor  eax,eax
        pop  ebp
        pop  ecx
        ret
    }
}
