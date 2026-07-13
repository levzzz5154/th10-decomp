// 00435580: FUN_00435580
// Original size: 144 bytes, actual code: 68 instructions
extern "C" void _free(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_00435580(void) {
    __asm {
        push  esi
        mov  esi,ecx
        cmp  DWORD PTR [esi+0x8],0x80000000
        je loc_00435592
        xor  eax,eax
        pop  esi
        ret  0x4
    loc_00435592:
        mov  eax,DWORD PTR [esi]
        push  ebp
        mov  ecx,esi
        call  DWORD PTR [eax+0x14]
        mov  ebp,eax
        cmp  ebp,DWORD PTR [esp+0xc]
        jbe loc_004355A9
        pop  ebp
        xor  eax,eax
        pop  esi
        ret  0x4
    loc_004355A9:
        push  edi
        push  ebp
        call _malloc
        mov  edi,eax
        add  esp,0x4
        test  edi,edi
        jne loc_004355BF
        pop  edi
        pop  ebp
        pop  esi
        ret  0x4
    loc_004355BF:
        mov  edx,DWORD PTR [esi]
        push  ebx
        mov  ecx,esi
        call  DWORD PTR [edx+0x10]
        mov  ebx,eax
        mov  eax,DWORD PTR [esi]
        push  0x0
        push  ebx
        mov  ecx,esi
        call  DWORD PTR [eax+0x18]
        test  al,al
        je loc_004355ED
        mov  edx,DWORD PTR [esi]
        push  ebp
        push  edi
        mov  ecx,esi
        call  DWORD PTR [edx+0x8]
        test  eax,eax
        jne loc_004355F6
        push  edi
        call _free
        add  esp,0x4
    loc_004355ED:
        pop  ebx
        pop  edi
        pop  ebp
        xor  eax,eax
        pop  esi
        ret  0x4
    loc_004355F6:
        mov  eax,DWORD PTR [esi]
        push  0x0
        push  ebx
        mov  ecx,esi
        call  DWORD PTR [eax+0x18]
        pop  ebx
        mov  eax,edi
        pop  edi
        pop  ebp
        pop  esi
        ret  0x4
    }
}
