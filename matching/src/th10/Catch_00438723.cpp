// 00438723: Catch@00438723
// Original size: 41 bytes, actual code: 14 instructions
extern "C" void operator_new(void);

extern "C" __declspec(naked) void Catch_00438723(void) {
    __asm {
        mov  eax,DWORD PTR [ebp+0x8]
        mov  DWORD PTR [ebp-0x18],eax
        inc  eax
        mov  DWORD PTR [ebp-0x10],esp
        push  eax
        mov  BYTE PTR [ebp-0x4],0x2
        call operator_new
        mov  DWORD PTR [ebp+0x8],eax
        add  esp,0x4
        mov  eax,0x438743
        ret
        mov  ebx,DWORD PTR [ebp-0x18]
        mov  esi,DWORD PTR [ebp-0x14]
        mov  edx,DWORD PTR [ebp+0x8]
    }
}
