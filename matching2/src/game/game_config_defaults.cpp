#include "th10/game/game_config_defaults.hpp"

#ifndef _MSC_VER
#include <cstring>
#else
extern "C" void* memset(void*, int, unsigned long);
#endif

// Preset table declared in retail at 0x00474E88..0x00474E98. The four
// words and the trailing halfword are copied verbatim into the record.
extern uint32_t DAT_00474e88;
extern uint32_t DAT_00474e8c;
extern uint32_t DAT_00474e90;
extern uint32_t DAT_00474e94;
extern uint16_t DAT_00474e98;

static_assert(sizeof(GameConfigRecord) == 0x34,
              "GameConfigRecord must match the retail 0x34-byte layout");

// 0x00418C40 - Reset a 0x34-byte configuration record to the retail
// defaults: clear all thirteen words, then apply the version tag
// 0x00100003, the 600/600 axis thresholds, the enable flags at
// +0x1B/+0x1C, mode 2, the 100/0x50 volume pair, bit 8 of the flags
// word at +0x30, and the preset block copied from 0x00474E88.
// The store order below follows the retail function.
void GameConfig_InitializeDefaults(GameConfigRecord* config) {
    memset(config, 0, sizeof(GameConfigRecord));
    config->threshold_16 = 600;
    config->threshold_18 = 600;
    config->flag_1b = 1;
    config->flag_1c = 1;
    config->flags_30 |= 0x100u;
    config->byte_1a = 0;
    config->signature = 0x00100003u;
    config->byte_1d = 0;
    config->byte_1e = 0;
    config->preset_words[0] = DAT_00474e88;
    config->preset_words[1] = DAT_00474e8c;
    config->preset_words[2] = DAT_00474e90;
    config->preset_words[3] = DAT_00474e94;
    config->preset_half = DAT_00474e98;
    config->mode_1f = 2;
    config->byte_22 = 0;
    config->volume_20 = 100;
    config->volume_21 = 0x50;
}
