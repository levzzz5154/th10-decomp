// 0x00408720..0x00408728: absolute value of the float argument.
#include <math.h>

extern "C" float __stdcall asm_unassigned_00408720(float value) {
    return fabsf(value);
}
