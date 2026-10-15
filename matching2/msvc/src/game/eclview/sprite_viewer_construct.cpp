// The sprite viewer's constructor (0x0040A040): clear it, mark it live and
// publish it through 0x004776F8.
#include "th10/game/sprite_viewer_state.hpp"

#pragma code_seg(".text$00_ystateinit")
__declspec(noinline) SpriteViewerState::SpriteViewerState() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    data_004776f8 = this;
}
#pragma code_seg()
