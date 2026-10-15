#include "th10/render/queued_cleanup_pair.hpp"
// 0x00421070..0x0042117B: mark queued animations and unprocessed children
// to stop, clear the queued handles and controller, then clear the shared gate.
#pragma code_seg(".text$10cleanup")
extern "C" __declspec(noinline) void __stdcall QueuedAnimationCleanup_00421070(QueuedAnmState_00421070* state) {
    if (state->pending_cleanup_6FC == 1) {
        QueuedCleanupManager_00421070 receiver;
        QueuedCleanupContext_00421070* context = *reinterpret_cast<QueuedCleanupContext_00421070**>(&g_sprt_ctrl);
        QueuedAnmObject_00421070* animation;
        animation = static_cast<QueuedAnmObject_00421070*>(receiver.Find(context, data_00477824));
        if (animation) {
            animation->cleanup_flag_304 = 1;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink_00421070* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 1;
        }
        animation = static_cast<QueuedAnmObject_00421070*>(receiver.Find(context, data_00477828));
        if (animation) {
            animation->cleanup_flag_304 = 1;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink_00421070* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 1;
        }
        animation = static_cast<QueuedAnmObject_00421070*>(receiver.Find(context, data_0047782c));
        if (animation) {
            animation->cleanup_flag_304 = 1;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink_00421070* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 1;
        }

        data_00477824.value = 0;
        data_00477828.value = 0;
        data_0047782c.value = 0;
        state->pending_cleanup_6FC = 0;
    }
    if (*reinterpret_cast<int*>(&data_00491bec))
        *reinterpret_cast<int*>(&data_00491bec) = 0;
}
#pragma code_seg()
