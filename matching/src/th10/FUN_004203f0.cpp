// 004203F0: FUN_004203f0
// Original size: 128 bytes, actual code: 43 instructions
extern "C" void FUN_0040b7b0(void);
extern "C" void FUN_00417c80(void);
extern "C" void FUN_0041fb50(void);
extern "C" void FUN_004294a0(void);
extern "C" void FUN_0042cb60(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_004203f0(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR ds:0x477810
        test  esi,esi
        je loc_0042040A
        push  esi
        call FUN_00417c80
        push  esi
        call _free
        add  esp,0x4
    loc_0042040A:
        mov  esi,DWORD PTR ds:0x47784c
        test  esi,esi
        je loc_00420423
        push  esi
        call FUN_0042cb60
        push  esi
        call _free
        add  esp,0x4
    loc_00420423:
        mov  esi,DWORD PTR ds:0x477820
        test  esi,esi
        je loc_0042043C
        push  esi
        call FUN_0041fb50
        push  esi
        call _free
        add  esp,0x4
    loc_0042043C:
        mov  esi,DWORD PTR ds:0x477700
        test  esi,esi
        je loc_00420455
        push  esi
        call FUN_0040b7b0
        push  esi
        call _free
        add  esp,0x4
    loc_00420455:
        mov  esi,DWORD PTR ds:0x477838
        test  esi,esi
        je loc_0042046E
        push  esi
        call FUN_004294a0
        push  esi
        call _free
        add  esp,0x4
    loc_0042046E:
        pop  esi
        ret
    }
}
