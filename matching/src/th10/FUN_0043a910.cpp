// 0043A910: FUN_0043a910
// Original size: 336 bytes, actual code: 48 instructions
extern "C" void FUN_0043aa60(void);
extern "C" void FUN_0043ae20(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0043a910(void) {
    __asm {
        push  ebx
        push  esi
        mov  esi,eax
        push  edi
        mov  edi,esi
        mov  DWORD PTR [esi],0x46f80c
        call FUN_0043ae20
        call FUN_0043aa60
        lea  ebx,[esi+0x98]
        mov  edi,0x20
    loc_0043A932:
        mov  eax,DWORD PTR [ebx]
        test  eax,eax
        je loc_0043A947
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx],0x0
    loc_0043A947:
        mov  DWORD PTR [ebx],0x0
        add  ebx,0x4
        dec  edi
        jne loc_0043A932
        mov  eax,DWORD PTR [esi+0x13c]
        test  eax,eax
        je loc_0043A97B
        push  eax
        call  DWORD PTR ds:0x4662a8
        mov  eax,DWORD PTR [esi+0x13c]
        push  eax
        call  DWORD PTR ds:0x4662a4
        mov  DWORD PTR [esi+0x13c],0x0
    loc_0043A97B:
        mov  eax,DWORD PTR [esi+0x4]
        test  eax,eax
        mov  DWORD PTR [esi],0x46f810
        je loc_0043A98F
        push  eax
        call  DWORD PTR ds:0x466288
    loc_0043A98F:
        mov  ecx,DWORD PTR [esi+0x8]
        mov  edi,DWORD PTR ds:0x466274
        push  ecx
        call  edi
        mov  edx,DWORD PTR [esi+0x8]
        push  edx
        mov  DWORD PTR [esi+0x4],0x0
        call  edi
        pop  edi
        pop  esi
        pop  ebx
        ret
    }
}
