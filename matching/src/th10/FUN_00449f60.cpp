// 00449F60: FUN_00449f60
// Original size: 160 bytes, actual code: 51 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00449f60(void) {
    __asm {
        push  edi
        xor  edi,edi
        cmp  ecx,edi
        je loc_00449FD0
        lea  eax,[edx+0x14]
        cmp  eax,edi
        push  esi
        je loc_00449F7B
        nop
    loc_00449F70:
        cmp  DWORD PTR [eax],ecx
        je loc_00449F90
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00449F70
    loc_00449F7B:
        lea  eax,[edx+0x38]
        cmp  eax,edi
        je loc_00449FCF
    loc_00449F82:
        cmp  DWORD PTR [eax],ecx
        je loc_00449F90
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00449F82
        pop  esi
        pop  edi
        ret
    loc_00449F90:
        mov  esi,DWORD PTR [eax+0x8]
        cmp  esi,edi
        je loc_00449FCF
        mov  edx,DWORD PTR [eax+0x4]
        cmp  edx,edi
        je loc_00449FA1
        mov  DWORD PTR [edx+0x8],esi
    loc_00449FA1:
        mov  edx,DWORD PTR [eax+0x8]
        cmp  edx,edi
        je loc_00449FAE
        mov  esi,DWORD PTR [eax+0x4]
        mov  DWORD PTR [edx+0x4],esi
    loc_00449FAE:
        mov  DWORD PTR [eax+0x4],edi
        mov  DWORD PTR [eax+0x8],edi
        test  BYTE PTR [ecx+0x4],0x1
        mov  DWORD PTR [ecx+0x8],edi
        je loc_00449FCF
        push  ecx
        mov  DWORD PTR [ecx+0x8],edi
        mov  DWORD PTR [ecx+0xc],edi
        mov  DWORD PTR [ecx+0x10],edi
        call _free
        add  esp,0x4
    loc_00449FCF:
        pop  esi
    loc_00449FD0:
        pop  edi
        ret
    }
}
