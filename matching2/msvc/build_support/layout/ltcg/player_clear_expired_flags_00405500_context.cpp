// Compiler context only; none of these bytes enter the image.
#include "../../../src/game/background/card_clear_capture_flags.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall PlayerClearExpiredFlagsContext_00405500(
        CardCaptureFlags** players, int count) {
    for (int i = 0; i < count; ++i)
        players[i]->ClearExpiredFlags();
    return count;
}
#pragma code_seg()
