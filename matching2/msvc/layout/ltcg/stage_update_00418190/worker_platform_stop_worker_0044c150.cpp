#define g_sprt_ctrl stage_worker_g_sprt_ctrl
#define g_front stage_worker_g_front
#define data_00474c40 stage_worker_data_00474c40
#define g_ascii_manager stage_worker_data_004776e0
#define g_enemy_ctrl stage_worker_g_enemy_ctrl
#define g_player stage_worker_data_00477834
#define data_00477838 stage_worker_data_00477838
#define data_0047783c stage_worker_data_0047783c
#define data_00476f78 stage_worker_data_00476f78
#define data_00491fc4 stage_worker_data_00491fc4
#define data_00491fb8 stage_worker_data_00491fb8
#define data_00492590 stage_worker_data_00492590
#include "th10/platform/worker.hpp"

// ESI is selected by native LTCG from the real caller/callee relationship.
#pragma code_seg(".text$0044c150_fn")
__declspec(noinline) void PlatformWorker::Stop() {
    if (thread) {
        stop_requested = 1;
        running = 0;
        while (WaitForSingleObject(thread, 200) == 258) {
            stop_requested = 1;
            running = 0;
            Sleep(1);
        }
        CloseHandle(thread);
        thread = 0;
        entry = 0;
    }
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef data_00474c40
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
