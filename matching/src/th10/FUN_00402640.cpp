// 00402640: FUN_00402640
// Original size: 224 bytes, actual code: 46 instructions
extern "C" void FUN_00402160(void);
extern "C" void FUN_00402230(void);
extern "C" void FUN_00402440(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00402640(void) {
    __asm {
        push  0xffffffff
        push  0x46588b
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  esi
        push  0x2b64
        call operator_new
        add  esp,0x4
        mov  DWORD PTR [esp+0x4],eax
        test  eax,eax
        mov  DWORD PTR [esp+0x10],0x0
        je loc_0040267E
        push  eax
        call FUN_00402160
        mov  esi,eax
        jmp loc_00402680
    loc_0040267E:
        xor  esi,esi
    loc_00402680:
        mov  eax,DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x18]
        push  eax
        mov  eax,esi
        mov  DWORD PTR [esp+0x14],0xffffffff
        call FUN_00402230
        test  eax,eax
        je loc_004026C3
        test  esi,esi
        je loc_004026AF
        push  esi
        call FUN_00402440
        push  esi
        call _free
        add  esp,0x4
    loc_004026AF:
        xor  eax,eax
        pop  esi
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x8
    loc_004026C3:
        mov  ecx,DWORD PTR [esp+0x8]
        mov  eax,esi
        pop  esi
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x8
    }
}
