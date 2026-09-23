# Replay-menu draw recovery note: `0x00433B30`

Date: 2026-09-23

Status: the region remains naked assembly. Ghidra makes the drawing logic
readable, and the entry ABI is a normal one-argument `__stdcall`; however,
every text append carries its position in `EBX` through the formatting helper
to the record writer. A direct C++ call to the helper cannot express that
implicit argument. Promoting this body therefore needs an ABI-aware formatter
bridge (or a local semantic reimplementation of the record append path), in
addition to the entry-symbol integration below. No build, probe, or test was
run for this audit.

## Live Ghidra evidence

On `th10.exe`, `get_function_by_address(0x00433B30)` reports
`FUN_00433b30`, signature `undefined4 __stdcall FUN_00433b30(int param_1)`,
and body `0x00433B30..0x00433EEA` (955 bytes). `analyze_function_complete`
reports 259 instructions, 30 basic blocks, 42 edges, 8 calls, and one xref at
`0x0042D29C`. The initial argument is used as a state pointer: the body reads
its phase at `+0x20`, selection at `+0x24`, timer at `+0x2B4`, and replay/name
data at `+0x58DC..+0x59E4`.

`disassemble_bytes(0x0042D28E, 48)` shows the caller path at
`0x0042D29B`: `push EDI; call 0x00433B30; mov EAX,1; pop EDI; ret`. There is
no caller-side stack adjustment. The target ends in `ret 4`, confirming the
callee-cleaned state argument. The source-level prototype should therefore
be `int __stdcall ReplayMenu_Draw(void *state)` (Ghidra's `undefined4` return
is the constant `1`).

The live decompilation shows three paths:

- Phase 2 draws 25 replay slots from the pointer array at state `+0x59E4`.
  It colors the selected slot differently, prints placeholders for empty
  slots, and formats date, replay metadata, and progress for populated ones.
- Phase 3 formats the current replay selected through the global pointer at
  `0x00477838`. Once the transition timer at `+0x2B4` reaches 10, it draws
  the name-entry alphabet referenced through `0x004746D8`, an underscore
  cursor, and the character grid selected by `+0x58F4`. The grid loop wraps
  its position every 13 entries and emits special character codes for its
  final three cells.
- Other phases return `1` immediately. The two drawing paths restore the
  GameThread color at `+0x8974`; the shared exit also clears its draw-mode
  field at `+0x8988` and returns `1`.

`search_strings` found the empty and populated replay-row formats at
`0x0046EF74` and `0x0046EFB0`, plus the alphabet
`ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-=.,!?@:;[]()_/{}|~^#$%&*   `
at `0x0046E2F8` (reached through the pointer global at `0x004746D8`).

## Formatter ABI blocker

Ghidra types `_localtime` at `0x00452BAA` as
`tm * __cdecl _localtime(time_t *)`; the draw body passes the timestamp at
replay-record offset `+0x24`. That dependency has an ordinary C ABI.

The logger path does not have an ordinary two-parameter call contract at the
draw sites:

- `0x00401630` is `AppendFormattedGameThreadRecord`, decompiled as a cdecl
  formatter. Its body formats the variadic stack arguments, then loads the
  thread pointer into `ECX`, the formatted text into `EAX`, and calls
  `0x00401530`.
- `0x00401530` is `AppendGameThreadRecord`, typed by Ghidra as
  `__fastcall` with the thread object in `ECX`. Its disassembly also reads
  `EAX` as the formatted text and reads the position vector from `EBX`:
  `MOV ESI,[EBX]`, followed by copies from `[EBX+4]` and `[EBX+8]` into the
  record fields at `+0x40..+0x48`.
- The draw body initializes a stack vector and sets `EBX` to its address
  before each call to `0x00401630` (for example, `LEA EBX,[ESP+0x38]` before
  the call at `0x00433C1F`). `AppendFormattedGameThreadRecord` preserves that
  nonvolatile register, so the position reaches the record writer implicitly.

The logger's semantic declaration needs an explicit position argument, for
example `GameThread_AppendFormatted(GameThread *, const float position[3],
const char *format, ...)`, and a bridge that carries that position to the
retail writer. The current `asm_GameThread_AppendFormatted_00401630` symbol
has no such typed argument and relies on `EBX`; calling it through an ordinary
cdecl variadic function pointer would lose the draw coordinates. The helper
and its declarations are outside this region's ownership, so this note does
not add a replacement call path.

## Symbol and alias integration

The current production region in `matching2/msvc/regions.json` maps
`_asm_FUN_00433b30_00433b30` at `0x00433B30` and is classified `asm`.
`matching2/msvc/include/asm_symbols.hpp` declares it as
`extern "C" void __cdecl asm_FUN_00433b30_00433b30();`; the sole caller uses
that undecorated cdecl alias, pushes the state pointer, and depends on the
callee's `ret 4` cleanup. A semantic entry will be emitted with the decorated
MSVC x86 name `_ReplayMenu_Draw@4` (assuming that C-linkage spelling and
return type), so the existing caller symbol needs an alias from
`_asm_FUN_00433b30_00433b30` to `_ReplayMenu_Draw@4`. The region classification
and address binding must also refer to the semantic symbol. Those shared
integration files and the caller were intentionally left unchanged in this
task.

The existing file comment records an earlier readable candidate measuring
483 bytes against the 955-byte region. This audit retained the current body;
without a formatter bridge and the required alias integration, replacing it
with a direct semantic call path would either drop the position argument or
leave the existing alias unresolved.
