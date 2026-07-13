// 00449B70: FUN_00449b70
// Original size: 144 bytes, actual code: 43 instructions

extern "C" __declspec(naked) void FUN_00449b70(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0xc]
        push  ebx
        xor  ebx,ebx
        test  eax,eax
        je loc_00449B88
        mov  ecx,DWORD PTR [esi+0x20]
        call  eax
        mov  ebx,eax
        mov  DWORD PTR [esi+0xc],0x0
    loc_00449B88:
        push  0x492274
        call  DWORD PTR ds:0x4660b0
        mov  dl,BYTE PTR ds:0x49231c
        mov  eax,DWORD PTR [esp+0x8]
        inc  dl
        mov  BYTE PTR ds:0x49231c,dl
        add  eax,0x38
        mov  DWORD PTR [esi],edi
        mov  ecx,DWORD PTR [eax+0x4]
        test  ecx,ecx
        je loc_00449BC3
    loc_00449BB1:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR [ecx]
        cmp  DWORD PTR [edx],edi
        jge loc_00449BC3
        mov  eax,ecx
        mov  ecx,DWORD PTR [eax+0x4]
        test  ecx,ecx
        jne loc_00449BB1
    loc_00449BC3:
        mov  edx,DWORD PTR [eax+0x4]
        test  edx,edx
        lea  ecx,[esi+0x14]
        je loc_00449BD6
        mov  DWORD PTR [ecx+0x4],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [edx+0x8],ecx
    loc_00449BD6:
        mov  DWORD PTR [eax+0x4],ecx
        push  0x492274
        mov  DWORD PTR [ecx+0x8],eax
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231c
        mov  eax,ebx
        pop  ebx
        ret  0x4
    }
}
