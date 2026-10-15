#define g_sprt_ctrl stage_bind_g_sprt_ctrl
#define g_front stage_bind_g_front
#define g_globals stage_bind_data_00474c40
#define g_ascii_manager stage_bind_data_004776e0
#define g_enemy_ctrl stage_bind_g_enemy_ctrl
#define g_player stage_bind_data_00477834
#define data_00477838 stage_bind_data_00477838
#define data_0047783c stage_bind_data_0047783c
#define g_game_speed stage_bind_data_00476f78
#define data_00491fc4 stage_bind_data_00491fc4
#define data_00491fb8 stage_bind_data_00491fb8
#define g_sound_manager stage_bind_data_00492590
#include "th10/game/enemy_script_bind_0040d830.hpp"

extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)

#pragma code_seg(".text$00450470_fn")
__declspec(noinline) int BindScriptTable_0040d830::Resolve(const char* name) {
    int low = 0;
    int high = this->count;
    if (--high >= 0) {
        const BindScriptEntry_0040d830* entries = this->entries;
        do {
            const int middle = low + (high - low) / 2;
            const BindScriptEntry_0040d830* entry = &entries[middle];
            const int order = strcmp(name, entry->name);
            if (order == 0)
                return static_cast<int>(entry->value) + 16;
            if (order < 0)
                high = middle - 1;
            else
                low = middle + 1;
        } while (low <= high);
    }
    return 0;
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef g_game_speed
#undef data_00491fc4
#undef data_00491fb8
#undef g_sound_manager
