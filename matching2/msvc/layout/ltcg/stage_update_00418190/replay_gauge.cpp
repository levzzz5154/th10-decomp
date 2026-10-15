#include "types.hpp"
#pragma code_seg(".text$00428e10_fn")
Player* Player::SetFixedPosition(const FixedPoint* source) {
    int* fixed = &fixed_position.x;
    fixed[0] = source->x;
    fixed[1] = source->y;
    position.x = float(fixed_position.x) * 0.01f;
    position.y = float(fixed_position.y) * 0.01f;
    for (int index = 0; index < 4; ++index)
        options[index].reset_position = 1;
    return this;
}
#pragma code_seg()
