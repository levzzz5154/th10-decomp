#include "th10/game/replay_spell_list.hpp"

#include <cstdio>
#include <cstring>

namespace {

void ClearInvalidHandle(uint32_t* handle,
                        const ReplaySpellListHooks* hooks) {
    if (*handle != 0 && !hooks->handle_valid(hooks->context, *handle))
        *handle = 0;
}

}  // namespace

// 0x00432690 - Populate/draw ten spell-list rows for the selected category
// and page. Retail scans the 110-byte category map instead of indexing a
// prebuilt list, and pads revealed names to 42 bytes before formatting.
int ReplaySpellList_Draw(ReplaySpellListState* state,
                         const ReplaySpellEntry entries[110],
                         const int8_t category_map[110],
                         const ReplaySpellListHooks* hooks) {
    int matched = 0;
    int cursor = 0;
    const int skip = state->page * 10 - 10;
    while (cursor < 110 && matched < skip) {
        if (category_map[cursor] == state->category) ++matched;
        ++cursor;
    }

    state->visible_count = 0;
    int row = 0;
    while (row < 10 && cursor < 110) {
        while (cursor < 110 && category_map[cursor] != state->category)
            ++cursor;
        if (cursor >= 110) break;

        const ReplaySpellEntry& entry = entries[cursor];
        ClearInvalidHandle(&state->handles[row], hooks);
        if (entry.available == 0) {
            hooks->draw_text(hooks->context, 0x00808080u, " ");
        } else {
            char padded[43];
            std::snprintf(padded, sizeof(padded), "%-42.42s",
                          entry.name != 0 ? entry.name : "");
            char line[96];
            std::snprintf(line, sizeof(line), "No.%3d %s %4d/%4d",
                          cursor + 1, padded, entry.captured, entry.attempts);
            const uint32_t color =
                entry.captured != 0 ? 0x00ffffffu : 0x00efefefu;
            hooks->draw_text(hooks->context, color, line);
        }
        ++state->visible_count;
        ++row;
        ++cursor;
    }

    while (row < 10) {
        ClearInvalidHandle(&state->handles[row], hooks);
        hooks->draw_text(hooks->context, 0xffffffffu, " ");
        ++row;
    }
    return 0;
}
