# `0x00418EE0` resource-manager teardown semantic model

`0x00418EE0` occupies 346 bytes (`0x00418EE0..0x00419039`) in the retail
`.text` region. The current C++ source is
[`matching2/msvc/src/game/fun_00418ee0_00418ee0.cpp`](../semantic_candidates/fun_00418ee0_00418ee0.cpp).
The manifest now records this region as a semantic C++ source and points its
symbol at the one-argument stdcall entry. The shared declaration and the
source-level callers now use that same ABI. Existing address aliases for the
legacy undecorated name remain available to assembly call sites.

## Behavior recovered from Ghidra

The function removes two non-null scheduled-resource pointers from the scheduler
in order: the manager field at `+0x08`, then the field at `+0x0C`. Each removal
is bracketed by calls through the `EnterCriticalSection` and
`LeaveCriticalSection` import slots (`0x004660B0` and `0x004660B4`) using the
critical section at `0x00492274`. The byte counter at `0x0049231C` is incremented
after entering and decremented after leaving. After reading each task field, the
scheduler pointer is reloaded from `0x00491BE4` before the null test, so the load
also occurs when the task is null. `Scheduler_Remove` at `0x00449F60` receives
the task in ECX and the scheduler in EDX.

Next, the routine reads the game-state-manager pointer at `0x00491C10` and
iterates ten manager slots beginning at `+0xDC`. For each non-null slot value,
it searches the linked list whose head is at manager offset `+0x72DAD4`; only
when that search misses does it search the list at `+0x72DADC`. A list link has
the observed pointer/next shape at offsets `+0` and `+4`. The first dword of
each pointed-to record is compared with the slot value. On a match, the function
sets flag `0x04000000` at record offset `+0x35C`. If the record field at `+0x18`
is null, it also sets that flag on each item in the related list at `+0x14`.
The manager slot is then cleared, whether it was null, absent from both lists,
or found and processed.

If byte `0x00491D6A` equals `2`, the routine calls `0x0041A200` with the manager
and the path `"hint/hint_auto.txt"`. It then calls the bucket clearer at
`0x00419040` on the same manager and stores zero to the dword at `0x00477814`.
That order is also visible in the callers and is kept in the semantic source.

The offset names in the C++ are intentionally provisional. In particular, the
evidence establishes a ten-pointer array, two list heads, a first-dword key,
the `+0x14/+0x18` relationship fields, and a flag word at `+0x35C`; it does not
establish the retail class names or the higher-level meanings of those fields.

## ABI and call sites

The entry has one pointer argument at `[ESP+4]`, no private register input, a
void result, and callee cleanup with `RET 4`. The retail body saves and restores
EBX, EBP, ESI, and EDI, and saves/restores ECX; EAX and EDX are scratch.

Ghidra reports these incoming call references:

- `FUN_00417C80`, call at `0x00417EB7`.
- `FUN_00419090`, call at `0x004190BD`.
- Calls at `0x004190E1` and `0x00419105`, outside recognized Ghidra caller
  functions; the repository has semantic source candidates beginning at
  `0x004190E0` and `0x00419100`.

The direct callees are the Enter/Leave critical-section imports, scheduler
removal at `0x00449F60`, the score-save routine at `0x0041A200`, and
`ClearBuckets` at `0x00419040`. The latter uses a private retail convention with
its manager in EAX and plain `RET`; the C++ member call records the recovered
object relationship, while reproducing that register at the call site requires
the caller-inclusive native-LTCG context described in
[`recovery_clear_eight_buckets_00419040_wave5.md`](recovery_clear_eight_buckets_00419040_wave5.md).
Ghidra gives the score-save callee the prototype
`undefined4 __stdcall(int, LPCSTR)`. Thus the manager and path are its two
stack arguments, it uses callee cleanup (`RET 8`), and its 32-bit return value
is ignored here. The source's `ScoreSaveCall_00418ee0` function pointer now
uses `__stdcall` to match that callee convention.

The source definition keeps the established C name and declares the recovered
one-pointer `__stdcall` ABI. Its x86 MSVC symbol is
`_asm_FUN_00418ee0_00418ee0@4`, which the semantic manifest record selects.
The shared declaration now has the same argument and calling convention; the
old no-argument cdecl alias remains mapped to the address for existing inline
assembly references. The direct source callers at `0x00419090`, `0x004190E0`,
and `0x00419100` also use the one-pointer stdcall type.

## Exactness status

This change records readable behavior in ordinary C++; it does not claim a
byte-exact build. Existing naked code established the retail extent and ABI,
and prior readable-code probes did not reproduce the full region. The private
`EAX` receiver call to `0x00419040`, code-generation order, and symbol binding
remain integration points. No build or tests were run for this semantic model.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
