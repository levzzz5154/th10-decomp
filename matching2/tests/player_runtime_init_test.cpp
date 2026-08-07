#include "th10/game/player_runtime_init.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

// Retail globals consumed by the linked player-runtime source.
uint32_t DAT_00491be4 = 0;
uint32_t DAT_00474e36 = 0;  // input (the 0x00426500 forwarder)
uint32_t DAT_00491bf0 = 0;
float DAT_00470b4c = 224.0f;   // stage controller projected x bias
float DAT_00470b48 = 16.0f;    // stage controller projected y bias
float DAT_00470cbc = 225.0f;   // effect x bias component
float DAT_00470cb4 = 17.0f;    // effect y bias component
float DAT_00470be8 = 24.0f;    // effect y bias component

// Render leaves globals.
extern "C" {
unsigned long dword_491C10 = 0;   // animation manager
unsigned long dword_491C30 = 0;   // D3D device
}
uint32_t DAT_00474c68 = 0;
uint32_t DAT_00477834 = 0;
uint32_t DAT_00476f78 = 0;
uint32_t DAT_00492274 = 0;
unsigned char DAT_0049231c = 0;
void* g_pGameStateManager = 0;
float _DAT_00470b0c = 1.0f;
float DAT_00476fa0[2] = {0.0f, 0.0f};
float DAT_00476fa8[2] = {0.0f, 0.0f};
float DAT_00476fb0[2] = {0.0f, 0.0f};
float DAT_00476fb8[2] = {0.0f, 0.0f};

extern "C" void* operator_new(uint32_t size) {
    return std::malloc(size);
}
extern "C" void _free(void* memory) {
    std::free(memory);
}
extern "C" void __stdcall EnterCriticalSection(void*) {}
extern "C" void __stdcall LeaveCriticalSection(void*) {}

int* ResourceManager_FindResource(int, void*, const char*) {
    return 0;
}

namespace {

struct Fixture {
    PlayerRuntimeState state;
    PlayerRuntimeObject object;
    PlayerRuntimeTables tables;
    PlayerRuntimeInitHooks hooks;
    bool load_ok;
    bool create_ok;
    int random_value;
    int errors;
    int animation_calls;
    int refresh_calls;
    std::vector<int> task_kinds;
    std::string resource;

    Fixture() : load_ok(true), create_ok(true), random_value(10), errors(0),
                animation_calls(0), refresh_calls(0) {
        std::memset(&state, 0, sizeof(state));
        std::memset(&object, 0, sizeof(object));
        tables = {{2.0f, 3.0f}, {4.0f, 5.0f}, {6.0f, 7.0f},
                  {1.0f, 1.5f}, {8.0f, 9.0f}, {16.0f, 17.0f}};
        hooks = {this, 1.0f, 0, Load, Create, Register, InitializeAnimation,
                 Random, Error, Refresh};
    }

    static Fixture* Self(void* context) {
        return static_cast<Fixture*>(context);
    }
    static void* Load(void* context, int slot, const char* name) {
        Fixture* f = Self(context);
        assert(slot == 8);
        f->resource = name;
        return f->load_ok ? reinterpret_cast<void*>(0x1234) : 0;
    }
    static PlayerRuntimeObject* Create(void* context) {
        Fixture* f = Self(context);
        return f->create_ok ? &f->object : 0;
    }
    static void* Register(void* context, int kind, PlayerRuntimeState*) {
        Fixture* f = Self(context);
        f->task_kinds.push_back(kind);
        return reinterpret_cast<void*>(static_cast<uintptr_t>(kind + 1));
    }
    static void InitializeAnimation(void* context, PlayerRuntimeState* state,
                                    void* archive) {
        Fixture* f = Self(context);
        assert(archive == reinterpret_cast<void*>(0x1234));
        state->position[2] = 12.0f;
        ++f->animation_calls;
    }
    static int Random(void* context) {
        return Self(context)->random_value++;
    }
    static void Error(void* context, const char*) {
        ++Self(context)->errors;
    }
    static void Refresh(void* context, PlayerRuntimeState*) {
        ++Self(context)->refresh_calls;
    }
};

void TestFreshInitialization() {
    Fixture f;
    assert(PlayerRuntime_Initialize(&f.state, 1, &f.tables, &f.hooks) == 0);
    assert(f.resource == "pl01.anm");
    assert(f.state.player_object == &f.object);
    assert((f.task_kinds == std::vector<int>{0, 1}));
    assert(f.animation_calls == 1 && f.refresh_calls == 1);
    assert(f.state.position[0] == 0.0f && f.state.position[1] == 400.0f);
    assert(f.state.position[2] == 12.0f);
    assert(f.state.random_values[0] == 10);
    assert(f.state.random_values[3] == 13);
    assert(f.state.history[32][1] == 40000);
    assert(f.object.speed == 3.0f);
    assert(f.object.vertical_speed == 5.0f);
    assert(f.object.horizontal_speed == 7.0f);
    assert(f.state.hitbox_bounds[0] == -1.5f);
    assert(f.state.hitbox_bounds[3] == 1.5f);
    assert(f.state.item_bounds[1] == 391.0f);
    assert(f.state.spawn_timer.target == 119);
    assert(f.state.spawn_timer.current == 120);
    assert(f.state.spawn_frames == 30);
}

void TestReuseAndFailures() {
    Fixture f;
    PlayerRuntimeObject reused = {};
    f.hooks.reused_player = &reused;
    assert(PlayerRuntime_Initialize(&f.state, 0, &f.tables, &f.hooks) == 0);
    assert(f.resource == "pl00.anm" && f.state.player_object == &reused);

    Fixture missing;
    missing.load_ok = false;
    assert(PlayerRuntime_Initialize(&missing.state, 0, &missing.tables,
                                    &missing.hooks) == -1);
    assert(missing.errors == 1 && missing.task_kinds.empty());

    Fixture no_object;
    no_object.create_ok = false;
    assert(PlayerRuntime_Initialize(&no_object.state, 0, &no_object.tables,
                                    &no_object.hooks) == -1);
    assert(no_object.errors == 1 && no_object.task_kinds.empty());
    assert(no_object.refresh_calls == 0);
}

}  // namespace

int main() {
    TestFreshInitialization();
    TestReuseAndFailures();
    return 0;
}
