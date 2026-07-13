// 0044B810: FUN_0044b810
// Original size: 208 bytes, actual code: 58 instructions
extern "C" void _vsprintf(void);
extern "C" void __security_check_cookie(void);
extern "C" void __chkstk(void);

extern "C" __declspec(naked) void FUN_0044b810(void) {
    __asm {
        mov  eax,0x2004
        call __chkstk
        mov  eax,ds:0x473660
        xor  eax,esp
        push  esi
        push  edi
        push  0x4922bc
        mov  DWORD PTR [esp+0x200c],eax
        mov  edi,ecx
        call  DWORD PTR ds:0x4660b0
        mov  al,ds:0x49231f
        mov  ecx,DWORD PTR [esp+0x2010]
        inc  al
        mov  ds:0x49231f,al
        lea  eax,[esp+0x2014]
        push  eax
        push  ecx
        lea  edx,[esp+0x10]
        push  edx
        call _vsprintf
        lea  eax,[esp+0x14]
        add  esp,0xc
        lea  edx,[eax+0x1]
    loc_0044B867:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0044B867
        mov  esi,DWORD PTR [edi+0x2000]
        sub  eax,edx
        lea  ecx,[esi+eax*1]
        lea  edx,[edi+0x1fff]
        cmp  ecx,edx
        jae loc_0044B8A4
        lea  edx,[esp+0x8]
    loc_0044B887:
        mov  cl,BYTE PTR [edx]
        inc  edx
        mov  BYTE PTR [esi],cl
        inc  esi
        test  cl,cl
        jne loc_0044B887
        mov  ecx,DWORD PTR [edi+0x2000]
        add  ecx,eax
        mov  DWORD PTR [edi+0x2000],ecx
        mov  edi,ecx
        mov  BYTE PTR [edi],0x0
    loc_0044B8A4:
        push  0x4922bc
        call  DWORD PTR ds:0x4660b4
        mov  al,ds:0x49231f
        mov  ecx,DWORD PTR [esp+0x2008]
        dec  al
        pop  edi
        pop  esi
        mov  ds:0x49231f,al
        mov  eax,DWORD PTR [esp+0x2008]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x2004
        ret
    }
}
