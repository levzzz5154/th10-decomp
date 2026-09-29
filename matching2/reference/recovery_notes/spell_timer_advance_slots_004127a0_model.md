# 0x004127A0 — spell-timer slot advance

Superseded on 2026-09-27 by an exact C++ recovery. See [the native spell-timer proof](spell_timer_advance_slots_004127a0_native_ltcg.md) and the current maintained source/manifest. The measurements below are historical.

The source now models `FUN_004127a0` as ordinary C++ in
`msvc/src/game/spell_timer.cpp`. The receiver and slot layout are local to that
translation unit so the function does not need a guessed shared class
hierarchy.

## Ghidra evidence

Ghidra decompiles the whole 593-byte range as
`undefined4 __fastcall FUN_004127a0(int param_1)`. The sole caller is
`FUN_0040dc80`; it calls the function at `0x0040E1C2` and `0x0040E27B`. At both
sites the caller loads the receiver from `[EBP+0x14D8]` into ECX, calls the
function with no stack arguments, then consumes EAX. The function has no
callees. This is representable by a C-linkage `__fastcall` function taking the
receiver pointer and returning a 32-bit result.

Ghidra's decompilation and disassembly show two distinct slot-result offsets:
the armed-ID path returns the dword at slot `+8`, while the deadline path
returns the dword at slot `+12`. The callers use each nonzero result as a
resource pointer, so the source models these as separate pointers,
`armed_resource` and `due_resource`; collapsing them into one field would
change behavior. A slot is 16 bytes, with signed ID and deadline fields at `+0`
and `+4`. The first scan selects the first nonnegative ID. It retires that slot
when its ID is at least the active ID; otherwise it proceeds to the deadline
scan. The latter selects the first slot with nonnegative ID and positive
deadline, publishes `(deadline - current + 59) / 60` capped at 99, returns null
while the deadline is in the future, and otherwise retires the slot and
performs the stage-side updates.

## Entry and link integration

The source uses `SpellTimer_AdvanceSlots_004127a0` as an external fastcall
symbol. Its pointer return type is inferred from both callsites' use of nonzero
EAX as a resource pointer; Ghidra leaves the return as `undefined4`. Existing
assembly callers currently declare and call `asm_FUN_004127a0_004127a0` as
cdecl in `msvc/include/asm_symbols.hpp`; the semantic region entry is now
bound to the fastcall symbol in the manifest, and the old name remains mapped
as the assembly alias used by existing naked callers. At the machine
interface, the required contract is clear: receiver in ECX, no stack
arguments, result in EAX, plain return. New C++ call sites should use the
typed fastcall entry.

## Byte-equivalence limits

No build, probe, shape run, or test was performed for this edit. The earlier
focused note reported a 0.870 register-normalized shape score for a different
member-function source model, with 554 of 593 bytes matching and the first byte
difference at the function entry. That score is historical and does not
measure this source. Byte equivalence remains unverified; this edit records the
semantic reconstruction, not a byte-matching claim.
