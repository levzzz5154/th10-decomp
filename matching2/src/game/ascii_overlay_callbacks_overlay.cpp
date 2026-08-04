// MSVC-only exact overlay for the ASCII overlay draw callback (retail
// 0x0043C410). The readable semantic reconstruction lives in
// ascii_overlay_callbacks.cpp; this translation unit keeps the overlay free
// of C++11 so the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
extern "C" int sub_43BDA0(void*);
extern "C" unsigned long ___security_cookie;
extern "C" void __stdcall security_check_cookie(unsigned long);
extern "C" int _vsprintf(char*, const char*, const char*);
extern "C" long __cdecl __ftol2(void);
extern "C" int sub_4479D0(void*, void*, int, int, int, int, int);
extern "C" float flt_470B98;

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

// 0x00447AE0 - Format a shadowed ASCII overlay string into the per-manager
// line buffer, center it with the configured glyph column width (default
// 0x11 when the override byte is zero), submit the overlay, and set the
// dirty bit.
__declspec(naked) void AsciiOverlay_FormatShadowedRetail() {
    __asm {
        sub esp, 88h
        mov eax, ___security_cookie
        xor eax, esp
        push ebx
        mov [esp+88h], eax
        mov al, [esi+3A0h]
        test al, al
        push ebp
        push edi
        mov ebp, 11h
        jbe loc_447B09
        movzx ebp, al
loc_447B09:
        mov ecx, [esp+0A0h]
        lea eax, [esp+0A4h]
        push eax
        push ecx
        lea edx, [esp+18h]
        push edx
        call _vsprintf
        lea eax, [esp+1Ch]
        add esp, 0Ch
        lea edx, [eax+1]
        _emit 8Dh
        _emit 49h
        _emit 00h
loc_447B30:
        mov cl, [eax]
        inc eax
        test cl, cl
        jnz loc_447B30
        mov ecx, [esi+360h]
        mov edi, [esi+394h]
        shr ecx, 1
        and ecx, 1
        push ecx
        sub eax, edx
        mov edx, [esp+0A0h]
        lea ecx, [ebp-1]
        imul ecx, eax
        shr ecx, 1
        test ecx, ecx
        mov [esp+10h], ecx
        push edx
        fild dword ptr [esp+14h]
        jge loc_447B6D
        fadd dword ptr [flt_470B98]
loc_447B6D:
        fsubr dword ptr [edi+34h]
        call __ftol2
        mov edx, [edi+4]
        push eax
        push edx
        lea ebx, [esp+20h]
        mov eax, ebp
        call sub_4479D0
        mov eax, [esi+35Ch]
        mov ecx, [esp+90h]
        pop edi
        pop ebp
        or eax, 1
        pop ebx
        xor ecx, esp
        mov [esi+35Ch], eax
        call security_check_cookie
        add esp, 88h
        ret
    }
}
#endif
