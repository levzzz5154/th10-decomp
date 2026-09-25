// 0x00418EE0..0x00419039: release the scheduled resources and references held
// by a recovery-state manager, then clear its resource buckets.
//
// The names below describe the observed offsets without claiming that the
// retail structures have been fully identified. The recovered entry ABI is
// one manager pointer on the stack, __stdcall, with RET 4.

#include "asm_symbols.hpp"

#include "th10/game/scheduler.hpp"

extern "C" void __cdecl asm_FUN_0041a200_0041a200();

typedef void (__stdcall *CriticalSectionCall_00418ee0)(void* section);
typedef void (__stdcall *ScoreSaveCall_00418ee0)(void* manager,
                                                 const char* path);

struct ResourceManagerView_00418ee0 {
    unsigned char unknown_0000[0x8];
    SchedulerTask* scheduled_resource_0008;
    SchedulerTask* scheduled_resource_000C;
    unsigned char unknown_0010[0xCC];
    void* resource_keys_00DC[10];
};

// The two manager lists contain links to records whose first dword is the
// resource key. Their remaining layout is not needed by this routine.
struct ResourceListLink_00418ee0 {
    void* record;
    ResourceListLink_00418ee0* next;
};

struct RelatedResourceLink_00418ee0 {
    void* related_resource;
    RelatedResourceLink_00418ee0* next;
};

struct RegisteredResourceView_00418ee0 {
    void* resource_key_0000;
    unsigned char unknown_0004[0x10];
    RelatedResourceLink_00418ee0* related_resources_0014;
    void* owner_or_parent_0018;
    unsigned char unknown_001C[0x340];
    unsigned int flags_035C;
};

// This declaration mirrors the bucket prefix used by the semantic
// ClearBuckets implementation at 0x00419040. That function's retail entry
// receives its object in EAX; a caller-inclusive compiler context is needed
// to reproduce that private register convention exactly.
struct ChainNode_00419040 {
    void* block;
    ChainNode_00419040* next;
};

struct Bucket_00419040 {
    ChainNode_00419040* head;
    unsigned reserved[2];
};

struct Manager_00419040 {
    unsigned char reserved_000[0x1C];
    Bucket_00419040 primary[8];
    Bucket_00419040 secondary[8];

    __declspec(noinline) void ClearBuckets();
};

#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) void __stdcall
asm_FUN_00418ee0_00418ee0(void* manager) {
    CriticalSectionCall_00418ee0 enterCriticalSection =
        *reinterpret_cast<CriticalSectionCall_00418ee0*>(&data_004660b0);
    CriticalSectionCall_00418ee0 leaveCriticalSection =
        *reinterpret_cast<CriticalSectionCall_00418ee0*>(&data_004660b4);
    void* criticalSection = reinterpret_cast<void*>(0x00492274);
    ResourceManagerView_00418ee0* state =
        static_cast<ResourceManagerView_00418ee0*>(manager);

    // Keep the observed order: remove the +0x08 task before reading/removing
    // the +0x0C task. Retail reloads the scheduler pointer after reading each
    // task and before testing it for null.
    SchedulerTask* firstTask = state->scheduled_resource_0008;
    Scheduler* firstScheduler =
        *reinterpret_cast<Scheduler**>(&data_00491be4);
    if (firstTask != 0) {
        enterCriticalSection(criticalSection);
        ++data_0049231c;
        Scheduler_Remove(firstTask, firstScheduler);
        leaveCriticalSection(criticalSection);
        --data_0049231c;
    }

    SchedulerTask* secondTask = state->scheduled_resource_000C;
    Scheduler* secondScheduler =
        *reinterpret_cast<Scheduler**>(&data_00491be4);
    if (secondTask != 0) {
        enterCriticalSection(criticalSection);
        ++data_0049231c;
        Scheduler_Remove(secondTask, secondScheduler);
        leaveCriticalSection(criticalSection);
        --data_0049231c;
    }

    // These list heads are reached through the current game-state manager.
    // The offsets and link shape are observed; their higher-level ownership
    // meaning remains provisional.
    void* gameStateManager = *reinterpret_cast<void**>(&data_00491c10);
    unsigned char* gameStateBytes =
        static_cast<unsigned char*>(gameStateManager);

    for (int index = 0; index != 10; ++index) {
        void* resourceKey = state->resource_keys_00DC[index];
        if (resourceKey != 0) {
            RegisteredResourceView_00418ee0* registeredResource = 0;

            ResourceListLink_00418ee0* link =
                *reinterpret_cast<ResourceListLink_00418ee0**>(
                    gameStateBytes + 0x72DAD4);
            while (link != 0) {
                RegisteredResourceView_00418ee0* candidate =
                    static_cast<RegisteredResourceView_00418ee0*>(link->record);
                if (candidate->resource_key_0000 == resourceKey) {
                    registeredResource = candidate;
                    break;
                }
                link = link->next;
            }

            // Retail consults the second list only when the first list has no
            // matching key.
            if (registeredResource == 0) {
                link = *reinterpret_cast<ResourceListLink_00418ee0**>(
                    gameStateBytes + 0x72DADC);
                while (link != 0) {
                    RegisteredResourceView_00418ee0* candidate =
                        static_cast<RegisteredResourceView_00418ee0*>(link->record);
                    if (candidate->resource_key_0000 == resourceKey) {
                        registeredResource = candidate;
                        break;
                    }
                    link = link->next;
                }
            }

            if (registeredResource != 0) {
                registeredResource->flags_035C |= 0x04000000;
                if (registeredResource->owner_or_parent_0018 == 0) {
                    for (RelatedResourceLink_00418ee0* related =
                             registeredResource->related_resources_0014;
                         related != 0; related = related->next) {
                        RegisteredResourceView_00418ee0* child =
                            static_cast<RegisteredResourceView_00418ee0*>(
                                related->related_resource);
                        child->flags_035C |= 0x04000000;
                    }
                }
            }
        }

        // The slot is cleared whether its key is null, absent from both lists,
        // or matched and marked.
        state->resource_keys_00DC[index] = 0;
    }

    if (data_00491d6a == 2) {
        ScoreSaveCall_00418ee0 saveScore =
            reinterpret_cast<ScoreSaveCall_00418ee0>(
                &asm_FUN_0041a200_0041a200);
        saveScore(manager, "hint/hint_auto.txt");
    }

    // Retail passes this same manager to the bucket clearer after the
    // optional score save. Its EAX receiver convention is a remaining
    // exact-codegen integration point; this call records the semantic relation.
    static_cast<Manager_00419040*>(manager)->ClearBuckets();
    *reinterpret_cast<unsigned int*>(&data_00477814) = 0;
}
#pragma code_seg()
