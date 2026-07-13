// 004492F0: FUN_004492f0
// Original size: 96 bytes, actual code: 34 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_004492f0(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        push  eax
        call FUN_004491c0
        test  eax,eax
        je loc_00449347
        push  edi
        mov  edx,esi
        mov  edi,DWORD PTR [edx]
        lea  ecx,[eax+0x340]
        mov  DWORD PTR [ecx],edi
        mov  edi,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ecx+0x4],edi
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ecx+0x8],edx
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        jne loc_00449346
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00449346
    loc_00449325:
        mov  ecx,DWORD PTR [eax]
        add  ecx,0x340
        mov  edx,esi
        mov  edi,DWORD PTR [edx]
        mov  DWORD PTR [ecx],edi
        mov  edi,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ecx+0x4],edi
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ecx+0x8],edx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00449325
    loc_00449346:
        pop  edi
    loc_00449347:
        ret  0x4
    }
}
