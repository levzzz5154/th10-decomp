#include "th10/game/enemy_drop_sweep.hpp"

#ifdef _MSC_VER
extern "C" void sub_41BB00(void*, void*, int, int, int, int);
extern "C" int sub_448DB0(void*, int, int, int);
extern "C" void* dword_4776F0;
#endif

#include <cstring>

namespace {

int32_t ReadI32(const uint8_t* bytes) {
    int32_t value;
    memcpy(&value, bytes, sizeof(value));
    return value;
}

void WriteI32(uint8_t* bytes, int32_t value) {
    memcpy(bytes, &value, sizeof(value));
}

}  // namespace

// 0x0041BA50 - Sweep the enemy slots for finished pickup effects.
// Retail walks all 0x96 slots in ESI-relative order; both recognized
// kinds (1 and 4) map to drop kind 9, and each hit clears the active
// word before spawning and playing the sound.
#ifdef _MSC_VER
__declspec(naked) int Enemy_SweepPendingDropsRetail() {
    __asm {
        push ecx
        push ebp
        push edi
        lea edi, [esi+3C0h]
        mov ebp, 96h
        _emit 8Bh
        _emit 0FFh
loc_41BA60:
        mov eax, [edi+30h]
        test eax, eax
        jz loc_41BAE2
        mov eax, [edi+34h]
        cmp eax, 1
        jz loc_41BA74
        cmp eax, 4
        jnz loc_41BAE2
loc_41BA74:
        cmp eax, 1
        mov dword ptr [edi+30h], 0
        jnz loc_41BA90
        push 400CCCCDh
        push 0BFC90FDBh
        push 0FFFFFFFFh
        push 9
        jmp loc_41BABD
loc_41BA90:
        cmp eax, 4
        jnz loc_41BAA5
        push 400CCCCDh
        push 0BFC90FDBh
        push 0FFFFFFFFh
        push 9
        jmp loc_41BABD
loc_41BAA5:
        cmp eax, 0Ah
        jz loc_41BAAF
        cmp eax, 0Bh
        jnz loc_41BAE2
loc_41BAAF:
        push 400CCCCDh
        push 0BFC90FDBh
        push 0FFFFFFFFh
        push 5
loc_41BABD:
        mov eax, esi
        mov ecx, edi
        call sub_41BB00
        mov ecx, dword ptr [dword_4776F0]
        mov edx, [ecx+3E0B50h]
        push 189h
        lea eax, [esp+0Ch]
        push eax
        push edx
        call sub_448DB0
loc_41BAE2:
        add edi, 3F0h
        dec ebp
        jnz loc_41BA60
        pop edi
        xor eax, eax
        pop ebp
        pop ecx
        ret
    }
}
#endif

uint32_t Enemy_SweepPendingDrops(
        uint8_t* manager,
        void (*spawn_drop)(uint8_t* slot, int32_t kind, int32_t id,
                           float angle, float speed),
        void (*play_drop_sound)()) {
    for (int index = 0; index < 0x96; ++index) {
        uint8_t* slot = manager + 0x3C0 + index * 0x3F0;
        if (ReadI32(slot + 0x30) == 0) {
            continue;
        }
        const int32_t kind = ReadI32(slot + 0x34);
        if (kind != 1 && kind != 4) {
            continue;
        }
        WriteI32(slot + 0x30, 0);
        if (spawn_drop != 0) {
            spawn_drop(slot, 9, -1, -1.5707964f, 2.2f);
        }
        if (play_drop_sound != 0) {
            play_drop_sound();
        }
    }
    return 0;
}
