// 0042AB20: FUN_0042ab20
// Original size: 400 bytes, actual code: 56 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0042ab20(void) {
    __asm {
        lea  eax,[eax+eax*2]
        mov  eax,DWORD PTR [ecx+eax*4+0x40]
        push  edi
        xor  edi,edi
        cmp  eax,edi
        je loc_0042AB7B
        push  esi
        nop
    loc_0042AB30:
        mov  esi,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax]
        cmp  eax,edi
        je loc_0042AB74
        mov  ecx,DWORD PTR [eax+0x627c]
        cmp  ecx,edi
        je loc_0042AB4C
        mov  edx,DWORD PTR [eax+0x6280]
        mov  DWORD PTR [ecx+0x8],edx
    loc_0042AB4C:
        mov  ecx,DWORD PTR [eax+0x6280]
        cmp  ecx,edi
        je loc_0042AB5F
        mov  edx,DWORD PTR [eax+0x627c]
        mov  DWORD PTR [ecx+0x4],edx
    loc_0042AB5F:
        push  eax
        mov  DWORD PTR [eax+0x627c],edi
        mov  DWORD PTR [eax+0x6280],edi
        call _free
        add  esp,0x4
    loc_0042AB74:
        cmp  esi,edi
        mov  eax,esi
        jne loc_0042AB30
        pop  esi
    loc_0042AB7B:
        pop  edi
        ret
    }
}
