// Complete primary-back registration at 0x004489D0; a real aggregate result
// represents the hidden output pointer, with no extra unused source formal.
#include "th10/game/pause_result_open_004231d0/player/movement/movement.hpp"
#pragma code_seg(".text$004489d0_fn")
AnimationScriptId MovementPrimaryLists::RegisterPrimaryBack(Entity* object) {
    AnimationManagerNodeOpen* node = reinterpret_cast<AnimationManagerNodeOpen*>(&object->manager_node_animation);
    node->animation = object;
    node->next = 0;
    node->previous = 0;
    if (head == 0) {
        head = node;
    } else {
        AnimationManagerNodeOpen* last = tail;
        AnimationManagerNodeOpen* next = last->next;
        if (next != 0) {
            node->next = next;
            last->next->previous = node;
        }
        last->next = node;
        node->previous = last;
    }
    tail = node;
    int id = ++next_id;
    if (id == 0)
        ++next_id;
    object->animation_handle = next_id;
    return AnimationScriptId(next_id);
}
#pragma code_seg()
