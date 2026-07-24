#include "th10/game/pool_constructors.hpp"

#include <cstring>

// Retail globals that publish the constructed managers.
uint32_t* DAT_00477840;  // effect manager instance
uint32_t* DAT_0047784c;  // progress manager instance
uint32_t* DAT_0047770c;  // entity block pool instance

// All three retail constructors share the same shape: a prologue of
// per-slot stores (sentinel bit clears, per-channel defaults, vtable
// pointers), followed by a full zero wipe of the whole block that makes
// every prologue store dead, then the constructed bit and the global
// publish. The readable forms keep only the observable effects and
// document the dead prologue.

// 0x0042B430 - Reset the effect manager. The retail prologue clears the
// in-use bit of nine embedded timer sentinels, wipes one 0x3AC-byte
// scratch record at +0x18 (with a 0xFFFF terminator half-word), and
// clears the in-use bit of 0x2D3 0x40-byte slots at +0x3F0 -- all dead
// stores, because the function then zeroes all 0x2E21 words. Bit 1 of
// the leading flags word marks the manager constructed and the instance
// is published through 0x00477840.
void EffectManager_ResetAndPublish(uint32_t* state) {
    memset(state, 0, kEffectManagerDwords * sizeof(uint32_t));
    state[0] |= 2u;
    DAT_00477840 = state;
}

// 0x0042C920 - Construct the progress manager. The retail prologue
// installs two vtable pointers and seeds four gauge channels with the
// {enabled = 1, limit = 999} defaults before the full 0x16B3-word wipe
// discards them. Bit 1 of the flags word at +0x04 marks the manager
// constructed and the instance is published through 0x0047784C.
uint32_t* ProgressManager_ConstructAndPublish(uint32_t* state) {
    memset(state, 0, kProgressManagerDwords * sizeof(uint32_t));
    state[1] |= 2u;
    DAT_0047784c = state;
    return state;
}

// 0x00413810 - Construct the entity block pool. Retail runs
// _eh_vector_constructor_iterator_ over six embedded arrays of
// 0x3AC-byte entities (10, 10, 9, 4, 2, and 7 elements at word offsets
// 4, 0x932, 0x1260, 0x1AA3, 0x1E4F, and 0x2025), then performs the same
// clear-and-publish tail as the other pool constructors: the sentinel
// bit clears and the 0x3AC-byte scratch wipe at +0x9A48 are dead
// because the whole 0x27B4-word block is zeroed afterwards. Bit 1 of
// the leading flags word marks the pool constructed and the instance is
// published through 0x0047770C.
uint32_t* EntityBlockPool_ConstructAndPublish(
        uint32_t* state, void (*construct_entity)(void*)) {
    static const struct {
        uint32_t word_offset;
        uint32_t count;
    } kArrays[6] = {
        {0x0004, 10}, {0x0932, 10}, {0x1260, 9},
        {0x1AA3, 4},  {0x1E4F, 2},  {0x2025, 7},
    };
    const uint32_t kEntityDwords = 0x3AC / 4;
    if (construct_entity != 0) {
        for (int range = 0; range < 6; ++range) {
            for (uint32_t index = 0; index < kArrays[range].count; ++index) {
                construct_entity(state + kArrays[range].word_offset +
                                 index * kEntityDwords);
            }
        }
    }
    memset(state, 0, kEntityBlockPoolDwords * sizeof(uint32_t));
    state[0] |= 2u;
    DAT_0047770c = state;
    return state;
}
