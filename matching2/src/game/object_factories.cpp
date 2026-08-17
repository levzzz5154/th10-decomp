#include "th10/game/object_factories.hpp"


#include <cstring>

extern "C" void _free(void* memory);

// Published score manager (retail 0x0047781C).
uint32_t* DAT_0047781c;

// 0x0041C290 - Create the score manager. Retail news 0x45C bytes,
// constructs the embedded sub-object at word 4, then zeroes all 0x117
// words (killing the construction) while publishing the pointer through
// 0x0047781C, and finally runs the score-display initializer; a failed
// initializer tears the object down again.

uint32_t* ScoreManager_CreateAndInit(void* (*allocate)(uint32_t size),
                                     void (*construct_base)(uint32_t* base),
                                     int32_t (*init)(uint32_t* state),
                                     void (*destroy)(uint32_t* state)) {
    uint32_t* state =
        allocate != 0 ? (uint32_t*)allocate(0x45C) : (uint32_t*)0;
    if (state != 0) {
        if (construct_base != 0) {
            construct_base(state + 4);  // dead: the wipe below covers it
        }
        memset(state, 0, 0x117 * sizeof(uint32_t));
        DAT_0047781c = state;
    }
    const int32_t failed = init != 0 ? init(state) : 0;
    if (failed != 0) {
        if (state != 0) {
            if (destroy != 0) {
                destroy(state);
            }
            _free(state);
        }
        return 0;
    }
    return state;
}

// 0x0041FD00 - Create one enemy slot. The constructor edge returns the
// object (retail FUN_0041F850 returns it in EAX); the initializer runs
// unconditionally, matching retail.

uint32_t* EnemySlot_CreateAndInit(void* (*allocate)(uint32_t size),
                                  uint32_t* (*construct)(uint32_t* state),
                                  int32_t (*init)(),
                                  void (*destroy)(uint32_t* state)) {
    uint32_t* state =
        allocate != 0 ? (uint32_t*)allocate(0x3F0) : (uint32_t*)0;
    if (state != 0 && construct != 0) {
        state = construct(state);
    }
    const int32_t failed = init != 0 ? init() : 0;
    if (failed != 0) {
        if (state != 0) {
            if (destroy != 0) {
                destroy(state);
            }
            _free(state);
        }
        return 0;
    }
    return state;
}
