// 0x00426F70: refresh the player's familiar/orbit records from the power
// gauge.  When the signed gauge word at 0x00474C48 reaches 100 the four
// attached-effect animations are marked for removal and immediately rebuilt
// from the shot-type/difficulty sprite table; below 100 they are stopped
// instead.  When the desired familiar count (gauge / 20, capped at four)
// changes, every active record is re-anchored on the player, its previous
// animation retired, and a new orbit animation is allocated, initialized and
// registered; surplus records are stopped.  Finally the new count is stored
// and all four dirty flags are raised.
#include "th10/game/familiar_refresh_00426f70.hpp"

// Difficulty and shot type selections (0x00474C6C and 0x00474C68), the
// per-count schedule base table, the shot schedule owner and the shared
// half scaler used by the random-offset conversion.
extern "C" int data_00474c6c;
extern "C" int data_00474c68;
extern "C" short data_00474c48;
extern "C" const int data_00476f7c[];
extern "C" void* data_00477834;
extern "C" float data_00470b44;
extern "C" void* data_00491c10;

// The retail sweep re-reads the manager global at every iteration that also
// allocates, so the refresh reads it through a volatile lvalue there; the
// call-free sweeps read it once.  The volatile view is spelled per site.
static __forceinline FamiliarAnimManager_00426f70* ManagerReload() {
    return *(FamiliarAnimManager_00426f70* volatile*)&data_00491c10;
}

// Trail sprite scheduler callback (0x00427950) and playback switch callback
// (0x00427AD0) installed on the refreshed orbit records.
struct TrailSprite_00427960;
struct PlaybackState;
int __fastcall TrailSpriteUpdateCallback_00427950(TrailSprite_00427960* sprite);
int __fastcall PlaybackState_OnSwitch_00427ad0(PlaybackState* state);

// The animation-manager create wrapper (0x00448E30): builds one sprite of the
// requested script on layer 0x0F and hands the registered handle back through
// the out slot.  Its private convention passes the out slot in EDI.
void** __stdcall AnimationManager_CreatePrimaryFront_00448e30(
    void* resource, void** out, int index, int render_bucket);

// Resolve a handle through both manager buckets the way the retail sweep
// inlines it: primary list first, then the secondary list, matching each
// node's registered object id.
static __forceinline FamiliarAnimEntry_00426f70* FindFamiliarAnimation(
        FamiliarAnimManager_00426f70* manager, int handle) {
    FamiliarAnimEntry_00426f70* node;
    for (node = manager->primary_head; node != 0; node = node->next)
        if (node->object->animation_handle == handle)
            return node;
    for (node = manager->secondary_head; node != 0; node = node->next)
        if (node->object->animation_handle == handle)
            return node;
    return 0;
}

// Mark one resolved animation and, unless its children are already flagged,
// the whole direct child chain for removal (power >= 100 sweep).
static __forceinline void RetireFamiliarAnimation(
        FamiliarAnimEntry_00426f70* node, unsigned int remove_flag) {
    FamiliarAnimObject_00426f70* object = node->object;
    if (object == 0)
        return;
    object->flags |= remove_flag;
    if (!object->children_flagged)
        for (FamiliarAnimEntry_00426f70* child = object->children;
             child != 0; child = child->next)
            child->object->flags |= remove_flag;
}

// Stop one resolved animation and its direct child chain (power < 100 sweep
// and the surplus-record tail).
static __forceinline void StopFamiliarAnimation(
        FamiliarAnimEntry_00426f70* node) {
    FamiliarAnimObject_00426f70* object = node->object;
    if (object == 0)
        return;
    object->stop_frame = 1;
    if (!object->children_flagged)
        for (FamiliarAnimEntry_00426f70* child = object->children;
             child != 0; child = child->next)
            child->object->stop_frame = 1;
}

// Allocate one manager object, force layer 0x0F and the live flag, run the
// requested script on it and register it; the handle lands in the out slot.
static __forceinline AnimationRef SpawnOrbitAnimation(
        int script, AnimationResource_00449870* resource, Entity* object) {
    unsigned int flags = object->flags_35C;
    object->render_bucket = 0xF;
    object->flags_35C = flags | 0x40000000u;
    resource->InitializeObject(object, script);
    return reinterpret_cast<AnimationLists*>(ManagerReload())
        ->RegisterPrimaryBack(object);
}

#pragma code_seg(".text$00426f70_fn")
extern "C" __declspec(noinline) void __stdcall PlayerFamiliarRefresh_00426f70(
        PlayerFamiliarRuntime_00426f70* player) {
    FamiliarOrbitControl_00426f70* effects =
        (FamiliarOrbitControl_00426f70*)((char*)player->orbit_slots + 0xBC);
    const unsigned int remove_flag = 0x4000000u;
    const short gauge = data_00474c48;
    const int power = gauge;
    int desired = power / 20;
    int orbit;                              // shared sweep/loop counter

    // Sweep the four attached-effect handles at +0x330C.
    if (gauge >= 100) {
        FamiliarOrbitControl_00426f70* control = effects;
        for (orbit = 4; orbit != 0; --orbit, ++control) {
            int handle = control->effect_handle;
            if (handle != 0) {
                FamiliarAnimEntry_00426f70* node = FindFamiliarAnimation(
                    ManagerReload(), handle);
                if (node != 0)
                    RetireFamiliarAnimation(node, remove_flag);
            }
            control->effect_handle = 0;
            switch (data_00474c68 * 3 + data_00474c6c) {
            case 0: {
                void* slot_0;
                void** out = AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_0, 0x14, 0xF);
                control->effect_handle = (int)(unsigned int)*out;
                break; }
            case 1: {
                void* slot_1;
                void** out = AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_1, 0x15, 0xF);
                control->effect_handle = (int)(unsigned int)*out;
                break; }
            case 2: {
                void* slot_2;
                void** out = AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_2, 0x16, 0xF);
                control->effect_handle = (int)(unsigned int)*out;
                break; }
            case 3: {
                void* slot_3;
                void** out = AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_3, 0x14, 0xF);
                control->effect_handle = (int)(unsigned int)*out;
                break; }
            case 4: {
                void* slot_4;
                void** out = AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_4, 0x15, 0xF);
                control->effect_handle = (int)(unsigned int)*out;
                break; }
            case 5: {
                void* slot_5;
                void** out = AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_5, 0x16, 0xF);
                control->effect_handle = (int)(unsigned int)*out;
                break; }
            default:
                break;
            }
        }
    } else {
        FamiliarAnimManager_00426f70* manager =
            (FamiliarAnimManager_00426f70*)data_00491c10;
        FamiliarOrbitControl_00426f70* control = effects;
        for (orbit = 4; orbit != 0; --orbit, ++control) {
            int handle = control->effect_handle;
            if (handle != 0) {
                FamiliarAnimEntry_00426f70* node =
                    FindFamiliarAnimation(manager, handle);
                if (node != 0)
                    StopFamiliarAnimation(node);
            }
        }
    }

    if (desired >= 5)
        desired = 4;
    if (player->orbit_slots[4].stored_count == desired)
        return;

    // Rebuild the requested number of orbit records.
    for (orbit = 0; orbit < desired; ++orbit) {
        int i = orbit;
        FamiliarOrbitSlot_00426f70* slot = &player->orbit_slots[i];
        FamiliarOrbitSlot_00426f70* next_slot = &player->orbit_slots[i + 1];
        FamiliarOrbitControl_00426f70* control =
            (FamiliarOrbitControl_00426f70*)((char*)slot + 0xBC);
        slot->position_x = player->anchor_x;
        slot->position_y = player->anchor_y;
        int handle = control->handle;
        if (handle != 0) {
            FamiliarAnimEntry_00426f70* node = FindFamiliarAnimation(
                ManagerReload(), handle);
            if (node != 0)
                RetireFamiliarAnimation(node, remove_flag);
        }
        control->handle = 0;
        control->orbit_index = i;

        if (data_00474c68 != 0) {
            if (data_00474c6c == 0) {
                // Shot 2, unfocused: schedule offsets, orbit base from the
                // shot schedule table, position history entry for the record.
                const int k = data_00476f7c[desired] + i;
                const int j = k * 3;
                if (!player->alternate) {
                    next_slot->carried_x =
                        (int)(data_00470b44 *
                              player->offsets->carried[j]);
                    next_slot->carried_y =
                        (int)(data_00470b44 *
                              player->offsets->carried[j + 1]);
                }
                next_slot->focused_x =
                    (int)(data_00470b44 * player->offsets->second[j]);
                next_slot->focused_y =
                    (int)(data_00470b44 * player->offsets->second[j + 1]);
                const int* orbit_base =
                    (const int*)((const char*)data_00477834 + 0x43AC) + i * 16;
                slot->x = orbit_base[0];
                slot->y = orbit_base[1];
                if (player->alternate && slot->state == 0) {
                    if (i == 0) {
                        next_slot->carried_x =
                            (int)(data_00470b44 *
                                  player->offsets->second[j]);
                        next_slot->carried_y =
                            (int)(data_00470b44 *
                                  player->offsets->second[j + 1]);
                    } else {
                        next_slot->carried_x = slot->carried_x;
                        next_slot->carried_y = slot->carried_y;
                    }
                }
                control->update_callback =
                    (FamiliarOrbitCallback_00426f70)
                        &TrailSpriteUpdateCallback_00427950;
                AnimationResource_00449870* resource = player->resource;
                AnimationPool* pool = (AnimationPool*)ManagerReload();
                Entity* object = pool->Allocate();
                AnimationRef ref = SpawnOrbitAnimation(0x11, resource, object);
                control->handle = ref.value;
                slot->position_x = player->history[i * 8].x;
                slot->position_y = player->history[i * 8].y;
            } else if (data_00474c6c == 1) {
                // Shot 2, focused: schedule offsets for both modes, position
                // anchored on the player.
                const int k = data_00476f7c[desired] + i;
                const int j = k * 3;
                next_slot->carried_x =
                    (int)(data_00470b44 * player->offsets->carried[j]);
                next_slot->carried_y =
                    (int)(data_00470b44 * player->offsets->carried[j + 1]);
                next_slot->focused_x =
                    (int)(data_00470b44 * player->offsets->second[j]);
                next_slot->focused_y =
                    (int)(data_00470b44 * player->offsets->second[j + 1]);
                const int* base = player->alternate
                    ? &next_slot->focused_x
                    : (const int*)(const float*)&player->offsets->carried[j];
                slot->x = player->anchor_x + base[0];
                slot->y = player->anchor_y + base[1];
                AnimationResource_00449870* resource = player->resource;
                AnimationPool* pool = (AnimationPool*)ManagerReload();
                Entity* object = pool->Allocate();
                AnimationRef ref = SpawnOrbitAnimation(0x12, resource, object);
                control->handle = ref.value;
            } else {
                // Shot 2, focused alternate: schedule offsets, position and
                // the focused pair from the unfocused row, stop frame and
                // playback callback installed through the new handle.
                const int k = data_00476f7c[desired] + i;
                const int j = k * 3;
                next_slot->carried_x =
                    (int)(data_00470b44 * player->offsets->carried[j]);
                next_slot->carried_y =
                    (int)(data_00470b44 * player->offsets->carried[j + 1]);
                if (!player->alternate || slot->state != 0) {
                    slot->x = next_slot->focused_x =
                        player->anchor_x + next_slot->carried_x;
                    slot->y = next_slot->focused_y =
                        player->anchor_y + next_slot->carried_y;
                }
                AnimationResource_00449870* resource = player->resource;
                AnimationPool* pool = (AnimationPool*)ManagerReload();
                Entity* object = pool->Allocate();
                AnimationRef ref = SpawnOrbitAnimation(0x13, resource, object);
                control->handle = ref.value;
                if (player->alternate)
                    ((AnimationHandle_00449470*)&control->handle)
                        ->SetStopFrame(3);
                control->update_callback =
                    (FamiliarOrbitCallback_00426f70)
                        &PlaybackState_OnSwitch_00427ad0;
            }
        } else {
            // Shot 1: four random offset words from the schedule, position
            // anchored on the player, then the difficulty's orbit script.
            const int k = data_00476f7c[desired] + i;
            const int j = k * 3;
            next_slot->carried_x =
                (int)(data_00470b44 * player->offsets->carried[j]);
            next_slot->carried_y =
                (int)(data_00470b44 * player->offsets->carried[j + 1]);
            next_slot->focused_x =
                (int)(data_00470b44 * player->offsets->second[j]);
            next_slot->focused_y =
                (int)(data_00470b44 * player->offsets->second[j + 1]);
            const int* base = player->alternate
                ? &next_slot->focused_x : &next_slot->carried_x;
            slot->x = slot->position_x = player->anchor_x + base[0];
            slot->y = slot->position_y = player->anchor_y + base[1];
            if (data_00474c6c == 0) {
                AnimationResource_00449870* resource = player->resource;
                AnimationPool* pool = (AnimationPool*)ManagerReload();
                Entity* object = pool->Allocate();
                AnimationRef ref =
                    SpawnOrbitAnimation(0x11, resource, object);
                control->handle = ref.value;
            } else if (data_00474c6c == 1) {
                AnimationResource_00449870* resource = player->resource;
                AnimationPool* pool = (AnimationPool*)ManagerReload();
                Entity* object = pool->Allocate();
                AnimationRef ref =
                    SpawnOrbitAnimation(0x12, resource, object);
                control->handle = ref.value;
            } else if (data_00474c6c == 2) {
                AnimationResource_00449870* resource = player->resource;
                AnimationPool* pool = (AnimationPool*)ManagerReload();
                Entity* object = pool->Allocate();
                AnimationRef ref =
                    SpawnOrbitAnimation(0x13, resource, object);
                control->handle = ref.value;
            }
        }
        slot->state = 2;
    }

    // Stop the surplus records beyond the desired count.
    FamiliarAnimManager_00426f70* manager =
        (FamiliarAnimManager_00426f70*)data_00491c10;
    for (int j = desired; j < 4; ++j) {
        FamiliarOrbitSlot_00426f70* slot = &player->orbit_slots[j];
        FamiliarOrbitControl_00426f70* control =
            (FamiliarOrbitControl_00426f70*)((char*)slot + 0xBC);
        int handle = control->handle;
        slot->state = 0;
        if (handle != 0) {
            FamiliarAnimEntry_00426f70* node =
                FindFamiliarAnimation(manager, handle);
            if (node != 0)
                StopFamiliarAnimation(node);
        }
    }

    player->orbit_slots[4].stored_count = desired;
    ((FamiliarOrbitControl_00426f70*)((char*)&player->orbit_slots[0] + 0xBC))->dirty = 1;
    ((FamiliarOrbitControl_00426f70*)((char*)&player->orbit_slots[1] + 0xBC))->dirty = 1;
    ((FamiliarOrbitControl_00426f70*)((char*)&player->orbit_slots[2] + 0xBC))->dirty = 1;
    ((FamiliarOrbitControl_00426f70*)((char*)&player->orbit_slots[3] + 0xBC))->dirty = 1;
}
#pragma code_seg()
