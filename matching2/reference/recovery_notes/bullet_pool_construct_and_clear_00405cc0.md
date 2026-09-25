# Bullet-pool construction and clear at 0x00405CC0

Ghidra recognizes the complete 51-byte body from `0x00405CC0` through
`0x00405CF2`. The retail entry receives the bullet pool in ESI. It invokes
the MSVC exception-safe vector constructor for 0x7D1 elements, each 0x7F0
bytes, starting at pool offset 0x60. The callbacks are the already recovered
`Entity_ResetRuntimeState_00405D00` and
`EntitySecondaryResource_Release`. It then zeroes 0x3E0B54 bytes from the
start of the pool, stores the pool pointer at `0x004776F0`, and returns it.

The [C++ source](../semantic_candidates/bullet_pool_construct_and_clear_00405cc0.cpp)
preserves that order and uses typed callbacks and `memset`. The manifest
records the previous assembly region. There are no Ghidra xrefs to this
entry; its original ESI input is currently represented as a cdecl argument.

Earlier [matching work](vein_callee_calls_wave20.md) modeled this body with
only two differing bytes, both image-base bytes in the pushed callback
addresses. That model was reverted then. The current source has not been
built or byte-compared, so exact matching remains unverified.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
