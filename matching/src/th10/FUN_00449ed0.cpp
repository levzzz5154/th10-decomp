// 00449ED0: FUN_00449ed0
// Original size: 144 bytes, actual code: 26 instructions
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_00449ed0(void) {
    __asm {
        push  0x24
        call operator_new
        xor  ecx,ecx
        add  esp,0x4
        cmp  eax,ecx
        je loc_00449EFF
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ecx
        mov  DWORD PTR [eax+0xc],ecx
        mov  DWORD PTR [eax+0x10],ecx
        mov  DWORD PTR [eax],ecx
        and  edx,0xfffffffe
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ecx
        mov  DWORD PTR [eax+0x1c],ecx
        jmp loc_00449F01
    loc_00449EFF:
        xor  eax,eax
    loc_00449F01:
        mov  edx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [eax+0xc],ecx
        mov  DWORD PTR [eax+0x10],ecx
        mov  ecx,DWORD PTR [eax+0x4]
        or   ecx,0x1
        mov  DWORD PTR [eax+0x8],edx
        mov  DWORD PTR [eax+0x4],ecx
        ret  0x4
    }
}
