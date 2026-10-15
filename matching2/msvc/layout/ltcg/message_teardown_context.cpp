// Actual complete 0x004203F0 caller, compiled as an unselected entry.
// Its original owner in recovery_leaves.cpp is retained.
#include "../../src/game/ending/ending_release.cpp"
#include "message_teardown_helpers.cpp"
extern "C" void* data_00477810;
extern "C" void* g_title;
extern "C" void* g_loading;
extern "C" void* data_00477838;
extern "C" void __stdcall ReleaseGlobalManager_00417c80(void*);
extern "C" void __stdcall ReleaseGlobalScript_0042cb60(void*);
extern "C" void __stdcall ReleaseGlobalResource_0041fb50(void*);
extern "C" void __stdcall ReleaseGlobalPending_004294a0(void*);
#pragma code_seg(".text$05globals")
void Recovery_ReleaseGlobalStates() {
    void* manager_state = data_00477810;
    if (manager_state) { ReleaseGlobalManager_00417c80(manager_state);entry_free_004524a1(manager_state); }
    void* script_state = g_title;
    if (script_state) { ReleaseGlobalScript_0042cb60(script_state);entry_free_004524a1(script_state); }
    void* resource_state = g_loading;
    if (resource_state) { ReleaseGlobalResource_0041fb50(resource_state);entry_free_004524a1(resource_state); }
    EndingState* small_state = (EndingState*)g_ending;
    if (small_state) { Ending_Release(small_state);entry_free_004524a1(small_state); }
    void* pending_block = data_00477838;
    if (pending_block) { ReleaseGlobalPending_004294a0(pending_block);entry_free_004524a1(pending_block); }
}
#pragma code_seg()
