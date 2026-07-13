// 0043AA60: FUN_0043aa60
// Original size: 112 bytes, actual code: 36 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0043aa60(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x118]
        push  ebx
        push  ebp
        xor  ebp,ebp
        xor  ebx,ebx
        cmp  eax,ebp
        jle loc_0043AAA3
        push  edi
        xor  edi,edi
    loc_0043AA73:
        mov  eax,DWORD PTR [esi+0x138]
        mov  eax,DWORD PTR [edi+eax*1+0x10]
        cmp  eax,ebp
        je loc_0043AA94
        push  eax
        call _free
        mov  ecx,DWORD PTR [esi+0x138]
        add  esp,0x4
        mov  DWORD PTR [edi+ecx*1+0x10],ebp
    loc_0043AA94:
        mov  eax,DWORD PTR [esi+0x118]
        inc  ebx
        add  edi,0x20
        cmp  ebx,eax
        jl loc_0043AA73
        pop  edi
    loc_0043AAA3:
        mov  eax,DWORD PTR [esi+0x138]
        cmp  eax,ebp
        je loc_0043AABC
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x138],ebp
    loc_0043AABC:
        mov  DWORD PTR [esi+0x138],ebp
        mov  DWORD PTR [esi+0x118],ebp
        pop  ebp
        pop  ebx
        ret
    }
}
