// MSVC-only exact overlay for the enemy shot-grid scan (retail 0x004073E0).
// The readable semantic reconstruction lives in enemy_grid_scan.cpp; this
// translation unit keeps the overlay free of C++11 so the MSVC 7.1 hybrid
// build can compile it.
#ifdef _MSC_VER
extern "C" float flt_470B04;
extern "C" void* dword_477834;
extern "C" int sub_4067D0(void*, int, int, float);
extern "C" void sub_43DD10(void*, void*);

__declspec(naked) int EnemyGrid_ScanCellsRetail() {
    __asm {
        push ecx
        push ebx
        mov ebx, eax
        mov eax, dword ptr [dword_477834]
        fld dword ptr [eax+3C0h]
        push esi
        fsub dword ptr [ebx+4]
        fld dword ptr [eax+3C4h]
        fsub dword ptr [ebx+8]
        fld dword ptr [flt_470B04]
        fld st(1)
        fucompp
        fnstsw ax
        test ah, 44h
        jp loc_40742C
        fld dword ptr [flt_470B04]
        fld st(2)
        fucompp
        fnstsw ax
        test ah, 44h
        jp loc_40742C
        fstp st(0)
        mov dword ptr [esp+8], 3FC90FDBh
        fstp st(0)
        jmp loc_407434
loc_40742C:
        fxch st(1)
        fpatan
        fstp dword ptr [esp+8]
loc_407434:
        push edi
        xor edi, edi
        cmp [ebx+1F6h], di
        jle loc_40747A
        push ebp
        mov ebp, [esp+10h]
loc_407445:
        xor esi, esi
        cmp [ebx+1F4h], si
        jle loc_40746D
loc_407450:
        mov eax, [esp+18h]
        push ebp
        push edi
        push esi
        push eax
        call sub_4067D0
        test eax, eax
        jnz loc_407479
        movsx ecx, word ptr [ebx+1F4h]
        inc esi
        cmp esi, ecx
        jl loc_407450
loc_40746D:
        movsx edx, word ptr [ebx+1F6h]
        inc edi
        cmp edi, edx
        jl loc_407445
loc_407479:
        pop ebp
loc_40747A:
        mov eax, [ebx+1FCh]
        test ah, 2
        pop edi
        jz loc_40749A
        mov eax, [ebx+4]
        mov ebx, [ebx+200h]
        push eax
        mov esi, 492590h
        call sub_43DD10
loc_40749A:
        pop esi
        xor eax, eax
        pop ebx
        pop ecx
        ret 4
    }
}
#endif
