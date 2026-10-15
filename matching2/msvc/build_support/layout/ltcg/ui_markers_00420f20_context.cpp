// Compiler context only; never selected as recovered game code. The animation
// manager callees are complete models so the pass derives their register
// arguments, and the marker handles escape as they do in the retail program.
#include "../../../src/game/mother/ui_markers.cpp"
#include "result_open_00423370/find.cpp"
#include "result_open_00423370/allocate.cpp"
#include "result_open_00423370/dispatcher_animation_helpers.cpp"
#include "../../../src/core/zunlib/platform_stop_worker_0044c150.cpp"

extern "C" void __stdcall UiMarkersObserve(DispatcherRef* handle);

#pragma code_seg(".text$30context")
extern "C" int __stdcall UiMarkersCompilerContext(
        GameUiThreadHost* hosts, const DispatcherVec3* positions, int count) {
    for (int index = 0; index < count; ++index) {
        hosts[index].CreateMarkers(&positions[index]);
        hosts[index].StopWorker();
        GameUi_ShowMarkers_00421180(&hosts[index], &positions[index]);
    }
    UiMarkersObserve(&g_queued_cleanup_a);
    UiMarkersObserve(&g_queued_cleanup_b);
    UiMarkersObserve(&g_queued_cleanup_c);
    return count;
}
#pragma code_seg()
