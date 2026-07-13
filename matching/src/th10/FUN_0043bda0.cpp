// 0043BDA0: FUN_0043bda0
// Original size: 512 bytes, actual code: 142 instructions
extern "C" void FUN_00442f50(void);

extern "C" __declspec(naked) void FUN_0043bda0(void) {
    __asm {
        sub  esp,0x5c
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,DWORD PTR [edi]
        mov  ecx,DWORD PTR [edi+0x4]
        mov  edx,eax
        mov  DWORD PTR [esp+0x4],eax
        mov  eax,ecx
        mov  DWORD PTR [esp+0x8],ecx
        mov  DWORD PTR [esp+0x10],edx
        mov  edx,DWORD PTR [edi+0x8]
        mov  DWORD PTR [esp+0x4],edx
        mov  DWORD PTR [esp+0xc],0x0
        mov  ecx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esp+0x18],ecx
        mov  ecx,edx
        mov  edx,eax
        mov  DWORD PTR [esp+0x14],eax
        mov  DWORD PTR [esp+0x8],eax
        mov  DWORD PTR [esp+0x24],ecx
        mov  ecx,DWORD PTR [edi]
        mov  DWORD PTR [esp+0x28],edx
        mov  edx,DWORD PTR [edi+0xc]
        mov  DWORD PTR [esp+0xc],0x0
        mov  eax,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esp+0x2c],eax
        mov  eax,ecx
        mov  DWORD PTR [esp+0x4],ecx
        mov  ecx,edx
        mov  DWORD PTR [esp+0x8],edx
        mov  DWORD PTR [esp+0x38],eax
        mov  eax,DWORD PTR [edi+0x8]
        mov  DWORD PTR [esp+0xc],0x0
        mov  edx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esp+0x40],edx
        mov  edx,eax
        push  0x2
        mov  DWORD PTR [esp+0x8],eax
        mov  eax,ecx
        mov  DWORD PTR [esp+0x40],ecx
        push  0x4
        mov  DWORD PTR [esp+0x10],ecx
        mov  DWORD PTR [esp+0x58],eax
        mov  eax,ds:0x491c30
        mov  DWORD PTR [esp+0x14],0x0
        mov  ecx,DWORD PTR [esp+0x14]
        xor  esi,esi
        push  esi
        mov  DWORD PTR [esp+0x58],edx
        mov  DWORD PTR [esp+0x60],ecx
        mov  DWORD PTR [esp+0x64],0x3f800000
        mov  DWORD PTR [esp+0x50],0x3f800000
        mov  DWORD PTR [esp+0x3c],0x3f800000
        mov  DWORD PTR [esp+0x28],0x3f800000
        mov  DWORD PTR [esp+0x68],ebx
        mov  DWORD PTR [esp+0x54],ebx
        mov  DWORD PTR [esp+0x40],ebx
        mov  DWORD PTR [esp+0x2c],ebx
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x10c]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x2
        push  0x1
        push  esi
        push  eax
        call  DWORD PTR [ecx+0x10c]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  esi
        push  0x5
        push  esi
        push  eax
        call  DWORD PTR [edx+0x10c]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  esi
        push  0x2
        push  esi
        push  eax
        call  DWORD PTR [ecx+0x10c]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x6
        push  0x14
        push  eax
        call  DWORD PTR [edx+0xe4]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x44
        push  eax
        call  DWORD PTR [ecx+0x164]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x14
        lea  ecx,[esp+0x14]
        push  ecx
        push  0x2
        push  0x5
        push  eax
        call  DWORD PTR [edx+0x14c]
        mov  eax,ds:0x491c10
        push  0x4
        mov  cl,0xff
        push  0x4
        mov  BYTE PTR [eax+0x3ada6a],cl
        mov  DWORD PTR [eax+0x3ada70],esi
        mov  DWORD PTR [eax+0x3ada64],esi
        mov  BYTE PTR [eax+0x3ada69],cl
        mov  BYTE PTR [eax+0x3ada68],0x3
        mov  BYTE PTR [eax+0x3ada6b],cl
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  esi
        push  eax
        call  DWORD PTR [edx+0x10c]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x4
        push  0x1
        push  esi
        push  eax
        call  DWORD PTR [ecx+0x10c]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x2
        push  0x5
        push  esi
        push  eax
        call  DWORD PTR [edx+0x10c]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x2
        push  0x2
        push  esi
        push  eax
        call  DWORD PTR [ecx+0x10c]
        pop  esi
        add  esp,0x5c
        ret
    }
}
