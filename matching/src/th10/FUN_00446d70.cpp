// 00446D70: FUN_00446d70
// Original size: 320 bytes, actual code: 109 instructions
extern "C" void FUN_004465b0(void);
extern "C" void D3DXLoadSurfaceFromMemory(void);
extern "C" void D3DXLoadSurfaceFromFileInMemory(void);

extern "C" __declspec(naked) void FUN_00446d70(void) {
    __asm {
        sub  esp,0x34
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x48]
        push  esi
        mov  esi,ecx
        mov  cl,BYTE PTR ds:0x491d78
        xor  ebx,ebx
        test  cl,0x1
        mov  DWORD PTR [esp+0xc],eax
        je loc_00446DB4
        mov  eax,DWORD PTR [eax*4+0x46f288]
        cmp  eax,0x15
        je loc_00446DAC
        cmp  eax,ebx
        je loc_00446DAC
        cmp  eax,0x14
        jne loc_00446DB4
        mov  DWORD PTR [esp+0xc],0x3
        jmp loc_00446DB4
    loc_00446DAC:
        mov  DWORD PTR [esp+0xc],0x5
    loc_00446DB4:
        mov  eax,DWORD PTR [esp+0x48]
        lea  edx,[esp+0x4c]
        push  edx
        mov  DWORD PTR [eax+0x8],ebp
        mov  eax,DWORD PTR [eax]
        push  ebx
        mov  DWORD PTR [esp+0x54],ebx
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        cmp  DWORD PTR [esp+0x50],ebx
        jne loc_00446E13
        mov  eax,DWORD PTR [esp+0x4c]
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x20]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x30]
        mov  eax,DWORD PTR [esp+0x38]
        mov  ecx,DWORD PTR [esp+0x3c]
        push  ebx
        push  ebx
        push  0x1
        push  ebx
        push  ebp
        push  edi
        lea  edx,[esp+0x28]
        push  edx
        mov  DWORD PTR [esp+0x34],eax
        mov  eax,DWORD PTR [esp+0x68]
        push  ebx
        push  eax
        mov  DWORD PTR [esp+0x34],ebx
        mov  DWORD PTR [esp+0x38],esi
        mov  DWORD PTR [esp+0x40],ecx
        call D3DXLoadSurfaceFromFileInMemory
        jmp loc_00446E82
    loc_00446E13:
        mov  ecx,DWORD PTR [edi+0x30]
        lea  eax,[ecx+edi*1]
        mov  DWORD PTR [esp+0x10],ebx
        mov  DWORD PTR [esp+0x14],ebx
        movsx edx,WORD PTR [eax+0x8]
        mov  DWORD PTR [esp+0x18],edx
        movsx ecx,WORD PTR [eax+0xa]
        mov  DWORD PTR [esp+0x1c],ecx
        mov  DWORD PTR [esp+0x20],ebx
        mov  DWORD PTR [esp+0x24],esi
        movsx edx,WORD PTR [eax+0x8]
        mov  DWORD PTR [esp+0x28],edx
        movsx ecx,WORD PTR [eax+0xa]
        push  ebx
        push  0x1
        add  ecx,esi
        mov  DWORD PTR [esp+0x34],ecx
        movsx ecx,WORD PTR [eax+0x6]
        lea  edx,[esp+0x18]
        push  edx
        movsx edx,WORD PTR [eax+0x8]
        shl  ecx,0x2
        imul  edx,DWORD PTR [ecx+0x46f2a0]
        mov  ecx,DWORD PTR [ecx+0x46f288]
        push  ebx
        push  edx
        push  ecx
        add  eax,0x10
        push  eax
        mov  eax,DWORD PTR [esp+0x68]
        lea  edx,[esp+0x3c]
        push  edx
        push  ebx
        push  eax
        call D3DXLoadSurfaceFromMemory
    loc_00446E82:
        mov  eax,DWORD PTR [esp+0x4c]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  esi,DWORD PTR [esp+0x48]
        mov  eax,esi
        call FUN_004465b0
        mov  edx,DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [edx*4+0x46f2a0]
        mov  DWORD PTR [esi+0xc],eax
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0x34
        ret  0x10
    }
}
