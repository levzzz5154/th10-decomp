// 0044CE80: FUN_0044ce80
// Original size: 128 bytes, actual code: 44 instructions
extern "C" void FUN_0044d110(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0044ce80(void) {
    __asm {
        push  ebx
        mov  ebx,eax
        lea  eax,[edi*4+0x0]
        push  eax
        mov  DWORD PTR [esi],0x4705d8
        call operator_new
        mov  DWORD PTR [esi+0x4],eax
        add  esp,0x4
        xor  eax,eax
        test  edi,edi
        jbe loc_0044CEB0
    loc_0044CEA2:
        mov  edx,DWORD PTR [ebx+eax*4]
        mov  ecx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [ecx+eax*4],edx
        inc  eax
        cmp  eax,edi
        jb loc_0044CEA2
    loc_0044CEB0:
        mov  eax,DWORD PTR [esp+0x8]
        mov  ecx,DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [esi+0x8],eax
        mov  DWORD PTR [esi+0x10],edi
        mov  DWORD PTR [esi+0xc],ecx
        mov  eax,DWORD PTR [edx]
        push  0x0
        push  eax
        mov  eax,esi
        call FUN_0044d110
        xor  ebx,ebx
        test  edi,edi
        jbe loc_0044CEE9
    loc_0044CED6:
        mov  ecx,DWORD PTR [esi+0x4]
        mov  eax,DWORD PTR [ecx+ebx*4]
        mov  edx,DWORD PTR [eax]
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x34]
        inc  ebx
        cmp  ebx,edi
        jb loc_0044CED6
    loc_0044CEE9:
        mov  DWORD PTR [esi+0x30],0x0
        mov  eax,esi
        pop  ebx
        ret  0x8
    }
}
