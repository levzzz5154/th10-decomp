# Focused allocator/initializer follow-up

2026-09-13. The 161-byte pool allocator (`0x00449950`) and 273-byte entity
initializer (`0x00401DE0`) remain assembly. These experiments were isolated in
`matching2/build/recovery-lab/project`; no production source or manifest entry
was promoted.

The earlier 15-function animation-manager attempt did not isolate the
initializer or pool source shape. This follow-up compiled those two definitions
in one native-LTCG scope, from separate inputs, with a pointer-array context
that calls `AnimationPool::Allocate`. The context selects ESI for the pool;
the initializer takes its entity in EDX without a dummy source argument.
Neither function is rooted or exported. External bindings are only allocation
and the already recovered constructor at `0x00402050`.

The maintained `Entity` aggregate fixes the earlier initializer's 0x40-byte
scratch-frame expansion. A saved `Vector3`, saved render bucket, `memset`,
restored fields, identity matrix, timer resets, and two self-owning list nodes
produce exactly the retail 273-byte extent and 0x10-byte scratch frame.
The prefix through `0x00401E19` matches. Chained identity assignments in
ascending source order produce the descending stores retail uses.

Remaining initializer differences are source scheduling, not its input ABI:

- With bucket restoration before the aggregate position copy, the compiler
  emits the third position store and `xor eax,eax` before restoring the
  bucket. Retail places the bucket store at `0x00401E1A`, the third position
  store at `0x00401E1D`, then clears EAX.
- Reversing the two source statements swaps the spill reload allocation and
  still does not give the retail interleaving.
- Explicit integer-bit restoration through a three-word `PositionBits`
  aggregate moves the first two stores before the spill reloads. This also
  preserves the complete extent, but first differs at `0x00401E0D`.
- The compiler restores EDI before the marker/timer stores (`0x00401E97`)
  and distributes ESI/EBP restores differently. Retail delays EDI until
  `0x00401EAD`. All identity-matrix stores match after correcting chain order.
- Aggregate assignment versus `memcpy`, a zeroing loop versus `memset`, and
  void versus zero-valued integer return did not remove these differences.
  Ordinary compilation with an explicit unused ECX fastcall parameter
  reproduces the same scheduling failures; caller visibility alone is not
  the missing ingredient for these stores.

For allocation, the typed pool has `Entity objects[4096]` at `+0x68`, busy
bytes at `+0x3AC068`, and a signed cursor at `+0x3AD068`. The signed modulo
4096 expression reproduces retail's negative-input correction. The source
checks the current slot and its successor, falling back to heap allocation
when both are busy, then advances the cursor again. The initializer is called
even on the allocator's null-construction path, as in retail.

A manual allocation/constructor spelling emits 153 bytes. A real `new Entity`
expression, with the constructor bound to `0x00402050`, emits 160 bytes and
restores the duplicated constructor-success/null call paths. Both keep the
result in EDX across the compiler-visible initializer, whereas retail keeps
it in EDI. The initializer's complete body preserves EDX, so LTCG can exploit
that fact. The resulting different live ranges also move the initial pool
index from EAX to ECX and retain a busy-byte address in EAX. Neither candidate
passes the 161-byte extent/byte gate.

Diagnostic native maps and images are retained under `recovery-lab/pool4`,
`pool5`, `pool6`, and `pool7`. `pool6` records the 160-byte `new Entity`
allocator. `init_ordinary`, `init_bits`, and `init_loop` retain the ordinary
initializer controls. The next useful experiment should investigate the
original inline aggregate/timer/list initialization boundaries and the
allocator's call-clobber assumptions. These misses do not establish that
any of the two functions is unreachable from C++.
