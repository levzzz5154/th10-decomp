// 0042AF20: FUN_0042af20
// Original size: 272 bytes, actual code: 25 instructions
extern "C" void FUN_0042ae60(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0042af20(void) {
    __asm {
        push  0xffffffff
        push  0x4655ab
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  0x1dcb4
        call operator_new
        add  esp,0x4
        mov  DWORD PTR [esp],eax
        test  eax,eax
        mov  DWORD PTR [esp+0xc],0x0
        je loc_0042AF6B
        call FUN_0042ae60
        mov  ds:0x47783c,eax
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    loc_0042AF6B:
        mov  ecx,DWORD PTR [esp+0x4]
        xor  eax,eax
        mov  ds:0x47783c,eax
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    }
}
