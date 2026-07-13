// 00447810: FUN_00447810
// Original size: 304 bytes, actual code: 79 instructions
extern "C" void FUN_004493e0(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00447810(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [edi+0x108]
        push  ebp
        xor  ebp,ebp
        cmp  eax,ebp
        je loc_004478FF
        mov  eax,ds:0x491c10
        mov  edx,edi
        call FUN_004493e0
        cmp  DWORD PTR [edi+0x10c],ebp
        mov  DWORD PTR [esp+0x4],ebp
        jle loc_00447882
        push  ebx
        push  esi
        xor  ebx,ebx
        mov  edi,edi
    loc_00447840:
        mov  esi,DWORD PTR [edi+0x120]
        mov  eax,DWORD PTR [esi+ebx*1]
        add  esi,ebx
        cmp  eax,ebp
        je loc_00447857
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esi],ebp
    loc_00447857:
        mov  eax,DWORD PTR [esi+0x4]
        cmp  eax,ebp
        je loc_0044786A
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x4],ebp
    loc_0044786A:
        mov  eax,DWORD PTR [esp+0xc]
        mov  ecx,DWORD PTR [edi+0x10c]
        inc  eax
        add  ebx,0x10
        cmp  eax,ecx
        mov  DWORD PTR [esp+0xc],eax
        jl loc_00447840
        pop  esi
        pop  ebx
    loc_00447882:
        mov  eax,DWORD PTR [edi+0x120]
        cmp  eax,ebp
        je loc_0044789B
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi+0x120],ebp
    loc_0044789B:
        mov  eax,DWORD PTR [edi+0x118]
        cmp  eax,ebp
        je loc_004478B4
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi+0x118],ebp
    loc_004478B4:
        mov  eax,DWORD PTR [edi+0x11c]
        cmp  eax,ebp
        je loc_004478CD
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi+0x11c],ebp
    loc_004478CD:
        mov  eax,DWORD PTR [edi+0x12c]
        cmp  eax,ebp
        je loc_004478E6
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi+0x12c],ebp
    loc_004478E6:
        mov  eax,DWORD PTR [edi+0x108]
        cmp  eax,ebp
        je loc_004478FF
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi+0x108],ebp
    loc_004478FF:
        pop  ebp
        pop  ecx
        ret
    }
}
