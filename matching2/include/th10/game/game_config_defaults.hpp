#pragma once

#include <cstdint>

// 0x34-byte configuration record reset by the retail defaults
// initializer at 0x00418C40. Field names describe the observed default
// values; the four-word block at +0x04 and the halfword at +0x14 are
// copied from the constant table at 0x00474E88..0x00474E98.
struct GameConfigRecord {
    uint32_t signature;        // +0x00 = 0x00100003 (version tag)
    uint32_t preset_words[4];  // +0x04 copied from DAT_00474E88..DAT_00474E94
    uint16_t preset_half;      // +0x14 copied from DAT_00474E98
    uint16_t threshold_16;     // +0x16 = 600 (axis threshold)
    uint16_t threshold_18;     // +0x18 = 600 (axis threshold)
    uint8_t byte_1a;           // +0x1A = 0
    uint8_t flag_1b;           // +0x1B = 1
    uint8_t flag_1c;           // +0x1C = 1
    uint8_t byte_1d;           // +0x1D = 0
    uint8_t byte_1e;           // +0x1E = 0
    uint8_t mode_1f;           // +0x1F = 2
    uint8_t volume_20;         // +0x20 = 100 (0x64)
    uint8_t volume_21;         // +0x21 = 0x50
    uint8_t byte_22;           // +0x22 = 0
    uint8_t reserved_23[13];   // +0x23..+0x2F cleared
    uint32_t flags_30;         // +0x30, bit 8 set after the clear
};

// 0x00418C40 - Clear the record and apply the retail defaults.
void GameConfig_InitializeDefaults(GameConfigRecord* config);
