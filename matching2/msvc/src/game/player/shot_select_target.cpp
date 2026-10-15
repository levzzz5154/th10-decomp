// 0x00428AD0. The first __fastcall argument selects the active enemy pool, the
// second receives the resolved pointer at +0x4C, and the third stack argument
// is unused. The pool's current enemy is rejected when its entry angle is
// farther than the threshold stored in flt_224.
#include <math.h>

extern "C" float flt_224;   // 0x00470B4C, 224.0f

int __fastcall Shot_SelectTarget(int state, int resolved, int unused) {
    *(int*)(resolved + 0x4C) = 0;
    int enemy = *(int*)(state + 0x3504);
    if (enemy) {
        *(int*)(resolved + 0x4C) = enemy;
        if (fabsf(*(float*)(enemy + 0x1068)) > flt_224)
            *(int*)(resolved + 0x4C) = 0;
    }
    return 0;
}
