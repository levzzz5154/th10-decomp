// 00408C90: FUN_00408c90
// Original size: 208 bytes, actual code: 42 instructions
extern "C" void FUN_00408910(void);
extern "C" void FUN_004089c0(void);
extern "C" void FUN_00408af0(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00408c90(void) {
    __asm {
        push  0xffffffff
        push  0x46586b
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  ebx
        push  0x37b0
        call operator_new
        add  esp,0x4
        mov  DWORD PTR [esp+0x4],eax
        test  eax,eax
        mov  DWORD PTR [esp+0x10],0x0
        je loc_00408CCE
        push  eax
        call FUN_00408910
        mov  ebx,eax
        jmp loc_00408CD0
    loc_00408CCE:
        xor  ebx,ebx
    loc_00408CD0:
        mov  DWORD PTR [esp+0x10],0xffffffff
        call FUN_004089c0
        test  eax,eax
        je loc_00408D06
        test  ebx,ebx
        je loc_00408CF4
        push  ebx
        call FUN_00408af0
        push  ebx
        call _free
        add  esp,0x4
    loc_00408CF4:
        xor  eax,eax
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    loc_00408D06:
        mov  ecx,DWORD PTR [esp+0x8]
        mov  eax,ebx
        pop  ebx
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    }
}
