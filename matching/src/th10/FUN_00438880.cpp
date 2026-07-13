// 00438880: FUN_00438880
// Original size: 432 bytes, actual code: 31 instructions
extern "C" void FUN_00449e50(void);
extern "C" void FUN_0044c150(void);

extern "C" __declspec(naked) void FUN_00438880(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x465363
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  esi
        push  edi
        mov  edi,DWORD PTR [esp+0x18]
        mov  esi,0x492254
        mov  DWORD PTR [esp+0x10],0x1
        call FUN_0044c150
        push  edi
        mov  eax,edi
        call FUN_00449e50
        lea  esi,[edi+0x24]
        push  edi
        mov  eax,esi
        call FUN_00449e50
        mov  ecx,DWORD PTR [esp+0x8]
        xor  eax,eax
        mov  DWORD PTR [esi+0x8],eax
        mov  DWORD PTR [esi+0xc],eax
        mov  DWORD PTR [esi+0x10],eax
        mov  DWORD PTR [edi+0x8],eax
        mov  DWORD PTR [edi+0xc],eax
        mov  DWORD PTR [edi+0x10],eax
        pop  edi
        mov  DWORD PTR fs:0x0,ecx
        pop  esi
        add  esp,0xc
        ret  0x4
    }
}
