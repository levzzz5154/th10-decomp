// 0x004200D0: the app's draw task at priority 0x32 (registered by
// 0x00420470); flushes the pending animation
// batch and zeroes the two floats at 0x00491E64/0x00491E68.  Compiled in the
// anm_batch_flush native-LTCG cluster so Flush receives the manager in ESI.
#include "th10/render/quad_batch.hpp"

extern "C" float g_screen_shake_x;
extern "C" float g_screen_shake_y;

struct AppDrawFlush {
    __declspec(noinline) int Run();
};

#pragma code_seg(".text$001z3gapb")
int AppDrawFlush::Run() {
    g_sprt_ctrl->Flush();
    g_screen_shake_x = 0.0f;
    g_screen_shake_y = 0.0f;
    return 1;
}
#pragma code_seg()
