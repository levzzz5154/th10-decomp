#pragma once

#include <stddef.h>

// Menu selection, its navigation history, and the entries skipped by Advance.
struct PauseChoiceCursor {
    int selection;                       // +0x00
    int previous_selection;              // +0x04, saved by menu input handlers
    int item_count;                      // +0x08
    int selection_history[16];           // +0x0C
    int item_count_history[16];          // +0x4C
    int history_depth;                   // +0x8C
    int disabled_items[16];              // +0x90
    int wrap;                           // +0xD0
    int disabled_count;                 // +0xD4

    __forceinline void Select(int selected) {
        if (item_count != 0)
            selection = selected >= item_count ? item_count - 1 : selected;
        else
            selection = selected;
    }

    __declspec(noinline) void PushSelection();
    __declspec(noinline) void PopSelection();
    __declspec(noinline) int Advance(int delta);
};

typedef char PauseChoiceCursor_00422c80_history_offset_must_be_12[offsetof(PauseChoiceCursor, selection_history) == 12 ? 1 : -1];
typedef char PauseChoiceCursor_00422c80_depth_offset_must_be_140[offsetof(PauseChoiceCursor, history_depth) == 140 ? 1 : -1];
typedef char PauseChoiceCursor_00422c80_disabled_offset_must_be_144[offsetof(PauseChoiceCursor, disabled_items) == 144 ? 1 : -1];
typedef char PauseChoiceCursor_00422c80_wrap_offset_must_be_208[offsetof(PauseChoiceCursor, wrap) == 208 ? 1 : -1];
typedef char PauseChoiceCursor_00422c80_disabled_count_offset_must_be_212[offsetof(PauseChoiceCursor, disabled_count) == 212 ? 1 : -1];
