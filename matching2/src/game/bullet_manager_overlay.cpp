// MSVC-only exact overlay for the bullet pool reset leaf (retail
// 0x00405ED0). The readable semantic reconstruction lives in
// bullet_manager.cpp; this translation unit keeps the overlay free of
// C++11 so the MSVC 7.1 hybrid build can compile it.
#ifdef _MSC_VER
extern "C" void sub_4493E0(void*, void*);
extern "C" unsigned long dword_491C10;

__declspec(naked) void BulletPool_ResetRetail() {
    __asm {
        mov edx, [esi+3E0B50h]
        mov eax, dword_491C10
        push edi
        call sub_4493E0
        lea edx, [esi+60h]
        mov ecx, 0F82BCh
        xor eax, eax
        mov edi, edx
        rep stosd
        mov [esi+10h], edx
        mov word ptr [esi+3E07A6h], 5
        pop edi
        ret
    }
}
#endif
