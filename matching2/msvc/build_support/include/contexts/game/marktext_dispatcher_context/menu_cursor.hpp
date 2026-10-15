#pragma once

#include <stddef.h>

// Menu selection, its navigation history, and the entries skipped by Advance.
struct MenuCursor {
    int selection;                       // +0x00
    int previous_selection;              // +0x04, saved by menu input handlers
    int item_count;                      // +0x08
    int selection_history[16];           // +0x0C
    int item_count_history[16];          // +0x4C
    int history_depth;                   // +0x8C
    int disabled_items[16];              // +0x90
    int wrap;                           // +0xD0
    int disabled_count;                 // +0xD4

    __declspec(noinline) void SetWrap(int enabled);
    __declspec(noinline) int Previous();
    __declspec(noinline) int Next();
    __declspec(noinline) void SetItemCount(int count);
    __declspec(noinline) int GetSelection() const;
    __declspec(noinline) void Reset();
    __declspec(noinline) void ClearDisabledItems();
    __declspec(noinline) void DisableItem(int item);
    __declspec(noinline) void PushSelection();
    __declspec(noinline) void PopSelection();
    __declspec(noinline) int Advance(int delta);
};

typedef char MenuCursor_history_offset_must_be_12[offsetof(MenuCursor, selection_history) == 12 ? 1 : -1];
typedef char MenuCursor_depth_offset_must_be_140[offsetof(MenuCursor, history_depth) == 140 ? 1 : -1];
typedef char MenuCursor_disabled_offset_must_be_144[offsetof(MenuCursor, disabled_items) == 144 ? 1 : -1];
typedef char MenuCursor_wrap_offset_must_be_208[offsetof(MenuCursor, wrap) == 208 ? 1 : -1];
typedef char MenuCursor_disabled_count_offset_must_be_212[offsetof(MenuCursor, disabled_count) == 212 ? 1 : -1];
