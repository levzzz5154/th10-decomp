// 00446F40: FUN_00446f40
// Original size: 272 bytes, actual code: 90 instructions
extern "C" void D3DXCreateTexture(void);
extern "C" void D3DXLoadSurfaceFromMemory(void);

extern "C" __declspec(naked) void FUN_00446f40(void) {
    __asm {
        sub  esp,0x14
        push  esi
        push  edi
        mov  edi,eax
        test  BYTE PTR ds:0x491d78,0x1
        mov  esi,ecx
        mov  DWORD PTR [esp+0x8],0x0
        je loc_00446F7B
        mov  eax,DWORD PTR [edi*4+0x46f288]
        cmp  eax,0x15
        je loc_00446F76
        test  eax,eax
        je loc_00446F76
        cmp  eax,0x14
        jne loc_00446F7B
        mov  edi,0x3
        jmp loc_00446F7B
    loc_00446F76:
        mov  edi,0x5
    loc_00446F7B:
        mov  edx,DWORD PTR [edi*4+0x46f288]
        movsx eax,WORD PTR [esi+0x8]
        movsx ecx,WORD PTR [esi+0xa]
        push  ebx
        push  0x1
        push  edx
        mov  edx,DWORD PTR ds:0x491c30
        push  0x0
        push  0x1
        mov  DWORD PTR [esp+0x28],eax
        mov  eax,DWORD PTR [esp+0x38]
        mov  DWORD PTR [esp+0x2c],ecx
        mov  ecx,DWORD PTR [esp+0x34]
        push  eax
        push  ecx
        push  edx
        mov  DWORD PTR [esp+0x2c],0x0
        mov  DWORD PTR [esp+0x30],0x0
        call D3DXCreateTexture
        test  eax,eax
        je loc_00446FDD
        mov  eax,DWORD PTR [esp+0x8]
        test  eax,eax
        je loc_00446FD2
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
    loc_00446FD2:
        pop  edi
        or   eax,0xffffffff
        pop  esi
        add  esp,0x14
        ret  0x8
    loc_00446FDD:
        mov  eax,DWORD PTR [ebx]
        mov  edx,DWORD PTR [eax]
        lea  ecx,[esp+0x8]
        push  ecx
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x48]
        movsx eax,WORD PTR [esi+0x6]
        movsx ecx,WORD PTR [esi+0x8]
        push  0x0
        shl  eax,0x2
        imul  ecx,DWORD PTR [eax+0x46f2a0]
        push  0x1
        lea  edx,[esp+0x14]
        push  edx
        mov  edx,DWORD PTR [eax+0x46f288]
        push  0x0
        push  ecx
        mov  ecx,DWORD PTR [esp+0x1c]
        push  edx
        add  esi,0x10
        push  esi
        lea  eax,[esp+0x28]
        push  eax
        push  0x0
        push  ecx
        call D3DXLoadSurfaceFromMemory
        mov  eax,DWORD PTR [esp+0x8]
        test  eax,eax
        mov  edx,DWORD PTR [edi*4+0x46f2a0]
        mov  DWORD PTR [ebx+0xc],edx
        je loc_0044703E
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
    loc_0044703E:
        pop  edi
        xor  eax,eax
        pop  esi
        add  esp,0x14
        ret  0x8
    }
}
