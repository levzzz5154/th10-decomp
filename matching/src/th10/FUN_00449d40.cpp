// 00449D40: FUN_00449d40
// Original size: 272 bytes, actual code: 90 instructions
extern "C" void FUN_00449f60(void);

extern "C" __declspec(naked) void FUN_00449d40(void) {
    __asm {
        sub  esp,0x8
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR ds:0x4660b0
        push  0x492274
        call  ebp
        mov  dl,BYTE PTR ds:0x49231c
        mov  eax,DWORD PTR [esp+0x14]
        mov  ebx,DWORD PTR ds:0x4660b4
        inc  dl
        mov  BYTE PTR ds:0x49231c,dl
        mov  eax,DWORD PTR [eax+0x3c]
        test  eax,eax
        mov  DWORD PTR [esp+0x8],0x0
        je loc_00449E12
        push  esi
        push  edi
        nop
    loc_00449D80:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  esi,DWORD PTR [eax]
        mov  eax,DWORD PTR [esi+0x8]
        test  eax,eax
        mov  DWORD PTR [esp+0x14],ecx
        je loc_00449DEC
        test  BYTE PTR [esi+0x4],0x2
        je loc_00449DDF
    loc_00449D96:
        push  0x492274
        call  ebx
        dec  BYTE PTR ds:0x49231c
        mov  ecx,DWORD PTR [esi+0x20]
        call  DWORD PTR [esi+0x8]
        push  0x492274
        mov  edi,eax
        call  ebp
        mov  cl,BYTE PTR ds:0x49231c
        inc  cl
        cmp  edi,0x5
        mov  BYTE PTR ds:0x49231c,cl
        ja loc_00449DDF
        jmp  DWORD PTR [edi*4+0x449e34]
        test  BYTE PTR [esi+0x4],0x2
        jne loc_00449D96
        jmp loc_00449DDF
        mov  edx,DWORD PTR [esp+0x1c]
        mov  ecx,esi
        call FUN_00449f60
    loc_00449DDF:
        mov  eax,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x14]
        inc  eax
        mov  DWORD PTR [esp+0x10],eax
    loc_00449DEC:
        test  ecx,ecx
        mov  eax,ecx
        jne loc_00449D80
        jmp loc_00449E10
        mov  DWORD PTR [esp+0x10],0x0
        jmp loc_00449E10
        mov  DWORD PTR [esp+0x10],0x1
        jmp loc_00449E10
        mov  DWORD PTR [esp+0x10],0xffffffff
    loc_00449E10:
        pop  edi
        pop  esi
    loc_00449E12:
        push  0x492274
        call  ebx
        mov  al,ds:0x49231c
        dec  al
        pop  ebp
        mov  ds:0x49231c,al
        mov  eax,DWORD PTR [esp+0x4]
        pop  ebx
        add  esp,0x8
        ret  0x4
        nop
        aam  0x9d
        inc  esp
        add  bh,bl
        popf
        inc  esp
        add  ah,cl
        popf
        inc  esp
        add  dh,bh
        popf
        inc  esp
        add  ah,dh
        popf
        inc  esp
        add  BYTE PTR [eax],cl
        sahf
        inc  esp
        add  ah,cl
    }
}
