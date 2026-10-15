#include "th10/game/game_thread_queue_native.hpp"
extern "C" const float data_00470c2c;
extern "C" const char data_0046e658[];
struct ReplayManagerPanel {
 unsigned char pad_00[0x10];
 int display_state;
 unsigned char pad_14[0x1b0];
 unsigned char value;
};
typedef char Panel_state_is_10[offsetof(ReplayManagerPanel, display_state) == 0x10 ? 1 : -1];
typedef char Panel_value_is_1c4[offsetof(ReplayManagerPanel, value) == 0x1c4 ? 1 : -1];

// 0x00429A70: the replay manager's draw body. The draw task 0x0042A430 copies ECX to EDX and tail-calls here.
// The nominal fastcall ECX slot is unused; the panel arrives in EDX.
#pragma code_seg(".text$11panel")
__declspec(noinline) int __fastcall ReplayManager_Draw(void* callback_context_ecx, ReplayManagerPanel* panel) {
 if (data_00477810 != 0 && panel->display_state != 0 && panel->display_state == 1) {
    Vec3_00401530 position = {383.0f,450.0f,0.0f};
    unsigned int color;
    if ((float)panel->value < data_00470c30)
        color=0xff5050ffu;
    else if ((float)panel->value < data_00470c2c)
        color=0xffa0a0ffu;
    else
        color=0xffffffffu;
    GameThread_00401530* thread=g_ascii_manager;
    thread->current_4c=color;
    AsciiManager_AddFormatted(thread,&position,data_0046e658,(int)panel->value);
    g_ascii_manager->current_4c=-1;
 }
 return 1;
}
#pragma code_seg()
