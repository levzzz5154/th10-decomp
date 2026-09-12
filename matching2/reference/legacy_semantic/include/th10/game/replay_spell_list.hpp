#pragma once

#include <cstdint>

struct ReplaySpellEntry {
    const char* name;
    int available;
    int captured;
    int attempts;
};

struct ReplaySpellListState {
    int category;
    int page;
    int difficulty;
    int visible_count;
    uint32_t handles[10];
};

struct ReplaySpellListHooks {
    void* context;
    bool (*handle_valid)(void* context, uint32_t handle);
    void (*draw_text)(void* context, uint32_t color, const char* text);
};

// 0x00432690 - Draw one ten-row spell/replay list page.
int ReplaySpellList_Draw(ReplaySpellListState* state,
                         const ReplaySpellEntry entries[110],
                         const int8_t category_map[110],
                         const ReplaySpellListHooks* hooks);
