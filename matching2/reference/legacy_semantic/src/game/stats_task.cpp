#include "th10/game/stats_task.hpp"

#include <cstring>

extern uint32_t DAT_00491be4;  // scheduler device token

// Published gameplay stats manager (retail 0x00477708). The high-score
// insert reads the completion doubles from this object.
uint8_t* DAT_00477708;

// 0x00413350 - Create the gameplay stats manager and its scheduler
// task. Retail news 0x8C bytes for the manager (0x23 words zeroed,
// constructed bit set, published) and 0x24 bytes for the node, whose
// fields are cleared, self-linked, pointed at the callback and owner,
// and flagged live before FUN_00449B70 registers it with the token from
// 0x00491BE4; the node lands in the manager's word 3.
uint32_t* GameplayStats_CreateAndRegister(
        void* (*allocate)(uint32_t size),
        void (*register_task)(uint32_t token), void* task_callback) {
    uint32_t* manager =
        allocate != 0 ? (uint32_t*)allocate(0x8C) : (uint32_t*)0;
    if (manager != 0) {
        memset(manager, 0, 0x23 * sizeof(uint32_t));
        manager[0] |= 2u;
        DAT_00477708 = (uint8_t*)manager;
    }
    StatsTaskNode* node =
        allocate != 0 ? (StatsTaskNode*)allocate(0x24) : (StatsTaskNode*)0;
    if (node == 0) {
        // Retail continues and dereferences the null node here.
        return manager;
    }
    node->reserved_3 = 0;
    node->reserved_4 = 0;
    node->state0 = 0;
    node->flags &= ~1u;
    node->self = node;
    node->reserved_6 = 0;
    node->reserved_7 = 0;
    node->callback = task_callback;
    node->owner = manager;
    node->flags |= 3u;
    if (register_task != 0) {
        register_task(DAT_00491be4);
    }
    if (manager != 0) {
        // Retail keeps a 32-bit pointer slot; the host image truncates.
        manager[3] = (uint32_t)(uintptr_t)node;
    }
    return manager;
}
