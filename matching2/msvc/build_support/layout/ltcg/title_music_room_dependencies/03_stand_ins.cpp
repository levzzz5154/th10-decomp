// Cluster-only stand-in for the stage-text line reader (0x00434A20) whose
// parameter order steers the order in which the music room loads the
// arguments, without touching the shared stage-text sources or their cluster.
#pragma code_seg(".text$00434a20_fn")
extern "C" __declspec(noinline) char* __stdcall UiFinalExtractLine(char* destination, char* cursor, int* remaining) {
    char* end = cursor;
    while (*end != '\n') {
        if (*end == '\r')
            break;
        if (*remaining == 0)
            return end;
        ++end;
        --*remaining;
    }
    if (*remaining == 0)
        return end;
    *end = 0;
    char* source = cursor;
    char* output = destination;
    while ((*output++ = *source++) != 0) {}
    ++end;
    --*remaining;
    while (*end == '\n' || *end == '\r') {
        if (*remaining == 0)
            break;
        ++end;
        --*remaining;
    }
    return end;
}
#pragma code_seg()

// Cluster-only stand-in for the two-list lookup (0x004491C0) whose parameter
// order steers the order in which the music room loads the arguments.
#include "th10/game/ending_script_executor.hpp"
#include "th10/game/title_menu.hpp"
#pragma code_seg(".text$004491c0_fn")
extern "C" __declspec(noinline) void* __fastcall UiFinalFind(
        void* lookup, AnmLookupContext* context, AnimationScriptId id) {
    AnmLookupNode* node;
    unsigned int value = static_cast<unsigned int>(id.value);
    if (!value)
        return 0;
    for (node = context->primary; node != 0; node = node->next)
        if (reinterpret_cast<TitleAnmVm*>(node->object)->id == value)
            return reinterpret_cast<TitleAnmVm*>(node->object);
    for (node = context->secondary; node != 0; node = node->next)
        if (reinterpret_cast<TitleAnmVm*>(node->object)->id == value)
            return reinterpret_cast<TitleAnmVm*>(node->object);
    return 0;
}

// Cluster-only stand-in for the transition setup (0x00434A80) whose parameter
// order steers the order in which the music room loads the arguments.
extern "C" float g_game_speed;
extern "C" TitleVec3 recovery_music_defaults;
static void UiFinalResetTimer(GameFrameTimer* timer) {
    if (!(timer->flags & 1u)) {
        timer->current = 0;
        timer->previous = -999999;
        timer->elapsed = 0;
        timer->speed = &g_game_speed;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->elapsed = 0;
    timer->previous = -1;
}
#pragma code_seg(".text$00434a80_fn")
extern "C" __declspec(noinline) void __stdcall UiFinalTransition(TitleAnmVm* self,
        int mode,
        const TitleVec3* target,
        const TitleVec3* base,
        unsigned char flag) {
    self->transition_mode = mode;
    const TitleVec3& defaults = recovery_music_defaults;
    self->defaults_088 = defaults;
    self->defaults_094 = defaults;
    self->transition_flag = flag;
    self->base_transition = *base;
    self->target_transition = *target;
    UiFinalResetTimer(&self->transition_timer);
}
#pragma code_seg()
