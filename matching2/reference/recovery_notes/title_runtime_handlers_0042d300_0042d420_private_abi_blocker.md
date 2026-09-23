# Title runtime handler ABI audit: 0x0042D300 and 0x0042D420

Both handlers remain inline assembly. Live Ghidra confirms that each is called
only by the state dispatcher at `0x0042CDF0`; the dispatcher keeps its state
object in `EBX` and enters the handlers without pushing an object argument.
That machine-level contract does not match the apparent `__fastcall` prototype
Ghidra inferred from the functions.

## `0x0042D300`

- Ghidra function body: `0x0042D300..0x0042D40B` (268 bytes); the owning
  288-byte manifest row also contains the five-entry jump table at
  `0x0042D40C..0x0042D41F`.
- Ghidra reports `undefined4 __fastcall FUN_0042d300(undefined4 param_1)` and
  one caller, `FUN_0042cdf0`. In that caller, `0x0042CDF1` copies the incoming
  state pointer from `EAX` to `EBX`; the mode-1 path calls `0x0042D300` at
  `0x0042D065` with no argument push. The handler reads the mode from
  `[EBX+0x20]` at `0x0042D301` and returns `1` in `EAX`.
- The Ghidra decompiler's `param_1` is not the state object used by the body:
  that object is the live-in `EBX`. The entry's `push ecx`/exit `pop ecx`
  preserve ECX; they do not supply a stack argument.
- Direct callees include `0x0042C670`, `0x0042C770`, and animation-manager
  helpers. `0x0042C670` still consumes its slot index in `EDI`; `0x0042C770`
  indexes state through `EAX`/`ECX` and consumes its frame value in `SI`.
  These calls prevent expressing the handler as an ordinary C++ body without
  recovering the surrounding register contract.

## `0x0042D420`

- Ghidra function body: `0x0042D420..0x0042D8CA` (1195 bytes); its owning row
  also contains the embedded jump-table bytes through `0x0042D91F`.
- Ghidra reports `undefined4 __fastcall FUN_0042d420(undefined4 param_1)` and
  one caller, again `FUN_0042cdf0`. The mode-2 path calls it at `0x0042D0BD`
  with no argument push. Its first state read is `[EBX+0x20]` at `0x0042D420`,
  and it returns `1` in `EAX` without callee-cleaning an argument.
- The handler has state-machine modes 0 through 4, and its direct callees
  include slot install/clear (`0x0042C670`/`0x0042C6D0`), animation dispatch
  (`0x0042C750`), frame propagation (`0x0042C770`), and animation-manager
  operations. These still use hidden state, owner/index, manager, and frame
  values in registers. The timer-target helper at `0x0042C620` is semantic,
  but resolving that single edge does not resolve the handler ABI or the
  remaining animation calls.

The exact caller and body ranges are from live Ghidra (`get_function_by_address`,
`get_function_callers`, `decompile_function`, and `disassemble_function` at
`0x0042CDF0`; function and disassembly queries at both handler entries). The
source bodies remain in `src/game/ending_screen.cpp` and
`src/game/title_main_menu.cpp`. A future conversion needs the caller and the
register-ABI animation leaves in the same recovered cluster; no manifest or
shared-header change is made by this audit.
