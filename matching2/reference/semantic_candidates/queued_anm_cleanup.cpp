#include <stddef.h>

extern "C" unsigned char data_00477824;
extern "C" unsigned char data_00477828;
extern "C" unsigned char data_0047782c;
extern "C" unsigned char data_00491bec;
extern "C" unsigned char data_00491c10;

// AnimationManager::Find's C++ definition is shared with the recovered
// 0x004491C0 entry. Keep these ABI types identical to that translation unit:
// the manager receiver is ignored, the context arrives in EDX, and the
// four-byte AnimationScriptId aggregate remains on the stack.
struct AnimationEntry {
    AnimationEntry* object;
    AnimationEntry* next;
    unsigned char reserved_008[0x0C];
    AnimationEntry* children;
    int children_flagged;
    unsigned char reserved_01C[0x340];
    unsigned int flags;
};

struct AnimationLookupContext {
    unsigned char reserved[0x72DAD4];
    AnimationEntry* primary_bucket;
    int reserved_2;
    AnimationEntry* secondary_bucket;
};

struct AnimationScriptId {
    int value;
};

class AnimationManager {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

struct QueuedAnmObject_00421070;

struct QueuedAnmChildLink_00421070 {
    QueuedAnmObject_00421070* object;
    QueuedAnmChildLink_00421070* next;
};

struct QueuedAnmObject_00421070 {
    unsigned char reserved_000[0x14];
    QueuedAnmChildLink_00421070* children_014;
    int children_processed_018;
    unsigned char reserved_01C[0x2E8];
    unsigned short cleanup_flag_304;
};

struct QueuedAnmState_00421070 {
    unsigned char reserved_000[0x6FC];
    int pending_cleanup_6FC;
};

typedef char QueuedAnmObject_children_offset_must_be_14[
    offsetof(QueuedAnmObject_00421070, children_014) == 0x14 ? 1 : -1];
typedef char QueuedAnmObject_processed_offset_must_be_18[
    offsetof(QueuedAnmObject_00421070, children_processed_018) == 0x18 ? 1 : -1];
typedef char QueuedAnmObject_flag_offset_must_be_304[
    offsetof(QueuedAnmObject_00421070, cleanup_flag_304) == 0x304 ? 1 : -1];
typedef char QueuedAnmState_flag_offset_must_be_6FC[
    offsetof(QueuedAnmState_00421070, pending_cleanup_6FC) == 0x6FC ? 1 : -1];

static __forceinline void MarkQueuedAnimation_00421070(
    AnimationManager* lookup_receiver,
    AnimationLookupContext* context,
    int script_id) {
    AnimationScriptId id = {script_id};
    QueuedAnmObject_00421070* animation =
        static_cast<QueuedAnmObject_00421070*>(lookup_receiver->Find(context, id));
    if (animation == 0) {
        return;
    }

    animation->cleanup_flag_304 = 1;
    if (animation->children_processed_018 != 0) {
        return;
    }

    for (QueuedAnmChildLink_00421070* child = animation->children_014;
         child != 0;
         child = child->next) {
        child->object->cleanup_flag_304 = 1;
    }
}

// The retail caller pushes only the game-state pointer and does not adjust
// ESP after the call, so this stdcall shape models the entry's RET 4 contract.
// The inbound ECX value is not observed by this routine or by Find's body.
extern "C" __declspec(noinline) void __stdcall QueuedAnimationCleanup_00421070(
    QueuedAnmState_00421070* state) {
    if (state->pending_cleanup_6FC == 1) {
        AnimationManager lookup_receiver;
        AnimationLookupContext* context =
            *reinterpret_cast<AnimationLookupContext**>(&data_00491c10);

        MarkQueuedAnimation_00421070(
            &lookup_receiver,
            context,
            *reinterpret_cast<int*>(&data_00477824));
        MarkQueuedAnimation_00421070(
            &lookup_receiver,
            context,
            *reinterpret_cast<int*>(&data_00477828));
        MarkQueuedAnimation_00421070(
            &lookup_receiver,
            context,
            *reinterpret_cast<int*>(&data_0047782c));

        *reinterpret_cast<int*>(&data_00477824) = 0;
        *reinterpret_cast<int*>(&data_00477828) = 0;
        *reinterpret_cast<int*>(&data_0047782c) = 0;
        state->pending_cleanup_6FC = 0;
    }

    int& pending_cleanup_gate = *reinterpret_cast<int*>(&data_00491bec);
    if (pending_cleanup_gate != 0) {
        pending_cleanup_gate = 0;
    }
}
