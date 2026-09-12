# Game-state/thread destructor recovery (0x00401260, 0x00402440)

Neither region was promoted. Both production sources remain their original exact
assembly implementations, and no manifest entry was changed.

## Recovered behavior

`DestroyGameThread` (`0x00401260`, 467 bytes) installs vtable `0x0046CB14`,
removes scheduled callbacks held at offsets `0x0C`, `0x10`, and `0x89A8` under
the scheduler critical section, releases three animation-manager resources,
clears global `0x004776E0`, and destroys the embedded `Entity` members at
`+0x3C0` and `+0x14`. The normal-path entity destruction is inlined as release
and nulling of the allocations at `+0x718` and `+0x36C`.

`DestroyGameState` (`0x00402440`, 499 bytes) removes scheduled callbacks at
`+0x08`, `+0x0C`, and `+0x2A40`, frees and nulls allocations at `+0x10`,
`+0x2A44`, and `+0x17C`, conditionally releases the indexed animation resource
selected by `((state[0x2A30] & 1) + 4)`, and clears globals `0x004776E8` and
`0x004776E4` when they point at this state. It then destroys two typed `Entity`
arrays in reverse construction order: three elements at `+0x1F08`, followed by
eight elements at `+0x180`; each element is `0x3AC` bytes.

## Retail EH/compiler evidence

The destructors are compiler-generated EH shapes, not merely explicit cleanup
sequences:

- Game-state handler thunk `0x004652D6` references FuncInfo `0x00471324` and
  unwind map `0x00471314`. Its actions at `0x004652A0` and `0x004652BB`
  destroy the eight- and three-element arrays respectively.
- Game-thread handler thunk `0x004652F9` references FuncInfo `0x00471350` and
  unwind map `0x00471340`. Its actions at `0x004652E0` and `0x004652EB`
  destroy the embedded entities at `+0x14` and `+0x3C0`.
- Both retail bodies begin with the optimized frameless VC7.1 registration
  sequence (`push -1`, handler thunk, previous `fs:[0]`) and maintain an unwind
  state slot. The state destructor calls the EH-aware 72-byte vector destructor
  iterator at `0x004525FF`.

The repository's supported compile flags omit `/GX`/C++ unwind semantics. A
typed native-LTCG candidate built with those supported flags therefore omitted
the entire retail EH registration, state transitions, and unwind metadata.
Adding `/GX` in a task-local diagnostic made VC7.1 emit the retail-family
frameless prologue, unwind-state writes, `__ehhandler` thunk, `.xdata`, and
calls to the EH-aware `??_M` vector destructor helper. This independently
confirms both the typed-array reconstruction and the missing compiler profile.

## Focused probe results

The retained assembly baselines are independently exact at their full extents:

- `0x00401260`: `467/467` exact.
- `0x00402440`: `499/499` exact.

The best readable typed native-LTCG candidates under the supported profile
were not retainable:

- `0x00401260`: candidate extent 360 versus retail 467; first mismatch `+0x0`
  (`83 EC 0C 53 8B 1D B4 60 ...` versus retail
  `6A FF 68 F9 52 46 00 64 ...`).
- `0x00402440`: candidate extent 418 versus retail 499; first mismatch `+0x0`
  (`51 53 8B 1D B0 60 46 00 ...` versus retail
  `6A FF 68 D6 52 46 00 64 ...`).

Secondary differences after enabling EH remain the custom resource-release ABI
at `0x00447810` (resource in `EDI`) and exact scheduling of the three thread
resource slots. Scheduler removal itself is already an exact read-only
dependency and was not modified.

## Next dependency

Retry only when a task-local layout can select the VC7.1 `/GX` profile and own
or bind the generated handler thunks, FuncInfo/unwind data, and EH-aware vector
iterator as one bounded native-LTCG topology. Then reproduce the `EDI` resource
release call sites and the retail unrolled resource order before probing each
destructor independently.
