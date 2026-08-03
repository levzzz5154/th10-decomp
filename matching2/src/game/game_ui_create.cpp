#include "th10/game/game_ui_create.hpp"

#include <cstring>

#include "th10/game/game_config_defaults.hpp"

#ifdef _MSC_VER
extern "C" void* sub_452493(unsigned long);
extern "C" void sub_418C40(void*);
extern "C" unsigned long dword_491C30;
extern "C" unsigned long dword_477810;
extern "C" void sub_420EA0(void*, void*, void*);
#endif

// Published game UI manager (retail 0x00477810).
uint32_t* DAT_00477810;

// 0x004180E0 - Create the game UI manager. Retail news 0x60 bytes,
// constructs the embedded config record at word 9 (0x00418C40), then
// zeroes all 0x18 words - killing the construction - before evicting
// managed device resources, stashing the caller's return address in
// word 0x17, publishing the pointer, setting the started bit, and
// spawning the UI worker thread.
#ifdef _MSC_VER
__declspec(naked) uint32_t* GameUi_CreateAndPublish(
        void* (*allocate)(uint32_t size),
        void (*evict_managed_resources)(),
        void (*spawn_worker)(void* start_address, void* argument),
        void* worker_proc, uint32_t return_address) {
    __asm {
        push esi
        push edi
        push 60h
        call sub_452493
        mov esi, eax
        add esp, 4
        test esi, esi
        je skip_construct
        mov eax, [esi+20h]
        and eax, 0FFFFFFFEh
        lea edx, [esi+24h]
        mov [esi+20h], eax
        call sub_418C40
        mov ecx, 18h
        xor eax, eax
        mov edi, esi
        rep stosd
        jmp after_construct
skip_construct:
        xor esi, esi
after_construct:
        mov eax, dword_491C30
        mov ecx, [eax]
        push eax
        call dword ptr [ecx+14h]
        mov edx, [esp+0Ch]
        mov [esi+5Ch], edx
        mov edx, [esi+58h]
        push 0
        or edx, 4
        push 417C70h
        mov edi, 491C28h
        mov dword_477810, esi
        mov [esi+58h], edx
        call sub_420EA0
        pop edi
        mov eax, esi
        pop esi
        ret 4
    }
}
#else
uint32_t* GameUi_CreateAndPublish(void* (*allocate)(uint32_t size),
                                  void (*evict_managed_resources)(),
                                  void (*spawn_worker)(void* start_address,
                                                       void* argument),
                                  void* worker_proc,
                                  uint32_t return_address) {
    uint32_t* state =
        allocate != 0 ? (uint32_t*)allocate(0x60) : (uint32_t*)0;
    if (state != 0) {
        state[8] &= ~1u;  // dead: the wipe below covers it
        GameConfig_InitializeDefaults(
            (GameConfigRecord*)(state + 9));  // dead: wiped below
        memset(state, 0, 0x18 * sizeof(uint32_t));
    }
    if (evict_managed_resources != 0) {
        evict_managed_resources();
    }
    if (state == 0) {
        // Retail continues and writes through the null pointer here.
        return 0;
    }
    state[0x17] = return_address;
    DAT_00477810 = state;
    state[0x16] |= 4u;
    if (spawn_worker != 0) {
        spawn_worker(worker_proc, 0);
    }
    return state;
}
#endif
