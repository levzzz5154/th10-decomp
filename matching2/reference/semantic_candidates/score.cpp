// Readable models removed from matching2/msvc/src/game/score.cpp: they compiled but did
// not reproduce the retail bytes, so that file keeps the exact assembly.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/game/score.hpp"
#include <math.h>

// The same 2D polar setter appears at 0x0041F800 and 0x004458B0. Retail
// uses one FSINCOS instruction; this readable source captures the component
// values, while its floating-point instruction sequence remains unverified.
struct PolarVector2_00408750 {
    float x;
    float y;

    __declspec(noinline) void SetPolar(float angle, float scale);
};

// 0x00408750..0x0040876D: set x=cos(angle)*scale and y=sin(angle)*scale.
// The ordinary member signature reflects ECX=this and the two stack floats.
void PolarVector2_00408750::SetPolar(float angle, float scale) {
    x = cosf(angle) * scale;
    y = sinf(angle) * scale;
}

// 0x0041BEB0: semantic C++ recovery for the two-component polar setter.
// The retail ABI is __thiscall: ECX is this, and angle and scale are stack
// floats cleaned by the callee. Retail uses one FSINCOS instruction; this
// ordinary C++ spelling preserves the component values, not that instruction
// sequence or its exact x87 rounding behavior.
struct PolarVector2_0041BEB0 {
    float x;
    float y;

    __declspec(noinline) void SetPolar(float angle, float scale);
};

void PolarVector2_0041BEB0::SetPolar(float angle, float scale) {
    x = cosf(angle) * scale;
    y = sinf(angle) * scale;
}

// Retail's entry uses one stack pointer and ends in RET 4. The shared alias
// declaration reflects that stdcall interface.
struct ScoreExtendedResourceNode_0041c1c0 {
    void** vtable;
    ScoreExtendedResourceNode_0041c1c0* previous;
    ScoreExtendedResourceNode_0041c1c0* next;
};

struct ScoreExtendedObjectDestroyLayout_0041c1c0 {
    unsigned char unknown_00[8];
    SchedulerTask* primary_task;
    SchedulerTask* secondary_task;
    unsigned char unknown_10[8];
    ScoreExtendedResourceNode_0041c1c0* resource_list;
};

typedef void (__stdcall *ScoreCriticalSectionCallback_0041c1c0)(void*);

typedef void (__fastcall *ScoreSchedulerRemove_0041c1c0)(SchedulerTask*, Scheduler*);

typedef void (__fastcall *ScoreResourceRelease_0041c1c0)(
    ScoreExtendedResourceNode_0041c1c0*);

typedef void (__cdecl *ScoreResourceFree_0041c1c0)(void*);

// 0x0041C1C0..0x0041C282: ScoreExtendedObject_DestroyRetail.
extern "C" __declspec(noinline) void __stdcall
asm_ScoreExtendedObject_DestroyRetail_0041c1c0(void* object_address) {
    ScoreExtendedObjectDestroyLayout_0041c1c0* object =
        static_cast<ScoreExtendedObjectDestroyLayout_0041c1c0*>(object_address);

    ScoreCriticalSectionCallback_0041c1c0 enter_critical_section =
        *reinterpret_cast<ScoreCriticalSectionCallback_0041c1c0*>(&data_004660b0);
    ScoreCriticalSectionCallback_0041c1c0 leave_critical_section =
        *reinterpret_cast<ScoreCriticalSectionCallback_0041c1c0*>(&data_004660b4);
    const ScoreSchedulerRemove_0041c1c0 remove_task =
        reinterpret_cast<ScoreSchedulerRemove_0041c1c0>(
            &asm_Scheduler_Remove_00449f60);
    const ScoreResourceFree_0041c1c0 free_resource =
        reinterpret_cast<ScoreResourceFree_0041c1c0>(&asm_free_004524a1);
    void* const critical_section =
        &g_thread_synchronization.critical_sections[0];

    Scheduler* scheduler = *reinterpret_cast<Scheduler**>(&data_00491be4);
    if (object->primary_task) {
        enter_critical_section(critical_section);
        ++g_thread_synchronization.scheduler_lock_depth;
        remove_task(object->primary_task, scheduler);
        leave_critical_section(critical_section);
        --g_thread_synchronization.scheduler_lock_depth;
    }

    scheduler = *reinterpret_cast<Scheduler**>(&data_00491be4);
    if (object->secondary_task) {
        enter_critical_section(critical_section);
        ++g_thread_synchronization.scheduler_lock_depth;
        remove_task(object->secondary_task, scheduler);
        leave_critical_section(critical_section);
        --g_thread_synchronization.scheduler_lock_depth;
    }

    ScoreExtendedResourceNode_0041c1c0* node = object->resource_list;
    while (node) {
        ScoreExtendedResourceNode_0041c1c0* const iteration_next = node->next;
        const ScoreResourceRelease_0041c1c0 release =
            reinterpret_cast<ScoreResourceRelease_0041c1c0>(node->vtable[4]);
        release(node);

        node->previous->next = node->next;
        if (node->next)
            node->next->previous = node->previous;
        free_resource(node);
        node = iteration_next;
    }

    *reinterpret_cast<void**>(&data_0047781c) = 0;
}
