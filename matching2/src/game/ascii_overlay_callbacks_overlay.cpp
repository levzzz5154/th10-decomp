// MSVC-only exact overlay for the ASCII overlay draw callback (retail
// 0x0043C410). The readable semantic reconstruction lives in
// ascii_overlay_callbacks.cpp; this translation unit keeps the overlay free
// of C++11 so the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
extern "C" int sub_43BDA0(void*);

__declspec(naked) int AsciiManager_OnDrawRetail() {
    __asm {
        sub esp, 10h
        mov eax, [ecx+20h]
        push ebx
        mov ebx, [ecx+18h]
        shl ebx, 18h
        push edi
        or ebx, eax
        lea edi, [esp+8]
        mov dword ptr [esp+8], 42000000h
        mov dword ptr [esp+0Ch], 41800000h
        mov dword ptr [esp+10h], 43D00000h
        mov dword ptr [esp+14h], 43E80000h
        call sub_43BDA0
        pop edi
        mov eax, 1
        pop ebx
        add esp, 10h
        ret
    }
}
#endif
