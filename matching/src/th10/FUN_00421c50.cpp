// 00421C50: FUN_00421c50
// Original size: 208 bytes, actual code: 6 instructions

extern "C" __declspec(naked) void FUN_00421c50(void) {
    __asm {
        lea  eax,[esi+esi*2]
        lea  ecx,[edi+eax*8+0x64c]
        push  ecx
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR [esi+edi*1+0x6f4]
        ret
    }
}
