// 0044B8E0: FUN_0044b8e0
// Original size: 256 bytes, actual code: 56 instructions
extern "C" void _vsprintf(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0044b8e0(void) {
    __asm {
        sub  esp,0x204
        mov  eax,ds:0x473660
        xor  eax,esp
        push  0x4922bc
        mov  DWORD PTR [esp+0x204],eax
        call  DWORD PTR ds:0x4660b0
        mov  al,ds:0x49231f
        mov  ecx,DWORD PTR [esp+0x208]
        inc  al
        mov  ds:0x49231f,al
        lea  eax,[esp+0x20c]
        push  eax
        push  ecx
        lea  edx,[esp+0x8]
        push  edx
        call _vsprintf
        lea  eax,[esp+0xc]
        add  esp,0xc
        lea  edx,[eax+0x1]
        nop
    loc_0044B930:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0044B930
        sub  eax,edx
        push  esi
        mov  esi,DWORD PTR [edi+0x2000]
        lea  ecx,[esi+eax*1]
        lea  edx,[edi+0x1fff]
        cmp  ecx,edx
        jae loc_0044B96E
        lea  edx,[esp+0x4]
    loc_0044B951:
        mov  cl,BYTE PTR [edx]
        inc  edx
        mov  BYTE PTR [esi],cl
        inc  esi
        test  cl,cl
        jne loc_0044B951
        mov  ecx,DWORD PTR [edi+0x2000]
        add  ecx,eax
        mov  eax,ecx
        mov  DWORD PTR [edi+0x2000],ecx
        mov  BYTE PTR [eax],0x0
    loc_0044B96E:
        push  0x4922bc
        mov  BYTE PTR [edi+0x2004],0x1
        call  DWORD PTR ds:0x4660b4
        mov  al,ds:0x49231f
        mov  ecx,DWORD PTR [esp+0x204]
        dec  al
        pop  esi
        mov  ds:0x49231f,al
        mov  eax,DWORD PTR [esp+0x208]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x204
        ret
    }
}
