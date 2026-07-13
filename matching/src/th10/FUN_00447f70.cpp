// 00447F70: FUN_00447f70
// Original size: 96 bytes, actual code: 26 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00447f70(void) {
    __asm {
        mov  eax,DWORD PTR [edi+esi*4+0x3ad4e0]
        push  ebx
        xor  ebx,ebx
        cmp  eax,ebx
        je loc_00447F8B
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edi+esi*4+0x3ad4e0],ebx
    loc_00447F8B:
        mov  eax,DWORD PTR [edi+esi*4+0x3ad560]
        cmp  eax,ebx
        je loc_00447FA3
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR [edi+esi*4+0x3ad560],ebx
    loc_00447FA3:
        mov  eax,DWORD PTR [edi+esi*4+0x3ad5e0]
        cmp  eax,ebx
        je loc_00447FBE
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi+esi*4+0x3ad5e0],ebx
    loc_00447FBE:
        mov  DWORD PTR [edi+esi*4+0x3ad5e0],ebx
        pop  ebx
        ret
    }
}
