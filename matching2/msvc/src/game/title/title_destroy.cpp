// 0x0042CB60: release Title, its loading worker and opened replays.
// Restore the title vtable, stop the worker, remove scheduler tasks, release
// animation banks 25/26, stop the owned animation and free its file buffer.
// Native LTCG supplies the receiver on the stack and RET 4.
#include "th10/game/manager_teardown_helpers.hpp"
#include "th10/platform/worker.hpp"
extern "C" void __cdecl crt_free(void*);
extern "C" void __stdcall DestroyEffectManager(void*);
struct ScriptWorker : PlatformWorker {
#ifdef SCRIPT_WORKER_EXPORTED_ABI
    __declspec(dllexport)
#endif
    ~ScriptWorker() {
        vtable = &platform_worker_vtable;
        Stop();
    }
};
struct ScriptAnimationNode;
struct ScriptAnimation {
    int id;
    unsigned char reserved_004[0x14 - 4];
    ScriptAnimationNode* children;
    int children_flagged;
    unsigned char reserved_01c[0x304 - 0x1C];
    short stop_frame;
};
struct ScriptAnimationNode {
    ScriptAnimation* object;
    ScriptAnimationNode* next;
};
struct ScriptAnimationLists {
    unsigned char reserved_000[0x72DAD4];
    ScriptAnimationNode* primary;
    unsigned int reserved_72dad8;
    ScriptAnimationNode* secondary;
};
inline ScriptAnimation* FindScriptAnimation(ScriptAnimationLists* lists, int id) {
    for (ScriptAnimationNode* node = lists->primary; node; node = node->next)
        if (node->object->id == id) return node->object;
    for (ScriptAnimationNode* node = lists->secondary; node; node = node->next)
        if (node->object->id == id) return node->object;
    return 0;
}
struct Title {
    virtual int ObjectSize();
    unsigned char reserved_004[8];
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    unsigned char reserved_014[0x5D0 - 0x14];
    int animation_id;
    unsigned char reserved_5d4[0x59E4 - 0x5D4];
    void* effects[50];
    void* file_buffer;
    ScriptWorker worker;
    __declspec(noinline) ~Title();
};
typedef char ScriptStateSizeCheck[sizeof(Title) == 0x5ACC ? 1 : -1];
typedef char ScriptWorkerOffsetCheck[offsetof(Title, worker) == 0x5AB0 ? 1 : -1];
typedef char ScriptEffectsOffsetCheck[offsetof(Title, effects) == 0x59E4 ? 1 : -1];

extern "C" {
extern AnimationBanks* g_sprt_ctrl;
extern Title* g_title;
}
#pragma code_seg(".text$01dtor")
Title::~Title() {
    worker.Stop();
    RemoveSchedulerTask(update_task);
    RemoveSchedulerTask(draw_task);
    ReleaseAnimationBank(g_sprt_ctrl, 25);
    ReleaseAnimationBank(g_sprt_ctrl, 26);
    void** effect = effects;
    int remaining = 50;
    do {
        void* object = *effect;
        if (object) {
            DestroyEffectManager(object);
            operator delete(object);
        }
        ++effect;
    } while (--remaining);
    if (animation_id) {
        ScriptAnimation* animation = FindScriptAnimation(reinterpret_cast<ScriptAnimationLists*>(g_sprt_ctrl), animation_id);
        if (animation) {
            animation->stop_frame = 1;
            if (!animation->children_flagged) {
                for (ScriptAnimationNode* child = animation->children; child; child = child->next)
                    child->object->stop_frame = 1;
            }
        }
    }
    if (file_buffer) {
        crt_free(file_buffer);
        file_buffer = 0;
    }
    g_title = 0;
}
#pragma code_seg()
