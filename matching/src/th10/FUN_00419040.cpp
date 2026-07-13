// 00419040: FUN_00419040
// Original size: 80 bytes, actual code: 36 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00419040(void) {
    __asm {
        push  ebx
        push  esi
        push  edi
        mov  edi,eax
        add  edi,0x7c
        mov  ebx,0x8
        nop
    loc_00419050:
        mov  eax,DWORD PTR [edi-0x60]
        test  eax,eax
        je loc_0041906B
    loc_00419057:
        mov  esi,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax]
        push  eax
        call _free
        add  esp,0x4
        test  esi,esi
        mov  eax,esi
        jne loc_00419057
    loc_0041906B:
        mov  eax,DWORD PTR [edi]
        test  eax,eax
        je loc_00419085
    loc_00419071:
        mov  ecx,DWORD PTR [eax]
        mov  esi,DWORD PTR [eax+0x4]
        push  ecx
        call _free
        add  esp,0x4
        test  esi,esi
        mov  eax,esi
        jne loc_00419071
    loc_00419085:
        add  edi,0xc
        dec  ebx
        jne loc_00419050
        pop  edi
        pop  esi
        pop  ebx
        ret
    }
}
