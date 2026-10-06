#define data_00491c10 stage_worker_data_00491c10
#define data_0047770c stage_worker_data_0047770c
#define data_00474c40 stage_worker_data_00474c40
#define data_004776e0 stage_worker_data_004776e0
#define data_00477704 stage_worker_data_00477704
#define data_00477834 stage_worker_data_00477834
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
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef data_004776e0
#undef data_00477704
#undef data_00477834
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
