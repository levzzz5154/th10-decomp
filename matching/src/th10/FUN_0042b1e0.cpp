// 0042B1E0: FUN_0042b1e0
// Original size: 592 bytes, actual code: 188 instructions
extern "C" void FUN_004359b0(void);
extern "C" void FUN_0044b220(void);
extern "C" void FUN_0044b620(void);
extern "C" void _free(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_0042b1e0(void) {
    __asm {
        mov  eax,DWORD PTR [ebx]
        sub  esp,0xc
        test  eax,eax
        jne loc_0042B1F0
        or   eax,0xffffffff
        add  esp,0xc
        ret
    loc_0042B1F0:
        push  ebp
        push  0x200000
        call _malloc
        mov  ecx,DWORD PTR [ebx]
        mov  edx,DWORD PTR [ecx]
        mov  DWORD PTR [esp+0x8],eax
        mov  DWORD PTR [eax],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [eax+0x8],edx
        mov  edx,DWORD PTR [ecx+0xc]
        mov  DWORD PTR [eax+0xc],edx
        mov  edx,DWORD PTR [ecx+0x10]
        mov  DWORD PTR [eax+0x10],edx
        mov  ecx,DWORD PTR [ecx+0x14]
        add  esp,0x4
        mov  DWORD PTR [eax+0x14],ecx
        mov  ebp,0x18
        xor  eax,eax
        push  esi
        mov  DWORD PTR [esp+0xc],ebp
        mov  DWORD PTR [esp+0x10],eax
        lea  edx,[ebx+0x14]
        push  edi
        lea  ebx,[ebx+0x0]
    loc_0042B240:
        cmp  WORD PTR [edx-0xc],0x5243
        jne loc_0042B2A3
        mov  DWORD PTR [edx],eax
        xor  ecx,ecx
        mov  eax,edx
        mov  edi,0xb3e
    loc_0042B253:
        movzx ebp,BYTE PTR [eax-0x3]
        movzx esi,BYTE PTR [eax-0x4]
        add  esi,ebp
        movzx ebp,BYTE PTR [eax-0x2]
        add  esi,ebp
        movzx ebp,BYTE PTR [eax-0x1]
        add  esi,ebp
        movzx ebp,BYTE PTR [eax+0x1]
        add  esi,ebp
        movzx ebp,BYTE PTR [eax]
        add  ebp,ecx
        add  eax,0x6
        dec  edi
        lea  ecx,[esi+ebp*1]
        jne loc_0042B253
        mov  ebp,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0xc]
        lea  edi,[eax+ebp*1]
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [edx-0x8],ecx
        mov  ecx,0x10df
        lea  esi,[edx-0xc]
        add  ebp,0x437c
        rep movsd
        mov  DWORD PTR [esp+0x10],ebp
    loc_0042B2A3:
        inc  eax
        add  edx,0x437c
        cmp  eax,0x7
        mov  DWORD PTR [esp+0x14],eax
        jb loc_0042B240
        xor  ecx,ecx
        lea  eax,[ebx+0x1d876]
        mov  edx,0x110
    loc_0042B2C0:
        movzx edi,BYTE PTR [eax-0x1]
        movzx esi,BYTE PTR [eax-0x2]
        add  esi,edi
        movzx edi,BYTE PTR [eax+0x1]
        add  esi,edi
        movzx edi,BYTE PTR [eax]
        add  edi,ecx
        add  eax,0x4
        dec  edx
        lea  ecx,[edi+esi*1]
        jne loc_0042B2C0
        mov  DWORD PTR [ebx+0x1d870],ecx
        mov  ecx,DWORD PTR [esp+0xc]
        lea  edi,[ecx+ebp*1]
        lea  esi,[ebx+0x1d86c]
        mov  ecx,0x112
        rep movsd
        mov  edx,DWORD PTR [ebx]
        add  ebp,0x430
        mov  DWORD PTR [edx+0x14],ebp
        mov  eax,DWORD PTR [ebx]
        mov  edx,DWORD PTR [eax+0x14]
        lea  ecx,[eax+0x10]
        mov  eax,DWORD PTR [esp+0xc]
        push  ecx
        push  edx
        add  eax,0x18
        push  eax
        call FUN_004359b0
        mov  edi,eax
        mov  eax,DWORD PTR [ebx]
        mov  ecx,DWORD PTR [eax+0x10]
        add  ecx,0x18
        mov  DWORD PTR [eax+0x4],ecx
        mov  edx,DWORD PTR [ebx]
        mov  eax,DWORD PTR [edx+0x10]
        push  eax
        push  0x10
        push  0x35
        push  eax
        push  edi
        mov  al,0xac
        call FUN_0044b220
        push  0x46e848
        call FUN_0044b620
        test  eax,eax
        je loc_0042B352
        pop  edi
        pop  esi
        or   eax,0xffffffff
        pop  ebp
        add  esp,0xc
        ret
    loc_0042B352:
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        mov  ebp,DWORD PTR ds:0x4660cc
        je loc_0042B39A
        mov  edx,DWORD PTR [ebx]
        push  0x0
        lea  ecx,[esp+0x18]
        push  ecx
        push  0x18
        push  edx
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  DWORD PTR [esp+0x14],0x18
        mov  eax,ds:0x474c38
        je loc_0042B39A
        push  eax
        call  ebp
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
        mov  eax,ds:0x474c38
    loc_0042B39A:
        cmp  eax,0xffffffff
        mov  ecx,DWORD PTR [ebx]
        mov  esi,DWORD PTR [ecx+0x10]
        je loc_0042B3F1
        push  0x0
        lea  edx,[esp+0x18]
        push  edx
        push  esi
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x14]
        je loc_0042B3D3
        mov  eax,ds:0x474c38
        push  eax
        call  ebp
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0042B3D3:
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0042B3F1
        push  eax
        call  ebp
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0042B3F1:
        test  edi,edi
        je loc_0042B3FE
        push  edi
        call _free
        add  esp,0x4
    loc_0042B3FE:
        mov  ecx,DWORD PTR [esp+0xc]
        push  ecx
        call _free
        add  esp,0x4
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        add  esp,0xc
        ret
    }
}
