# Animation stop-frame/run family

2026-10-01. Three complete assembly functions are now ordinary C++:

| Address | Bytes | Recovered function | Native entry |
| --- | ---: | --- | --- |
| 0x00449250 | 76 | AnimationManager_SetStopFrameAndRun | Frame DI, context EDX, ID on stack; RET 4 |
| 0x0042C730 | 27 | DispatchAnimationSlot | State EAX, slot ECX; plain RET |
| 0x0042C750 | 27 | DispatchAnimationSlotSecondary | State EAX, slot ECX; plain RET |

This retires 130 assembly bytes. The already classified 15-byte wrapper at
0x004494C0 was also corrected: its new `AnimationRunHandle::SetStopFrameAndRun`
method explicitly takes the inherited frame in DI and forwards the handle ID.
It is co-compiled with its real callee, rather than calling an opaque declaration
that omits that frame input. Its ownership moved from the position-wrapper source
to `src/render/animation_handle_set_stop_frame_and_run_004494c0.cpp`; this is not
counted as another newly recovered region.

## Behavior and evidence

The two state callers select the four-byte ID at state +0x2C4 + slot*4 and use
stop frames 2 and 3 respectively. The shared header exposes this table through
an opaque-state accessor; it does not assume the full state's size or table
capacity. The helper uses the genuine lookup at 0x004491C0. If found, it writes
the parent's word at +0x304 and immediately runs the animation interpreter.
Unless the parent marks its children processed at +0x18, it then follows the
child links at +0x14, writes each child's stop word and runs that child.

Fresh Ghidra disassembly confirms both slot callers' EAX/ECX inputs and EDI
constants, the helper's incoming DI, its calls to the lookup and interpreter,
and the post-interpreter child-flag test. The helper reloads each child object
for the interpreter call after storing its stop word; the C++ preserves this
alias-sensitive ordering. Compile-time checks cover four-byte IDs/handles and
the stop word, child head and child-flag offsets.

The interpreter at 0x0043EE30 is a genuine one-pointer stack argument / RET 4
external. It remains the separately owned 9,964-byte assembly region. There is
no private dispatcher stand-in in this batch. The genuine 73-byte lookup is
selected and checked together with all callers. Ghidra has no function boundary
at 0x004494C0; that wrapper's full 15-byte extent and inherited DI flow are
verified independently from the retail byte listing and native caller/callee
comparison.

## Native cluster and source shape

The existing `stop_at_frame_pair_0040c480` cluster now owns these four complete
functions in addition to its ten earlier recoveries. Every selected function
retains its original complete extent and retail address. The old position-wrapper
cluster retains its two original 15-byte functions. Its compiler context was
remeasured at 57 bytes after the stop/run wrapper moved out. Synthetic contexts
and layout gaps are unselected and contribute no recovered bytes.

The first paired slot model declared state before index. It emitted the correct
27-byte functions except for one byte in each address calculation: native used
`[ECX+EAX*4+0x2C4]`, while retail uses `[EAX+ECX*4+0x2C4]`. Declaring index
before state lets LTCG choose the retail entry registers and matches both complete
functions without changing the helper or any earlier recovery.

A scalar local ID in the corrected handle wrapper loaded and pushed EAX, causing
two differing bytes. An ID stored directly as the four-byte `AnimationScriptId`
record, or a reference to that record, loads and pushes ECX and matches the full
15-byte wrapper. The maintained source uses the directly typed record and its
explicit frame argument. No instruction rewriting, address rewriting, masks,
inline assembly or assembly shim was used.

## Verification

The final production probe checks 16 complete functions / 844 bytes, covering
all fourteen members of the lookup/stop/run cluster and both remaining position
wrappers. Every comparison is exact. The full production build then compares
all .text and all 487,936 executable bytes with the independent reference.
The companion evidence JSON records source fingerprints, native compiler
provenance, exact comparisons, Ghidra evidence and whole-image verification.

```sh
python3 matching2/tools/matching/probe.py \
  --source src/render/animation_manager_set_stop_frame_and_run_00449250.cpp \
  --source src/unidentified/unassigned_anim_setters_00449.cpp
make MSVC_ARGS='--jobs 32 --verify matching2/build/oracle/th10.exe'
make progress
```

Scratch evidence and rejected parameter/handle forms are retained under
`matching2/build/experiments/stop_frame_run_2026_10_01`. Accounting is 1,844
semantic regions / 96,583 bytes and 455 assembly regions / 226,314 bytes.
Some semantic rendering sources still contain inline x87 blocks. The complete
no-inline-assembly decompilation goal remains unfinished.
