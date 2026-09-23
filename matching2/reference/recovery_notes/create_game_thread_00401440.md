# `0x00401440` CreateGameThread

2026-09-23. Promoted the factory from naked assembly to a readable C++ model.
The function is a no-argument factory for a `0x89AC`-byte `GameThread`; it
allocates and constructs the object, asks the resource loader to initialize
it, and returns either the object or null. A nonzero loader result takes the
failure path, which destroys and frees the object when the allocation is
non-null.

The failure test intentionally comes first in the source. Earlier candidate
measurements showed that this spelling gives retail's `je` into the out-of-line
success epilogue. Testing success first changes that branch layout.

## ABI and exactness

The external ABI is an ordinary no-argument pointer return: the object is
returned in EAX and the function uses a plain `ret`. The call site at
`0x0041F9CC` relies on that shape.

The internal receiver conventions are private and are not represented by the
ordinary C++ declarations in the candidate:

- The constructor receives `this` in ESI and returns `this` in EAX.
- The resource loader receives the thread pointer in EAX. Its body saves that
  value in EBX and restores EBX before returning; nonzero indicates failure.
- The destroy helper is stdcall with the object on the stack. The free helper
  is cdecl with the object on the stack.

These register conventions are visible in the retail listing and are recorded
in `create_game_thread_00401440_cluster.md` and
`load_game_thread_resources_00401110_unlock.md`. The current factory source
uses typed calls to express the high-level operation. Its `__fastcall` loader
declaration is a source-model pointer parameter, not a claim that retail uses
ECX for this call.

Historical candidate measurements in
`create_game_thread_00401440_cluster.md` are useful context, but were made in
throwaway projects and are not a verification of this source revision:

- The standalone candidate emitted 69 bytes with two differing bytes. It used
  ECX instead of ESI for the constructor receiver and ECX instead of EAX for
  the loader receiver.
- The constructor-inclusive LTCG candidate emitted 69 bytes with one differing
  byte at `0x00401460`.
- The later loader-chain model made this factory exact at 69/69, but its loader
  still had four differing bytes and neither region was integrated together.

This promotion records the recovered behavior while leaving the internal ABI
and exact code generation unresolved. No current build or matching probe was
run as part of the promotion.
