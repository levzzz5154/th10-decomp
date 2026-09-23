# Menu-flow update — 0x0042F540

## Disposition

Keep the current retail assembly body. A standalone C++ replacement cannot
preserve the target's entry contract: the game-state object arrives in `EBX`,
with no stack argument or `ECX` receiver. The one direct caller is itself an
assembly region, so converting just this row would require either changing its
call site or retaining an assembly adapter. Neither produces a clean,
standard-ABI C++ replacement within this region.

No source body or manifest row was changed. No build, probe, or test was run.

## Live Ghidra evidence

Target: open `th10.exe` in project `th10`, queried 2026-09-23.

- `get_function_by_address(0x0042F540)` reports `FUN_0042f540` with a nominal
  `__stdcall(void)` signature and body `0x0042F540..0x0042F89A`. The
  decompilation uses `unaff_EBX` throughout, so that nominal signature does
  not capture its actual input.
- The first instruction at `0x0042F540` reads `[EBX + 0x20]` before saving any
  registers. The body repeatedly accesses the same object through `EBX +`.
- `get_function_callers(0x0042F540)` reports only `FUN_0042cdf0`.
  Disassembly at `0x0042CDF0` begins `PUSH EBX; MOV EBX,EAX`; in switch case 5,
  `0x0042D146` calls `0x0042F540` without setting `ECX` or pushing an
  argument. `EBX` still holds the object supplied to the outer function.
- The matching manifest row at `0x0042F540` is an 880-byte assembly region,
  ending at `0x0042F8B0`. The machine-code routine returns `1` in `EAX`, but
  its receiver is not passed through any standard C++ argument location.
- Ghidra reports direct callees at `0x0042C5C0`, `0x0042C620`, `0x0042C670`,
  `0x0042C770`, `0x0042F8B0`, `0x0043DC90`, `0x00449250`, `0x0044A4E0`,
  `0x0044BE70`, and `0x0044BEA0`. Several consume register-carried state;
  notably, each call to `0x0042F8B0` is preceded by `MOV EAX,EBX`.

## Integration blocker

The only caller is `asm_FUN_0042cdf0` in
`matching2/msvc/src/game/title_menu_runtime.cpp`, whose manifest row is also
assembly. A semantic definition with `__thiscall`, `__fastcall`, or another
ordinary compiler ABI would expect its receiver in a different location.
Changing only the target body would therefore break the existing caller. A
future conversion needs the caller and callee migrated together, including
their register-based helper interactions. The nearby `0x0042F8B0` helper
already carries a source-side exact-match/private-ABI blocker note.
