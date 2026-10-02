#include "input_recorder_dependencies.hpp"

#pragma code_seg(".text$01key")
unsigned short RecorderKeyRepeatState::Update() {
    unsigned short held = held_keys;
    pressed = 0;
    unsigned short* counter = repeat_counters;
    for (int index = 0; index < 16; ++index) {
        if (held & 1) {
            if (++*counter >= 26) {
                repeat_flags |= 1;
                *counter -= 8;
            }
        } else {
            *counter = 0;
        }
        held >>= 1;
        ++counter;
    }
    unsigned short now = held_keys;
    unsigned short before = previous_keys;
    unsigned short changed = now ^ before;
    new_press = changed & now;
    unsigned short released = changed & ~now;
    new_release = released;
    return released;
}
#pragma code_seg()

#include "input_recorder_dependencies.hpp"

#pragma code_seg(".text$09page")
RecorderPoolLink* RecorderPoolLists::AppendPage(int stage) {
    RecorderPoolLink* link = &(new RecorderPool)->link;
    RecorderPoolLink* tail = &stages[stage];
    while (tail->next)
        tail = tail->next;
    if (tail->next) {
        link->next = tail->next;
        tail->next->previous = link;
    }
    tail->next = link;
    link->previous = tail;
    return link;
}
#pragma code_seg()
