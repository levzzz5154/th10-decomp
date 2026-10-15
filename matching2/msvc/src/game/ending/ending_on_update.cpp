#include "th10/game/ending_update.hpp"

#pragma code_seg(".text$00zcallback")
__declspec(noinline) int
EndingUpdateView::OnUpdate() {
    return Update();
}
#pragma code_seg()
