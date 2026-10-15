#ifndef TH10_QUEUED_CLEANUP_PAIR_HPP
#define TH10_QUEUED_CLEANUP_PAIR_HPP
extern "C" unsigned char g_queued_anm_release;
extern "C" unsigned char g_sprt_ctrl;

// QueuedCleanupManager_00421070::Find's C++ definition is shared with the recovered
// 0x004491C0 entry. Keep these ABI types identical to that translation unit:
// the manager receiver is ignored, the context arrives in EDX, and the
// four-byte QueuedCleanupScriptId_00421070 aggregate remains on the stack.
struct QueuedCleanupLookupEntry_00421070 {
    QueuedCleanupLookupEntry_00421070* object;
    QueuedCleanupLookupEntry_00421070* next;
    unsigned char reserved_008[0x0C];
    QueuedCleanupLookupEntry_00421070* children;
    int children_flagged;
    unsigned char reserved_01C[0x340];
    unsigned int flags;
};

struct QueuedCleanupContext_00421070 {
    unsigned char reserved[0x72DAD4];
    QueuedCleanupLookupEntry_00421070* primary_bucket;
    int reserved_2;
    QueuedCleanupLookupEntry_00421070* secondary_bucket;
};

struct QueuedCleanupScriptId_00421070 {
    int value;
};

extern "C" QueuedCleanupScriptId_00421070 g_queued_cleanup_a;
extern "C" QueuedCleanupScriptId_00421070 g_queued_cleanup_b;
extern "C" QueuedCleanupScriptId_00421070 g_queued_cleanup_c;

class QueuedCleanupManager_00421070 {
public:
    __declspec(noinline) void* __fastcall Find(QueuedCleanupContext_00421070* context, QueuedCleanupScriptId_00421070 id);
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

extern "C" __declspec(noinline) void __stdcall QueuedAnimationCleanup_00421070(QueuedAnmState_00421070* state);
extern "C" __declspec(noinline) void __stdcall ReleaseAnimationHandles_00421300(QueuedAnmState_00421070* state);
#endif
