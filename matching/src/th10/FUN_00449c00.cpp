// 00449C00: FUN_00449c00
// Original size: 320 bytes, actual code: 100 instructions
extern "C" void FUN_00449f60(void);

extern "C" __declspec(naked) void FUN_00449c00(void) {
    __asm {
        sub  esp,0x8
        push  ebx
        mov  ebx,DWORD PTR ds:0x4660b0
        push  ebp
        push  esi
        push  edi
        push  0x492274
        call  ebx
        mov  al,ds:0x49231c
        mov  ebp,DWORD PTR ds:0x4660b4
        inc  al
        mov  ds:0x49231c,al
        jmp loc_00449C30
        nop
        nop
    loc_00449C30:
        mov  eax,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [eax+0x18]
        mov  DWORD PTR [esp+0x10],0x0
        nop
    loc_00449C40:
        test  eax,eax
        je loc_00449CF0
        mov  ecx,DWORD PTR [eax+0x4]
        mov  esi,DWORD PTR [eax]
        mov  eax,DWORD PTR [esi+0x8]
        test  eax,eax
        mov  DWORD PTR [esp+0x14],ecx
        je loc_00449CCB
        test  BYTE PTR [esi+0x4],0x2
        je loc_00449CC7
        mov  edi,edi
    loc_00449C60:
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
        mov  ecx,DWORD PTR [esi+0x20]
        call  DWORD PTR [esi+0x8]
        push  0x492274
        mov  edi,eax
        call  ebx
        mov  cl,BYTE PTR ds:0x49231c
        inc  cl
        cmp  edi,0x7
        mov  BYTE PTR ds:0x49231c,cl
        ja loc_00449CC7
        jmp  DWORD PTR [edi*4+0x449d14]
        test  BYTE PTR [esi+0x4],0x2
        jne loc_00449C60
        inc  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x14]
        jmp loc_00449C40
        mov  edx,DWORD PTR [esp+0x1c]
        mov  ecx,esi
        call FUN_00449f60
        inc  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x14]
        jmp loc_00449C40
        mov  eax,DWORD PTR [esi+0x10]
        test  eax,eax
        je loc_00449CC7
        mov  ecx,DWORD PTR [esi+0x20]
        call  eax
    loc_00449CC7:
        inc  DWORD PTR [esp+0x10]
    loc_00449CCB:
        mov  eax,DWORD PTR [esp+0x14]
        jmp loc_00449C40
        mov  DWORD PTR [esp+0x10],0x0
        jmp loc_00449CF0
        mov  DWORD PTR [esp+0x10],0x1
        jmp loc_00449CF0
        mov  DWORD PTR [esp+0x10],0xffffffff
    loc_00449CF0:
        push  0x492274
        call  ebp
        mov  al,ds:0x49231c
        pop  edi
        pop  esi
        dec  al
        pop  ebp
        mov  ds:0x49231c,al
        mov  eax,DWORD PTR [esp+0x4]
        pop  ebx
        add  esp,0x8
        ret  0x4
        nop
        cmps  BYTE PTR ds:[esi],BYTE PTR es:[edi]
        pushf
        inc  esp
        add  bh,al
        pushf
        inc  esp
        add  BYTE PTR [esi-0x21ffbb64],dl
        pushf
        inc  esp
        add  ah,dl
        pushf
        inc  esp
        add  al,ch
        pushf
        inc  esp
        add  BYTE PTR [eax],dh
        pushf
        inc  esp
        add  BYTE PTR [ebx-0x33ffbb64],bh
    }
}
