// 0x00426520: Player::LoadShotType — load a .sht shot-type file, compute
// diagonal movement speeds (speed * sin(pi/4)), and relocate the 10 ShotList
// offsets and ShotDefinition callback table indices (on_fire/on_update/etc.).
#include <math.h>
#include "th10/platform/archive_callers.hpp"
extern "C" const double dbl_pi_4;
extern "C" const unsigned int g_shot_on_fire_table[], g_shot_on_update_table[], g_shot_extra_table[], g_shot_skip_hit_table[];
#pragma code_seg(".text$02zparameter")
int PlayerShotLoader::Load(const char* name) {
    file = (ShotFileHeader*)Archive_LoadFile(name, 0, 0);
    if (!file) return -1;
    float projection = (float)sin(dbl_pi_4);
    file->projected_width = projection * file->width;
    file->projected_height = projection * file->height;
    file->projected_width = projection * file->width;
    file->projected_height = projection * file->height;
    for (int i = 0; i < file->group_count; ++i) {
        file->groups[i].offset += (unsigned int)file;
        ShotDefinitionRecord* record = file->groups[i].records;
        while (record->kind >= 0) {
            record->command = g_shot_on_fire_table[record->command];
            record->easing = g_shot_on_update_table[record->easing];
            record->variable = g_shot_extra_table[record->variable];
            record->callback = g_shot_skip_hit_table[record->callback];
            ++record;
        }
    }
    return 0;
}
#pragma code_seg()
