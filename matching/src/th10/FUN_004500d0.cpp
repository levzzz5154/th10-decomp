// 004500D0: FUN_004500d0
// Original size: 144 bytes, actual code: 45 instructions
extern "C" void FUN_0044df70(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_004500d0(void) {
    __asm {
        push  ebx
        push  esi
        push  0x1024
        call operator_new
        xor  ebx,ebx
        add  esp,0x4
        cmp  eax,ebx
        je loc_004500F5
        mov  DWORD PTR [eax+0x1008],ebx
        mov  DWORD PTR [eax+0x100c],ebx
        mov  esi,eax
        jmp loc_004500F7
    loc_004500F5:
        xor  esi,esi
    loc_004500F7:
        push  0xc
        call operator_new
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi+0x1010],ecx
        mov  DWORD PTR [esi+0x1014],edi
        mov  DWORD PTR [esi],ebx
        mov  DWORD PTR [esi+0x4],ebx
        mov  edx,DWORD PTR [edi+0x4]
        mov  cl,BYTE PTR [edx+0x101c]
        mov  BYTE PTR [esi+0x101c],cl
        lea  ecx,[edi+0x1030]
        mov  DWORD PTR [eax],esi
        mov  DWORD PTR [eax+0x4],ebx
        mov  DWORD PTR [eax+0x8],ebx
        mov  edx,DWORD PTR [ecx+0x4]
        add  esp,0x4
        cmp  edx,ebx
        je loc_00450143
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_00450143:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
        mov  eax,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [edi+0x4]
        push  eax
        push  ecx
        mov  eax,esi
        call FUN_0044df70
        pop  esi
        pop  ebx
        ret  0x8
    }
}
