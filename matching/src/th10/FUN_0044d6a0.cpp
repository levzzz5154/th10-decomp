// 0044D6A0: FUN_0044d6a0
// Original size: 112 bytes, actual code: 37 instructions
extern "C" void FUN_0044d110(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0044d6a0(void) {
    __asm {
        push  edi
        push  0x4
        mov  DWORD PTR [esi],0x4705d8
        call operator_new
        mov  ecx,DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi+0x4],eax
        mov  DWORD PTR [eax],ecx
        mov  eax,DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esi+0x4]
        add  esp,0x4
        mov  DWORD PTR [esi+0xc],eax
        mov  DWORD PTR [esi+0x8],edx
        mov  DWORD PTR [esi+0x10],0x1
        mov  edx,DWORD PTR [ecx]
        xor  edi,edi
        push  edi
        push  edx
        mov  eax,esi
        call FUN_0044d110
        mov  eax,DWORD PTR [esi+0x4]
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        push  edi
        push  eax
        call  DWORD PTR [ecx+0x34]
        mov  edx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esi+0x30],edi
        mov  DWORD PTR [esi+0x5c],edi
        mov  DWORD PTR [esi+0x60],edi
        mov  DWORD PTR [esi+0x64],edi
        mov  DWORD PTR [esi+0x68],edi
        mov  DWORD PTR [esi],0x4705d4
        mov  DWORD PTR [esi+0x6c],edx
        mov  eax,esi
        pop  edi
        ret  0x10
    }
}
