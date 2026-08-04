// MSVC-only exact overlay for the main-menu task registration and timer
// reset (retail 0x00422150). The readable semantic reconstruction lives in
// main_menu_dispatch.cpp; this translation unit keeps the overlay free of
// C++11 so the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
extern "C" void* sub_449ED0(void*);
extern "C" int sub_449AE0(void*, int, void*);
extern "C" int sub_449B70(void*, int, void*);
extern "C" unsigned long dword_491BE4;

__declspec(naked) int MainMenu_RegisterTasksRetail() {
    __asm {
        push esi
        push edi
        push 422A90h
        call sub_449ED0
        mov esi, eax
        mov edi, [esi+4]
        mov eax, dword ptr [dword_491BE4]
        and edi, 0FFFFFFFDh
        mov [esi+4], edi
        push eax
        mov edi, 9
        mov [esi+20h], ebx
        call sub_449AE0
        push 422AA0h
        mov [ebx+8], esi
        call sub_449ED0
        mov ecx, dword ptr [dword_491BE4]
        mov esi, eax
        mov eax, [esi+4]
        and eax, 0FFFFFFFDh
        push ecx
        mov edi, 2Eh
        mov [esi+20h], ebx
        mov [esi+4], eax
        call sub_449B70
        mov [ebx+0Ch], esi
        mov eax, [ebx+20h]
        xor ecx, ecx
        test al, 1
        pop edi
        pop esi
        jnz loc_4221CE
        or eax, 1
        mov [ebx+14h], ecx
        mov dword ptr [ebx+10h], 0FFF0BDC1h
        mov [ebx+18h], ecx
        mov dword ptr [ebx+1Ch], 476F78h
        mov [ebx+20h], eax
loc_4221CE:
        mov [ebx+14h], ecx
        mov [ebx+18h], ecx
        mov dword ptr [ebx+10h], 0FFFFFFFFh
        xor eax, eax
        ret
    }
}
#endif
