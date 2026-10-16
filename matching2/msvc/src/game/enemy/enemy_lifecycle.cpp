#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"





// 0x0040DAE0. Teardown of one enemy record: unlink it from the manager's list,
// drop it from the selector's name tables and the active-enemy slot table,
// detach it from the current game state and release its owned allocation list.
// The link node at +0x116C is embedded in the record, so the same triple is
// both the record's link and the list's node type.
extern "C" unsigned char g_enemy_vtable_live;   // 0x0046D0C0: live method table
extern "C" unsigned char g_enemy_vtable_released;   // 0x0046D0D8: released method table
extern "C" void __cdecl crt_free_startup(void* block);

struct Enemy5;

struct EnemyLink {
    Enemy5* owner;        // +0x00, points back to the containing enemy
    EnemyLink* next;     // +0x04
    EnemyLink* prev;     // +0x08

    void Unlink();
};

struct EnemyCtrlLifecycleView {
    char unknown_000[0x10];       // +0x00
    int entries[0x12];            // +0x10, indexed by the record's slot index
    EnemyLink* head;     // +0x58
    EnemyLink* tail;     // +0x5C
    int count;                    // +0x60
};

// One bucket of the selector's name tables: the owner pointer designates the
// record whose first word is the searched name.
struct SelectorNode {
    int* owner;                   // +0x00
    SelectorNode* next;  // +0x04
};

struct SelectorTarget;

struct MemberNode {
    SelectorTarget* target;   // +0x00
    MemberNode* next;         // +0x04
};

struct SelectorTarget {
    char unknown_000[0x14];            // +0x000
    MemberNode* members;      // +0x014
    int unknown_018;                   // +0x018
    char unknown_01C[0x35C - 0x1C];    // +0x01C
    int flags;                         // +0x35C
};

struct EnemySelector {
    char unknown_00000[0x72DAD4];      // +0x000000
    SelectorNode* primary;    // +0x72DAD4
    int unknown_72DAD8;                // +0x72DAD8
    SelectorNode* secondary;  // +0x72DADC
};

struct EnemyFreeNode {
    void* data;                        // +0x00
    EnemyFreeNode* next;      // +0x04
};

struct Enemy5 {
    int vtable;                        // +0x0000
    char unknown_0004[0x1034 - 0x4];   // +0x0004
    EnemyFreeNode* free_list; // +0x1034
    char unknown_1038[0x10FC - 0x1038];
    int entries[10];                   // +0x10FC
    char unknown_1124[0x116C - 0x1124];
    EnemyLink link;           // +0x116C
    char unknown_1178[0x2480 - 0x1178];
    int flags;                         // +0x2480
    char unknown_2484[0x248C - 0x2484];
    int index;                         // +0x248C
};

struct EnemyState3 {
    char unknown_0000[0x3504];         // +0x0000
    Enemy5* enemy;             // +0x3504
    unsigned char mirror;              // +0x3508
};

void EnemyLink::Unlink() {
    if (next != 0)
        next->prev = prev;
    if (prev != 0)
        prev->next = next;
    next = 0;
    prev = 0;
}

void __stdcall Enemy_Release(Enemy5* self) {
    EnemyCtrlLifecycleView* manager = *(EnemyCtrlLifecycleView**)&g_enemy_ctrl;
    self->vtable = (int)&g_enemy_vtable_live;
    if (manager->head == &self->link)
        manager->head = self->link.next;
    if (manager->tail == &self->link)
        manager->tail = self->link.prev;
    self->link.Unlink();
    --manager->count;
    if (self->flags & 0x8000)
        manager->entries[self->index] = 0;

    EnemySelector* selector = *(EnemySelector**)&g_sprt_ctrl;
    int* entry = self->entries;
    for (int remaining = 10; remaining != 0; --remaining) {
        int name = *entry;
        if (name != 0) {
            SelectorNode* node = selector->primary;
            while (node != 0 && *node->owner != name)
                node = node->next;
            if (node == 0) {
                node = selector->secondary;
                while (node != 0 && *node->owner != name)
                    node = node->next;
            }
            if (node != 0) {
                SelectorTarget* target = (SelectorTarget*)node->owner;
                if (target != 0) {
                    target->flags |= 0x4000000;
                    if (target->unknown_018 == 0) {
                        for (MemberNode* member = target->members; member != 0;
                             member = member->next)
                            member->target->flags |= 0x4000000;
                    }
                }
            }
        }
        *entry = 0;
        ++entry;
    }

    EnemyState3* state = *(EnemyState3**)&g_player;
    if (state != 0) {
        if (state->enemy == self) {
            state->enemy = 0;
            state->mirror = 0;
        }
        int* slot = (int*)((char*)state + 0x4E8);
        for (int count = 0x80; count != 0; --count) {
            if (*slot == (int)self)
                *slot = 0;
            slot = (int*)((char*)slot + 0x5C);
        }
    }

    EnemyFreeNode* block = self->free_list;
    self->vtable = (int)&g_enemy_vtable_released;
    while (block != 0) {
        EnemyFreeNode* next = block->next;
        crt_free_startup(block->data);
        crt_free_startup(block);
        block = next;
    }
}
