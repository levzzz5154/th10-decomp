#include "th10/game/title_main_menu.hpp"

#include <cassert>

int main() {
    TitleMainMenuState state = {};
    TitleMainMenu_Initialize(&state);
    assert(TitleMainMenu_Update(&state, 0, nullptr) == TITLE_MENU_ACTION_NONE);
    for (int frame = 0; frame < 11; ++frame)
        TitleMainMenu_Update(&state, 0, nullptr);
    assert(state.phase == 2);

    TitleMainMenuEnv locked_env = {};
    locked_env.extra_unlocked = [](void*) { return 0; };
    TitleMainMenu_Initialize(&state);
    TitleMainMenu_Update(&state, 0, &locked_env);
    for (int frame = 0; frame < 11; ++frame)
        TitleMainMenu_Update(&state, 0, &locked_env);
    assert(state.unavailable_count == 1);
    assert(state.unavailable[0] == 1);
    TitleMainMenu_Update(&state, TITLE_MENU_DOWN, &locked_env);
    assert(state.selection == 2);

    TitleMainMenu_Initialize(&state);
    TitleMainMenu_Update(&state, 0, nullptr);
    for (int frame = 0; frame < 11; ++frame)
        TitleMainMenu_Update(&state, 0, nullptr);
    assert(state.phase == 2);
    TitleMainMenu_Update(&state, TITLE_MENU_UP, nullptr);
    assert(state.selection == 7);
    TitleMainMenu_Update(&state, TITLE_MENU_DOWN, nullptr);
    assert(state.selection == 0);
    TitleMainMenu_Update(&state, TITLE_MENU_DOWN, nullptr);
    assert(state.selection == 1);
    TitleMainMenu_Update(&state, TITLE_MENU_CONFIRM, nullptr);
    for (int frame = 0; frame < 19; ++frame)
        assert(TitleMainMenu_Update(&state, 0, nullptr) == TITLE_MENU_ACTION_NONE);
    assert(TitleMainMenu_Update(&state, 0, nullptr) == TITLE_MENU_ACTION_EXTRA);

    TitleMainMenu_Initialize(&state);
    TitleMainMenu_Update(&state, 0, nullptr);
    for (int frame = 0; frame < 11; ++frame)
        TitleMainMenu_Update(&state, 0, nullptr);
    assert(state.phase == 2);

    // Cancel carries the cursor down to Quit but does not commit on its own:
    // retail 0x0042D420 only commits when the cancel (or confirm) lands while
    // the cursor is already on Quit.
    TitleMainMenu_Update(&state, TITLE_MENU_CANCEL, nullptr);
    assert(state.selection == 7);
    assert(state.phase == 2);
    for (int frame = 0; frame < 19; ++frame)
        assert(TitleMainMenu_Update(&state, 0, nullptr) == TITLE_MENU_ACTION_NONE);
    assert(state.phase == 2);

    // Confirm on Quit commits; the action lands only after the 20-frame exit
    // animation.
    TitleMainMenu_Update(&state, TITLE_MENU_CONFIRM, nullptr);
    assert(state.phase == 4);
    for (int frame = 0; frame < 19; ++frame)
        assert(TitleMainMenu_Update(&state, 0, nullptr) == TITLE_MENU_ACTION_NONE);
    assert(TitleMainMenu_Update(&state, 0, nullptr) == TITLE_MENU_ACTION_QUIT);

    TitleMainMenu_Initialize(&state);
    TitleMainMenu_Update(&state, 0, nullptr);
    for (int frame = 0; frame < 11; ++frame)
        TitleMainMenu_Update(&state, 0, nullptr);
    TitleMainMenu_Update(&state, TITLE_MENU_CANCEL, nullptr);
    assert(state.selection == 7);
    // Cancel while already on Quit commits just like confirm.
    TitleMainMenu_Update(&state, TITLE_MENU_CANCEL, nullptr);
    assert(state.phase == 4);
    for (int frame = 0; frame < 19; ++frame)
        assert(TitleMainMenu_Update(&state, 0, nullptr) == TITLE_MENU_ACTION_NONE);
    assert(TitleMainMenu_Update(&state, 0, nullptr) == TITLE_MENU_ACTION_QUIT);
    return 0;
}
