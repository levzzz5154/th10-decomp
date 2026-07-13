// 00435220: FUN_00435220
// Original size: 48 bytes, actual code: 24 instructions
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_00435220(void) {
    __asm {
        mov  eax,edi
        lea  edx,[eax+0x1]
    loc_00435225:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00435225
        sub  eax,edx
        inc  eax
        push  eax
        call _malloc
        add  esp,0x4
        test  eax,eax
        je loc_0043524E
        push  esi
        mov  esi,eax
        mov  ecx,edi
        sub  esi,edi
    loc_00435243:
        mov  dl,BYTE PTR [ecx]
        mov  BYTE PTR [esi+ecx*1],dl
        inc  ecx
        test  dl,dl
        jne loc_00435243
        pop  esi
    loc_0043524E:
        ret
    }
}
