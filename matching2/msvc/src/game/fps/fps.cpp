#include "th10/game/fps_runtime.hpp"
#include "th10/game/game_thread_queue_native.hpp"
extern "C" GameThread_00401530 *g_ascii_manager;
extern "C" int data_00491fb8;
extern "C" unsigned char data_00491d66;
extern "C" const float data_00470c30;
extern "C" const float data_00470c64;
extern "C" const char data_0046d198[];

// Complete FPS display180: capture the refreshed rate once for color and text.
#pragma code_seg(".text$07draw")
int FPS::Draw() {
    Update();
    if (data_00491fb8 != 0xE) {
        GameThread_00401530 *thread = g_ascii_manager;
        const float updated_fps = fps;
        if (thread) {
        unsigned int color;
        if (updated_fps < data_00470c30) color=0xFF5050FF;
        else if (updated_fps < data_00470c64) color=0xFFA0A0FF;
        else color=0xFFFFFFFF;
        thread->current_4c=color;
        Vec3_00401530 position={590.0f,470.0f,0.0f};
        AsciiManager_AddFormattedMarked(thread,&position,data_0046d198,(double)updated_fps);
        g_ascii_manager->current_4c=0xFFFFFFFF;
        }
    }
    frame_count += (unsigned int)data_00491d66 + 1;
    return 1;
}
#pragma code_seg()


#include "th10/game/fps_runtime.hpp"

// 0x00413690: the FPS counter's draw task: counter in ECX, result in EAX, plain RET.
#pragma code_seg(".text$09callback")
__declspec(noinline) int __fastcall FPS_OnDraw(FPS *counter) {
    return counter->Draw();
}
#pragma code_seg()

