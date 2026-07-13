// 00446EB0: FUN_00446eb0
// Original size: 144 bytes, actual code: 48 instructions
extern "C" void FUN_004465b0(void);
extern "C" void D3DXCreateTextureFromFileInMemoryEx(void);

extern "C" __declspec(naked) void FUN_00446eb0(void) {
    __asm {
        push  edi
        mov  edi,eax
        test  BYTE PTR ds:0x491d78,0x1
        je loc_00446EDD
        mov  eax,DWORD PTR [edi*4+0x46f288]
        cmp  eax,0x15
        je loc_00446ED8
        test  eax,eax
        je loc_00446ED8
        cmp  eax,0x14
        jne loc_00446EDD
        mov  edi,0x3
        jmp loc_00446EDD
    loc_00446ED8:
        mov  edi,0x5
    loc_00446EDD:
        mov  eax,DWORD PTR [esp+0xc]
        mov  ecx,DWORD PTR [edi*4+0x46f288]
        push  esi
        push  0x0
        push  0x0
        push  eax
        mov  eax,DWORD PTR [esp+0x20]
        push  0xffffffff
        push  0x1
        push  0x1
        push  ecx
        mov  ecx,DWORD PTR [esi+0x8]
        push  0x0
        push  0x0
        push  edx
        mov  edx,DWORD PTR [esi+0x4]
        push  eax
        mov  eax,ds:0x491c30
        push  ecx
        push  edx
        push  eax
        call D3DXCreateTextureFromFileInMemoryEx
        test  eax,eax
        je loc_00446F1D
        or   eax,0xffffffff
        pop  edi
        ret  0xc
    loc_00446F1D:
        mov  eax,esi
        call FUN_004465b0
        mov  ecx,DWORD PTR [edi*4+0x46f2a0]
        mov  DWORD PTR [esi+0xc],ecx
        xor  eax,eax
        pop  edi
        ret  0xc
    }
}
