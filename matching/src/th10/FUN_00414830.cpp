// 00414830: FUN_00414830
// Original size: 208 bytes, actual code: 42 instructions
extern "C" void FUN_00413810(void);
extern "C" void FUN_00413980(void);
extern "C" void FUN_004145f0(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00414830(void) {
    __asm {
        push  0xffffffff
        push  0x46584b
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  ebx
        push  0x9ed0
        call operator_new
        add  esp,0x4
        mov  DWORD PTR [esp+0x4],eax
        test  eax,eax
        mov  DWORD PTR [esp+0x10],0x0
        je loc_0041486E
        push  eax
        call FUN_00413810
        mov  ebx,eax
        jmp loc_00414870
    loc_0041486E:
        xor  ebx,ebx
    loc_00414870:
        mov  DWORD PTR [esp+0x10],0xffffffff
        call FUN_00413980
        test  eax,eax
        je loc_004148A6
        test  ebx,ebx
        je loc_00414894
        push  ebx
        call FUN_004145f0
        push  ebx
        call _free
        add  esp,0x4
    loc_00414894:
        xor  eax,eax
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    loc_004148A6:
        mov  ecx,DWORD PTR [esp+0x8]
        mov  eax,ebx
        pop  ebx
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    }
}
