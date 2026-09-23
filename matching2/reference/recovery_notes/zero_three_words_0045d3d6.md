# Clear three words at `0x0045D3D6`

The C++ model in `matching2/msvc/src/unidentified/FUN_0045d3d6_0045d3d6.cpp`
clears three consecutive 32-bit words through its destination pointer.

Ghidra identifies a 12-byte function with a single pointer at `[ESP+4]`, three
`STOSD` stores of zero, and a plain `RET`; the caller removes the stack
argument. The function has no direct callees or registered callers. Its entry
and body extent match the 12-byte manifest region.

The active manifest marks the region semantic and retains the original row in
`previous_record`; the C-linkage symbol remains unchanged. The source has no
inline assembly. Exact compiler output and retail byte identity remain
unverified. No build, probe, or test was run.
