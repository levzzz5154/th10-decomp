// 0x00426F70: refresh the player's familiars from the power counter.  At
// 100 power or more the four attached effects are retired and recreated from
// the character/shot-type effect script; below 100 they are stopped instead.
// When the desired familiar count (power / 20, capped at four) differs from
// the applied one, each kept familiar is re-anchored on the player, its old
// animation retired, its schedule offsets rescaled and a new orbit animation
// allocated, initialized and registered; the surplus familiars are stopped.
// Finally the new count is stored and all four dirty flags are raised.
#include "th10/game/familiar_refresh_00426f70.hpp"

// The per-count schedule base table, the shot schedule owner (orbit bases),
// the shared half scaler of the schedule offsets and the animation manager.
extern "C" const int data_00476f7c[];
extern "C" void* g_player;
extern "C" float flt_100;
extern "C" void* g_sprt_ctrl;

static __forceinline FamiliarAnimManager_00426f70* AnimManager() {
    return (FamiliarAnimManager_00426f70*)g_sprt_ctrl;
}

// Trail sprite scheduler callback (0x00427950) and playback switch callback
// (0x00427AD0) installed on the refreshed orbit records.
struct PlayerOption;
struct PlaybackState;
int __fastcall PlayerOption_FollowTrail(PlayerOption* option);
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
    return reinterpret_cast<AnimationLists*>(AnimManager())
        ->RegisterPrimaryBack(object);
}

// Scale one schedule row (half size) into a record offset.
static __forceinline void ScaleOffset(FamiliarPoint_00426f70* out,
                                      const FamiliarOffsetRow_00426f70* row) {
    out->x = (int)(flt_100 * row->x);
    out->y = (int)(flt_100 * row->y);
}

static __forceinline int SpawnFamiliar(PlayerFamiliarRuntime_00426f70* player,
                                       int script) {
    AnimationResource_00449870* resource = player->resource;
    Entity* object = ((AnimationPool*)AnimManager())->Allocate();
    return SpawnOrbitAnimation(script, resource, object).value;
}

#pragma code_seg(".text$00426f70_fn")
extern "C" __declspec(noinline) void __stdcall Player_RefreshOptions(
        PlayerFamiliarRuntime_00426f70* player) {
    FamiliarRecord_00426f70* record = player->familiars;
    const unsigned int remove_flag = 0x4000000u;
    const int power = g_globals_score.power;
    int desired = power / 20;
    int i;

    // Sweep the four attached-effect handles.
    if (g_globals_score.power >= 100) {
        for (i = 4; i != 0; --i, ++record) {
            int handle = record->effect_handle;
            if (handle != 0) {
                FamiliarAnimEntry_00426f70* node = FindFamiliarAnimation(
                    AnimManager(), handle);
                if (node != 0)
                    RetireFamiliarAnimation(node, remove_flag);
            }
            record->effect_handle = 0;
            switch (g_globals_score.character * 3 + g_globals_score.shot_type) {
            case 0: {
                void* slot_0;
                record->effect_handle = (int)*AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_0, 0x14, 0xF);
                break; }
            case 1: {
                void* slot_1;
                record->effect_handle = (int)*AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_1, 0x15, 0xF);
                break; }
            case 2: {
                void* slot_2;
                record->effect_handle = (int)*AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_2, 0x16, 0xF);
                break; }
            case 3: {
                void* slot_3;
                record->effect_handle = (int)*AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_3, 0x14, 0xF);
                break; }
            case 4: {
                void* slot_4;
                record->effect_handle = (int)*AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_4, 0x15, 0xF);
                break; }
            case 5: {
                void* slot_5;
                record->effect_handle = (int)*AnimationManager_CreatePrimaryFront_00448e30(
                    player->resource, &slot_5, 0x16, 0xF);
                break; }
            }
        }
    } else {
        for (i = 4; i != 0; --i, ++record) {
            int handle = record->effect_handle;
            if (handle != 0) {
                FamiliarAnimEntry_00426f70* node =
                    FindFamiliarAnimation(AnimManager(), handle);
                if (node != 0)
                    StopFamiliarAnimation(node);
            }
        }
    }

    if (desired >= 5)
        desired = 4;
    if (player->familiar_count == desired)
        return;

    // Rebuild the requested number of familiars.
    for (i = 0; i < desired; ++i) {
        player->familiars[i].anchor.CopyFrom(player->anchor);
        int handle = player->familiars[i].handle;
        if (handle != 0) {
            FamiliarAnimEntry_00426f70* node = FindFamiliarAnimation(
                AnimManager(), handle);
            if (node != 0)
                RetireFamiliarAnimation(node, remove_flag);
        }
        player->familiars[i].handle = 0;
        player->familiars[i].index = i;

        switch (g_globals_score.character) {
        case 0: {
            // First character: both offsets from the schedule, the familiar
            // placed on the player at the offset of the current mode, then
            // the shot type's orbit script.
            ScaleOffset(&player->familiars[i].carried,
                        &player->offsets->carried[data_00476f7c[desired] + i]);
            ScaleOffset(&player->familiars[i].focused,
                        &player->offsets->focused[data_00476f7c[desired] + i]);
            const FamiliarPoint_00426f70* offset = player->alternate
                ? &player->familiars[i].focused : &player->familiars[i].carried;
            FamiliarPoint_00426f70 position = player->anchor + *offset;
            player->familiars[i].position.CopyFrom(position);
            player->familiars[i].anchor.CopyFrom(position);
            switch (g_globals_score.shot_type) {
            case 0: player->familiars[i].handle = SpawnFamiliar(player, 0x11); break;
            case 1: player->familiars[i].handle = SpawnFamiliar(player, 0x12); break;
            case 2: player->familiars[i].handle = SpawnFamiliar(player, 0x13); break;
            }
            break; }
        case 1:
            switch (g_globals_score.shot_type) {
            case 0: {
                // Second character, first shot type: the familiar follows the shot
                // schedule's orbit base and trails the player's position
                // history; in the alternate mode an idle familiar inherits
                // the unfocused offset of the previous one (the first takes
                // the focused offset of its schedule row).
                if (!player->alternate)
                    ScaleOffset(&player->familiars[i].carried,
                                &player->offsets->carried[data_00476f7c[desired] + i]);
                ScaleOffset(&player->familiars[i].focused,
                            &player->offsets->focused[data_00476f7c[desired] + i]);
                const int* orbit_base =
                    (const int*)((const char*)g_player + 0x43AC) + i * 16;
                player->familiars[i].position.x = orbit_base[0];
                player->familiars[i].position.y = orbit_base[1];
                if (player->alternate && player->familiars[i].state == 0) {
                    if (i == 0) {
                        ScaleOffset(&player->familiars[i].carried,
                                    &player->offsets->focused[data_00476f7c[desired] + i]);
                    } else {
                        player->familiars[i].carried.CopyFrom(player->familiars[i - 1].carried);
                    }
                }
                player->familiars[i].callback = (FamiliarCallback_00426f70)
                    &PlayerOption_FollowTrail;
                player->familiars[i].handle = SpawnFamiliar(player, 0x11);
                player->familiars[i].anchor.x = player->history[i * 8].x;
                player->familiars[i].anchor.y = player->history[i * 8].y;
                break; }
            case 1: {
                // Second shot type: both offsets, the familiar placed on the
                // player at the offset of the current mode.
                ScaleOffset(&player->familiars[i].carried,
                            &player->offsets->carried[data_00476f7c[desired] + i]);
                ScaleOffset(&player->familiars[i].focused,
                            &player->offsets->focused[data_00476f7c[desired] + i]);
                const FamiliarPoint_00426f70* offset = player->alternate
                    ? &player->familiars[i].focused : &player->familiars[i].carried;
                player->familiars[i].position = *offset + player->anchor;
                player->familiars[i].handle = SpawnFamiliar(player, 0x12);
                break; }
            case 2: {
                // Third shot type: the unfocused offset only; outside the
                // alternate mode (or for an idle familiar) the familiar and
                // its focused offset sit on the player at that offset.  The
                // playback switch callback runs it, stopped at frame 3 in the
                // alternate mode.
                ScaleOffset(&player->familiars[i].carried,
                            &player->offsets->carried[data_00476f7c[desired] + i]);
                if (!player->alternate || player->familiars[i].state == 0) {
                    player->familiars[i].position =
                        player->familiars[i].carried + player->anchor;
                    player->familiars[i].focused = player->familiars[i].position;
                }
                player->familiars[i].handle = SpawnFamiliar(player, 0x13);
                if (player->alternate)
                    ((AnimationHandle_00449470*)&player->familiars[i].handle)
                        ->SetStopFrame(3);
                player->familiars[i].callback = (FamiliarCallback_00426f70)
                    &PlaybackState_OnSwitch_00427ad0;
                break; }
            }
            break;
        }
        player->familiars[i].state = 2;
    }

    // Stop the surplus familiars beyond the desired count.
    for (; i < 4; ++i) {
        int* slot = &player->familiars[i].handle;
        int handle = *slot;
        ((FamiliarRecord_00426f70*)((char*)slot - 0x68))->state = 0;
        if (handle != 0) {
            FamiliarAnimEntry_00426f70* node =
                FindFamiliarAnimation(AnimManager(), handle);
            if (node != 0)
                StopFamiliarAnimation(node);
        }
    }

    player->familiar_count = desired;
    player->familiars[0].dirty = 1;
    player->familiars[1].dirty = 1;
    player->familiars[2].dirty = 1;
    player->familiars[3].dirty = 1;
}
#pragma code_seg()
