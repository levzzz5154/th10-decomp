#include "th10/render/queued_cleanup_pair.hpp"
// 0x00421300..0x0042140C: mark queued animations and unprocessed children
// for release, clear all three handles, then mark the controller complete.
// The volatile views preserve the observed order of the four final stores.
#pragma code_seg(".text$30release")
extern "C" __declspec(noinline) void __stdcall ReleaseAnimationHandles_00421300(QueuedAnmState_00421070* state) {
    if (state->pending_cleanup_6FC == 1) {
        QueuedCleanupManager_00421070 receiver;
        QueuedCleanupContext_00421070* context = *reinterpret_cast<QueuedCleanupContext_00421070**>(&g_sprt_ctrl);
        QueuedAnmObject_00421070* animation;
        animation = static_cast<QueuedAnmObject_00421070*>(receiver.Find(context, data_00477824));
        if (animation) {
            animation->cleanup_flag_304 = 2;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink_00421070* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 2;
        }
        animation = static_cast<QueuedAnmObject_00421070*>(receiver.Find(context, data_00477828));
        if (animation) {
            animation->cleanup_flag_304 = 2;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink_00421070* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 2;
        }
        animation = static_cast<QueuedAnmObject_00421070*>(receiver.Find(context, data_0047782c));
        if (animation) {
            animation->cleanup_flag_304 = 2;
            if (!animation->children_processed_018)
                for (QueuedAnmChildLink_00421070* child = animation->children_014;
                     child; child = child->next)
                    child->object->cleanup_flag_304 = 2;
        }

        static_cast<volatile QueuedCleanupScriptId_00421070*>(&data_00477824)->value = 0;
        static_cast<volatile QueuedCleanupScriptId_00421070*>(&data_00477828)->value = 0;
        static_cast<volatile QueuedCleanupScriptId_00421070*>(&data_0047782c)->value = 0;
        static_cast<volatile QueuedAnmState_00421070*>(state)->pending_cleanup_6FC = 2;
    }
    if (*reinterpret_cast<int*>(&data_00491bec))
        *reinterpret_cast<int*>(&data_00491bec) = 0;
}
#pragma code_seg()
