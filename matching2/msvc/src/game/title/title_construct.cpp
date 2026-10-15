// Exact Title constructor, compiled with its factory closure.
#include "th10/game/title.hpp"

#pragma code_seg(".text$03aprogressctor")
__declspec(noinline) Title::Title() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    g_title = this;
}
#pragma code_seg()
