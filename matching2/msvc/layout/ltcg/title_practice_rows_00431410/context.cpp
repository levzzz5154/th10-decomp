// Compiler context only; none of these bytes enter the image.
#include "../../../src/game/title/title_practice_rows_00431410.cpp"
#include "formatted.cpp"

#pragma code_seg(".text$07context")
extern "C" int __stdcall TitlePracticeRowsContext(TitleDrawView** menus, int count,
                                                  GameSelection_00431410** selection) {
    // The game state is reachable through pointers in the game, so stores
    // through other pointers may alias its members.
    *selection = &data_00474c68;
    int total = 0;
    for (int i = 0; i < count; ++i)
        total += menus[i]->DrawPracticeRows();
    for (int i = 0; i < count; ++i)
        total += menus[i]->DrawScoreRows();
    return total;
}
#pragma code_seg()
