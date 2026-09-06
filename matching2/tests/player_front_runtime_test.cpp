#include "th10/game/player_front_runtime.hpp"

#include <cassert>
#include <cmath>

float DAT_00476f78 = 1.0f;

namespace {

struct Hooks {
    int direction_changes{};
    int creates{};
    int releases{};
    int positions{};
    float position_x{};
    float position_y{};

    static Hooks& Self(void* context) {
        return *static_cast<Hooks*>(context);
    }
    static void DirectionChanged(void* context) {
        ++Self(context).direction_changes;
    }
    static void SpriteCreate(void* context) {
        ++Self(context).creates;
    }
    static void SpriteRelease(void* context) {
        ++Self(context).releases;
    }
    static void SpritePosition(void* context, float x, float y) {
        Hooks& hooks = Self(context);
        ++hooks.positions;
        hooks.position_x = x;
        hooks.position_y = y;
    }
};

th10::player_front::PlayerEdges Edges(Hooks& hooks) {
    return {&hooks, nullptr, Hooks::DirectionChanged, Hooks::SpriteCreate,
            Hooks::SpriteRelease, Hooks::SpritePosition};
}

void TestRetailDirectionPriorityAndSpeedSlots() {
    using namespace th10::player_front;
    const PlayerSpeedSlots speeds{11, 7, 23, 5};

    Player opposing;
    UpdatePlayer(opposing, 0x30, true, speeds, {});
    assert(opposing.direction == 2); // retail tests 0x20 before 0x10
    assert(opposing.vx == 11 && opposing.vy == 0);

    Player diagonal;
    UpdatePlayer(diagonal, 0x50, true, speeds, {});
    assert(diagonal.direction == 5);
    assert(diagonal.vx == -23 && diagonal.vy == -23);
    UpdatePlayer(diagonal, 0x54, true, speeds, {});
    assert(diagonal.slow == 1);
    assert(diagonal.vx == -5 && diagonal.vy == -5);

    Player cardinal;
    UpdatePlayer(cardinal, 0x20 | 4, true, speeds, {});
    assert(cardinal.direction == 2 && cardinal.vx == 7);
}

void TestSceneGateAndPreviousVelocity() {
    using namespace th10::player_front;
    Hooks hooks;
    const PlayerEdges edges = Edges(hooks);
    const PlayerSpeedSlots speeds{10, 8, 20, 6};
    Player player;
    player.slow_age = 4;

    UpdatePlayer(player, 0, true, speeds, edges, false);
    assert(player.slow_age == 4); // gate closed: retail leaves age untouched
    assert(hooks.direction_changes == 0);

    UpdatePlayer(player, 0x40, true, speeds, edges, true);
    assert(player.slow_age == 5);
    assert(hooks.direction_changes == 1);
    assert(player.previous_vy == -10);

    UpdatePlayer(player, 0x80, true, speeds, edges, true);
    assert(player.slow_age == 6);
    assert(hooks.direction_changes == 2);
    assert(player.previous_vy == 10);

    UpdatePlayer(player, 4, true, speeds, edges, true);
    assert(player.slow == 1 && player.slow_age == 0);
    assert(hooks.direction_changes == 3); // nonzero vertical -> zero

    UpdatePlayer(player, 0, false, speeds, edges, true);
    assert(player.slow == 0 && player.slow_age == 30);
}

void TestSpriteLifecycleAndPositionHook() {
    using namespace th10::player_front;
    Hooks hooks;
    const PlayerEdges edges = Edges(hooks);
    const PlayerSpeedSlots speeds{10, 8, 20, 6};
    Player player;
    player.x = 100;
    player.y = 4000;

    UpdatePlayer(player, 4, true, speeds, edges);
    assert(player.sprite_handle != 0 && hooks.creates == 1);
    assert(hooks.positions == 1);
    assert(std::fabs(hooks.position_x - 224.0f - 1.0f) < 0.0001f);
    assert(std::fabs(hooks.position_y - 16.0f - 40.0f) < 0.0001f);

    UpdatePlayer(player, 0, true, speeds, edges);
    assert(player.sprite_handle == 0 && hooks.releases == 1);
    assert(hooks.positions == 1); // no valid handle after release
}

void TestCompatibilityAdapter() {
    using namespace th10::player_front;
    Player player;
    UpdatePlayer(player, 0x50, true, 400, 200, {});
    assert(player.vx == -400 && player.vy == -400);
}

} // namespace

int main() {
    TestRetailDirectionPriorityAndSpeedSlots();
    TestSceneGateAndPreviousVelocity();
    TestSpriteLifecycleAndPositionHook();
    TestCompatibilityAdapter();
}
