// 004387C2: Catch@004387c2
// Original size: 190 bytes, actual code: 54 instructions
extern "C" void _free(void);
extern "C" void __CxxThrowException_8(void);

extern "C" __declspec(naked) void Catch_004387c2(void) {
    __asm {
        mov  esi,DWORD PTR [ebp-0x14]
        cmp  DWORD PTR [esi+0x18],0x10
        jb loc_004387D7
        mov  edx,DWORD PTR [esi+0x4]
        push  edx
        call _free
        add  esp,0x4
    loc_004387D7:
        push  0x0
        mov  DWORD PTR [esi+0x18],0xf
        mov  DWORD PTR [esi+0x14],0x0
        push  0x0
        mov  BYTE PTR [esi+0x4],0x0
        call __CxxThrowException_8
        mov  esi,DWORD PTR [ecx+0x18]
        cmp  esi,0x10
        push  edi
        lea  eax,[ecx+0x4]
        jb loc_00438811
        mov  edx,DWORD PTR [eax]
        jmp loc_00438813
    loc_00438811:
        mov  edx,eax
    loc_00438813:
        mov  edi,DWORD PTR [esp+0xc]
        cmp  edi,edx
        jb loc_00438832
        cmp  esi,0x10
        jb loc_00438822
        mov  eax,DWORD PTR [eax]
    loc_00438822:
        mov  ecx,DWORD PTR [ecx+0x14]
        add  ecx,eax
        cmp  ecx,edi
        jbe loc_00438832
        pop  edi
        mov  al,0x1
        pop  esi
        ret  0x4
    loc_00438832:
        pop  edi
        xor  al,al
        pop  esi
        ret  0x4
    }
}