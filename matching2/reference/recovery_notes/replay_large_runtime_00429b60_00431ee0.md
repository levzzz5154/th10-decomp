# Replay-large runtime recovery

Date: 2026-09-12

## Scope and disposition

This pass covered the two owners in `src/game/replay_large_runtime.cpp`, for a
total of 3649 live bytes.  No readable semantic body was independently exact;
the maintained source was restored to retail ASM and `regions.json` was not
edited.

| Address | Live extent | Semantic role | Final state |
| --- | ---: | --- | --- |
| `0x00429B60` | 1681 | replay serialization/resource write | retail ASM retained |
| `0x00431EE0` | 1968 | replay input/menu state update | retail ASM retained |
| **total** | **3649** |  | **no promotion** |

The temporary raw-layout header, candidate bodies, and focused build outputs
were removed.  No task-local proposal remains, and no shared Python tooling or
other agent source was changed.  Existing replay-related work and concurrent
worktree changes were preserved.

## Final focused baseline

After restoration, the focused probe compiled the shared source and reported
`EXACT`, with no failures and zero different bytes:

```text
0x00429B60 1681/1681 different_bytes=0
0x00431EE0 1968/1968 different_bytes=0
total      3649/3649 different_bytes=0
```

## Evidence and extent caveat

The semantic evidence came from
`matching2/reference/legacy_semantic/src/game/replay_large_runtime.cpp` and
`include/th10/game/replay_large_runtime.hpp`, plus the prior replay-menu
recovery note and the maintained retail instruction listing in
`matching2/msvc/src/game/replay_large_runtime.cpp`.

`legacy_semantic/function_registry.json` records both addresses as having
Ghidra raw sources and semantic overlays.  Its recorded legacy size for
`0x00429B60` is 1696 bytes, while the live manifest/body extent is 1681 bytes;
`0x00431EE0` is recorded as 1968 bytes and agrees with the live extent.  The
referenced raw Ghidra files are not physically present in this checkout, so
the byte/ABI observations below are from the maintained retail disassembly
and the checked-in legacy semantic overlay, without claiming an unavailable
raw export.

## Recovered semantic behavior

### `0x00429B60` — replay serialization and resource write

The archived model calls this `Serialize`.  It treats the replay as eight
stage blobs, copies an incoming name into the eight-byte replay name field,
pads a short name with spaces, counts present stages, and constructs the
serialized payload.  The output includes a fixed header, two byte-wise
encryption passes, aligned USER text/notice chunks, formatted score/rank/
slow-rate metadata, and the stage header/command/tail data.

The retail listing confirms the corresponding stateful shape: it copies and
pads the name at manager offset `+0x18`, walks eight stage/list heads rooted
at `+0x1C` and `+0x40`, computes record counts from the stage layout, writes
the count and timing fields, allocates/copies intermediate buffers, formats
the replay text, and performs the file write under the critical-section IAT.
It calls the archive/format helpers, `FUN_004359B0`, `EncryptDatBuffer` twice,
`File_OpenSharedWrite`, `localtime`, `malloc`, and the matching free routine;
the final path checks the file-size result and unwinds the lock/counters.

The entry is not a normal `Replay&`/`name` C++ call.  Retail reserves
`0x124` bytes, protects the frame with `data_00473660` and the security-cookie
check, copies `ECX` to `EDI` and `EDX` to `ESI`, reads the stack argument from
`[esp+0x134]` after the prologue, preserves the callee-saved registers, and
returns with `ret 4`.  The exact stack-local offsets and the two encrypted
buffer lifetimes are part of the 1681-byte ownership boundary.

### `0x00431EE0` — replay input/menu state update

The archived model calls this `UpdateInputMenu`.  Its typed state tracks the
phase, selection/page, timer, previous/current input bytes, and pressed-edge
array; phase 0 initializes the menu, phase 1 waits for entry timing, phase 2
handles cursor movement and confirm/cancel, and phase 3 completes the exit
transition while dispatching event callbacks.

The retail body is a much larger menu/resource state machine than that
minimal overlay.  It dispatches four phase cases through the table at
`0x00432680`, updates state at `+0x20`, `+0x24`, `+0x28`, `+0x2C`, `+0xF0`,
`+0xFC`, `+0x104`, `+0x1D4`, `+0x1DC`, and `+0x2A4`, computes stage/progress
counts, finds or installs animation slots, advances menu cursors, queues
animation resources, creates the replay-stage list, and handles the global
keyboard snapshots at `0x00497D90`/`0x00497E90`.  It derives pressed edges
into `0x004979A8..0x004979AB`, unlocks all stages when the progress threshold
is reached, updates the progress globals, and tears down the animation/input
state on exit.

Its ABI is also mixed: the entry first preserves `ECX`, then loads the state
pointer into `EBP` from `[esp+0x0C]` after the two pushes, consumes the input
and helper state through the live register setup, and returns `ret 4`.
Consequently the phase logic cannot be compiled as an ordinary three-argument
`InputMenu` function without changing both the prologue and all nested calls.

## Dependency and ABI inventory

The serializer needs one bounded resource/serialization cluster containing
`0x00452ABC`, `0x00452AE8`, `0x004359B0`, both `0x0044B220` encryption calls,
`0x0044B620` shared-write open, `0x00452706`, `0x00452422`, `localtime`, the
critical-section IATs at `0x004660B4`/`0x004660D4`, and the lock-depth byte at
`0x0049231E`.  The stage-list pointer arithmetic and the 15-byte legacy/live
extent discrepancy must be resolved before changing the required body size.

The input/menu body depends on the custom edges for pattern counting
(`0x004088C0`), animation lookup/install/clear and primary-back creation,
timer target (`0x0042C620`), cursor advance (`0x0044BEA0`), animation
stop-frame/resource queue, replay-stage creation (`0x00432690`), keyboard
state update (`0x0044B010`), stage unlock, and input-history cleanup.  The
prior replay-menu recovery note records the important register conventions:
cursor/timer/animation helpers use EAX/ECX/EDI/ESI combinations rather than
ordinary C++ parameter order.

## Native-LTCG candidate probes and mismatch matrix

A task-local typed-layout probe implemented readable name/payload handling and
the phase/cursor/input transitions behind register-preserving bridges.  The
candidate source was never retained as production code.

| Address | Required extent | Candidate extent | First mismatch/evidence | Result |
| --- | ---: | ---: | --- | --- |
| `0x00429B60` | 1681 | 17 | extent mismatch at region entry; bridge `push [esp+4] / push edx / push ecx / call helper / add esp,0xC / ret 4`, while retail starts `sub esp,0x124; mov eax,[data_00473660]` | rejected |
| `0x00431EE0` | 1968 | 17 | independent input-only probe reached the extent gate; same three-input bridge, while retail starts `push ecx; push ebp; mov ebp,[esp+0x0C]` and dispatches the large phase body | rejected |

The combined probe stopped at the lower-address serializer region after
measuring its 17-byte bridge; a second probe kept the original serializer ASM
and measured the input-menu bridge independently at 17 bytes.  Neither body
reached byte comparison because the native bridge cannot reproduce the retail
cookie/prologue, stack locals, register lifetimes, or nested fixed-address
call shape.  Both production regions were restored and rechecked exact.

## Best next dependencies

The next productive experiment is not another ordinary semantic spelling.  It
needs a bounded native-LTCG context that preserves `ECX`/`EDX` plus the stack
argument across the serializer's frame, and separately preserves the
`ECX`-saved/state-`EBP`/`ret 4` convention for the input handler.  For
`0x00429B60`, first isolate the exact archive writer, two-pass encryption,
critical-section depth, and 1696-versus-1681 legacy extent discrepancy.  For
`0x00431EE0`, bind the cursor/timer/animation/input-history helpers as
read-only dependencies and reproduce the four-way phase table before adding
the keyboard snapshot and stage-unlock tails.  Promote either region only
after its own focused section has the exact live extent and exact bytes.
