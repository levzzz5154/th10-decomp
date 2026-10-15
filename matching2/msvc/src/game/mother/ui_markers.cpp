#include "th10/game/ui_thread_host.hpp"
#include "th10/game/pause_result_open_004231d0/dispatcher_contract.hpp"

// The three marker animations, also released by the queued cleanup at 0x00421070.
extern "C" DispatcherRef g_queued_cleanup_a;
extern "C" DispatcherRef g_queued_cleanup_b;
extern "C" DispatcherRef g_queued_cleanup_c;

// 0x00420F20 (16 bytes): stop the embedded UI worker.
#pragma code_seg(".text$00420f20_fn")
void GameUiThreadHost::StopWorker() {
    worker.Stop();
}
#pragma code_seg()

static DispatcherRef CreateMarker(AnimationBank* resource, int script_index) {
    Entity* object = reinterpret_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = 15;
    object->flags_35C = flags | 0x40000000;
    resource->InitializeObject(object, script_index);
    return reinterpret_cast<DispatcherPrimaryLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
}

// Create the three marker animations once and place them all at the given
// position.
static __forceinline void CreateMarkersOnce(GameUiThreadHost* host, const DispatcherVec3* position) {
    if (host->markers_created)
        return;
    g_queued_cleanup_a = CreateMarker(host->marker_resource, 0);
    g_queued_cleanup_b = CreateMarker(host->marker_resource, 1);
    g_queued_cleanup_c = CreateMarker(host->marker_resource, 2);
    host->markers_created = 1;
    AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl);
    DispatcherSetPosition(position, context, AnimationScriptId(g_queued_cleanup_a.value));
    DispatcherSetPosition(position, context, AnimationScriptId(g_queued_cleanup_b.value));
    DispatcherSetPosition(position, context, AnimationScriptId(g_queued_cleanup_c.value));
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
    AnimationManagerView* view = reinterpret_cast<AnimationManagerView*>(g_sprt_ctrl);
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
