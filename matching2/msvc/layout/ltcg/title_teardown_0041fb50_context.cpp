#include "title_teardown_0041fb50/title_teardown_dependencies.hpp"
#include "title_teardown_0041fb50/message_teardown_helpers.cpp"

#pragma code_seg(".text$01entity")
inline TitleAnimation_00401FF0::~TitleAnimation_00401FF0() {
    void* owned = resource;
    if (owned)
        entry_free_00452422(owned);
    resource = 0;
}
#pragma code_seg()

#pragma code_seg(".text$14worker")
inline TitleWorker_0044C130::~TitleWorker_0044C130() {
    Stop();
}
#pragma code_seg()

#pragma code_seg(".text$02pair")
extern "C" __declspec(noinline) int __cdecl ReleasePair_0041f930() {
    AnimationResource_00447810** slot = reinterpret_cast<AnimationResource_00447810**>(&data_00491c10->banks[6]);
    if (*slot) {
        (*slot)->Release();
        entry_free_004524a1(*slot);
        *slot = 0;
    }
    slot = reinterpret_cast<AnimationResource_00447810**>(&data_00491c10->banks[7]);
    if (*slot) {
        (*slot)->Release();
        entry_free_004524a1(*slot);
        *slot = 0;
    }
    return 0;
}
#pragma code_seg()

#include "../../src/game/fun_0041fb50_0041fb50.cpp"
#include "title_teardown_0041fb50/title_score.cpp"
#include "title_teardown_0041fb50/title_encrypt.cpp"

extern "C" void __stdcall ReleaseGlobalManager_00417c80(void*);
extern "C" void __stdcall ReleaseGlobalScript_0042cb60(void*);
extern "C" void __stdcall ReleaseGlobalMessage_0040b7b0(void*);
extern "C" void __stdcall ReleaseGlobalPending_004294a0(void*);
#pragma code_seg(".text$05globals")
void Recovery_ReleaseGlobalStates() {
    void* manager_state = data_00477810;
    if (manager_state) { ReleaseGlobalManager_00417c80(manager_state);entry_free_004524a1(manager_state); }
    void* script_state = data_0047784c;
    if (script_state) { ReleaseGlobalScript_0042cb60(script_state);entry_free_004524a1(script_state); }
    TitleState_0041FB50* resource_state = static_cast<TitleState_0041FB50*>(data_00477820);
    if (resource_state) { resource_state->~TitleState_0041FB50();entry_free_004524a1(resource_state); }
    void* small_state = data_00477700;
    if (small_state) { ReleaseGlobalMessage_0040b7b0(small_state);entry_free_004524a1(small_state); }
    void* pending_block = data_00477838;
    if (pending_block) { ReleaseGlobalPending_004294a0(pending_block);entry_free_004524a1(pending_block); }
}
#pragma code_seg()

#include "title_teardown_0041fb50/manager_remove.cpp"
#include "title_teardown_0041fb50/manager_entity_init.cpp"
