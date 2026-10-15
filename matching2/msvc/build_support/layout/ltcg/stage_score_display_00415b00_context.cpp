// Compiler-only dependencies: complete pool, primary-list, lookup and activation bodies.
#include "../../../src/game/front/stage_score_display_00415b00.cpp"
void* __cdecl operator new(unsigned int,void*);

#pragma code_seg(".text$00401000_context")
extern "C" StageScoreDisplay* __stdcall entry(StageScoreDisplay* target,const void* data) { return new(target) StageScoreDisplay(data); }
#pragma code_seg()
void* __cdecl operator new(unsigned int,void* target) { return target; }
#pragma code_seg(".text$004489d0_fn")
SlotRef SlotLists::RegisterPrimaryBack(Entity* object) {
    AnimationManagerNodeOpen* node = reinterpret_cast<AnimationManagerNodeOpen*>(
        &object->manager_node_animation);
    node->animation = object;
    node->next = 0;
    node->previous = 0;
    if (!primary_head)
        primary_head = node;
    else {
        AnimationManagerNodeOpen* tail = primary_tail;
        AnimationManagerNodeOpen* next = tail->next;
        if (next) {
            node->next = next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    primary_tail = node;
    if (++next_id == 0)
        ++next_id;
    object->animation_handle = next_id;
    return SlotRef(next_id);
}
#pragma code_seg()


#include "result_open_00423370/allocate.cpp"

#include "result_open_00423370/find.cpp"

__declspec(noinline) void** __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource, void** out, int index, const Vector3* position);

// 0x00408030: start a live record's vanish.
//
// Only records in state 1 or 2 react. The record moves to state 3; one that
// is still on the playfield spawns its vanish animation and restarts its
// timer, one already more than 8 units outside is just flagged for removal.
// The record arrives in ESI.
#pragma code_seg(".text$00408030_fn")
int StageCollisionRecord::Activate() {
    if (state != 2 && state != 1) return 0;
    if (!reinterpret_cast<const PlayfieldPoint*>(&position)->OutsideBounds(8.0f, 8.0f)) {
        state = 3;
        animation_state = 1;
        if (animation_index >= 0) {
            void* output;
            ItemAnimation_CreateOffset_00448db0(data_004776f0->item_animation, &output,
                animation_index, reinterpret_cast<const Vector3*>(&position));
        }
        if (!(timer_flags & 1u)) {
            timer_current = 0;
            timer_previous = -999999;
            timer_elapsed = 0.0f;
            timer_speed = &g_game_speed;
            timer_flags |= 1u;
        }
        timer_current = 0;
        timer_elapsed = 0.0f;
        timer_previous = -1;
        return 1;
    }
    state = 3;
    animation_state = 1;
    flags |= 8;
    return 1;
}
#pragma code_seg()


