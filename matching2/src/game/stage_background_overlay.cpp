// MSVC-only exact overlay for the stage background texture rebind (retail
// 0x0040C3C0). The readable semantic reconstruction lives in
// stage_background.cpp; this translation unit keeps the overlay free of
// C++11 so the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
extern "C" unsigned char byte_497C38;
extern "C" unsigned long dword_491C10;
extern "C" void* dword_4776E0;
extern "C" void* sub_447280(void*, const char*, int);
extern "C" void sub_409E50(void*);

__declspec(naked) int StageBackground_RebindTextureRetail() {
    __asm {
        mov eax, [ebx+70h]
        push esi
        push edi
        mov byte ptr [byte_497C38], 0
        mov esi, eax
        _emit 8Bh
        _emit 0FFh
loc_40C3D0:
        mov cl, [eax]
        inc eax
        test cl, cl
        jnz loc_40C3D0
        mov edi, offset byte_497C38
        sub eax, esi
        dec edi
        nop
loc_40C3E0:
        mov cl, [edi+1]
        inc edi
        test cl, cl
        jnz loc_40C3E0
        mov edx, dword_491C10
        mov ecx, eax
        shr ecx, 2
        rep movsd
        mov ecx, eax
        and ecx, 3
        rep movsb
        mov eax, [ebx+54h]
        mov ecx, [eax+4]
        push 497C38h
        add ecx, 1Dh
        call sub_447280
        mov ecx, [ebx+54h]
        mov edx, [ecx+4]
        mov esi, dword_4776E0
        mov [ebx+edx*4+80h], eax
        and dword ptr [ebx+74h], 0FFFFFFFBh
        add esi, 89A4h
        mov eax, esi
        call sub_409E50
        pop edi
        mov dword ptr [esi], 0
        xor eax, eax
        pop esi
        ret
    }
}
#endif
