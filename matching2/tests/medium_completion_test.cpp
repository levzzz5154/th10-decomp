#include "th10/game/bullet_runtime_update.hpp"
#include "th10/game/menu_flow_updates.hpp"
#include "th10/game/replay_spell_list.hpp"

#include <cassert>
#include <cstring>
#include <string>
#include <vector>

namespace {

struct BulletLog {
    int destroyed;
    int prepared;
    int canceled;
    int sounds;
    int animation_result;
    int collision;
    bool outside;
    std::vector<uint32_t> behaviors;
};
void Destroy(void* c, BulletRuntimeState*) {
    ++static_cast<BulletLog*>(c)->destroyed;
}
void Prepare(void* c, BulletRuntimeState*) {
    ++static_cast<BulletLog*>(c)->prepared;
}
void Behavior(void* c, BulletRuntimeState*, uint32_t bit) {
    static_cast<BulletLog*>(c)->behaviors.push_back(bit);
}
void Delayed(void* c, BulletRuntimeState*) {
    static_cast<BulletLog*>(c)->behaviors.push_back(0x8000);
}
int Collide(void* c, BulletRuntimeState*) {
    return static_cast<BulletLog*>(c)->collision;
}
void Cancel(void* c, BulletRuntimeState*) {
    ++static_cast<BulletLog*>(c)->canceled;
}
void Sound(void* c) { ++static_cast<BulletLog*>(c)->sounds; }
bool Outside(void* c, BulletRuntimeState*) {
    return static_cast<BulletLog*>(c)->outside;
}
int Tick(void* c, BulletRuntimeState*) {
    return static_cast<BulletLog*>(c)->animation_result;
}

void TestBulletRuntime() {
    BulletLog log = {};
    BulletRuntimeHooks hooks = {
        &log, 2.0f, 0.5f, Destroy, Prepare, Behavior, Delayed,
        Collide, Cancel, Sound, Behavior, Outside, Tick,
    };
    BulletRuntimeState bullet = {};
    bullet.mode = 1;
    bullet.velocity[0] = 3.0f;
    bullet.behavior_flags = 0x11;
    bullet.flags = 2;
    bullet.lifetime = 2;
    bullet.collision_delay = 2;
    assert(BulletRuntime_Update(&bullet, &hooks) == 0);
    assert(bullet.position[0] == 6.0f);
    assert(log.prepared == 1 && log.behaviors.size() == 2);
    assert(bullet.lifetime == 1 && bullet.collision_delay == 1);

    bullet.flags = 8;
    assert(BulletRuntime_Update(&bullet, &hooks) == -1);
    assert(log.destroyed == 1);

    bullet = {};
    bullet.mode = 2;
    bullet.animation_state = 1;
    bullet.velocity[1] = 4.0f;
    assert(BulletRuntime_Update(&bullet, &hooks) == 0);
    assert(bullet.mode == 1 && bullet.position[1] == 12.0f);
}

struct MenuLog {
    std::vector<int> phases;
    std::vector<int> views;
    std::vector<int> launches;
    int changes;
};
void SetPhase(void* c, int v) {
    static_cast<MenuLog*>(c)->phases.push_back(v);
}
void Reset(void*) {}
void Move(void*, MenuFlowState* s, int d) {
    s->selection += d;
}
void Change(void* c) { ++static_cast<MenuLog*>(c)->changes; }
void View(void* c, int v) { static_cast<MenuLog*>(c)->views.push_back(v); }
void Commit(void*, const uint16_t[5]) {}
void Launch(void* c, int kind, int selection) {
    static_cast<MenuLog*>(c)->launches.push_back(kind * 100 + selection);
}

MenuFlowHooks MakeMenuHooks(MenuLog* log) {
    return {log, SetPhase, Reset, Move, Change, View, View, View, Commit,
            Launch};
}

void TestMenuFlows() {
    MenuLog log = {};
    MenuFlowHooks hooks = MakeMenuHooks(&log);
    int8_t available[31] = {};
    available[3] = -1;
    ConfigMenuEnv config = {{0, 0}, {}, available};
    MenuFlowState state = {};
    ConfigMenuFlow_Update(&state, &config, &hooks);
    assert(state.phase == 0);
    assert(!log.phases.empty() && log.phases[0] == 1);
    state.phase = 2;
    state.selection = 6;
    config.input.pressed = 1;
    ConfigMenuFlow_Update(&state, &config, &hooks);
    assert(log.phases.back() == 4);

    state = {};
    state.phase = 2;
    state.selection = 2;
    StageMenuEnv stage = {{0, 1}, 1, 0, 4};
    StageMenuFlow_Update(&state, &stage, &hooks);
    assert(log.phases.back() == 3);
    state.phase = 3;
    state.phase_timer = 14;
    StageMenuFlow_Update(&state, &stage, &hooks);
    assert(stage.stage == 2);

    state = {};
    ShotMenuEnv shot = {{0, 0}, 4, 0, {0, 0, 0, 1, 0, 0}};
    ShotMenuFlow_Update(&state, &shot, &hooks);
    assert(state.selection == 1 && state.queued_count == 1);
    state.phase = 2;
    shot.input.pressed = 0x0a;
    ShotMenuFlow_Update(&state, &shot, &hooks);
    assert(log.phases.back() == 4);
}

struct SpellLog {
    std::vector<std::string> lines;
    std::vector<uint32_t> colors;
};
bool Valid(void*, uint32_t handle) { return handle == 7; }
void DrawSpell(void* c, uint32_t color, const char* text) {
    SpellLog* log = static_cast<SpellLog*>(c);
    log->colors.push_back(color);
    log->lines.push_back(text);
}

void TestReplaySpellList() {
    ReplaySpellEntry entries[110] = {};
    int8_t categories[110] = {};
    for (int i = 0; i < 12; ++i) {
        categories[i] = 2;
        entries[i] = {"Spell", 1, i == 10 ? 1 : 0, i + 2};
    }
    ReplaySpellListState state = {2, 2, 0, 0, {7, 9}};
    SpellLog log;
    ReplaySpellListHooks hooks = {&log, Valid, DrawSpell};
    assert(ReplaySpellList_Draw(&state, entries, categories, &hooks) == 0);
    assert(state.visible_count == 2);
    assert(log.lines.size() == 10);
    assert(log.lines[0].find("No. 11") != std::string::npos);
    assert(state.handles[0] == 7 && state.handles[1] == 0);
    assert(log.colors[0] == 0x00ffffffu);
}

}  // namespace

int main() {
    TestBulletRuntime();
    TestMenuFlows();
    TestReplaySpellList();
    return 0;
}
