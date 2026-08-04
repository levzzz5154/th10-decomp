// MSVC-only exact overlay for the key-config slot reassignment (retail
// 0x00430250). The readable semantic reconstruction lives in
// key_config.cpp; this translation unit keeps the overlay free of C++11 so
// the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
extern "C" void sub_42F8B0(void);
extern "C" void sub_43DC90(void*, int);

__declspec(naked) void KeyConfig_ReassignSlotRetail() {
    __asm {
        push esi
        mov si, [eax+ecx*2+59CCh]
        push edi
        movsx edi, si
        cmp edi, edx
        jz loc_430315
        test ecx, ecx
        jz loc_43027B
        movsx edi, word ptr [eax+59CCh]
        cmp edi, edx
        jnz loc_43027B
        mov [eax+59CCh], si
loc_43027B:
        cmp ecx, 1
        jz loc_43029A
        movsx esi, word ptr [eax+59CEh]
        cmp esi, edx
        jnz loc_43029A
        mov si, [eax+ecx*2+59CCh]
        mov [eax+59CEh], si
loc_43029A:
        cmp ecx, 2
        jz loc_4302B9
        movsx esi, word ptr [eax+59D0h]
        cmp esi, edx
        jnz loc_4302B9
        mov si, [eax+ecx*2+59CCh]
        mov [eax+59D0h], si
loc_4302B9:
        cmp ecx, 3
        jz loc_4302D8
        movsx esi, word ptr [eax+59D2h]
        cmp esi, edx
        jnz loc_4302D8
        mov si, [eax+ecx*2+59CCh]
        mov [eax+59D2h], si
loc_4302D8:
        cmp ecx, 4
        jz loc_4302F7
        movsx esi, word ptr [eax+59D4h]
        cmp esi, edx
        jnz loc_4302F7
        mov si, [eax+ecx*2+59CCh]
        mov [eax+59D4h], si
loc_4302F7:
        mov [eax+ecx*2+59CCh], dx
        call sub_42F8B0
        push 0
        mov edi, 0Ah
        mov ecx, 492590h
        call sub_43DC90
loc_430315:
        pop edi
        pop esi
        ret
    }
}
#endif
