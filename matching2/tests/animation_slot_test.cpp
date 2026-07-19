// Test for the FUN_004136c0 reconstruction (AnimationSlot_Release).
//
// The helper marks each of the six slot handles via
// AnimationManager_SetFlag(manager, handle, 0x04000000) and then writes
// zero back into the slot word.  The stub animation manager below records
// the (handle, flag) pairs so the test can verify both halves of each
// retail iteration.

#include "th10/render/animation_slot.hpp"
#include "th10/render/animation_manager.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>


namespace {

struct RecordedSetFlag {
    int handle;
    unsigned int flag;
};

static RecordedSetFlag g_set_flag_log[16];
static unsigned int g_set_flag_count = 0;

}  // namespace

// Stand-in for AnimationManager_SetFlag that records the call instead
// of looking up an animation.  The signature matches the declaration in
// animation_manager.hpp so the C++-mangled symbol resolves at link time.
void AnimationManager_SetFlag(
    void* /*manager*/, int animationHandle, unsigned int flag) {
    assert(g_set_flag_count < sizeof(g_set_flag_log) / sizeof(g_set_flag_log[0]));
    g_set_flag_log[g_set_flag_count].handle = animationHandle;
    g_set_flag_log[g_set_flag_count].flag = flag;
    ++g_set_flag_count;
}

static void TestNullSlot() {
    g_set_flag_count = 0;
    AnimationSlot_Release(0, 0);
    assert(g_set_flag_count == 0);
}

static void TestAllSixHandlesMarkedAndCleared() {
    uint32_t slot[0x20] = {};
    slot[0x10] = 100;
    slot[0x11] = 200;
    slot[0x12] = 0;        // zero: must NOT be flagged
    slot[0x13] = 300;
    slot[0x14] = 400;
    slot[0x15] = 500;

    g_set_flag_count = 0;
    AnimationSlot_Release(slot, /*animation_manager=*/(void*)0xDEAD);

    assert(g_set_flag_count == 5);
    assert(g_set_flag_log[0].handle == 100);
    assert(g_set_flag_log[1].handle == 200);
    assert(g_set_flag_log[2].handle == 300);
    assert(g_set_flag_log[3].handle == 400);
    assert(g_set_flag_log[4].handle == 500);
    for (unsigned int i = 0; i < g_set_flag_count; ++i) {
        assert(g_set_flag_log[i].flag == 0x04000000u);
    }

    // Each slot word must be zeroed regardless of whether its handle
    // was originally nonzero.
    for (unsigned int i = 0x10; i <= 0x15; ++i) {
        assert(slot[i] == 0);
    }
}

static void TestNoHandlesMarkedWhenAllZero() {
    uint32_t slot[0x20] = {};
    g_set_flag_count = 0;
    AnimationSlot_Release(slot, 0);
    assert(g_set_flag_count == 0);
    for (unsigned int i = 0x10; i <= 0x15; ++i) {
        assert(slot[i] == 0);
    }
}

int main() {
    TestNullSlot();
    TestAllSixHandlesMarkedAndCleared();
    TestNoHandlesMarkedWhenAllZero();
    return 0;
}