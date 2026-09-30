#include "th10/game/marktext_dispatcher_context/worker.hpp"

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
