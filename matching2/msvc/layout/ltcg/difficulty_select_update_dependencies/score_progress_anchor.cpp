// 0x0042C850, which reports whether any play record of the score file is
// set, as the title main menu 0x0042D420 calls it: unselected here (the
// maintained form is src/game/progress.cpp).
#include "th10/game/title_main_menu_update_0042d420.hpp"
#pragma code_seg(".text$0042c850_fn")
int ScoreFileProgress_0042c850::HasAnyClear() {
    return cleared[0] != 0
        || cleared[1] != 0
        || cleared[2] != 0
        || cleared[3] != 0
        || cleared[4] != 0
        || cleared[5] != 0;
}
#pragma code_seg()
