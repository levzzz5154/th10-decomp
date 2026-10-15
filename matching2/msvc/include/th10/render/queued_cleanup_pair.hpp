#ifndef TH10_QUEUED_CLEANUP_PAIR_HPP
#define TH10_QUEUED_CLEANUP_PAIR_HPP
extern "C" unsigned char g_queued_anm_release;
extern "C" unsigned char g_sprt_ctrl;

// QueuedCleanupManager::Find's C++ definition is shared with the recovered
// 0x004491C0 entry. Keep these ABI types identical to that translation unit:
// the manager receiver is ignored, the context arrives in EDX, and the
// four-byte QueuedCleanupScriptId aggregate remains on the stack.
struct QueuedCleanupLookupEntry {
    QueuedCleanupLookupEntry* object;
    QueuedCleanupLookupEntry* next;
    unsigned char reserved_008[0x0C];
    QueuedCleanupLookupEntry* children;
    int children_flagged;
    unsigned char reserved_01C[0x340];
    unsigned int flags;
};

struct QueuedCleanupContext {
    unsigned char reserved[0x72DAD4];
    QueuedCleanupLookupEntry* primary_bucket;
    int reserved_2;
    QueuedCleanupLookupEntry* secondary_bucket;
};

struct QueuedCleanupScriptId {
    int value;
};

extern "C" QueuedCleanupScriptId g_queued_cleanup_a;
extern "C" QueuedCleanupScriptId g_queued_cleanup_b;
extern "C" QueuedCleanupScriptId g_queued_cleanup_c;

class QueuedCleanupManager {
public:
    __declspec(noinline) void* __fastcall Find(QueuedCleanupContext* context, QueuedCleanupScriptId id);
};

struct QueuedAnmObject;

struct QueuedAnmChildLink {
    QueuedAnmObject* object;
    QueuedAnmChildLink* next;
};

struct QueuedAnmObject {
    unsigned char reserved_000[0x14];
    QueuedAnmChildLink* children_014;
    int children_processed_018;
    unsigned char reserved_01C[0x2E8];
    unsigned short cleanup_flag_304;
};

struct QueuedAnmState {
    unsigned char reserved_000[0x6FC];
    int pending_cleanup_6FC;
};

extern "C" __declspec(noinline) void __stdcall QueuedAnimationCleanup(QueuedAnmState* state);
extern "C" __declspec(noinline) void __stdcall ReleaseAnimationHandles(QueuedAnmState* state);
#endif
