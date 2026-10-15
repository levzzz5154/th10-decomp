#include "th10/render/queued_cleanup_pair.hpp"
// 0x00421300..0x0042140C: mark queued animations and unprocessed children
// for release, clear all three handles, then mark the controller complete.
// The volatile views preserve the observed order of the four final stores.
#pragma code_seg(".text$30release")
extern "C" __declspec(noinline) void __stdcall ReleaseAnimationHandles(QueuedAnmState* state) {
    if (state->pending_cleanup_6FC == 1) {
        QueuedCleanupManager receiver;
        QueuedCleanupContext* context = *reinterpret_cast<QueuedCleanupContext**>(&g_sprt_ctrl);
        QueuedAnmObject* animation;
        animation = static_cast<QueuedAnmObject*>(receiver.Find(context, g_queued_cleanup_a));
        if (animation) {
            animation->cleanup_flag_304 = 2;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 2;
        }
        animation = static_cast<QueuedAnmObject*>(receiver.Find(context, g_queued_cleanup_b));
        if (animation) {
            animation->cleanup_flag_304 = 2;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 2;
        }
        animation = static_cast<QueuedAnmObject*>(receiver.Find(context, g_queued_cleanup_c));
        if (animation) {
            animation->cleanup_flag_304 = 2;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 2;
        }

        static_cast<volatile QueuedCleanupScriptId*>(&g_queued_cleanup_a)->value = 0;
        static_cast<volatile QueuedCleanupScriptId*>(&g_queued_cleanup_b)->value = 0;
        static_cast<volatile QueuedCleanupScriptId*>(&g_queued_cleanup_c)->value = 0;
        static_cast<volatile QueuedAnmState*>(state)->pending_cleanup_6FC = 2;
    }
    if (*reinterpret_cast<int*>(&g_queued_anm_release))
        *reinterpret_cast<int*>(&g_queued_anm_release) = 0;
}
#pragma code_seg()
