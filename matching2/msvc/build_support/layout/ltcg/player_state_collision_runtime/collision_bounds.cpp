#include "collision.hpp"
extern "C" {
extern const float flt_neg192, flt_192, flt_0, flt_448;
}
#pragma code_seg(".text$f004086b0F")
int PlayfieldPoint::OutsideBounds(float horizontal_margin, float vertical_margin) const {
    if (!(x + horizontal_margin <= flt_neg192) &&
        !(x - horizontal_margin >= flt_192) &&
        !(y + vertical_margin <= flt_0) &&
        !(y - vertical_margin >= flt_448)) return 0;
    return 1;
}
#pragma code_seg()
