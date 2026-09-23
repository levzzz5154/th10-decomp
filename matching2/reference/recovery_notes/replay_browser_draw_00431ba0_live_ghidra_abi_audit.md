# Replay browser draw `0x00431BA0`: live Ghidra ABI audit

Date: 2026-09-23. Read-only inspection of the active `th10.exe` program.

## Function and visible behavior

Ghidra identifies `FUN_00431ba0` at `0x00431BA0`, with body end `0x00431ED8`.
The manifest extent is 825 bytes, including the final `RET 4`. Ghidra's
prototype is `undefined4 __stdcall FUN_00431ba0(int *param_1)`. Its only direct
xref is the call at `0x0042D276`; that caller pushes its object pointer and
calls this function. The epilogue returns `1` in EAX and removes the one
four-byte argument.

The state at `param_1 + 0x20` selects the screen:

- State `2` draws 25 replay slots from the pointer array at `+0x59E4`, using
  the current slot at `+0x59DC`. Each present slot supplies a record at
  `slot + 0x18`; absent slots use the `No.%.2d -------- ...` placeholder. The
  row origin is `(80, 80, 0)` and Y advances by 15.
- State `4` draws the selected replay record. It uses the same slot array and
  record offset. While the timer at `+0x2B4` is below 10, the record row's Y
  position is animated using the transition value at `+0x2B8` and the selected
  slot index. At timer 10 or later it draws seven score rows, starting at
  `(220, 128, 0)` and advancing Y by 18. The row labels come from the pointer
  table at `0x0047471C`; missing values use `"%s  ---------"` and present
  values use `"%s  %.8d%d"`.
- Other states return `1` without drawing.

While drawing, the global GameThread pointer at `data_004776E0` has its busy
field at `+0x8988` set to 1. Each row writes `0xFFFFFF00` for the selected row
or `0xFF808080` otherwise to `+0x8974`. The function restores color to
`0xFFFFFFFF` and clears busy before returning.

The formatted replay record reads a `time_t` at record offset `+0x0C` through
`_localtime`; the clear percentage float is at `+0x48`. Values at `+0x50` and
`+0x54` combine to index the table at `0x004746DC`; values at `+0x58` and
`+0x5C` index tables at `0x004746F4` and `0x00474744`. The `%s` argument is
passed as the record base pointer itself (`push EDI`), so the first record
member's exact representation still needs a record-layout owner before it
should be modeled as a pointer field.

## ABI blocker

`_localtime` at `0x00452BAA` is an ordinary CRT call. Live Ghidra reports
`tm * __cdecl _localtime(time_t *_Time)`, so its call edge is expressible in
normal C++.

The record formatter is not fully expressible through an ordinary C++ call.
Ghidra reports `AppendFormattedGameThreadRecord` at `0x00401630` as cdecl with
the GameThread pointer and format string on the stack; the body uses
`_vsprintf` and then calls `AppendGameThreadRecord` at `0x00401530`. Ghidra
decompiles that second helper as `__fastcall(int param_1)` with its text buffer
in EAX and an unlisted `unaff_EBX` pointer. Its disassembly explicitly reads
`[EBX]`, `[EBX+4]`, and `[EBX+8]` as the record's three position values.

Before each formatter call in this function, the assembly sets EBX to the
stack-local `(x, y, z)` values. For example, `0x00431C88` sets EBX to
`ESP+0x34` after the date and format arguments have been staged; the
placeholder and score-row paths similarly set it to `ESP+0x1C` or
`ESP+0x20` after pushing their arguments. This private register input is
forwarded unchanged by `AppendFormattedGameThreadRecord` to
`AppendGameThreadRecord`. A normal variadic call can supply the GameThread,
format, and stack arguments, but cannot require EBX to point at this function's
position locals. Therefore the readable state and record behavior do not make
the logger call ABI-safe for a standalone C++ rewrite. Keep this 825-byte
body naked until the logger has a semantic wrapper that accepts the position
explicitly or the integration owns an appropriate register bridge.

## Prototype and symbol integration

For a future ordinary C++ entry, the audited target prototype is:

```cpp
extern "C" int __stdcall asm_FUN_00431ba0_00431ba0(int* browser_state);
```

Its decorated x86 linker spelling is `_asm_FUN_00431ba0_00431ba0@4`, already
listed as an alias in `regions.json`. The shared `asm_symbols.hpp` currently
declares the naked entry as zero-argument cdecl; that declaration must be
reconciled by the parent if the manifest owner is changed. The corresponding
existing helper aliases are `asm_GameThread_AppendFormatted_00401630` at
`0x00401630`, `asm_GameThread_AppendRecord_00401530` at `0x00401530`, and
`asm_localtime_00452baa` at `0x00452BAA`. Their header declarations are
assembly stubs with no explicit parameters; do not treat the AppendRecord
alias as an ordinary C++ function because it also consumes EAX and EBX.
