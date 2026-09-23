# Resource lookup error path at `0x00405F00`

`src/unidentified/unassigned_00405f00.cpp` now expresses this 50-byte region as ordinary C++. The entry takes no arguments, loads resource ID `7` from the cache pointer at `0x00491C10` using the name at `0x0046CD88`, and returns `0` when the lookup succeeds. If it returns null, the function appends the message at `0x0046CD54` to the text log at `0x00474F70` and returns `-1`.

The existing C-linkage identifier `asm_unassigned_00405f00` is retained so the unchanged manifest symbol `_asm_unassigned_00405f00` still names this entry. `regions.json` remains `kind: asm`; this is a readable semantic source candidate, not a manifest promotion or a claim of byte identity.

## Evidence

Ghidra disassembles `0x00405F00..0x00405F31` as the 50-byte body with two return paths: the failed lookup calls `0x0044B810`, sets EAX to `-1`, and returns; the successful lookup zeros EAX and returns. Ghidra does not currently register a function boundary or references to `0x00405F00`, so its callers remain unknown.

The called helpers have ordinary source-level declarations: Ghidra identifies `0x00447280` as `__fastcall` with ID in ECX, cache in EDX, and name on the stack; `0x0044B810` is the text-log append routine. Those match the resource lookup call sequence and establish the return-value meaning. The implementation uses the same `TextLog_0044b810` layout and variadic `Append` declaration as the nearby readable call sites.

## Exactness limit

The prior `vein_callee_calls_wave20.md` record measured a readable standalone candidate at 49 bytes against this 50-byte body. The remaining difference is the text-log call ABI. Retail loads `0x00474F70` into ECX, pushes the format pointer, calls `0x0044B810`, and removes four bytes. A standalone variadic member call under MSVC x86 treats the method as cdecl: it pushes both `this` and the format pointer, then removes eight bytes. The behavior is the same, but the call shape differs.

That note found the required TextLog body/context can let LTCG reproduce the retail ECX receiver shape; the `load_archive_file` layout uses a 201-byte ABI anchor for this purpose. Exactness therefore still depends on the appropriate TextLog call context and a fresh whole-region comparison. No build, probe, or test was run for this source change.
