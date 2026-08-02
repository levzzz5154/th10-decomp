#include "th10/game/player_runtime_init.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/runtime/missing_edge.hpp"

#include <cstdint>
#include <cstring>

extern void* g_pGameStateManager;
extern unsigned int DAT_00491be4;
extern unsigned int DAT_00491bf0;
extern unsigned int DAT_00474c68;
extern unsigned int DAT_00477834;
extern unsigned int DAT_00476f78;
extern float _DAT_00470b0c;
extern float DAT_00476fa0[2];
extern float DAT_00476fa8[2];
extern float DAT_00476fb0[2];
extern float DAT_00476fb8[2];
extern int* ResourceManager_FindResource(int type, void* manager,
                                         const char* name);

namespace {
LargePlayerRuntimeBindings g_large_player_bindings = {};

void ResetTimer(PlayerRuntimeTimer* timer, const float* speed,
                int target, int current, int previous) {
    if ((timer->flags & 1u) == 0) {
        timer->current = 0;
        timer->target = static_cast<int>(0xfff0bdc1u);
        timer->previous = 0;
        timer->speed = speed;
        timer->flags |= 1u;
    }
    timer->target = target;
    timer->current = current;
    timer->previous = previous;
}

void BuildBounds(const float position[3], const float half[3],
                 float bounds[6]) {
    for (int axis = 0; axis < 3; ++axis) {
        bounds[axis] = position[axis] - half[axis];
        bounds[axis + 3] = position[axis] + half[axis];
    }
}

void ResetRawTimer(unsigned char* bytes, unsigned int base,
                   int target, int current, int previous_bits) {
    unsigned int* flags = (unsigned int*)(bytes + base + 0x10);
    if ((*flags & 1u) == 0) {
        *(int*)(bytes + base + 4) = 0;
        *(int*)(bytes + base) = (int)0xFFF0BDC1u;
        *(int*)(bytes + base + 8) = 0;
        *(unsigned int*)(bytes + base + 12) =
            (unsigned int)(unsigned long)&DAT_00476f78;
        *flags |= 1u;
    }
    *(int*)(bytes + base) = target;
    *(int*)(bytes + base + 4) = current;
    *(int*)(bytes + base + 8) = previous_bits;
}

int __fastcall LargePlayer_Update(void* owner) {
    if (g_large_player_bindings.update == 0)
        Runtime_MissingEdge(0x00426500u, "large player update");
    return g_large_player_bindings.update(owner);
}

int __fastcall LargePlayer_Draw(void* owner) {
    if (g_large_player_bindings.draw == 0)
        Runtime_MissingEdge(0x00426510u, "large player draw");
    return g_large_player_bindings.draw(owner);
}

}  // namespace

// 0x004247F0 - Player runtime initialization. PE32 establishes the state in
// EBX; the conventional signature makes that owner explicit.
int PlayerRuntime_Initialize(PlayerRuntimeState* state, int character,
                             const PlayerRuntimeTables* tables,
                             const PlayerRuntimeInitHooks* hooks) {
    const char* resource = character == 0 ? "pl00.anm" : "pl01.anm";
    state->animation_archive =
        hooks->load_animation(hooks->context, 8, resource);
    if (state->animation_archive == 0) {
        hooks->report_error(hooks->context, resource);
        return -1;
    }

    if (hooks->reused_player != 0) {
        state->player_object =
            static_cast<PlayerRuntimeObject*>(hooks->reused_player);
    } else {
        state->player_object = hooks->create_player_object(hooks->context);
        if (state->player_object == 0) {
            hooks->report_error(hooks->context, resource);
            return -1;
        }
    }

    state->update_task = hooks->register_task(hooks->context, 0, state);
    state->draw_task = hooks->register_task(hooks->context, 1, state);
    hooks->initialize_animation(hooks->context, state,
                                state->animation_archive);

    state->position[0] = 0.0f;
    state->position[1] = 400.0f;
    state->score_seed = 40000;
    for (int index = 0; index < 4; ++index)
        state->random_values[index] = hooks->random_int(hooks->context);
    for (int index = 0; index < 33; ++index) {
        state->history[index][0] = state->position[0] == 0.0f ? 0 : 1;
        state->history[index][1] = state->score_seed;
    }

    ResetTimer(&state->movement_timer, &hooks->frame_speed, -2, -1, -1);

    state->player_object->speed = tables->object_speed[character];
    state->player_object->vertical_speed =
        tables->object_vertical_speed[character];
    state->player_object->horizontal_speed =
        tables->object_horizontal_speed[character];

    state->hitbox_half[0] = tables->hitbox_x[character];
    state->hitbox_half[1] = tables->hitbox_x[character];
    state->hitbox_half[2] = 5.0f;
    state->item_half[0] = tables->item_x[character];
    state->item_half[1] = tables->item_x[character];
    state->item_half[2] = 5.0f;
    state->graze_half[0] = tables->graze_x[character];
    state->graze_half[1] = tables->graze_x[character];
    state->graze_half[2] = 5.0f;

    BuildBounds(state->position, state->hitbox_half, state->hitbox_bounds);
    BuildBounds(state->position, state->item_half, state->item_bounds);
    BuildBounds(state->position, state->graze_half, state->graze_bounds);
    std::memcpy(state->graze_bounds_copy, state->graze_bounds,
                sizeof(state->graze_bounds));

    ResetTimer(&state->focus_timer, &hooks->frame_speed, -1, 0, 0);
    ResetTimer(&state->spawn_timer, &hooks->frame_speed, 119, 120,
               static_cast<int>(0x42f00000u));
    state->spawn_frames = 30;

    // Retail's final call is void and unconditional. It establishes the
    // derived player records but cannot affect this initializer's result.
    hooks->refresh_derived(hooks->context, state);
    return 0;
}

void LargePlayerRuntime_SetBindings(
        const LargePlayerRuntimeBindings* bindings) {
    if (bindings != 0)
        g_large_player_bindings = *bindings;
    else
        g_large_player_bindings = LargePlayerRuntimeBindings{};
}

// 0x004246C0 - The constructor's many preliminary stores are overwritten by
// its final full clear. Publish the resulting zeroed 0x4478-byte state.
void* LargePlayerRuntime_Construct(void* state) {
    if (state == 0)
        return 0;
    std::memset(state, 0, 0x4478);
    DAT_00477834 = (unsigned int)(unsigned long)state;
    return state;
}

// 0x004247F0 - ABI-ready initialization over the retail byte layout.
int LargePlayerRuntime_Initialize(void* state) {
    if (state == 0 || DAT_00491be4 == 0 ||
        g_large_player_bindings.create_player_object == 0 ||
        g_large_player_bindings.initialize_animation == 0 ||
        g_large_player_bindings.random_int == 0 ||
        g_large_player_bindings.refresh_derived == 0)
        return -1;
    unsigned char* bytes = (unsigned char*)state;
    const unsigned int character = DAT_00474c68 != 0 ? 1u : 0u;
    const char* resource_name = character == 0 ? "pl00.anm" : "pl01.anm";
    int* archive = ResourceManager_FindResource(
        8, g_pGameStateManager, resource_name);
    *(int**)(bytes + 0x10) = archive;
    if (archive == 0)
        return -1;

    void* player_object = reinterpret_cast<void*>(
        static_cast<uintptr_t>(DAT_00491bf0));
    if (player_object != 0) {
        DAT_00491bf0 = 0;
    } else {
        player_object = g_large_player_bindings.create_player_object();
        if (player_object == 0)
            return -1;
    }
    *(void**)(bytes + 0x45C) = player_object;

    SchedulerCallback* update = SchedulerCallback_Create(LargePlayer_Update);
    if (update == 0)
        return -1;
    update->flags &= ~2u;
    update->owner = state;
    Scheduler_RegisterPrimary(update, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 8) = update;
    SchedulerCallback* draw = SchedulerCallback_Create(LargePlayer_Draw);
    if (draw == 0) {
        Scheduler_Remove(update, (void*)(uintptr_t)DAT_00491be4);
        *(SchedulerCallback**)(bytes + 8) = 0;
        return -1;
    }
    draw->flags &= ~2u;
    draw->owner = state;
    Scheduler_RegisterSecondary(draw, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 12) = draw;
    g_large_player_bindings.initialize_animation(state, archive);

    *(float*)(bytes + 0x3C0) = 0.0f;
    *(float*)(bytes + 0x3C4) = 400.0f;
    *(float*)(bytes + 0x3C8) = 0.0f;
    *(int*)(bytes + 0x3CC) = 0;
    *(int*)(bytes + 0x3D0) = 40000;
    for (int index = 0; index != 4; ++index)
        *(int*)(bytes + 0x3D4 + index * 4) =
            g_large_player_bindings.random_int();
    for (int index = 0; index != 33; ++index) {
        *(int*)(bytes + 0x436C + index * 8) = *(int*)(bytes + 0x3CC);
        *(int*)(bytes + 0x4370 + index * 8) = *(int*)(bytes + 0x3D0);
    }
    ResetRawTimer(bytes, 0x460, -2, -1, (int)0xBF800000u);

    float* object = (float*)player_object;
    object[1] = DAT_00476fb8[character];
    object[3] = DAT_00476fb0[character];
    object[2] = DAT_00476fa0[character];
    const float half[3][3] = {
        {object[1] * _DAT_00470b0c, object[1] * _DAT_00470b0c, 5.0f},
        {DAT_00476fb0[character] * _DAT_00470b0c,
         DAT_00476fb0[character] * _DAT_00470b0c, 5.0f},
        {DAT_00476fa8[character] * _DAT_00470b0c,
         DAT_00476fa8[character] * _DAT_00470b0c, 5.0f},
    };
    std::memcpy(bytes + 0x41C, half, sizeof(half));
    const float position[3] = {
        *(float*)(bytes + 0x3C0), *(float*)(bytes + 0x3C4),
        *(float*)(bytes + 0x3C8)
    };
    const unsigned int bounds_offsets[] = {0x404, 0x4324, 0x433C, 0x4354};
    const int half_indices[] = {0, 1, 2, 2};
    for (int set = 0; set != 4; ++set) {
        float* bounds = (float*)(bytes + bounds_offsets[set]);
        const float* h = half[half_indices[set]];
        for (int axis = 0; axis != 3; ++axis) {
            bounds[axis] = position[axis] - h[axis];
            bounds[axis + 3] = position[axis] + h[axis];
        }
    }
    ResetRawTimer(bytes, 0x474, -1, 0, 0);
    ResetRawTimer(bytes, 0x430C, 119, 120, (int)0x42F00000u);
    *(int*)(bytes + 0x4308) = 30;
    g_large_player_bindings.refresh_derived(state);
    return 0;
}
