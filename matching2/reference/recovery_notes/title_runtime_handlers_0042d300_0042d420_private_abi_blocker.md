# Title runtime handler ABI audit: 0x0042D300 and 0x0042D420

The 0x42D2E0 outer adapter is now selected exact C++ using the full readable
dispatcher as an unselected native anchor. See
`title_dispatch_callback_0042d2e0_2026_10_04.md`. The two handlers discussed
below remain assembly-owned; their recovery is not implied by the adapter.

## Full script caller graph control, 2026-10-04

The next control compiled the complete existing script executor, indicator,
text, animation creation, and music-room caller graph from
`recovery_animation_slot_frames_0042c6d0.json`, alongside the complete readable
title dispatcher and ending handler. The original helper-cluster context is
the linker entry; the natural title adapter is independently rooted. The
context is an experimental compiler root, not a newly recovered retail caller.
All additional source bodies are the maintained complete implementations.

This resolves two previously observed mismatches: the ending handler now reads
its incoming room directly from EBX without saving/moving EBX, and slot
installation again consumes its room on the stack and index in EDI. The slot
install contribution is 95 bytes, and frame propagation is 65 bytes. Neither
extent alone establishes exactness at these experimental addresses.

The complete ending contribution is 284 bytes including its five-entry table.
It pushes ESI early and initializes a persistent zero with `xor esi,esi` after
lookup. It pushes that zero for animation creation and uses it in selection
comparisons/stores. Retail uses an immediate push, a TEST, and distinct zero
stores; it saves ESI only in phase 2. Animation creation also loads its resource
in EAX and result in ECX, whereas this retail caller uses ECX and EDX.

A second executed control changes only the signed-count branch ordering:
zero, positive, negative rather than zero, negative, positive. This produces
288 bytes and preserves separate zero-store blocks, but it still caches zero
in ESI and remains nonexact. No selected ownership or production source changed
for these controls; the already exact seven-byte adapter remains intact.

Reproduction from the repository root:

```
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py full_script
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py full_script_count
```

Both compile with and without /GL and link using the original compiler. The
runner now resolves complete manifest absolute-symbol declarations and the
production symbol table, including security-cookie and thread-sync metadata.
It preserves complete source bodies and binds external declarations through
section-free COFF metadata. These compiler artifacts are not executed.
`full_script_controls.json` records the extents; commands, native images/maps,
full disassembly and source snapshots are archived in
`build/experiments/ending_screen_caller_full_script{,_count}_2026_10_04`.

The incoming-room contract is therefore no longer the immediate blocker in
the expanded graph. Next inspect the shared animation-creation call context
and recover the complete main-menu handler at 0x42D420, currently represented
by an opaque logical declaration in the title caller. That real sibling adds
the missing title-side helper calls; do not repeat the music-only control.

## 2026-10-04 readable baseline

The earlier statement that the animation leaves themselves are unrecovered is
outdated: slot installation at 0x42C670 and frame propagation at 0x42C770 now
have selected, exact semantic models. Their private register contracts remain
relevant when adding a new caller to their compilation graph.

`reference/semantic_candidates/ending_screen_0042d300/ending_screen.cpp`
contains the complete readable 0x42D300 state machine, including phase-0
fallthrough, negative item-count handling, input mask 0x160B, and both timer
thresholds. Original MSVC 13.10.6030 compiled it successfully with the production
optimization flags and /GL; the adjacent compile.log records the result.
This is a compilation baseline, not a byte comparison or selected replacement.

Live Ghidra decompilation of both the handler and its dispatcher was checked
against the maintained retail disassembly. In particular, the misleading
`AnimationManager_QueueResource_0043dc90` name denotes `SoundQueue::Queue`:
the handler passes sound 32 in EDI, request 0 on the stack, and the queue at
0x492590 in ECX. At 0x42D3DB it passes the address of the handle at room+0x684
in EAX to StopHandle_00409e50; Ghidra's extraout_ECX is not its argument.
The frame argument at 0x42D3AD is 6, and the slot argument is 90.

Next, co-compile the complete dispatcher and real leaves. A standalone
stdcall baseline cannot establish the retail incoming EBX convention. Keep
the complete 268-byte body and 20-byte switch table accounted for when making
that cluster; no production ownership changes were made here.

### Complete caller and leaf-visibility controls

The candidate directory now also contains the complete readable dispatcher
`title_dispatcher.cpp`, including the 900-frame idle-demo path, replay header
and first-present-stage selection, signed modulo-four demo rotation, title
resource retirement, transition-dependent menu setup, all 17 dispatch modes,
and the final timer increment/conversion. Every recovered branch was checked
against `src/game/title_menu_runtime.cpp`; the private EDX return from the
timer's conversion is not modeled as an additional C++ result.

`native_leaves.cpp` supplies complete lookup, timer reset/target/owner, handle
stop, slot install/frame, sound queue, and resource-removal bodies. It includes
maintained sources where possible; copied lookup and timer bodies identify
their maintained origins. This is a source-visibility control, not a production
cluster. Remaining external logical declarations are bound to original code
addresses using section-free COFF symbol metadata. There are no implementation
stand-ins, byte patches, or inline assembly. The images are compiler artifacts
and are not executed: opaque declarations do not express the retail private
contracts. No address-aligned exact comparison has been claimed.

Run from the repository root:

```
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py opaque
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py leaves
```

Both controls compile with and without /GL and link successfully using the
original toolkit. Measured complete contributions, including embedded switch
tables, are recorded in `caller_controls.json`:

| Context | Dispatcher | Ending handler |
| --- | ---: | ---: |
| Opaque leaves | 1072 | 264 |
| Visible complete leaves | 1096 | 288 |
| Retail owned regions | 1128 | 288 |

In the visible-leaf control, the dispatcher holds its room in EBX, and the
handler moves its incoming EAX room to EBX. The handler therefore still pushes
and restores EBX, unlike retail's implicit incoming-EBX contract. It also
preserves ESI early and uses a zero in ESI. Slot installation retains room
implicitly in EBX and index in EDI rather than retail's stack room / EDI index.
Equal contribution extent is not equal bytes.

The next concrete control is to add the complete existing music-room caller
at 0x433EF0, which calls the same slot/frame helpers. A single title-only graph
has changed their private conventions. Also recover the real outer caller of
0x42CDF0 before removing its forced public stack entry. Artifacts and complete
source snapshots are in `build/experiments/ending_screen_caller_{opaque,leaves}_2026_10_04`.

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
