#define data_00491c10 stage_hud_data_00491c10
#define data_0047770c stage_hud_data_0047770c
#define data_00474c40 stage_hud_data_00474c40
#define data_004776e0 stage_hud_data_004776e0
#define data_00477704 stage_hud_data_00477704
#define g_player stage_hud_data_00477834
#define data_00477838 stage_hud_data_00477838
#define data_0047783c stage_hud_data_0047783c
#define data_00476f78 stage_hud_data_00476f78
#define data_00491fc4 stage_hud_data_00491fc4
#define data_00491fb8 stage_hud_data_00491fb8
#define data_00492590 stage_hud_data_00492590
#include "hud_view.hpp"
extern "C" short data_004749ce[];
// 0x0043DC90
#pragma code_seg(".text$0043dc90_fn")
int SoundQueue::Queue(int sound_id, int request) {
    int priority = data_004749ce[sound_id * 4];
    int slot;
    for (slot = 0; slot < 12; ++slot) {
        if (sound_ids[slot] < 0)
            break;
        if (sound_ids[slot] == sound_id) {
            int count = counts[slot];
            if (count < 128) {
                requests[slot][count] = request;
                ++counts[slot];
            }
            return slot;
        }
    }
    if (slot < 12) {
        sound_ids[slot] = sound_id;
        priorities[sound_id] = priority;
        requests[slot][0] = request;
        ++counts[slot];
    }
    return slot;
}
#pragma code_seg()


#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef data_004776e0
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
