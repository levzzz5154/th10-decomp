// 0041A120: FUN_0041a120
// Original size: 224 bytes, actual code: 71 instructions
extern "C" void operator_new(void);
extern "C" void _strncpy(void);

extern "C" __declspec(naked) void FUN_0041a120(void) {
    __asm {
        push  esi
        push  0x88
        call operator_new
        mov  edx,eax
        add  esp,0x4
        test  edx,edx
        je loc_0041A168
        push  edi
        xor  eax,eax
        mov  ecx,0x22
        mov  edi,edx
        rep stosd
        mov  DWORD PTR [edx+0x10],eax
        mov  DWORD PTR [edx+0x14],eax
        mov  DWORD PTR [edx+0xc],edx
        or   eax,0xffffffff
        mov  DWORD PTR [edx+0x84],eax
        mov  DWORD PTR [edx+0x6c],0x12c
        mov  DWORD PTR [edx+0x7c],0x3f800000
        mov  DWORD PTR [edx+0x70],eax
        mov  esi,edx
        pop  edi
        jmp loc_0041A16A
    loc_0041A168:
        xor  esi,esi
    loc_0041A16A:
        mov  eax,ds:0x474c7c
        mov  edx,DWORD PTR [esp+0x8]
        lea  eax,[eax+eax*2+0x1e]
        lea  eax,[edx+eax*4]
        mov  edx,DWORD PTR [eax+0x4]
        test  edx,edx
        lea  ecx,[esi+0xc]
        je loc_0041A18E
    loc_0041A184:
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR [eax+0x4]
        test  edx,edx
        jne loc_0041A184
    loc_0041A18E:
        mov  edx,DWORD PTR [eax+0x4]
        test  edx,edx
        je loc_0041A19E
        mov  DWORD PTR [ecx+0x4],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [edx+0x8],ecx
    loc_0041A19E:
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [ecx+0x8],eax
        mov  DWORD PTR [esi+0x70],0x1e
        mov  ecx,DWORD PTR [ebx]
        mov  eax,esi
        mov  DWORD PTR [eax],ecx
        mov  edx,DWORD PTR [ebx+0x4]
        mov  DWORD PTR [eax+0x4],edx
        mov  ecx,DWORD PTR [ebx+0x8]
        mov  edx,DWORD PTR [esp+0xc]
        push  0x40
        mov  DWORD PTR [eax+0x8],ecx
        push  edx
        lea  eax,[esi+0x1c]
        push  eax
        call _strncpy
        mov  DWORD PTR [esi+0x64],0x0
        mov  ecx,DWORD PTR ds:0x474c84
        mov  DWORD PTR [esi+0x68],ecx
        mov  eax,ds:0x474c84
        add  esp,0xc
        test  eax,eax
        mov  eax,ds:0x474c8c
        jne loc_0041A1F3
        mov  eax,ds:0x474c88
    loc_0041A1F3:
        mov  DWORD PTR [esi+0x60],eax
        mov  eax,esi
        pop  esi
        ret  0x8
    }
}
