// 00446220: FUN_00446220
// Original size: 208 bytes, actual code: 58 instructions
extern "C" void FUN_00448bb0(void);
extern "C" void _free(void);
extern "C" void _eh_vector_destructor_iterator_(void);

extern "C" __declspec(naked) void FUN_00446220(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x465225
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ebx
        push  esi
        push  edi
        mov  edi,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x14],0x2
        mov  eax,DWORD PTR [edi+0x72dad4]
        test  eax,eax
        je loc_00446260
        mov  edi,edi
    loc_00446250:
        mov  esi,DWORD PTR [eax]
        mov  ebx,DWORD PTR [eax+0x4]
        call FUN_00448bb0
        test  ebx,ebx
        mov  eax,ebx
        jne loc_00446250
    loc_00446260:
        mov  eax,DWORD PTR [edi+0x72dadc]
        test  eax,eax
        je loc_00446280
        lea  ebx,[ebx+0x0]
    loc_00446270:
        mov  esi,DWORD PTR [eax]
        mov  ebx,DWORD PTR [eax+0x4]
        call FUN_00448bb0
        test  ebx,ebx
        mov  eax,ebx
        jne loc_00446270
    loc_00446280:
        push  0x401ff0
        push  0x14
        push  0x3ac
        lea  eax,[edi+0x72dae4]
        push  eax
        mov  BYTE PTR [esp+0x24],0x1
        call _eh_vector_destructor_iterator_
        mov  eax,DWORD PTR [edi+0x3ad488]
        test  eax,eax
        je loc_004462B0
        push  eax
        call _free
        add  esp,0x4
    loc_004462B0:
        push  0x401ff0
        push  0x1000
        mov  DWORD PTR [edi+0x3ad488],0x0
        push  0x3ac
        add  edi,0x68
        push  edi
        mov  DWORD PTR [esp+0x24],0xffffffff
        call _eh_vector_destructor_iterator_
        mov  ecx,DWORD PTR [esp+0xc]
        pop  edi
        pop  esi
        mov  DWORD PTR fs:0x0,ecx
        pop  ebx
        add  esp,0xc
        ret  0x4
    }
}
