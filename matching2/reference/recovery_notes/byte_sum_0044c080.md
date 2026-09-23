# Alternate-byte sum, `0x0044C080`

The 36-byte retail body receives a byte pointer in ECX and a signed count in
EDX. It adjusts odd counts down by one, reads offsets `0, 2, 4, ...`, adds the
selected bytes modulo 256, and returns the zero-extended sum in AX. Counts of
zero or less do not read the pointer.

`src/unidentified/unassigned_0044c080.cpp` now expresses that behavior as an
ordinary `extern "C" __fastcall` function. Its signed `count / 2` loop has the
same iteration count as the retail adjustment for both positive and
nonpositive counts. The result is kept as an unsigned byte and converted to an
unsigned-short return, modeling the observed AX result.

The adjacent `ByteChecksum_0044c070` uses the same pointer/count fastcall shape
for stride-one accumulation. No retail caller of the stride-two function has
been established. `layout/ltcg/byte_sum_0044c080_context.cpp` supplies a
synthetic array caller to retain a direct call edge and make the ABI candidate
available to native LTCG.

This is an **unverified semantic candidate**. The earlier measured ordinary
C++ spelling in the shared byte-sum/vector-return note had the correct 36-byte
extent but 14 differing bytes, concentrated in loop setup and register
lifetime. The present source and its synthetic caller were not built or
probed, so neither exact bytes nor the estimated context extent is established.
