#define data_00491c10 stage_front_data_00491c10
#define data_0047770c stage_front_data_0047770c
#define data_00474c40 stage_front_data_00474c40
#define g_ascii_manager stage_front_data_004776e0
#define data_00477704 stage_front_data_00477704
#define g_player stage_front_data_00477834
#define data_00477838 stage_front_data_00477838
#define data_0047783c stage_front_data_0047783c
#define data_00476f78 stage_front_data_00476f78
#define data_00491fc4 stage_front_data_00491fc4
#define data_00491fb8 stage_front_data_00491fb8
#define data_00492590 stage_front_data_00492590
// Complete 4096-entry pool allocator at 0x00449950, manager ESI and Entity* result EAX.
#include "front_view.hpp"

#pragma code_seg(".text$00449950_fn")
Entity *FrontAnimationPool::Allocate() {
    int slot = next_slot;
    Entity *object = &objects[slot];
    if (occupied[slot]) {
        slot = (slot + 1) % 4096;
        next_slot = slot;
        object = &objects[slot];
        if (occupied[slot]) {
            Entity *block = (Entity *)operator new(sizeof(Entity));
            Entity *created = block != 0 ? Entity_Constructor(block) : (Entity *)0;
            object = created;
            Entity_Init(created);
        } else {
            occupied[slot] = 1;
        }
    } else {
        occupied[slot] = 1;
    }
    next_slot = (next_slot + 1) % 4096;
    return object;
}
#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
