// Finite, in-range contracts for the maintained C++98 timer. Expected results
// use explicit vectors or exactly representable dyadic arithmetic. The native
// MSVC byte proof covers custom register conventions and x87 conversion details;
// this host test makes no NaN or overflowing float-to-int claims.
#include <cassert>
#include <cstring>
#include <limits>

#include "th10/math/timer.hpp"

float g_frame_timer_normal_lower = 0.99f;
float g_frame_timer_normal_upper = 1.01f;

static const unsigned int retained_flags = 0xA5C31278;

static FrameTimer timer_at(float* speed, int current, float elapsed) {
    const FrameTimer timer = {-9876, current, elapsed, speed, retained_flags};
    return timer;
}

static void expect(const FrameTimer& timer, const float* speed,
                   int previous, int current, float elapsed) {
    assert(timer.previous == previous);
    assert(timer.current == current);
    assert(timer.elapsed == elapsed);
    assert(timer.speed == speed && timer.flags == retained_flags);
}

// Both thresholds are positive finite binary32 values, so adjacent bit
// patterns are their immediate representable neighbors.
static float adjacent(float value, int direction) {
    unsigned int bits;
    std::memcpy(&bits, &value, sizeof(bits));
    if (direction > 0)
        ++bits;
    else
        --bits;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

static void test_strict_thresholds() {
    struct Probe { float speed; bool normal; int tick_current; int advance_current; };
    const Probe probes[] = {
        {adjacent(g_frame_timer_normal_lower, -1), false, 0, 1},
        {g_frame_timer_normal_lower, false, 0, 1},
        {adjacent(g_frame_timer_normal_lower, 1), true, 41, 2},
        {1.0f, true, 41, 2},
        {adjacent(g_frame_timer_normal_upper, -1), true, 41, 2},
        {g_frame_timer_normal_upper, false, 1, 2},
        {adjacent(g_frame_timer_normal_upper, 1), false, 1, 2}
    };
    for (unsigned int i = 0; i < sizeof(probes) / sizeof(probes[0]); ++i) {
        float speed = probes[i].speed;
        FrameTimer timer = timer_at(&speed, 40, 0.0f);
        timer.Tick();
        expect(timer, &speed, 40, probes[i].tick_current,
               probes[i].normal ? 1.0f : speed);

        timer = timer_at(&speed, 40, 0.0f);
        timer.Advance(2.0f);
        expect(timer, &speed, 40, probes[i].advance_current,
               probes[i].normal ? 2.0f : speed * 2.0f);

        timer = timer_at(&speed, 40, 0.0f);
        timer.Decrement(2);
        expect(timer, &speed, 40, -probes[i].advance_current,
               probes[i].normal ? -2.0f : speed * -2.0f);
        assert(speed == probes[i].speed);
    }

    // The decision reads the supplied bounds rather than hardcoded literals.
    g_frame_timer_normal_lower = 0.5f;
    g_frame_timer_normal_upper = 2.0f;
    float speed = 1.5f;
    FrameTimer timer = timer_at(&speed, 4, 1.25f);
    timer.Tick();
    expect(timer, &speed, 4, 5, 2.25f);
    timer = timer_at(&speed, 4, 1.25f);
    timer.Advance(0.75f);
    expect(timer, &speed, 4, 2, 2.0f);
    g_frame_timer_normal_lower = 0.99f;
    g_frame_timer_normal_upper = 1.01f;
}

struct TickCase {
    float speed;
    int old_current;
    float old_elapsed;
    int current;
    float elapsed;
};

static void test_tick_bookkeeping() {
    const TickCase cases[] = {
        {1.0f, 5, 5.0f, 6, 6.0f},
        // Normal Tick increments current independently of fractional elapsed.
        {1.0f, 7, 2.25f, 8, 3.25f},
        {1.0f, -4, -0.25f, -3, 0.75f},
        {0.5f, 6, 6.25f, 6, 6.75f},
        {-0.75f, 123, -1.5f, -2, -2.25f},
        {0.0f, -20, -0.75f, 0, -0.75f},
        {0.25f, 19, -0.5f, 0, -0.25f},
        {-0.25f, 19, 0.5f, 0, 0.25f},
        {2.0f, 19, -0.5f, 1, 1.5f},
        {-2.0f, 19, 1.25f, 0, -0.75f},
        {2.0f, -7, 123.875f, 125, 125.875f}
    };
    for (unsigned int i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        float speed = cases[i].speed;
        FrameTimer timer = timer_at(&speed, cases[i].old_current, cases[i].old_elapsed);
        timer.Tick();
        expect(timer, &speed, cases[i].old_current, cases[i].current, cases[i].elapsed);
        assert(speed == cases[i].speed);
    }
}

struct AdvanceCase {
    float speed;
    int old_current;
    float old_elapsed;
    float delta;
    int current;
    float elapsed;
};

static void test_advance_bookkeeping() {
    const AdvanceCase cases[] = {
        {1.0f, 5, 5.0f, -2.0f, 3, 3.0f},
        {2.0f, 5, 5.0f, 1.5f, 8, 8.0f},
        {0.5f, 6, 6.25f, -1.5f, 5, 5.5f},
        {-0.75f, 123, -1.5f, 1.0f, -2, -2.25f},
        {0.0f, -20, 3.25f, 100.0f, 3, 3.25f},
        {2.0f, 19, -0.5f, 0.125f, 0, -0.25f},
        {-2.0f, 19, 0.5f, 0.125f, 0, 0.25f},
        // Unlike normal Tick, Advance recomputes current even for zero delta.
        {1.0f, 7, 2.25f, 0.0f, 2, 2.25f},
        {1.0f, -4, -0.25f, 0.0f, 0, -0.25f},
        {0.25f, 17, -1.75f, 0.5f, -1, -1.625f}
    };
    for (unsigned int i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        float speed = cases[i].speed;
        FrameTimer timer = timer_at(&speed, cases[i].old_current, cases[i].old_elapsed);
        timer.Advance(cases[i].delta);
        expect(timer, &speed, cases[i].old_current, cases[i].current, cases[i].elapsed);
        assert(speed == cases[i].speed);
    }
}

static void test_decrement_and_changing_speed() {
    struct DecrementCase { float speed; float elapsed; int count; int current; float result; };
    const DecrementCase cases[] = {
        {1.0f, 10.0f, 0, 10, 10.0f},
        {1.0f, 10.0f, 2, 8, 8.0f},
        {1.0f, 10.0f, -3, 13, 13.0f},
        {0.5f, 10.0f, 3, 8, 8.5f},
        {2.0f, 10.0f, 3, 4, 4.0f},
        {-0.5f, 10.0f, 3, 11, 11.5f},
        {0.0f, 10.0f, -30, 10, 10.0f},
        {0.5f, -0.75f, 1, -1, -1.25f},
        {2.0f, -1.25f, -1, 0, 0.75f},
        {1.0f, -0.25f, 0, 0, -0.25f}
    };
    for (unsigned int i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        float speed = cases[i].speed;
        FrameTimer timer = timer_at(&speed, 77, cases[i].elapsed);
        timer.Decrement(cases[i].count);
        expect(timer, &speed, 77, cases[i].current, cases[i].result);
        assert(speed == cases[i].speed);
    }

    float speed = 1.0f;
    FrameTimer timer = timer_at(&speed, 5, 5.0f);
    timer.Tick();
    expect(timer, &speed, 5, 6, 6.0f);
    speed = 0.5f;
    timer.Tick();
    expect(timer, &speed, 6, 6, 6.5f);
    timer.Advance(1.0f);
    expect(timer, &speed, 6, 7, 7.0f);
    speed = -0.75f;
    timer.Advance(2.0f);
    expect(timer, &speed, 7, 5, 5.5f);
    timer.Decrement(2);
    expect(timer, &speed, 5, 7, 7.0f);
    speed = 1.0f;
    timer.Decrement(3);
    expect(timer, &speed, 7, 4, 4.0f);
}

int main() {
    assert(sizeof(float) == 4 && std::numeric_limits<float>::is_iec559);
    test_strict_thresholds();
    test_tick_bookkeeping();
    test_advance_bookkeeping();
    test_decrement_and_changing_speed();
}
