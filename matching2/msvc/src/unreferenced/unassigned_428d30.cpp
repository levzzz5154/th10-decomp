// 0x00428D30..0x00428D3C (13 bytes): angle of the vector between two positions.
//
// Retail loads the two y floats, subtracts, loads the two x floats, subtracts
// and takes FPATAN, the compiler's inline expansion of atan2.  The first
// operand loaded comes from EAX, so the record handed to the function first
// (in ECX) is the far end and the one in EAX is the near end; both arguments
// are register arguments.

#include <math.h>

struct Position2 {
    float x;                               // +0x00
    float y;                               // +0x04
};

__declspec(noinline) float __fastcall Position_00428d30_AngleTo(Position2* to,
                                                                Position2* from);

#pragma code_seg(".text$01angle")
float __fastcall Position_00428d30_AngleTo(Position2* to, Position2* from) {
    return atan2f(from->y - to->y, from->x - to->x);
}
#pragma code_seg()
