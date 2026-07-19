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
// Public API refers to the state as an opaque pointer so callers do not
// need to know the internal layout.

#ifndef TH10_SCRIPT_PRNG_HPP
#define TH10_SCRIPT_PRNG_HPP

#include <cstdint>

// Returns the next pseudo-random uint32 in the range [0, modulo).  A
// modulo of 0 yields 0 (avoids the divide-by-zero that retail would
// fault on).  ``state`` is the 6-byte PRNG state, mutated in place.
uint32_t EntityScript_NextRandomModulo(void* state, uint32_t modulo);

#endif  // TH10_SCRIPT_PRNG_HPP