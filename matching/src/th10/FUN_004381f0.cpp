// 004381F0: FUN_004381f0
// Original size: 112 bytes, actual code: 14 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_004381f0(void) {
    __asm {
        push  esi
        mov  esi,ecx
        cmp  DWORD PTR [esi+0x18],0x10
        jb loc_00438205
        mov  eax,DWORD PTR [esi+0x4]
        push  eax
        call _free
        add  esp,0x4
    loc_00438205:
        xor  eax,eax
        mov  DWORD PTR [esi+0x18],0xf
        mov  DWORD PTR [esi+0x14],eax
        mov  BYTE PTR [esi+0x4],al
        pop  esi
        ret
    }
}
