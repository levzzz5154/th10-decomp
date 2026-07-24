#include "th10/app/game_state_init.hpp"

#include <cassert>
#include <cstring>
#include <vector>

namespace {

struct HookState {
    int construct_calls;
    int bind_calls;
    int primary_calls;
    int secondary_calls;
    int device_calls;
};

void Construct(void* context, void*, int stride, int count) {
    HookState* state = static_cast<HookState*>(context);
    ++state->construct_calls;
    assert(stride == GAME_STATE_ENTITY_STRIDE_BYTES);
    assert(count == GAME_STATE_ENTITY_COUNT ||
           count == GAME_STATE_SECOND_TABLE_COUNT);
}

void Bind(void* context, int index, void*) {
    HookState* state = static_cast<HookState*>(context);
    assert(index == state->bind_calls);
    ++state->bind_calls;
}

int Primary(void* context, int index) {
    HookState* state = static_cast<HookState*>(context);
    assert(index == state->primary_calls);
    ++state->primary_calls;
    return 0;
}

int Secondary(void* context, int index) {
    HookState* state = static_cast<HookState*>(context);
    assert(index == state->secondary_calls);
    ++state->secondary_calls;
    return 0;
}

void Device(void* context) {
    ++static_cast<HookState*>(context)->device_calls;
}

} // namespace

int main() {
    std::vector<unsigned char> arena(0x732460u, 0xFFu);
    HookState state = {};
    GameStateInitHooks hooks = {
        &state, Construct, Bind, Primary, Secondary, Device,
    };
    GameStateCallbackPlan plan = {2, 18};
    GameStateMatrixGlobals matrices;
    for (float& value : matrices.values)
        value = -7.0f;

    assert(GameStateInit_Construct(arena.data(), arena.size(), &hooks, &plan,
                                   &matrices) == arena.data());
    assert(state.construct_calls == 2);
    assert(state.bind_calls == GAME_STATE_ENTITY_COUNT);
    assert(state.primary_calls == 2);
    assert(state.secondary_calls == 18);
    assert(state.device_calls == 1);

    const unsigned int identity_offsets[] = {
        0x48, 0x30, 0x18, 0x00, 0x1C, 0x38, 0x4C, 0x50,
        0xB4, 0x98, 0x7C, 0x60, 0x84, 0xA4, 0xBC, 0xC0,
    };
    for (unsigned int offset : identity_offsets)
        assert(matrices.values[offset / 4u] == 1.0f);
    assert(matrices.values[1] == 0.0f);
    assert(matrices.values[2] == 0.0f);
    assert(matrices.values[48] == 1.0f);
    return 0;
}
