#include "th10/source_views/fun_a1dd06_0.hpp"
#include "../../../src/core/main/game_frame_advance.cpp"
#include "th10/source_views/fun_a1dd06_1.hpp"
#include "../../../src/game/mother/render_stage_state.cpp"
#include "th10/source_views/fun_a1dd06_6.hpp"
__declspec(noinline) void* WorkerThread_00439390::Stop() {
    void* result = handle;
    if (result != 0) {
        stopping = 1;
        stop_reason = 0;
        while (entry_free_004524a1(result) == 258) {
            stopping = 1;
            stop_reason = 0;
            entry_free_004524a1(handle);
        }
        entry_free_004524a1(handle);
        handle = 0;
        joinable = 0;
    }
    return result;
}

#pragma code_seg()
