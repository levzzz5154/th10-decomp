#include "th10/render/queued_cleanup_pair.hpp"
// 0x00421070..0x0042117B: mark queued animations and unprocessed children
// to stop, clear the queued handles and controller, then clear the shared gate.
#pragma code_seg(".text$10cleanup")
extern "C" __declspec(noinline) void __stdcall QueuedAnimationCleanup(QueuedAnmState* state) {
    if (state->pending_cleanup_6FC == 1) {
        QueuedCleanupManager receiver;
        QueuedCleanupContext* context = *reinterpret_cast<QueuedCleanupContext**>(&g_sprt_ctrl);
        QueuedAnmObject* animation;
        animation = static_cast<QueuedAnmObject*>(receiver.Find(context, g_queued_cleanup_a));
        if (animation) {
            animation->cleanup_flag_304 = 1;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 1;
        }
        animation = static_cast<QueuedAnmObject*>(receiver.Find(context, g_queued_cleanup_b));
        if (animation) {
            animation->cleanup_flag_304 = 1;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 1;
        }
        animation = static_cast<QueuedAnmObject*>(receiver.Find(context, g_queued_cleanup_c));
        if (animation) {
            animation->cleanup_flag_304 = 1;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 1;
        }

        g_queued_cleanup_a.value = 0;
        g_queued_cleanup_b.value = 0;
        g_queued_cleanup_c.value = 0;
        state->pending_cleanup_6FC = 0;
    }
    if (*reinterpret_cast<int*>(&g_queued_anm_release))
        *reinterpret_cast<int*>(&g_queued_anm_release) = 0;
}
#pragma code_seg()
