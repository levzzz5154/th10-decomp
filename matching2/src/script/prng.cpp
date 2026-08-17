// 0x0043CB80 FUN_0043cb80
// Readable reconstruction of retail helper FUN_0043cb80.
//
// FUN_0043cb80 is a xor-shift-style PRNG step used by the entity VM
// interpreter (FUN_0043ee30, opcode 0x29) to draw a uniform pseudo-random
// integer in the range [0, modulo).  The caller passes the PRNG state
// pointer in ECX and the modulo bound in EDI; both registers are live
// across the call and Ghidra surfaces the modulo as ``unaff_EDI``.
//
// Layout of the 6-byte PRNG state (DAT_004918a8 at retail):
//   bytes 0..1 : 16-bit shift register (the in-place ``*param_1`` word)
//   bytes 2..3 : padding
//   bytes 4..7 : 32-bit iteration counter (``*(int*)(param_1 + 2)``)
//
// The retail algorithm:
//   1. mix  = (reg ^ 0x9630) - 0x6553
//   2. step = (mix >> 14 & 3) + mix * 4       (32-bit)
//   3. reg  = (uint16)step
//   4. tmp  = (reg ^ 0x9630) + 0x9aad
//   5. *param_1 = reg                          (intermediate write)
//   6. tmp  = (tmp >> 14) + tmp * 4            (16-bit truncation)
//   7. counter += 2
//   8. *param_1 = (uint16)tmp                  (final write)
//   9. result = (step * 0x10000 | tmp) % modulo
//
// Step 5 is observable but immediately overwritten by step 8; the readable
// reconstruction keeps both writes so a debugger stepping through matches
// the retail memory trace exactly.

#include "th10/script/prng.hpp"

uint32_t EntityScript_NextRandomModulo(void* state, uint32_t modulo) {
    if (modulo == 0)
        return 0;
    uint16_t* reg = static_cast<uint16_t*>(state);
    uint32_t mix = (static_cast<uint32_t>(*reg) ^ 0x9630u) - 0x6553u;
    uint32_t step = ((mix >> 14) & 3u) + mix * 4u;
    uint16_t low_step = static_cast<uint16_t>(step);
    uint32_t tmp = (static_cast<uint32_t>(low_step) ^ 0x9630u) + 0x9aadu;
    *reg = low_step;
    tmp = (tmp >> 14) + tmp * 4u;
    uint16_t next_reg = static_cast<uint16_t>(tmp);
    int32_t* counter = reinterpret_cast<int32_t*>(reg + 2);
    *counter += 2;
    *reg = next_reg;
    uint32_t combined = (step << 16) | static_cast<uint32_t>(next_reg);
    return combined % modulo;
}
