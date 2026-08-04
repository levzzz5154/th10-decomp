#include "th10/game/task_registration.hpp"
#include "th10/runtime/missing_edge.hpp"

#ifdef _MSC_VER
#include <string.h>
#endif

extern uint32_t DAT_00491be4;  // scheduler device token
extern uint8_t DAT_00491d6a;   // demo-tips enabled flag
extern float DAT_00476f78;     // shared unit timer speed (1.0f)
extern uint32_t DAT_004918a4;  // title-screen selection latch
extern void* g_pGameStateManager;
extern int* ResourceManager_FindResource(int type, void* manager,
                                         const char* name);

#ifdef _MSC_VER
extern "C" void* sub_449ED0(void*);
extern "C" int sub_449AE0(void*, int, void*);
extern "C" int sub_449B70(void*, int, void*);
extern "C" void* sub_447280(void*, const char*, int);
extern "C" void sub_44B810(void*, const char*, ...);
extern "C" int sub_413A20(void*);
extern "C" unsigned long dword_491C10;
#endif

namespace {
ItemFrontRuntimeBindings g_item_front_bindings = {};

// One callback creation + registration, matching the retail skeleton
// (clear flag bit 1, set the owner, register with the device token).
SchedulerCallback* CreateAndRegister(void* owner, SchedulerCreateFn create,
                                     SchedulerRegisterFn register_edge,
                                     SchedulerFunction function) {
    SchedulerCallback* callback = create(function);
    callback->flags &= ~2u;
    callback->owner = owner;
    if (register_edge != 0) {
        register_edge(callback, DAT_00491be4);
    }
    return callback;
}

int __fastcall ItemFront_Update(void* owner) {
    if (g_item_front_bindings.update == 0)
        Runtime_MissingEdge(0x00415AE0u, "item/front update");
    return g_item_front_bindings.update(owner);
}

int __fastcall ItemFront_Render(void* owner) {
    if (g_item_front_bindings.render == 0)
        Runtime_MissingEdge(0x00415AF0u, "item/front render");
    return g_item_front_bindings.render(owner);
}

}  // namespace

// 0x00418E30 - Register the stage-tip manager's scheduler callbacks and
// optionally spawn the two demo tips.
uint32_t StageTip_RegisterTasks(
        void* owner, TaskPairSlots* slots, uint32_t* counter,
        SchedulerCreateFn create, SchedulerRegisterFn register_primary,
        SchedulerRegisterFn register_secondary, SchedulerFunction update_proc,
        SchedulerFunction render_proc,
        void (*spawn_tip)(void* owner, uint32_t text_address, int32_t slot)) {
    slots->update_task =
        CreateAndRegister(owner, create, register_primary, update_proc);
    slots->render_task =
        CreateAndRegister(owner, create, register_secondary, render_proc);
    *counter = 0;
    if (DAT_00491d6a != 0 && spawn_tip != 0) {
        spawn_tip(owner, 0x0046D6D8u, 0);
        spawn_tip(owner, 0x0046D6C4u, 1);
    }
    return 0;
}

// 0x00422150 - Register a callback pair and reset the embedded timer.
uint32_t TimedTask_RegisterPair(void* owner, TimedTaskState* state,
                                SchedulerCreateFn create,
                                SchedulerRegisterFn register_primary,
                                SchedulerRegisterFn register_secondary,
                                SchedulerFunction update_proc,
                                SchedulerFunction render_proc) {
    state->update_task =
        CreateAndRegister(owner, create, register_primary, update_proc);
    state->render_task =
        CreateAndRegister(owner, create, register_secondary, render_proc);
    if ((state->timer.flags & 1u) == 0) {
        state->timer.current = 0;
        state->timer.target = (int)0xFFF0BDC1;
        state->timer.previous = 0;
        state->timer.speed = &DAT_00476f78;
        state->timer.flags |= 1u;
    }
    state->timer.current = 0;
    state->timer.previous = 0;
    state->timer.target = -1;
    return 0;
}

// 0x0041C120 - Initialize the score display.
int32_t ScoreDisplay_RegisterTasks(
        void* owner, TaskPairSlots* slots, int32_t** resource_slot,
        ScorePopupNode** queue_tail, ScorePopupNode* queue_head,
        int32_t* (*find_resource)(int32_t slot, const char* name),
        void (*report_error)(), SchedulerCreateFn create,
        SchedulerRegisterFn register_primary,
        SchedulerRegisterFn register_secondary, SchedulerFunction update_proc,
        SchedulerFunction render_proc) {
    int32_t* resource =
        find_resource != 0 ? find_resource(7, "bullet.anm") : 0;
    *resource_slot = resource;
    if (resource == 0) {
        if (report_error != 0) {
            report_error();
        }
        return -1;
    }
    slots->update_task =
        CreateAndRegister(owner, create, register_primary, update_proc);
    slots->render_task =
        CreateAndRegister(owner, create, register_secondary, render_proc);
    *queue_tail = queue_head;
    return 0;
}

// 0x00413980 - Initialize the front UI overlay.
int32_t FrontAnm_RegisterTasks(
        void* owner, TaskPairSlots* slots, int32_t** resource_slot,
        int32_t* (*find_resource)(int32_t slot, const char* name),
        void (*report_error)(), int32_t (*initialize)(void* owner),
        SchedulerCreateFn create, SchedulerRegisterFn register_primary,
        SchedulerRegisterFn register_secondary, SchedulerFunction update_proc,
        SchedulerFunction render_proc) {
    int32_t* resource =
        find_resource != 0 ? find_resource(6, "front.anm") : 0;
    *resource_slot = resource;
    if (resource == 0) {
        if (report_error != 0) {
            report_error();
        }
        return -1;
    }
    if (initialize != 0 && initialize(owner) != 0) {
        return -1;
    }
    slots->update_task =
        CreateAndRegister(owner, create, register_primary, update_proc);
    slots->render_task =
        CreateAndRegister(owner, create, register_secondary, render_proc);
    return 0;
}

void ItemFrontRuntime_SetBindings(
        const ItemFrontRuntimeBindings* bindings) {
    if (bindings != 0)
        g_item_front_bindings = *bindings;
    else
#ifdef _MSC_VER
        memset(&g_item_front_bindings, 0, sizeof(g_item_front_bindings));
#else
        g_item_front_bindings = ItemFrontRuntimeBindings{};
#endif
}

// 0x00413980 - Resolve front.anm, construct the score/front task through the
// explicit runtime edge, and register the item manager callback pair.
#ifdef _MSC_VER
__declspec(naked) int ItemFrontRuntime_InitializeRetail() {
    __asm {
        mov edx, dword ptr [dword_491C10]
        push 46D254h
        mov ecx, 6
        call sub_447280
        test eax, eax
        mov [ebx+9EC8h], eax
        jnz loc_4139B5
        push 46CB68h
        mov ecx, 474F70h
        call sub_44B810
        add esp, 4
loc_4139B1:
        or eax, 0FFFFFFFFh
        ret
loc_4139B5:
        push ebx
        call sub_413A20
        test eax, eax
        jnz loc_4139B1
        push esi
        push edi
        push 415AE0h
        call sub_449ED0
        mov esi, eax
        and dword ptr [esi+4], 0FFFFFFFDh
        mov eax, dword ptr [DAT_00491be4]
        push eax
        mov edi, 18h
        mov [esi+20h], ebx
        call sub_449AE0
        push 415AF0h
        mov [ebx+8], esi
        call sub_449ED0
        mov esi, eax
        and dword ptr [esi+4], 0FFFFFFFDh
        mov ecx, dword ptr [DAT_00491be4]
        push ecx
        mov edi, 2Bh
        mov [esi+20h], ebx
        call sub_449B70
        pop edi
        mov [ebx+0Ch], esi
        xor eax, eax
        pop esi
        ret
    }
}
#endif

int ItemFrontRuntime_Initialize(void* owner) {
    if (owner == 0 || DAT_00491be4 == 0 ||
        g_item_front_bindings.initialize_score_task == 0)
        return -1;
    unsigned char* bytes = (unsigned char*)owner;
    int* resource =
        ResourceManager_FindResource(6, g_pGameStateManager, "front.anm");
    *(int**)(bytes + 0x9EC8) = resource;
    if (resource == 0)
        return -1;
    if (g_item_front_bindings.initialize_score_task(owner) != 0)
        return -1;

    SchedulerCallback* update =
        SchedulerCallback_Create(ItemFront_Update);
    if (update == 0)
        return -1;
    update->flags &= ~2u;
    update->owner = owner;
    Scheduler_RegisterPrimary(update, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 8) = update;

    SchedulerCallback* render =
        SchedulerCallback_Create(ItemFront_Render);
    if (render == 0) {
        Scheduler_Remove(update, (void*)(uintptr_t)DAT_00491be4);
        *(SchedulerCallback**)(bytes + 8) = 0;
        return -1;
    }
    render->flags &= ~2u;
    render->owner = owner;
    Scheduler_RegisterSecondary(render, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 12) = render;
    return 0;
}

// Semantic reconstruction 0x0042CAA0 - initialize the title screen.
#ifdef _MSC_VER
__declspec(naked) int32_t Title_RegisterTasksRetail() {
    __asm {
        push esi
        push edi
        push 42D2E0h
        call sub_449ED0
        mov esi, eax
        mov edi, [esi+4]
        mov eax, dword ptr [DAT_00491be4]
        and edi, 0FFFFFFFDh
        mov [esi+4], edi
        push eax
        mov edi, 6
        mov [esi+20h], ebx
        call sub_449AE0
        push 42D2F0h
        mov [ebx+0Ch], esi
        call sub_449ED0
        mov ecx, dword ptr [DAT_00491be4]
        mov esi, eax
        mov eax, [esi+4]
        and eax, 0FFFFFFFDh
        push ecx
        mov edi, 3
        mov [esi+20h], ebx
        mov [esi+4], eax
        call sub_449B70
        mov edx, dword ptr [dword_491C10]
        push 46F0ACh
        mov ecx, 19h
        mov [ebx+10h], esi
        call sub_447280
        test eax, eax
        pop edi
        mov [ebx+14h], eax
        pop esi
        jz loc_42CB33
        mov edx, dword ptr [dword_491C10]
        push 46F0A0h
        mov ecx, 1Ah
        call sub_447280
        test eax, eax
        mov [ebx+18h], eax
        jnz loc_42CB49
loc_42CB33:
        push 46CB68h
        mov ecx, 474F70h
        call sub_44B810
        add esp, 4
        or eax, 0FFFFFFFFh
        ret
loc_42CB49:
        mov dword ptr [ebx+0F4h], 1
        mov dword ptr [DAT_004918a4], 0
        xor eax, eax
        ret
    }
}
#endif

int32_t Title_RegisterTasks(
        void* owner, TitleInitState* state,
        int32_t* (*find_resource)(int32_t slot, const char* name),
        void (*report_error)(), SchedulerCreateFn create,
        SchedulerRegisterFn register_primary,
        SchedulerRegisterFn register_secondary, SchedulerFunction update_proc,
        SchedulerFunction render_proc) {
    state->update_task =
        CreateAndRegister(owner, create, register_primary, update_proc);
    state->render_task =
        CreateAndRegister(owner, create, register_secondary, render_proc);
    state->title_resource =
        find_resource != 0 ? find_resource(0x19, "title.anm") : 0;
    if (state->title_resource != 0) {
        state->title_v_resource = find_resource(0x1A, "title_v.anm");
        if (state->title_v_resource != 0) {
            state->ready_flag = 1;
            DAT_004918a4 = 0;
            return 0;
        }
    }
    if (report_error != 0) {
        report_error();
    }
    return -1;
}
