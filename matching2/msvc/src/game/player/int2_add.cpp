// 0x00427DC0 (16 bytes): add two integer coordinate pairs by value.
// Native LTCG supplies the result in EAX, the left operand in ESI and the
// right operand in EDX; the compiler-only array caller derives this ABI.
#include "th10/math/int2.hpp"
#pragma code_seg(".text$01sum")
Int2 Int2::operator+(const Int2& right) const {
    int sum_x = x + right.x;
    int sum_y = y + right.y;
    return Int2(sum_x, sum_y);
}
#pragma code_seg()
