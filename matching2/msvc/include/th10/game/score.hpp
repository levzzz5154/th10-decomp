#pragma once

// Clamp a requested signed counter value against the active upper bound.
// The fastcall ABI reflects the retail entry: requested arrives in ECX and
// the counter record in EDX.
unsigned int __fastcall UpdateBoundedCounter(
    unsigned int requested, unsigned int* counter);
