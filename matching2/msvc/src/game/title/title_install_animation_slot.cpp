// 0x0042C670 (95 bytes): create a script-owned animation object in render
// bucket 15, start script `index` of the room's animation resource on it,
// register it at the back of the primary list and remember its handle in the
// room's slot `index`.
//
// Native LTCG passes the index in EDI; the room stays on the stack.
#include "th10/game/title_menu.hpp"

extern "C" void* g_sprt_ctrl;
extern "C" void* __cdecl AnimationPool_AllocateEntry(void* manager);
extern "C" void** __cdecl AnimationManager_RegisterPrimaryBack(
    void* manager, void** out, void* object);
struct AnimationBank {
    __declspec(noinline) void* InitializeObject(void* object, int index);
};

#pragma code_seg(".text$0042c670_fn")
__declspec(noinline) void __stdcall Title_InstallAnimationSlot(
        Title* room, int index) {
    void* resource = room->animation_resource;
    TitleAnmVm* object = static_cast<TitleAnmVm*>(
        AnimationPool_AllocateEntry(g_sprt_ctrl));
    object->render_bucket = 15;
    object->flags |= 0x40000000u;
    static_cast<AnimationBank*>(resource)->InitializeObject(object, index);
    void* handle;
    AnimationManager_RegisterPrimaryBack(g_sprt_ctrl, &handle, object);
    room->animation_slots[index].value = reinterpret_cast<int>(handle);
}
#pragma code_seg()
