# Huge resource state creation at `0x0042B660`

## Disposition

Keep `msvc/src/game/recovery_create_huge_resource_state_0042b660.cpp` as its
retail assembly overlay. The target returns a pointer in `EAX`, but its two
initialization helpers use private register-only inputs that an ordinary
standalone C++ call cannot express. This audit made no build, probe, or test
run; the source comment's earlier D3903 measurement remains the only output
comparison (`23/71` same-position bytes for a typed standalone candidate).

## Retail boundary and callers

The live Ghidra `th10.exe` program is x86 little-endian, 32-bit. It identifies
`FUN_0042b660` at `0x0042B660..0x0042B6A6` (71 bytes), with five direct callees:
`operator_new` (`0x00452493`), `FUN_0042b430`, `FUN_0042b4d0`,
`FUN_0042b570`, and `_free` (`0x004524A1`). The function takes no stack
arguments and returns its selected state pointer through `EAX`.

Ghidra reports two direct callers:

- `FUN_0040A350` calls it at `0x0040A365` and ignores `EAX` before continuing
  initialization.
- `FUN_00417870` calls it at `0x00417AEE`; the following path tests `EAX` and
  enters cleanup when the result is null.

The current region ledger assigns exactly 71 bytes at `0x0042B660` to
`asm_Recovery_CreateHugeResourceState_0042b660`, source
`src/game/recovery_create_huge_resource_state_0042b660.cpp`, with kind `asm`.

## Observed call and return contract

The target requests `0xB884` bytes from the cdecl allocator at `0x00452493`
and removes its one stack argument with `add esp, 4`. On allocation success it
copies the pointer to `EBX`, calls `0x0042B430`, and captures that helper's
`EAX` result in `ESI`; on the null branch it instead clears `ESI`. It then
unconditionally copies `ESI` to `EAX` and calls `0x0042B4D0`.

If initialization reports nonzero in `EAX`, the target calls `0x0042B570`
only when `ESI` is non-null, then passes that same pointer to cdecl `_free`
and cleans the argument itself. It returns null on this path. If initialization
reports zero, it returns `ESI` unchanged. In particular, allocation failure
does not skip the call to `0x0042B4D0`: it passes a null state in `EAX`. That
helper's first state write uses `[EAX + 0x10]`, so a null-returning allocator
would make this path fault. Preserve this sequence; do not silently turn it
into an early allocation-failure return.

## Register-only dependency blocker

`FUN_0042b430` reads its manager receiver from `EBX`, resets fields and large
regions of that object, publishes the pointer to `0x00477840`, then returns
the same pointer in `EAX`. The call at `0x0042B675` has no stack argument and
does not load a standard argument register. The caller saves its own `EBX`
around this helper because the helper treats `EBX` as its receiver.

`FUN_0042b4d0` takes the manager pointer from `EAX`, moves it into `EBX`,
initializes callback and entity state, and returns a status in `EAX`. The call
at `0x0042B683` likewise passes no stack argument. Its status controls the
target's cleanup/return branch. These entry contracts are not representable
with MSVC's ordinary x86 C++ calling conventions: `__cdecl`, `__stdcall`,
`__thiscall`, and `__fastcall` do not pass a first argument in `EAX` or a
receiver in `EBX`. `0x0042B570` itself is a conventional one-pointer cleanup
at the call site, but its retail body uses `ret 4` and the current symbol
declaration does not encode that signature.

The individual helper sources remain register-preserving naked bodies:
`effect_manager_reset_and_publish_retail_0042b430.cpp` and
`effect_manager_runtime_initialize_retail_0042b4d0.cpp`. The cleanup helper's
ABI and behavior are also recorded in
`effect_manager_destroy_0042b570.md`. Promoting just this factory would
therefore require reimplementing or changing dependencies outside its owned
source, or retaining an assembly bridge. A future source-only revisit should
wait for a caller-inclusive native-LTCG cluster that can evaluate the factory
with the reset and runtime-initialization helpers together.

## Alias integration if promoted later

A later promotion must update the shared `asm_symbols.hpp` declaration and
VA alias: the current declaration is `void __cdecl` even though callers
consume the returned pointer. It must also change the `0x0042B660` region's
manifest kind/symbol mapping and replace direct assembly references in
`src/game/stage_entry.cpp` (call at `0x00417AEE`) and
`src/unidentified/FUN_0040a350_0040a350.cpp` (call at `0x0040A365`). The
semantic entry signature should return `void*` with no arguments. This audit
left the manifest, shared declarations, callers, layouts, and the assembly
source unchanged.
