// =============================================================================
// timer.cpp - Readable frame-timer advancement from 0x00404ED0
// =============================================================================
#include "th10/math/timer.hpp"
#include "th10/math/retail_numeric.hpp"

extern float _DAT_00470afc;      // 1.0f
extern float _DAT_00470b68;      // normal-speed lower bound
extern float _DAT_00470b64;      // normal-speed upper bound
extern float DAT_00476f78;       // default speed (1.0f)


void FrameTimer_Tick(FrameTimer* timer) {
    timer->previous = timer->current;

    const float speed = *timer->speed;
    if (_DAT_00470b68 < speed && speed < _DAT_00470b64) {
        timer->current = Retail_AddI32(timer->current, 1);
        timer->elapsed += _DAT_00470afc;
        return;
    }

    // 0x00404F0C stores without popping ST0: __ftol2 consumes the retained
    // sum, not the binary32 field written by FST.
    const long double elapsed = static_cast<long double>(speed) + timer->elapsed;
    timer->elapsed = static_cast<float>(elapsed);
    timer->current = Retail_TruncateI32(elapsed);
}

// 0x0044BF40 - Advance a timer by an explicit delta while
// retaining the retail previous/current and speed-dependent accumulation.
void FrameTimer_Advance(FrameTimer* timer, float delta) {
    timer->previous = timer->current;
    const float speed = *timer->speed;
    if (_DAT_00470b68 < speed && speed < _DAT_00470b64)
        timer->elapsed += delta;
    else
        timer->elapsed = static_cast<float>(
            static_cast<long double>(delta) * speed + timer->elapsed);
    // Unlike Tick, Advance reloads the binary32 field before __ftol2.
    timer->current = Retail_TruncateI32(timer->elapsed);
}

// 0x00428DD0 - Decrement variant used by the replay/input path. Retail
// negates the caller-supplied count and forwards it to 0x0044BF40.
void FrameTimer_Decrement(FrameTimer* timer, int count) {
    const int negated = Retail_I32Bits(0u - static_cast<std::uint32_t>(count));
    FrameTimer_Advance(timer, static_cast<float>(negated));
}

// 0x0042C620 - Store the owner value and reset the embedded state timer.
void GameState_SetTimerTarget(unsigned char* state, int owner_value) {
    *(int*)(state + 0x20) = owner_value;
    unsigned int* flags = (unsigned int*)(state + 0x2C0);
    if ((*flags & 1u) == 0) {
        *(int*)(state + 0x2B4) = 0;
        *(int*)(state + 0x2B0) = (int)0xFFF0BDC1;
        *(int*)(state + 0x2B8) = 0;
        const std::uint32_t speed = static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&DAT_00476f78));
        std::memcpy(state + 0x2BC, &speed, sizeof(speed));
        *flags |= 1u;
    }
    *(int*)(state + 0x2B4) = 0;
    *(int*)(state + 0x2B8) = 0;
    *(int*)(state + 0x2B0) = -1;
}

// 0x0042C5C0 - Set the timer owner, clear the previous value at +0x20, and
// disable the timer by resetting the target to -1. The default speed pointer
// is wired to the global DAT_00476f78 the first time the sentinel initializes.
void GameState_DisableTimerWithOwner(void* state, int owner) {
    unsigned char* bytes = (unsigned char*)state;
    *(int*)(bytes + 0x1C) = owner;
    *(int*)(bytes + 0x20) = 0;
    unsigned int* flags = (unsigned int*)(bytes + 0x2C0);
    if ((*flags & 1u) == 0) {
        *(int*)(bytes + 0x2B4) = 0;
        *(int*)(bytes + 0x2B0) = (int)0xFFF0BDC1;
        *(int*)(bytes + 0x2B8) = 0;
        const std::uint32_t speed = static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&DAT_00476f78));
        std::memcpy(bytes + 0x2BC, &speed, sizeof(speed));
        *flags |= 1u;
    }
    *(int*)(bytes + 0x2B4) = 0;
    *(int*)(bytes + 0x2B8) = 0;
    *(int*)(bytes + 0x2B0) = -1;
}

// 0x004050D0 - Lazily initialize and then disable the embedded timer at the
// +0x30 state offset, preserving the retail sentinel and flag transitions.
void EmbeddedTimer_Reset(EmbeddedTimerState* timer, const float* speed) {
    if ((timer->flags & 1u) == 0) {
        timer->current = 0;
        timer->target = (int)0xFFF0BDC1;
        timer->previous = 0;
        timer->speed = speed;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->previous = 0;
    timer->target = -1;
}
