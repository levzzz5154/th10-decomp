// 0x00426520: load parameter groups and relocate their command-table indices.
#include <math.h>
#include "th10/platform/archive_callers.hpp"
extern "C" const double dbl_pi_4;
extern "C" const unsigned int g_music_room_commands[], g_music_room_easings[], g_music_room_variable_map[], g_music_room_callback_map[];
#pragma code_seg(".text$a11body")
int ParameterLoader::Load(const char* name) {
    file = (ParameterFile*)Archive_LoadFile(name, 0, 0);
    if (!file) return -1;
    float projection = (float)sin(dbl_pi_4);
    file->projected_width = projection * file->width;
    file->projected_height = projection * file->height;
    file->projected_width = projection * file->width;
    file->projected_height = projection * file->height;
    for (int i = 0; i < file->group_count; ++i) {
        file->groups[i].offset += (unsigned int)file;
        ParameterRecord* record = file->groups[i].records;
        while (record->kind >= 0) {
            record->command = g_music_room_commands[record->command];
            record->easing = g_music_room_easings[record->easing];
            record->variable = g_music_room_variable_map[record->variable];
            record->callback = g_music_room_callback_map[record->callback];
            ++record;
        }
    }
    return 0;
}
#pragma code_seg()
