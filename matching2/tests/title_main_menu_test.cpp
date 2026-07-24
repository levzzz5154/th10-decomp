#include "th10/game/title_main_menu.hpp"

#include <cassert>

int main() {
    TitleMainMenuState state = {};
    TitleMainMenu_Initialize(&state);
    assert(TitleMainMenu_Update(&state, 0) == TITLE_MENU_ACTION_NONE);
    for (int frame = 0; frame < 11; ++frame)
        TitleMainMenu_Update(&state, 0);
    assert(state.phase == 2);

    TitleMainMenu_Update(&state, TITLE_MENU_UP);
    assert(state.selection == 7);
    TitleMainMenu_Update(&state, TITLE_MENU_DOWN);
    assert(state.selection == 0);
    TitleMainMenu_Update(&state, TITLE_MENU_DOWN);
    assert(state.selection == 1);
    TitleMainMenu_Update(&state, TITLE_MENU_CONFIRM);
    for (int frame = 0; frame < 19; ++frame)
        assert(TitleMainMenu_Update(&state, 0) == TITLE_MENU_ACTION_NONE);
    assert(TitleMainMenu_Update(&state, 0) == TITLE_MENU_ACTION_EXTRA);

    TitleMainMenu_Initialize(&state);
    TitleMainMenu_Update(&state, 0);
    for (int frame = 0; frame < 11; ++frame)
        TitleMainMenu_Update(&state, 0);
    TitleMainMenu_Update(&state, TITLE_MENU_CANCEL);
    for (int frame = 0; frame < 19; ++frame)
        TitleMainMenu_Update(&state, 0);
    assert(TitleMainMenu_Update(&state, 0) == TITLE_MENU_ACTION_QUIT);
    return 0;
}
