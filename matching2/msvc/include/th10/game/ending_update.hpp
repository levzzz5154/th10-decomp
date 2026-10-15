#pragma once
#include <stddef.h>

struct EndingTextTickView;
__declspec(noinline) int __stdcall EndingText_Tick(
    EndingTextTickView* state);

struct EndingUpdateView {
    unsigned char reserved_000[0x18];
    EndingTextTickView* tick_state_018;
    unsigned char reserved_01c[4];
    unsigned char flags_020;
    unsigned char reserved_021[3];
    int decision_counter_024;

    __declspec(noinline) int Update();
    __declspec(noinline) int OnUpdate();
};

typedef char EndingUpdateSizeCheck[
    sizeof(EndingUpdateView) == 0x28 ? 1 : -1];
typedef char EndingUpdateTextOffsetCheck[
    offsetof(EndingUpdateView, tick_state_018) == 0x18 ? 1 : -1];
typedef char EndingUpdateFlagsOffsetCheck[
    offsetof(EndingUpdateView, flags_020) == 0x20 ? 1 : -1];
typedef char EndingUpdateFrameOffsetCheck[
    offsetof(EndingUpdateView, decision_counter_024) == 0x24 ? 1 : -1];

// Read-only view of the tick object's separately recovered flag word.
struct EndingTextFlagsView {
    unsigned char reserved_000[0x74];
    unsigned int flags_074;
};
typedef char EndingTextFlagsOffsetCheck[
    offsetof(EndingTextFlagsView, flags_074) == 0x74 ? 1 : -1];
