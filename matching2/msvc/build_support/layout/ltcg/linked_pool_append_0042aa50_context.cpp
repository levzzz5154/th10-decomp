// Compiler context only; never selected as recovered game code.
#include "th10/game/linked_pool_append.hpp"
#include "../../../src/game/replay/linked_pool_append_0042aa50.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$a09context")
extern "C" int __stdcall LinkedPoolAppendContext(PoolOwner_0042aa50** owners, const int* slots, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += (int)owners[index]->AppendPage(slots[index]);
    return total;
}
#pragma code_seg()
#pragma inline_depth()
