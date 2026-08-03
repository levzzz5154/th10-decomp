#include "th10/game/frame_counter.hpp"

// 0x00427C70 - Interval test on a two-word frame counter. Retail lays
// the counter out as {previous at +0x00, current at +0x04} and returns
// 1 only when the two differ and current % interval is zero.
#ifdef _MSC_VER
__declspec(naked) int32_t FrameCounter_AtInterval(
        const int32_t* counter, int32_t interval) {
    __asm {
        mov eax, [ecx+4]
        cmp eax, [ecx]
        jz loc_427C88
        cdq
        idiv dword ptr [esp+4]
        test edx, edx
        jnz loc_427C88
        mov eax, 1
        ret 4
loc_427C88:
        xor eax, eax
        ret 4
    }
}
#else
int32_t FrameCounter_AtInterval(const int32_t* counter, int32_t interval) {
    if (counter[1] != counter[0] && counter[1] % interval == 0) {
        return 1;
    }
    return 0;
}
#endif
