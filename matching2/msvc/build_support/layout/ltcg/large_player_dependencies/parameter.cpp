// 0x00426520: load parameter groups and relocate their command-table indices.
#include <math.h>
#include "th10/platform/archive_callers.hpp"
extern "C" const double dbl_pi_4;
extern "C" const unsigned int data_0047476c[], data_00474778[], data_00491bf4[], data_00491bf8[];
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
            record->command = data_0047476c[record->command];
            record->easing = data_00474778[record->easing];
            record->variable = data_00491bf4[record->variable];
            record->callback = data_00491bf8[record->callback];
            ++record;
        }
    }
    return 0;
}
#pragma code_seg()
