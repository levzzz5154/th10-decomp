// 00401530: FUN_00401530
// Original size: 256 bytes, actual code: 40 instructions

extern "C" __declspec(naked) void FUN_00401530(void) {
    __asm {
        mov  edx,DWORD PTR [ecx+0x896c]
        cmp  edx,0x100
        push  esi
        mov  esi,eax
        jge loc_004015B2
        mov  eax,edx
        imul  eax,eax,0x68
        push  edi
        lea  eax,[eax+ecx*1+0x76c]
        inc  edx
        mov  edi,eax
        mov  DWORD PTR [ecx+0x896c],edx
        sub  edi,esi
        nop
    loc_00401560:
        mov  dl,BYTE PTR [esi]
        mov  BYTE PTR [edi+esi*1],dl
        inc  esi
        test  dl,dl
        jne loc_00401560
        mov  esi,DWORD PTR [ebx]
        lea  edx,[eax+0x40]
        mov  DWORD PTR [edx],esi
        mov  esi,DWORD PTR [ebx+0x4]
        mov  DWORD PTR [edx+0x4],esi
        mov  esi,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [edx+0x8],esi
        mov  edx,DWORD PTR [ecx+0x8974]
        mov  DWORD PTR [eax+0x4c],edx
        mov  edx,DWORD PTR [ecx+0x8978]
        mov  DWORD PTR [eax+0x50],edx
        mov  edx,DWORD PTR [ecx+0x897c]
        mov  DWORD PTR [eax+0x54],edx
        mov  edx,DWORD PTR [ecx+0x8980]
        mov  DWORD PTR [eax+0x5c],edx
        mov  DWORD PTR [eax+0x60],0x0
        mov  ecx,DWORD PTR [ecx+0x8988]
        mov  DWORD PTR [eax+0x64],ecx
        pop  edi
    loc_004015B2:
        pop  esi
        ret
    }
}
