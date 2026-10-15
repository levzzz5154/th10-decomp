// Ending-text constructor at 0x0040BA90 with its worker ownership; the
// generated unwind at 0x004654C0 and handler at 0x004654CE come from it.
#include <string.h>
#include "th10/render/animation_public_callers.hpp"
#include "th10/render/animation_byte_interpolator.hpp"
#include "th10/platform/worker.hpp"
struct EndingTimer : FrameTimer { EndingTimer() { flags &= ~1u; } };
#ifndef TH10_ENDING_TEXT_WORKER_SECTION
#define TH10_ENDING_TEXT_WORKER_SECTION ".text$16worker"
#endif
#pragma code_seg(TH10_ENDING_TEXT_WORKER_SECTION)
struct EndingWorker : PlatformWorker {
    EndingWorker() { vtable = &platform_worker_vtable; thread = 0; thread_id = 0; stop_requested = 0; running = 0; }
#ifndef TH10_ENDING_TEXT_LAYOUT_ONLY
    __declspec(dllexport) ~EndingWorker() { vtable = &platform_worker_vtable; Stop(); }
#endif
};
#pragma code_seg()
struct EndingGlyph {
    int id;
    unsigned char reserved_004[0x20 - 4];
    int render_bucket;
    unsigned char reserved_024[0x35C - 0x24];
    unsigned int flags;
    unsigned int text_flags;
    unsigned char reserved_364[0x3A0 - 0x364];
    unsigned char width, height;
};
inline EndingGlyph* FindEndingGlyph(AnimationLookupContext* manager, int id) {
    if (!id) return 0;
    for (AnimationEntry* node = manager->primary_bucket; node; node = node->next)
        if (*(int*)node->object == id) return (EndingGlyph*)node->object;
    for (AnimationEntry* node = manager->secondary_bucket; node; node = node->next)
        if (*(int*)node->object == id) return (EndingGlyph*)node->object;
    return 0;
}
inline EndingGlyph* ResolveEndingGlyph(AnimationLookupContext* manager, int& id) {
    EndingGlyph* object = FindEndingGlyph(manager, id);
    if (!object) id = 0;
    return object;
}
struct EndingText {
    int unknown_000;
    EndingTimer timer_004, timer_018, timer_02c;
    int handles[5];
    void* script;
    unsigned char reserved_058[0x74 - 0x58];
    unsigned int flags;
    int reserved_078;
    unsigned int color;
    unsigned char reserved_080[0xD0 - 0x80];
    EndingWorker worker;
    __declspec(noinline) EndingText(void* script);
};
typedef char EndingTextSize[sizeof(EndingText) == 0xEC ? 1 : -1];
typedef char EndingWorkerOffset[offsetof(EndingText,worker) == 0xD0 ? 1 : -1];
// A caller cluster uses the complete constructor as an unselected ABI model.
// Its worker cleanup remains owned by this constructor's separate EH cluster.
#ifndef TH10_ENDING_TEXT_CONSTRUCTOR_SECTION
#define TH10_ENDING_TEXT_CONSTRUCTOR_SECTION ".text$01ctor"
#endif
#pragma code_seg(TH10_ENDING_TEXT_CONSTRUCTOR_SECTION)
EndingText::EndingText(void* script_data) {
    AnimationLookupContext* manager = (AnimationLookupContext*)data_00491c10;
    memset(this, 0, sizeof(*this));
    for (unsigned int i = 0; i < 5; ++i) {
        AnimationResource_00449870* bank = *(AnimationResource_00449870**)((char*)g_ascii_manager + 0x899C);
        EndingGlyph* glyph = (EndingGlyph*)((AnimationPool*)manager)->Allocate();
        unsigned int old_flags = glyph->flags;
        glyph->render_bucket = 15;
        glyph->flags = old_flags | 0x40000000u;
        bank->InitializeObject(glyph, i + 0x42);
        manager = (AnimationLookupContext*)data_00491c10;
        int id;
        asm_AnimationManager_RegisterPrimaryBack_004489d0(manager, (void**)&id, glyph);
        handles[i] = id;
        ResolveEndingGlyph(manager, handles[i])->width = 16;
        ResolveEndingGlyph(manager, handles[i])->height = 16;
        ResolveEndingGlyph(manager, handles[i])->text_flags |= 2u;
    }
    script = script_data;
    FrameTimer_Restart(&timer_004);
    FrameTimer_Restart(&timer_018);
    FrameTimer_Restart(&timer_02c);
    flags |= 1u;
    color = 0xFFFFFFu;
}
#pragma code_seg()
