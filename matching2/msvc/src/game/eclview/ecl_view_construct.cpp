// The ECL viewer's constructor (0x0040A040): clear it, mark it live and
// publish it through 0x004776F8.
#include "th10/game/ecl_view.hpp"

#pragma code_seg(".text$00_ystateinit")
__declspec(noinline) EclViewState::EclViewState() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    g_ecl_view = this;
}
#pragma code_seg()
