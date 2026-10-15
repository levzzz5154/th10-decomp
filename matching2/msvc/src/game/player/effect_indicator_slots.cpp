#include <stddef.h>
typedef unsigned int uint32_t;
typedef int int32_t;
#include <string.h>

extern "C" float g_game_speed;

struct EffectIndicatorTimerRetail {
    uint32_t previous_frame_bits;  // +0x00; -999999 before the first countdown
    uint32_t current_frame_bits; // +0x04
    float elapsed;        // +0x08; retail stores the float image
    const float* speed;          // +0x0C
    uint32_t flags;              // +0x10; bit 0 means initialized
};

struct SlotPositionRetail { float x, y, z; };

struct EffectIndicatorSlotRetail {
    uint32_t value_00_bits;       // +0x00; caller supplies raw dword bits
    uint32_t value_04_bits;       // +0x04
    uint32_t reserved_08[4];      // +0x08..+0x17
    SlotPositionRetail position;            // +0x18..+0x23
    uint32_t reserved_24[8];      // +0x24..+0x43
    EffectIndicatorTimerRetail timer; // +0x44..+0x57
    uint32_t mode;                // +0x58
    uint32_t counter;             // +0x5C
    uint32_t limit;               // +0x60
    uint32_t phase;               // +0x64
    uint32_t flags;               // +0x68; bit 0 is occupied, bit 1 is active
};

struct EffectIndicatorManagerRetail {
    unsigned char unknown_0000_350b[0x350c];
    EffectIndicatorSlotRetail slots[0x20];
};

typedef char EffectIndicatorSlotRetail_size_must_be_0x6c[
    sizeof(EffectIndicatorSlotRetail) == 0x6c ? 1 : -1];
typedef char EffectIndicatorSlots_offset_must_be_0x350c[
    offsetof(EffectIndicatorManagerRetail, slots) == 0x350c ? 1 : -1];

// Ghidra's 0x00427B50 entry is __fastcall-shaped: ECX is unused, the manager
// is in EDX, and the position plus four scalar words are on the stack. The two
// scalar payloads are kept as raw bits because callers pass float encodings.
// The return value is the first available slot, or the one-past-pool pointer.
extern "C" __declspec(noinline) EffectIndicatorSlotRetail* __fastcall
EffectIndicatorPool_AllocateRetail_00427b50(
    uint32_t unused_ecx,
    EffectIndicatorManagerRetail* manager,
    const SlotPositionRetail* volatile position,
    uint32_t value_00_bits,
    uint32_t value_04_bits,
    int32_t countdown_frames,
    uint32_t mode) {
    (void)unused_ecx;
    // Retail reads the stack position pointer once before searching the pool.
    const SlotPositionRetail* saved_position = position;

    EffectIndicatorSlotRetail* slot = manager->slots;
    for (int index = 0; index < 0x20; ++index, ++slot) {
        if ((slot->flags & 1u) != 0) {
            continue;
        }

        // Retail first clears all 27 words, marks the slot, then redundantly
        // clears words 6 through 16 before copying the position.
        memset(slot, 0, sizeof(*slot));
        slot->flags |= 3u;
        memset(&slot->position, 0,
               sizeof(slot->position) + sizeof(slot->reserved_24));

        slot->position = *saved_position;
        // Keep these two observed writes adjacent and before the timer flag load.
        volatile uint32_t* payload = &slot->value_00_bits;
        payload[0] = value_00_bits;
        payload[1] = value_04_bits;

        if ((slot->timer.flags & 1u) == 0) {
            slot->timer.current_frame_bits = 0;
            slot->timer.previous_frame_bits = 0xfff0bdc1u;
            slot->timer.elapsed = 0.0f;
            slot->timer.speed = &g_game_speed;
            slot->timer.flags |= 1u;
        }
        slot->timer.current_frame_bits = static_cast<uint32_t>(countdown_frames);
        slot->timer.previous_frame_bits =
            static_cast<uint32_t>(countdown_frames) - 1u;
        slot->timer.elapsed = static_cast<float>(countdown_frames);

        slot->mode = mode;
        slot->counter = 0;
        slot->limit = 999999u;
        slot->phase = 4u;
        return slot;
    }

    return slot;
}
