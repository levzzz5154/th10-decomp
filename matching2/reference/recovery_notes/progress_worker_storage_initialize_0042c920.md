# Progress worker storage initialization at `0x0042C920`

`0x0042C920..0x0042C9EB` is a 204-byte initializer for the allocation made by
`ProgressManager_CreateAndStartWorker` at `0x0042CD50`. Its C++ model is in
`matching2/msvc/src/game/pool_constructors.cpp`.

## Behavior

Ghidra's decompilation and raw disassembly show an object pointer in EDX. Retail
first writes a vtable-like value and several fields, then executes `rep stosd`
with count `0x16B3` and destination equal to the object. That clears all
`0x16B3 * 4 == 0x5ACC` bytes, including those earlier stores. It then sets the
dword at `+4` to `2`, writes the object pointer to `data_0047784c`, and returns
the same pointer in EAX. Since the pre-clear stores have no remaining effect,
the readable model expresses the final object state with one zero fill and the
two final writes.

## ABI and call topology

The entry uses the MSVC x86 `__fastcall` register pair:

| Value | Location |
| --- | --- |
| Unused first argument | `ECX` |
| State object | `EDX` |
| Return pointer | `EAX` |
| Stack arguments | None |
| Return | Plain `RET` |

Ghidra lists one direct caller, `0x0042CD50`. Its assembly moves the allocation
pointer from EAX to EDX immediately before the call; the caller's ECX value is
not used by this function. The retail body has no `CALL` instruction and
therefore no direct callees. It preserves ESI and EDI; both are nonvolatile in
the ordinary x86 ABI as well.

## Model status

The active manifest now marks `0x0042C920` as semantic and retains the previous
assembly row in `previous_record`. The ordinary C++ entry uses a `__fastcall`
signature with an explicit unused ECX argument; its decorated function symbol
is the manifest anchor, while the pre-existing `_asm_FUN_0042c920_0042c920`
absolute alias remains available to the raw caller. The clear goes through the
integrated semantic `_memset` entry instead of adding a CRT dependency. The
function is represented by its final observable writes; retail byte identity
and exact compiler output remain unverified. No build, probe, or test was run.
