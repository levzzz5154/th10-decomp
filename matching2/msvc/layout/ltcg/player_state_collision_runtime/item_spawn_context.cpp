#include "item_spawn.hpp"

// The game counters are one object that other code holds by address. This
// stand-in only makes that visible to the link; its bytes do not enter the image.
struct ItemGameCounters;
extern "C" ItemGameCounters g_item_counters;
#pragma code_seg(".text$f0040dca0F")
extern "C" void __stdcall ItemSpawnContext(ItemGameCounters** counters) {
    *counters = &g_item_counters;
}
#pragma code_seg()
