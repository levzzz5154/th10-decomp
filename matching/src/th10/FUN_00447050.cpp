// 00447050: FUN_00447050
// Original size: 112 bytes, actual code: 15 instructions
extern "C" void D3DXCreateTexture(void);

extern "C" __declspec(naked) void FUN_00447050(void) {
    __asm {
        mov  eax,DWORD PTR [esi*4+0x46f288]
        push  edi
        push  0x1
        push  eax
        mov  eax,ds:0x491c30
        push  0x0
        push  0x1
        push  ecx
        push  edx
        push  eax
        call D3DXCreateTexture
        mov  ecx,DWORD PTR [esi*4+0x46f2a0]
        mov  DWORD PTR [edi+0xc],ecx
        xor  eax,eax
        ret
    }
}
