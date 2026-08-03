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

#ifdef _MSC_VER
extern "C" unsigned long dword_474E88;
extern "C" unsigned long dword_474E8C;
extern "C" unsigned long dword_474E90;
extern "C" unsigned long dword_474E94;
extern "C" unsigned short word_474E98;
#endif

#ifndef _MSC_VER
static_assert(sizeof(GameConfigRecord) == 0x34,
              "GameConfigRecord must match the retail 0x34-byte layout");
#endif

// 0x00418C40 - Reset a 0x34-byte configuration record to the retail
// defaults: clear all thirteen words, then apply the version tag
// 0x00100003, the 600/600 axis thresholds, the enable flags at
// +0x1B/+0x1C, mode 2, the 100/0x50 volume pair, bit 8 of the flags
// word at +0x30, and the preset block copied from 0x00474E88.
// The store order below follows the retail function.
#ifdef _MSC_VER
__declspec(naked) void GameConfig_InitializeDefaults(GameConfigRecord* config) {
    __asm {
        push esi
        push edi
        xor eax, eax
        mov ecx, 0Dh
        mov edi, edx
        rep stosd
        mov ecx, 258h
        mov word ptr [edx+16h], cx
        mov word ptr [edx+18h], cx
        mov cl, 1
        mov [edx+1Bh], cl
        mov [edx+1Ch], cl
        or dword ptr [edx+30h], 100h
        xor al, al
        mov [edx+1Ah], al
        mov dword ptr [edx], 100003h
        mov [edx+1Dh], al
        mov [edx+1Eh], al
        mov esi, dword_474E88
        lea ecx, [edx+4]
        mov [ecx], esi
        mov esi, dword_474E8C
        mov [ecx+4], esi
        mov esi, dword_474E90
        mov [ecx+8], esi
        mov esi, dword_474E94
        mov [ecx+0Ch], esi
        mov si, word_474E98
        pop edi
        mov word ptr [ecx+10h], si
        mov byte ptr [edx+1Fh], 2
        mov [edx+22h], al
        mov byte ptr [edx+20h], 64h
        mov byte ptr [edx+21h], 50h
        pop esi
        ret
    }
}
#else
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
#endif
