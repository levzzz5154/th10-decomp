// MSVC-only exact overlay for the ANM pending-entry service (retail
// 0x00447700). The readable semantic reconstruction lives in
// anm_pending_service.cpp; this translation unit keeps the overlay free of
// C++11 so the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
extern "C" void sub_447810(void);
extern "C" void j__free(void*);
extern "C" int sub_4473C0(void*, void*);

__declspec(naked) int AnmPending_ServiceRetail() {
    __asm {
        push ebx
        push esi
        mov esi, [esp+0Ch]
        xor ebx, ebx
        push edi
        add esi, 3AD06Ch
        nop
loc_447710:
        mov edi, [esi]
        test edi, edi
        jz loc_447757
        mov eax, [edi+128h]
        test eax, eax
        jz loc_44774D
        test ebx, ebx
        jl loc_44773F
        cmp ebx, 21h
        jnb loc_44773F
        call sub_447810
        mov eax, [esi]
        push eax
        call j__free
        add esp, 4
        mov dword ptr [esi], 0
loc_44773F:
        mov ecx, [esi]
        mov dword ptr [ecx+128h], 0
        jmp loc_447757
loc_44774D:
        mov eax, [edi+124h]
        test eax, eax
        jnz loc_447768
loc_447757:
        inc ebx
        add esi, 4
        cmp ebx, 21h
        jb loc_447710
        pop edi
        pop esi
        xor eax, eax
        pop ebx
        ret 4
loc_447768:
        mov eax, [esp+10h]
        mov edx, [eax+ebx*4+3AD06Ch]
        push edx
        push eax
        call sub_4473C0
        neg eax
        sbb eax, eax
        pop edi
        neg eax
        pop esi
        dec eax
        pop ebx
        ret 4
    }
}
#endif
