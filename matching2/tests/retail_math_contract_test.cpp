#include "th10/math/rng.hpp"
#include "th10/math/timer.hpp"
#include "th10/math/easing.hpp"
#include "th10/game/trajectory_evaluate.hpp"

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <initializer_list>

float _DAT_00470afc = 1.0f;
float _DAT_00470b68 = 0.99f;
float _DAT_00470b64 = 1.01f;
float DAT_00476f78 = 1.0f;
float _DAT_00470b98 = 4294967296.0f;
float _DAT_00470bec = 0x1p-31f;
float _DAT_00470bf0 = 0x1p-32f;

static std::uint16_t RetailWord(std::uint16_t seed) {
    // XOR/SUB in a 16-bit register followed by ROL AX,2.
    const std::uint16_t word = static_cast<std::uint16_t>((seed ^ 0x9630) - 0x6553);
    return static_cast<std::uint16_t>((word << 2) | (word >> 14));
}

static void TestRng() {
    static_assert(sizeof(RngState) == 8 && offsetof(RngState, generation) == 4,
                  "retail RNG layout");
    for (unsigned int seed = 0; seed < 65536; ++seed) {
        const std::uint16_t a = RetailWord(static_cast<std::uint16_t>(seed));
        const std::uint16_t b = RetailWord(a), c = RetailWord(b), d = RetailWord(c);
        RngState two = {static_cast<std::uint16_t>(seed), 0x1234, 0xFFFFFFFEu};
        RngState four = {static_cast<std::uint16_t>(seed), 0x1234, 0xFFFFFFFCu};
        assert(Rng_NextU32(&two) == ((unsigned(a) << 16) | b));
        assert(Rng_NextU32DoubleStep(&four) == (a | (unsigned(b) << 16)));
        assert(two.seed == b && four.seed == d);
        assert(two.generation == 0 && four.generation == 0);
        assert(two.reserved_02 == 0x1234 && four.reserved_02 == 0x1234);
    }
    const unsigned counters[] = {0x7FFFFFFCu, 0x7FFFFFFEu, 0xFFFFFFFFu};
    for (unsigned counter : counters) {
        RngState state = {0, 0, counter};
        Rng_NextU32DoubleStep(&state);
        assert(state.generation == counter + 4u);
        state = {0, 0, counter};
        assert(Rng_NextFloat(&state) == 0x1.86e98p-1f);
        assert(state.generation == counter + 2u);
        state = {0, 0, counter};
        assert(Rng_NextFloatSigned(&state) == 0x1.0dd30p-1f);
        assert(state.generation == counter + 2u);
    }
}

static void TestTimers() {
    float speed = 1.0f;
    for (int count : {0, 1, 2, -3}) {
        FrameTimer timer = {0, 10, 10.0f, &speed, 1};
        FrameTimer_Decrement(&timer, count);
        assert(timer.previous == 10 && timer.current == 10 - count);
        assert(timer.elapsed == 10.0f - count);
    }
    alignas(16) unsigned char owner[0x2C8] = {};
    owner[0x2C4] = 0xA5;
    GameState_SetTimerTarget(owner, 7);
    assert(*reinterpret_cast<int*>(owner + 0x20) == 7);
    assert(*reinterpret_cast<int*>(owner + 0x2B0) == -1);
    assert(*reinterpret_cast<int*>(owner + 0x2B4) == 0);
    assert(*reinterpret_cast<int*>(owner + 0x2B8) == 0);
    assert(*reinterpret_cast<unsigned*>(owner + 0x2C0) == 1);
    std::uint32_t speed_bits;
    std::memcpy(&speed_bits, owner + 0x2BC, 4);
    assert(speed_bits == static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&DAT_00476f78)));
    assert(owner[0x2C4] == 0xA5);
    *reinterpret_cast<unsigned*>(owner + 0x2BC) = 0x12345678;
    *reinterpret_cast<unsigned*>(owner + 0x2C0) = 0x81;
    *reinterpret_cast<int*>(owner + 0x2B0) = 30;
    GameState_SetTimerTarget(owner, 8);
    assert(*reinterpret_cast<int*>(owner + 0x20) == 8);
    assert(*reinterpret_cast<int*>(owner + 0x2B0) == -1);
    assert(*reinterpret_cast<unsigned*>(owner + 0x2BC) == 0x12345678);
    assert(*reinterpret_cast<unsigned*>(owner + 0x2C0) == 0x81);
}

static void TestEasing() {
    // Stack-independent dyadic counterexamples from 0x44C350's quartic
    // (mode 11) and quadratic (mode 12) branches, including both halves.
    const int modes[] = {11, 11, 12, 12};
    const float times[] = {2.5f, 7.5f, 2.5f, 7.5f};
    const float expected[] = {0.03125f, 0.96875f, 0.375f, 0.625f};
    for (int i = 0; i < 4; ++i) {
        assert(Easing_Evaluate(modes[i], times[i], 10.0f) == expected[i]);
        assert(Trajectory_EaseFraction(times[i], 10.0f, modes[i]) == expected[i]);
    }
    float speed = 1;
    Trajectory2D state = {};
    state.speed = &speed;
    state.duration = 10;
    state.mode = 12;
    state.elapsed = 1.5f;
    state.velocity[0] = 16;
    TrajectoryEnv env = {&speed, Trajectory_EaseFraction};
    float output[2];
    Trajectory_Evaluate2D(&state, output, &env);
    assert(output[0] == 6.0f);
}

static void TestX87StoreBoundaries() {
#if defined(__i386__) || defined(__x86_64__)
    unsigned short saved;
    __asm__ volatile("fnstcw %0" : "=m"(saved));
    const unsigned short precisions[] = {0x000, 0x200, 0x300};
    for (unsigned short precision : precisions) {
        const unsigned short control = (saved & ~0xF00u) | precision;
        __asm__ volatile("fldcw %0" : : "m"(control) : "memory");
        float speed = 0.1f;
        float elapsed = 0.9f;
        float stored;
        int current;
        // Original Tick's FLD/FADD/FST order. For these small finite
        // values FISTTP is the same truncation as __ftol2's EAX result.
        __asm__ volatile("flds %[speed]; fadds %[elapsed]; fsts %[stored]; fisttpl %[current]"
            : [stored] "=m"(stored), [current] "=m"(current)
            : [speed] "m"(speed), [elapsed] "m"(elapsed) : "st", "memory");
        FrameTimer timer = {0, 0, elapsed, &speed, 1};
        FrameTimer_Tick(&timer);
        assert(timer.elapsed == stored && timer.current == current);

        Trajectory2D state = {};
        state.speed = &speed;
        state.elapsed = elapsed;
        state.duration = 10;
        TrajectoryEnv env = {&speed, Trajectory_EaseFraction};
        float output[2];
        Trajectory_Evaluate2D(&state, output, &env);
        assert(state.elapsed == stored && state.current == current);

        elapsed = -0.01f;
        float delta = 0.1f;
        // Original Advance stores and reloads before conversion, but
        // retains the multiply result until the add and binary32 store.
        __asm__ volatile("flds %[delta]; fmuls %[speed]; fadds %[elapsed]; fstps %[stored]; flds %[stored]; fisttpl %[current]"
            : [stored] "=m"(stored), [current] "=m"(current)
            : [delta] "m"(delta), [speed] "m"(speed), [elapsed] "m"(elapsed) : "st", "memory");
        timer = {0, 0, elapsed, &speed, 1};
        FrameTimer_Advance(&timer, delta);
        assert(timer.elapsed == stored && timer.current == current);
    }
    __asm__ volatile("fldcw %0" : : "m"(saved) : "memory");
#endif
}

int main() {
    TestRng();
    TestTimers();
    TestEasing();
    TestX87StoreBoundaries();
}
