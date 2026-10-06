#include "collision.hpp"
extern "C" {
extern const float data_00470b40, data_00470b3c, data_00470b04, data_00470b38;
}
#pragma code_seg(".text$f004086b0F")
int PlayfieldPoint::OutsideBounds(float horizontal_margin, float vertical_margin) const {
    if (!(x + horizontal_margin <= data_00470b40) &&
        !(x - horizontal_margin >= data_00470b3c) &&
        !(y + vertical_margin <= data_00470b04) &&
        !(y - vertical_margin >= data_00470b38)) return 0;
    return 1;
}
#pragma code_seg()
