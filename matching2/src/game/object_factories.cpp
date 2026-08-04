#include "th10/game/object_factories.hpp"

#ifdef _MSC_VER
extern "C" void* sub_452493(unsigned long);
extern "C" void* sub_41F850(void*);
extern "C" int sub_41FAC0(void);
extern "C" void sub_41FB50(void*);
extern "C" void j__free(void*);
extern "C" void* sub_41C030(void*, void*);
extern "C" int sub_41C120(void);
extern "C" void sub_41C1C0(void*);
#endif

#include <cstring>

extern "C" void _free(void* memory);

// Published score manager (retail 0x0047781C).
uint32_t* DAT_0047781c;

// 0x0041C290 - Create the score manager. Retail news 0x45C bytes,
// constructs the embedded sub-object at word 4, then zeroes all 0x117
// words (killing the construction) while publishing the pointer through
// 0x0047781C, and finally runs the score-display initializer; a failed
// initializer tears the object down again.
#ifdef _MSC_VER
__declspec(naked) uint32_t* ScoreManager_CreateAndInitRetail() {
    __asm {
        push esi
        push 45Ch
        call sub_452493
        mov esi, eax
        add esp, 4
        test esi, esi
        jz loc_41C2C1
        push edi
        lea edx, [esi+10h]
        call sub_41C030
        mov ecx, 117h
        xor eax, eax
        mov edi, esi
        rep stosd
        mov dword ptr [DAT_0047781c], esi
        pop edi
        jmp loc_41C2C3
loc_41C2C1:
        xor esi, esi
loc_41C2C3:
        push ebx
        mov ebx, esi
        call sub_41C120
        test eax, eax
        pop ebx
        jz loc_41C2E7
        test esi, esi
        jz loc_41C2E3
        push esi
        call sub_41C1C0
        push esi
        call j__free
        add esp, 4
loc_41C2E3:
        xor eax, eax
        pop esi
        ret
loc_41C2E7:
        mov eax, esi
        pop esi
        ret
    }
}
#endif

uint32_t* ScoreManager_CreateAndInit(void* (*allocate)(uint32_t size),
                                     void (*construct_base)(uint32_t* base),
                                     int32_t (*init)(uint32_t* state),
                                     void (*destroy)(uint32_t* state)) {
    uint32_t* state =
        allocate != 0 ? (uint32_t*)allocate(0x45C) : (uint32_t*)0;
    if (state != 0) {
        if (construct_base != 0) {
            construct_base(state + 4);  // dead: the wipe below covers it
        }
        memset(state, 0, 0x117 * sizeof(uint32_t));
        DAT_0047781c = state;
    }
    const int32_t failed = init != 0 ? init(state) : 0;
    if (failed != 0) {
        if (state != 0) {
            if (destroy != 0) {
                destroy(state);
            }
            _free(state);
        }
        return 0;
    }
    return state;
}

// 0x0041FD00 - Create one enemy slot. The constructor edge returns the
// object (retail FUN_0041F850 returns it in EAX); the initializer runs
// unconditionally, matching retail.
#ifdef _MSC_VER
__declspec(naked) uint32_t* EnemySlot_CreateAndInitRetail() {
    __asm {
        push ebx
        push 3F0h
        call sub_452493
        add esp, 4
        test eax, eax
        jz loc_41FD1F
        push esi
        mov esi, eax
        call sub_41F850
        mov ebx, eax
        pop esi
        jmp loc_41FD21
loc_41FD1F:
        xor ebx, ebx
loc_41FD21:
        call sub_41FAC0
        test eax, eax
        jz loc_41FD41
        test ebx, ebx
        jz loc_41FD3D
        push ebx
        call sub_41FB50
        push ebx
        call j__free
        add esp, 4
loc_41FD3D:
        xor eax, eax
        pop ebx
        ret
loc_41FD41:
        mov eax, ebx
        pop ebx
        ret
    }
}
#endif

uint32_t* EnemySlot_CreateAndInit(void* (*allocate)(uint32_t size),
                                  uint32_t* (*construct)(uint32_t* state),
                                  int32_t (*init)(),
                                  void (*destroy)(uint32_t* state)) {
    uint32_t* state =
        allocate != 0 ? (uint32_t*)allocate(0x3F0) : (uint32_t*)0;
    if (state != 0 && construct != 0) {
        state = construct(state);
    }
    const int32_t failed = init != 0 ? init() : 0;
    if (failed != 0) {
        if (state != 0) {
            if (destroy != 0) {
                destroy(state);
            }
            _free(state);
        }
        return 0;
    }
    return state;
}
