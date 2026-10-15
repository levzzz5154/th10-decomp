// 0x00401000: the ASCII manager's constructor (GameThread is this file's view
// of the object; the full layout is AsciiManager in th10/game/ascii_manager.hpp).
//
// The retail body stores the type marker, retires the flag bits of the two
// per-player slots, clears them and publishes a handful of scalar defaults.
// The object pointer arrives in ESI and is returned in EAX, so the body is
// compiled as a native LTCG cluster (see layout/ltcg/game_thread.json).
// The including driver selects the code section.

#include <string.h>

// Global pointer to the constructed thread.
extern "C" void* g_ascii_manager;

#include "th10/game/game_thread.hpp"

// Clears the "slot is live" bit of one slot flag word. Holding the flag's
// address in a pointer keeps the store in the read-modify-write form the
// image uses.
#define GameThread_ClearSlotFlag(address) \
    do { unsigned* flag_ = (address); *flag_ &= ~1u; } while (0)

GameThread::GameThread() {
    GameThreadSlot* slot = &this->slots_0014;
    GameThread_ClearSlotFlag(&slot->field_06C);
    GameThread_ClearSlotFlag(&slot->field_0B0);
    GameThread_ClearSlotFlag(&slot->field_0FC);
    GameThread_ClearSlotFlag(&slot->field_128);
    GameThread_ClearSlotFlag(&slot->field_174);
    GameThread_ClearSlotFlag(&slot->field_1B0);
    GameThread_ClearSlotFlag(&slot->field_1FC);
    GameThread_ClearSlotFlag(&slot->field_228);
    GameThread_ClearSlotFlag(&slot->field_378);
    memset(slot, 0, sizeof(*slot));
    slot->field_384 = 0xFFFF;
    slot = &this->slots_03c0;
    GameThread_ClearSlotFlag(&slot->field_06C);
    GameThread_ClearSlotFlag(&slot->field_0B0);
    GameThread_ClearSlotFlag(&slot->field_0FC);
    GameThread_ClearSlotFlag(&slot->field_128);
    GameThread_ClearSlotFlag(&slot->field_174);
    GameThread_ClearSlotFlag(&slot->field_1B0);
    GameThread_ClearSlotFlag(&slot->field_1FC);
    GameThread_ClearSlotFlag(&slot->field_228);
    GameThread_ClearSlotFlag(&slot->field_378);
    memset(slot, 0, sizeof(*slot));
    slot->field_384 = 0xFFFF;
    memset(this, 0, sizeof(*this));
    this->flags |= 2u;
    g_ascii_manager = this;
    this->field_8974 = -1;
    this->field_8978 = 1.0f;
    this->field_897C = 1.0f;
    this->field_8984 = 0;
    this->field_898C = 9;
}
