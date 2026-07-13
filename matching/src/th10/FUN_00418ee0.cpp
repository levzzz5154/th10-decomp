// 00418EE0: FUN_00418ee0
// Original size: 352 bytes, actual code: 105 instructions
extern "C" void FUN_00419040(void);
extern "C" void FUN_0041a200(void);
extern "C" void FUN_00449f60(void);

extern "C" __declspec(naked) void FUN_00418ee0(void) {
    __asm {
        push  ecx
        mov  edx,DWORD PTR [esp+0x8]
        push  ebx
        mov  ebx,DWORD PTR ds:0x4660b0
        push  ebp
        mov  ebp,DWORD PTR ds:0x4660b4
        push  esi
        mov  esi,DWORD PTR [edx+0x8]
        test  esi,esi
        push  edi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_00418F2F
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        mov  al,ds:0x49231c
        mov  edx,DWORD PTR [esp+0x18]
        dec  al
        mov  ds:0x49231c,al
    loc_00418F2F:
        mov  esi,DWORD PTR [edx+0xc]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_00418F69
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        mov  al,ds:0x49231c
        mov  edx,DWORD PTR [esp+0x18]
        dec  al
        mov  ds:0x49231c,al
    loc_00418F69:
        mov  ebx,DWORD PTR ds:0x491c10
        lea  esi,[edx+0xdc]
        mov  DWORD PTR [esp+0x10],0xa
        mov  edi,0x4000000
    loc_00418F82:
        mov  ecx,DWORD PTR [esi]
        test  ecx,ecx
        je loc_00418FF1
        mov  eax,DWORD PTR [ebx+0x72dad4]
        test  eax,eax
        je loc_00418FA0
    loc_00418F92:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00418FC0
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00418F92
    loc_00418FA0:
        mov  eax,DWORD PTR [ebx+0x72dadc]
        test  eax,eax
        je loc_00418FF1
        lea  ebx,[ebx+0x0]
    loc_00418FB0:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],ecx
        je loc_00418FC0
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00418FB0
        jmp loc_00418FF1
    loc_00418FC0:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00418FF1
        mov  ebp,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        or   ebp,edi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],ebp
        jne loc_00418FF1
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00418FF1
    loc_00418FE2:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],edi
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00418FE2
    loc_00418FF1:
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi],0x0
        add  esi,0x4
        dec  eax
        mov  DWORD PTR [esp+0x10],eax
        jne loc_00418F82
        cmp  BYTE PTR ds:0x491d6a,0x2
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        jne loc_00419025
        push  0x46d6d8
        push  edx
        call FUN_0041a200
        mov  edx,DWORD PTR [esp+0x8]
    loc_00419025:
        mov  eax,edx
        call FUN_00419040
        mov  DWORD PTR ds:0x477814,0x0
        pop  ecx
        ret  0x4
    }
}
