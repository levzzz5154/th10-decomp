#include "th10/game/gameplay_render_pass.hpp"

#include <cassert>
#include <cstring>
#include <vector>

namespace {

enum EventKind {
    kFlush,
    kSnapshot,
    kState,
    kClear,
    kRect,
    kCreateText,
    kStart,
    kStop,
    kAudio,
    kResource,
    kLayer,
};

struct Event {
    EventKind kind;
    int a;
    uint32_t b;
};

struct Fixture {
    GameplayRenderState state;
    GameplayRenderGlobals globals;
    GameplayRenderHooks hooks;
    std::vector<Event> events;

    Fixture() {
        std::memset(&state, 0, sizeof(state));
        std::memset(&globals, 0, sizeof(globals));
        hooks = {this, Flush, Snapshot, SetState, Clear, Rect, CreateText,
                 Start, Stop, Audio, Resource, Layer};
    }

    static Fixture* Self(void* context) {
        return static_cast<Fixture*>(context);
    }
    static void Add(void* context, EventKind kind, int a = 0,
                    uint32_t b = 0) {
        Self(context)->events.push_back({kind, a, b});
    }
    static void Flush(void* c) { Add(c, kFlush); }
    static void Snapshot(void* c, const void*) { Add(c, kSnapshot); }
    static void SetState(void* c, int state, uint32_t value) {
        Add(c, kState, state, value);
    }
    static void Clear(void* c, uint32_t color) { Add(c, kClear, 0, color); }
    static void Rect(void* c, const GameplayRenderRect* rect,
                     uint32_t color) {
        assert(rect->left == 32 && rect->top == 16);
        assert(rect->right == 416 && rect->bottom == 464);
        Add(c, kRect, 0, color);
    }
    static void CreateText(void* c) { Add(c, kCreateText); }
    static void Start(void* c, int value) { Add(c, kStart, value); }
    static void Stop(void* c) { Add(c, kStop); }
    static void Audio(void* c) { Add(c, kAudio); }
    static void Resource(void* c, int index) { Add(c, kResource, index); }
    static void Layer(void* c, int index) { Add(c, kLayer, index); }
};

int Count(const Fixture& fixture, EventKind kind) {
    int count = 0;
    for (const Event& event : fixture.events)
        if (event.kind == kind) ++count;
    return count;
}

const Event* FindState(const Fixture& fixture, int state) {
    for (const Event& event : fixture.events)
        if (event.kind == kState && event.a == state) return &event;
    return 0;
}

void TestDisabledFastPath() {
    Fixture fixture;
    fixture.state.flags = 8;
    fixture.state.transient[0] = 9;
    assert(GameplayRenderPass_Run(&fixture.state, &fixture.globals,
                                  &fixture.hooks) == 1);
    assert(fixture.events.empty());
    assert(fixture.state.transient[0] == 9);
}

void TestBaseRenderPass() {
    Fixture fixture;
    fixture.globals.seed_a = 0x11;
    fixture.globals.seed_b = 0x22;
    fixture.state.render_state_22 = 0xff123456u;
    fixture.state.render_state_24 = 7;
    fixture.state.render_state_25 = 8;
    fixture.state.transient[0] = 1;
    fixture.state.transient[1] = 2;
    fixture.state.transient[2] = 3;
    GameplayRenderPass_Run(&fixture.state, &fixture.globals, &fixture.hooks);
    assert(fixture.state.render_seed_a == 0x11);
    assert(fixture.state.render_seed_b == 0x22);
    assert(Count(fixture, kSnapshot) == 1);
    assert(FindState(fixture, 34)->b == 0xff123456u);
    assert(FindState(fixture, 36)->b == 7);
    assert(FindState(fixture, 37)->b == 8);
    assert(Count(fixture, kClear) == 1);
    assert(Count(fixture, kRect) == 1);
    for (const Event& event : fixture.events)
        if (event.kind == kRect) assert(event.b == 0x00123456u);
    assert(fixture.state.transient[0] == 0);
    assert(fixture.state.transient[1] == 0);
    assert(fixture.state.transient[2] == 0);
    assert(fixture.globals.tint_enabled == 0);
    assert(fixture.globals.tint_color == 0x80808080u);
}

void TestTransitionAndLayers() {
    Fixture fixture;
    fixture.state.flags = 4;
    fixture.state.transition_timer = 12;
    fixture.state.transition_frame = 20;
    fixture.state.tint_active = 1;
    fixture.state.tint_color = 0xaabbccddu;
    fixture.state.render_resources = 1;
    fixture.state.layer_active[1] = 1;
    fixture.state.layer_active[6] = 1;
    fixture.state.activity_counter = 4;
    GameplayRenderPass_Run(&fixture.state, &fixture.globals, &fixture.hooks);
    assert((fixture.state.flags & 1u) != 0);
    assert(Count(fixture, kCreateText) == 1);
    assert(Count(fixture, kStart) == 1);
    assert(Count(fixture, kStop) == 1);
    assert(Count(fixture, kAudio) == 1);
    assert(Count(fixture, kResource) == 2);
    assert(Count(fixture, kLayer) == 8);
    assert(fixture.state.activity_counter == 5);
    assert(fixture.globals.mode_28_initialized == 1);
    const Event* mode = FindState(fixture, 28);
    assert(mode != 0 && mode->b == 1);
    for (const Event& event : fixture.events)
        if (event.kind == kRect) assert(event.b == 0);
}

void TestExpiredTransitionAndFinalTint() {
    Fixture fixture;
    fixture.state.flags = 5;
    fixture.state.transition_timer = 60;
    fixture.state.tint_active = 1;
    fixture.state.secondary_tint = 1;
    GameplayRenderPass_Run(&fixture.state, &fixture.globals, &fixture.hooks);
    assert((fixture.state.flags & 1u) == 0);
    assert(fixture.state.tint_active == 0);
    assert(Count(fixture, kSnapshot) == 0);
    assert(Count(fixture, kLayer) == 0);
    assert(fixture.globals.tint_enabled == 1);
    assert(fixture.globals.tint_color == 0xff404040u);
}

}  // namespace

int main() {
    TestDisabledFastPath();
    TestBaseRenderPass();
    TestTransitionAndLayers();
    TestExpiredTransitionAndFinalTint();
    return 0;
}
