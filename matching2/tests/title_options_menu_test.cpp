#include "th10/game/title_options_menu.hpp"

#include <cassert>

int main() {
    TitleOptionsState state;
    TitleOptionsConfig config = {0, 100, 80};
    TitleOptions_Initialize(&state);
    assert(TitleOptions_Update(&state, &config, 0) ==
           TITLE_OPTIONS_ACTION_NONE);
    for (int frame = 0; frame < 7; ++frame)
        TitleOptions_Update(&state, &config, 0);
    assert(state.phase == 2);

    TitleOptions_Update(&state, &config, TITLE_OPTIONS_RIGHT);
    assert(config.bgm_mode == 1);
    TitleOptions_Update(&state, &config, TITLE_OPTIONS_LEFT);
    assert(config.bgm_mode == 0);
    TitleOptions_Update(&state, &config, TITLE_OPTIONS_DOWN);
    TitleOptions_Update(&state, &config, TITLE_OPTIONS_LEFT);
    assert(config.music_volume == 95);
    TitleOptions_Update(&state, &config, TITLE_OPTIONS_DOWN);
    for (int step = 0; step < 20; ++step)
        TitleOptions_Update(&state, &config, TITLE_OPTIONS_LEFT);
    assert(config.sound_volume == 0);

    TitleOptions_Update(&state, &config, TITLE_OPTIONS_DOWN);
    TitleOptions_Update(&state, &config, TITLE_OPTIONS_DOWN);
    assert(TitleOptions_Update(&state, &config, TITLE_OPTIONS_CONFIRM) ==
           TITLE_OPTIONS_ACTION_DEFAULTS);
    assert(config.music_volume == 100 && config.sound_volume == 80);

    // Retail 0x0042D920: a cancel away from the last entry only carries the
    // cursor there; the second cancel is what commits the return.
    TitleOptions_Update(&state, &config, TITLE_OPTIONS_CANCEL);
    assert(state.selection == 5 && state.phase == 2);
    TitleOptions_Update(&state, &config, TITLE_OPTIONS_CANCEL);
    assert(state.phase == 4);
    TitleOptionsAction action = TITLE_OPTIONS_ACTION_NONE;
    for (int frame = 0; frame < 10; ++frame)
        action = TitleOptions_Update(&state, &config, 0);
    assert(action == TITLE_OPTIONS_ACTION_RETURN);
    return 0;
}
