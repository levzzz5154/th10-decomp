#include "th10/game/ui_thread_host.hpp"
#include "th10/game/pause_result_open_004231d0/dispatcher_contract.hpp"

// The three marker animations, also released by the queued cleanup at 0x00421070.
extern "C" DispatcherRef data_00477824;
extern "C" DispatcherRef data_00477828;
extern "C" DispatcherRef data_0047782c;

// 0x00420F20 (16 bytes): stop the embedded UI worker.
#pragma code_seg(".text$00420f20_fn")
void GameUiThreadHost::StopWorker() {
    worker.Stop();
}
#pragma code_seg()

static DispatcherRef CreateMarker(AnimationResource_00449870* resource, int script_index) {
    Entity* object = reinterpret_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = 15;
    object->flags_35C = flags | 0x40000000;
    resource->InitializeObject(object, script_index);
    return reinterpret_cast<DispatcherPrimaryLists*>(data_00491c10)->RegisterPrimaryBack(object);
}

// Create the three marker animations once and place them all at the given
// position.
static __forceinline void CreateMarkersOnce(GameUiThreadHost* host, const DispatcherVec3* position) {
    if (host->markers_created)
        return;
    data_00477824 = CreateMarker(host->marker_resource, 0);
    data_00477828 = CreateMarker(host->marker_resource, 1);
    data_0047782c = CreateMarker(host->marker_resource, 2);
    host->markers_created = 1;
    AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(data_00491c10);
    DispatcherSetPosition(position, context, AnimationScriptId(data_00477824.value));
    DispatcherSetPosition(position, context, AnimationScriptId(data_00477828.value));
    DispatcherSetPosition(position, context, AnimationScriptId(data_0047782c.value));
}

// 0x00420F30 (309 bytes)
#pragma code_seg(".text$00420f30_fn")
void GameUiThreadHost::CreateMarkers(const DispatcherVec3* position) {
    CreateMarkersOnce(this, position);
}
#pragma code_seg()

struct ScreenRect {
    int left, top, right, bottom;
};

// The head of the animation manager: the active layer and its two rectangles.
struct AnimationManagerView {
    int layer;                              // +0x00, negative until chosen
    unsigned char reserved_004[0x28];
    ScreenRect source;                      // +0x2c
    ScreenRect target;                      // +0x3c
};

// 0x00421180 (369 bytes): create and place the markers, then give the
// animation manager its full-screen default view if none is selected.
#pragma code_seg(".text$00421180_fn")
extern "C" void __stdcall GameUi_ShowMarkers_00421180(
        GameUiThreadHost* host, const DispatcherVec3* position) {
    CreateMarkersOnce(host, position);
    AnimationManagerView* view = reinterpret_cast<AnimationManagerView*>(data_00491c10);
    if (view->layer < 0) {
        view->layer = 8;
        view->source.left = 0;
        view->source.top = 0;
        view->source.right = 640;
        view->source.bottom = 480;
        view->target.left = 0;
        view->target.top = 0;
        view->target.right = 640;
        view->target.bottom = 480;
    }
}
#pragma code_seg()
