// 00402720: FUN_00402720
// Original size: 304 bytes, actual code: 71 instructions
extern "C" void FUN_00403990(void);
extern "C" void FUN_00403c80(void);
extern "C" void FUN_0043ee30(void);
extern "C" void D3DXVec3Normalize(void);

extern "C" __declspec(naked) void FUN_00402720(void) {
    __asm {
        sub  esp,0x10
        push  ebx
        mov  ebx,eax
        mov  eax,DWORD PTR [ebx+0x2a18]
        test  al,0x8
        jne loc_00402846
        test  al,0x4
        je loc_00402745
        cmp  DWORD PTR [ebx+0x2a20],0x3c
        jge loc_00402846
    loc_00402745:
        mov  DWORD PTR [esp+0x8],0x0
        mov  ecx,DWORD PTR [esp+0x8]
        lea  eax,[ebx+0x2b3c]
        mov  DWORD PTR [eax],ecx
        push  esi
        mov  DWORD PTR [esp+0x10],0x0
        mov  edx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax+0x4],edx
        push  edi
        mov  DWORD PTR [esp+0x18],0x0
        mov  ecx,DWORD PTR [esp+0x18]
        lea  edx,[ebx+0x2a58]
        mov  DWORD PTR [eax+0x8],ecx
        push  edx
        lea  eax,[ebx+0x2a70]
        push  eax
        mov  DWORD PTR [ebx+0x2b34],0x0
        mov  DWORD PTR [ebx+0x2b38],0x0
        call D3DXVec3Normalize
        mov  DWORD PTR [ebx+0x1ee8],0x808080
        call FUN_00403990
        push  ebx
        call FUN_00403c80
        lea  esi,[ebx+0x180]
        mov  edi,0x8
    loc_004027C0:
        push  esi
        call FUN_0043ee30
        add  esi,0x3ac
        dec  edi
        jne loc_004027C0
        mov  eax,DWORD PTR [ebx+0x1eec]
        test  eax,eax
        je loc_0040281B
        mov  ecx,DWORD PTR ds:0x476f78
        lea  edx,[ebx+0x1f08]
        push  edx
        mov  DWORD PTR [esp+0x10],ecx
        mov  DWORD PTR ds:0x476f78,0x3f800000
        call FUN_0043ee30
        lea  eax,[ebx+0x22b4]
        push  eax
        call FUN_0043ee30
        lea  ecx,[ebx+0x2660]
        push  ecx
        call FUN_0043ee30
        mov  edx,DWORD PTR [esp+0xc]
        mov  DWORD PTR ds:0x476f78,edx
    loc_0040281B:
        lea  esi,[ebx+0x2a4c]
        mov  ecx,0x46
        mov  edi,0x491d7c
        mov  DWORD PTR [ebx+0x1eec],0x0
        rep movsd
        mov  eax,DWORD PTR [ebx+0x2a34]
        inc  eax
        pop  edi
        mov  DWORD PTR [ebx+0x2a34],eax
        pop  esi
    loc_00402846:
        mov  eax,0x1
        pop  ebx
        add  esp,0x10
        ret
    }
}
