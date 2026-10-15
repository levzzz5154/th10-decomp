// 0x0041F850: the loading screen's constructor, shared with Loading_Create.
#include "th10/game/loading.hpp"

#pragma code_seg(".text$00bstatector")
__declspec(noinline) Loading::Loading() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    g_loading = this;
}
#pragma code_seg()
