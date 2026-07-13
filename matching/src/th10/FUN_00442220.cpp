// 00442220: FUN_00442220
// Original size: 224 bytes, actual code: 60 instructions

extern "C" __declspec(naked) void FUN_00442220(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [eax+0x100],esi
        xor  esi,esi
        push  edi
        xor  edi,edi
        lea  ebp,[eax+0xd4]
        mov  DWORD PTR [ebp+0x0],esi
        mov  DWORD PTR [ebp+0x4],edi
        xor  ebx,ebx
        mov  DWORD PTR [ebp+0x8],ebx
        lea  ebp,[eax+0xe0]
        mov  DWORD PTR [ebp+0x0],esi
        movzx esi,BYTE PTR [esp+0x24]
        mov  DWORD PTR [ebp+0x4],edi
        mov  DWORD PTR [ebp+0x8],ebx
        mov  DWORD PTR [eax+0x104],esi
        movzx ebx,BYTE PTR [ecx+0x2]
        movzx ebp,BYTE PTR [ecx+0x1]
        movzx ecx,BYTE PTR [ecx]
        movzx esi,BYTE PTR [edx+0x2]
        movzx edi,BYTE PTR [edx+0x1]
        movzx edx,BYTE PTR [edx]
        mov  DWORD PTR [esp+0x10],ecx
        lea  ecx,[eax+0xbc]
        mov  DWORD PTR [ecx],edx
        mov  DWORD PTR [ecx+0x4],edi
        mov  DWORD PTR [ecx+0x8],esi
        mov  ecx,DWORD PTR [esp+0x10]
        lea  edx,[eax+0xc8]
        mov  DWORD PTR [edx],ecx
        mov  DWORD PTR [edx+0x4],ebp
        pop  edi
        mov  DWORD PTR [edx+0x8],ebx
        mov  ecx,DWORD PTR [eax+0xfc]
        pop  esi
        pop  ebp
        xor  edx,edx
        test  cl,0x1
        pop  ebx
        jne loc_004422D4
        or   ecx,0x1
        mov  DWORD PTR [eax+0xf0],edx
        mov  DWORD PTR [eax+0xec],0xfff0bdc1
        mov  DWORD PTR [eax+0xf4],edx
        mov  DWORD PTR [eax+0xf8],0x476f78
        mov  DWORD PTR [eax+0xfc],ecx
    loc_004422D4:
        mov  DWORD PTR [eax+0xf0],edx
        mov  DWORD PTR [eax+0xf4],edx
        mov  DWORD PTR [eax+0xec],0xffffffff
        add  esp,0xc
        ret  0x8
        mov  BYTE PTR [eax],cl
        mov  cl,BYTE PTR [esp+0x4]
        mov  BYTE PTR [eax+0x1],dl
        mov  BYTE PTR [eax+0x2],cl
        ret  0x4
    }
}
