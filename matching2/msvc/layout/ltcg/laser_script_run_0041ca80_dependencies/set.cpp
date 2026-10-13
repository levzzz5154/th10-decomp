// Compiler context only: the real scheduler store 0x00405410, so the pass sees
// the callee's body and gives its callers the private register convention
// (record in EAX, value on the stack). Never selected from this cluster.
#define code_seg(name) code_seg(".text$00405410_fn")
#include "../../../src/game/player_set_scheduler_value_00405410.cpp"
