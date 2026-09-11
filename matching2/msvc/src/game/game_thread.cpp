// 0x00401000: construct the global game thread object in place.
//
// The retail body stores the type marker, retires the flag bits of the two
// per-player slots, clears them and publishes a handful of scalar defaults.
// The object pointer arrives in ESI and is returned in EAX, so the body is
// compiled as a native LTCG cluster (see layout/ltcg/game_thread.json).

#include <string.h>

// Type marker installed at +0x00 (the object's method table in retail).
extern "C" unsigned char data_0046cb14[];
// Global pointer to the constructed thread.
extern "C" void* data_004776e0;

// +0x14 and +0x3C0: the two per-player state blocks.
struct GameThreadSlot {
    char pad_000[0x6C];
    unsigned field_06C;
    char pad_070[0x40];
    unsigned field_0B0;
    char pad_0B4[0x48];
    unsigned field_0FC;
    char pad_100[0x28];
    unsigned field_128;
    char pad_12C[0x48];
    unsigned field_174;
    char pad_178[0x38];
    unsigned field_1B0;
    char pad_1B4[0x48];
    unsigned field_1FC;
    char pad_200[0x28];
    unsigned field_228;
    char pad_22C[0x14C];
    unsigned field_378;
    char pad_37C[8];
    unsigned short field_384;
    char pad_386[0x26];
};

struct GameThread {
    const void* type;
    unsigned flags;
    char pad_008[0x0C];
    GameThreadSlot slots[2];
    char pad_76C[0x8974 - 0x76C];
    int field_8974;
    float field_8978;
    float field_897C;
    char pad_8980[4];
    int field_8984;
    char pad_8988[4];
    int field_898C;
    char pad_8990[0x89AC - 0x8990];

    __declspec(noinline) GameThread();
};

// Clears the "slot is live" bit of one slot flag word. Holding the flag's
// address in a pointer keeps the store in the read-modify-write form the
// image uses.
#define GameThread_ClearSlotFlag(address) \
    do { unsigned* flag_ = (address); *flag_ &= ~1u; } while (0)

#pragma code_seg(".text$01thread")
GameThread::GameThread() {
    this->type = data_0046cb14;
    GameThreadSlot* slot = &this->slots[0];
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
    slot = &this->slots[1];
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
    data_004776e0 = this;
    this->field_8974 = -1;
    this->field_8978 = 1.0f;
    this->field_897C = 1.0f;
    this->field_8984 = 0;
    this->field_898C = 9;
}
#pragma code_seg()
