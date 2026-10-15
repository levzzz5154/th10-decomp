// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../src/game/background/power_display_set_digits_004054b0.cpp"

#include "../../src/core/sprtanim/animation_object_configure_from_resource_0043e5a0.cpp"

#pragma code_seg(".text$05context")
extern "C" int __stdcall PowerDisplaySetDigitsContext_004054b0(
        PowerDisplayOwner_004054b0** owners, int count) {
    for (int i = 0; i < count; ++i)
        owners[i]->SetPowerDigits(i, count);
    return count;
}
#pragma code_seg()
