// Equivalent-only stand-in for the stage-text line reader (0x00434A20) whose
// parameter order steers the order in which the music-room model loads the
// arguments, without touching the shared stage-text sources or their cluster.
#pragma code_seg(".text$01uifinalextract")
extern "C" __declspec(noinline) char* __stdcall UiFinalExtractLine(int* remaining, char* destination, char* cursor) {
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

// Equivalent-only stand-in for the two-list lookup (0x004491C0) whose parameter
// order steers the order in which the music-room model loads the arguments.
#include "th10/game/recovery_script_executor.hpp"
#include "th10/game/title_menu.hpp"
extern "C" __declspec(noinline) void* __fastcall UiFinalFind(
        void* lookup, RecoveryLookupContext* context, RecoveryScriptId id) {
    RecoveryLookupNode* node;
    unsigned int value = static_cast<unsigned int>(id.value);
    if (!value)
        return 0;
    for (node = context->primary; node != 0; node = node->next)
        if (reinterpret_cast<RecoveryMusicVm*>(node->object)->id == value)
            return reinterpret_cast<RecoveryMusicVm*>(node->object);
    for (node = context->secondary; node != 0; node = node->next)
        if (reinterpret_cast<RecoveryMusicVm*>(node->object)->id == value)
            return reinterpret_cast<RecoveryMusicVm*>(node->object);
    return 0;
}

// Equivalent-only stand-in for the transition setup (0x00434A80) whose parameter
// order steers the order in which the music-room model loads the arguments.
extern "C" float g_game_speed;
extern "C" RecoveryMusicVector recovery_music_defaults;
static void UiFinalResetTimer(RecoveryTimer2* timer) {
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
extern "C" __declspec(noinline) void __stdcall UiFinalTransition(RecoveryMusicVm* self,
        const RecoveryMusicVector* target,
        const RecoveryMusicVector* base,
        int mode,
        unsigned char flag) {
    self->transition_mode = mode;
    const RecoveryMusicVector& defaults = recovery_music_defaults;
    self->defaults_088 = defaults;
    self->defaults_094 = defaults;
    self->transition_flag = flag;
    self->base_transition = *base;
    self->target_transition = *target;
    UiFinalResetTimer(&self->transition_timer);
}
