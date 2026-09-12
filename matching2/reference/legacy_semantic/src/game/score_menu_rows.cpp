#include "th10/game/score_menu_rows.hpp"

#include <cstdio>

namespace {

const int kScoreRowCount = 6;
const unsigned int kWhite = 0xffffffffu;
const unsigned int kSelected = 0xffffff00u;
const unsigned int kUnavailableSelected = 0xffdfdfdfu;
const unsigned int kUnselected = 0xff808080u;
const unsigned int kBlinkHidden = 0xff000000u;

unsigned int RowColor(const ScoreMenu* menu,
                      const ScoreMenuRow& row, int row_index) {
    if (menu->selection != row_index) {
        return kUnselected;
    }
    if (!row.available) {
        return kUnavailableSelected;
    }
    if (menu->state == 3 && menu->timer % 4 > 1) {
        return kBlinkHidden;
    }
    return kSelected;
}

}  // namespace

// 0x00431410 - Draw the six score rows while the menu is in a list state,
// including the selected-row blink and unavailable-score placeholder.
int ScoreMenu_DrawRows(const ScoreMenu* menu,
                       const ScoreMenuEnv* env) {
    if (menu->state > 1 && menu->state < 4) {
        *env->list_printing = 1;

        if (menu->timer > 9 || menu->state == 3) {
            for (int index = 0; index < kScoreRowCount; ++index) {
                const ScoreMenuRow& row = menu->rows[index];
                *env->text_color = RowColor(menu, row, index);

                char buffer[96];
                if (row.available) {
                    std::snprintf(buffer, sizeof(buffer), "%s  %.8d0",
                                  row.name, row.score_units);
                } else {
                    std::snprintf(buffer, sizeof(buffer), "%s  ---------",
                                  row.name);
                }
                env->draw_text(buffer);
            }
        }

        *env->text_color = kWhite;
        *env->list_printing = 0;
    }
    return 1;
}
