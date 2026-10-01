# Runtime callback and four helpers

The subsequent [file-opening checkpoint](file_open_and_resolve_2026-10-01.md) recovers two additional functions / 360 bytes. Counts below describe this five-function checkpoint; its manifest and report snapshots are retained with the evidence.

Five complete functions, totaling **1,614 bytes**, now compile as readable C++ without inline assembly. The maintained executable matches all **487,936 bytes** of the original. Recovery is **1,859 semantic functions / 99,587 bytes**, with **439 assembly functions / 223,311 bytes** remaining. Excluding the five semantic functions still containing inline x87 leaves **1,854 fully assembly-free functions / 95,136 bytes**. The full decompilation goal remains incomplete.

| Function | Address | Complete bytes | Original native contract |
| --- | --- | ---: | --- |
| `BulletRuntimeTick` | `0x00406240` | 885 | State on stack, retained in EBP; EAX result; RET 4 |
| `PlayerHomingState_00407EF0::HomeTowardTarget` | `0x00407EF0` | 306 | State ESI; plain RET |
| `KeyConfigReassignSlot_00430250` | `0x00430250` | 200 | State EAX, slot ECX, key EDX; plain RET |
| `SoundQueue::QueuePan` | `0x0043DD10` | 149 | Queue ESI, sound ID EBX, pan on stack; RET 4 |
| `ReturningFrameTimer::TickReturningFrame` | `0x0044BFA0` | 74 | Timer ESI; frame in EAX; plain RET |

## Runtime callback

`matching2/msvc/src/game/bullet_runtime_update.cpp` preserves the state switch, three position integrations, optional motion helpers, immunity timer, field contact effects, sound, wrapping, bounds, countdowns, and animation update. Flag 8 immediately resets both scheduler links and returns -1. Modes 3 and 2 integrate at half velocity; mode 2 can enter mode 1 during the same tick when animation progress is nonzero. Contact 1 enters mode 3 and optionally creates the death effect. Contact 2 creates animation 434 and queues sound 28 once, guarded by flag 4. Failed bounds or nonzero animation results reset the scheduler links and return -1; otherwise the result is zero.

The typed state asserts original position, velocity, motion-flag, mode, and immunity-timer offsets. `MotionVector3` retains the constructor/operator evaluation that reproduces x87 arithmetic and temporary stores. All 20 direct calls retain their original targets and private register contracts. Writing retirement in both failure paths lets native LTCG share the original terminal block.

This cluster selects only the 885-byte callback. Its fourteen complete genuine helper models live under `layout/ltcg/bullet_runtime_dependencies`, preserving every existing helper's owner. The evidence measures all unselected bodies, including nonexact wraps, DeathShrink, EaseStep, and resource-loading/registration/allocation anchors. Exactness of the caller does not establish recovery of those helpers, and their bytes are not substituted into the maintained executable.

## Homing

`matching2/msvc/src/game/player_homing_00407ef0.cpp` computes the direction in double precision, uses the original quarter turn for a zero direction, and compiles ordinary `atan2` directly to FPATAN. It adds the heading offset at `+0x7CC`, scales the wrapped angle difference by `+0x7C8` and frame scale, normalizes the heading, and calls the genuine polar setter. At deadline it clears flag `0x04000000`. The timer at `+0x7B4` always advances. A volatile clock-pointer read retains the original left-operand evaluation in the scaled branch. All 306 bytes match, including genuine angle, polar, and conversion calls. The field is named `heading_offset_7CC`; it is not a clamp.

## Key reassignment

`matching2/msvc/src/game/key_config.cpp` returns when the selected key is unchanged. Five explicit duplicate tests preserve the original swaps: the first uses the cached old selected key; the others reload the selected binding. It stores the signed-short key, calls real Refresh at `0x0042F8B0`, and calls the sound queue at `0x0043DC90` for event 10 with request zero. Complete helper visibility gives native LTCG the original EAX/ECX/EDX entry. Refresh (2,452 bytes), Queue (123), and Find (73) are exact unselected anchors. Configure's complete 356-byte model differs in six operand bytes belonging to two float addresses and remains unselected. The earlier 128-byte loop/callback candidate is superseded.

## Panned sound

`matching2/msvc/src/platform/sound_queue_pan_0043dd10.cpp` converts `pan * (1000.0f / 192.0f)` through genuine `__ftol2`. The binary32 multiplier at `0x00470B20` is `5.208333492279053`; priority metadata is a signed short at `0x004749CE + sound_id * 8`. Twelve slots merge repeated IDs, accepting up to 128 requests. A free slot receives the ID, priority indexed by sound ID, first request, and count increment. A full queue drops the request. The header checks the original ID/count/request-array offsets. The replacement cluster also preserves five previously recovered functions: all six functions / 1,816 bytes match in the maintained probe.

## Returning timer

`matching2/msvc/src/math/timer_return.cpp` copies current to previous, advances the timer, and returns the integer frame. The normal-speed branch increments current and adds one to elapsed; otherwise `current = int(elapsed += *speed)` retains the x87 sum for conversion while storing binary32 elapsed. The compiler supplies the original conversion call and instruction order. The complete 74-byte unassigned region is now recognized in Ghidra. `ReturningFrameTimer` adds no fields to the maintained 20-byte `FrameTimer`.

## Verification

The [checkpoint evidence](runtime_and_helpers_2026-10-01.evidence.json) proves complete native extents and byte identity for all five functions, four maintained focused probes, all 20 direct runtime calls, and original constants. It records complete unselected anchor comparisons with their size differences and literal residuals. Original ASM aliases and region records are preserved. The 412,672-byte `.text` partition is contiguous, and every owned source is covered by the build.

All **3,914 project-file hashes** and **3,059 native input-hash records** passed. All **1,911 maintained build units** succeeded. Native compilation uses no reference bytes; extraction changes neither instruction bytes nor address operands; no bytes are masked. Formatting and declaration cleanup were followed by the maintained 885-byte probe and whole build:

```sh
make MSVC_ARGS='--jobs 32 --verify matching2/build/oracle/th10.exe'
python3 matching2/build/experiments/panned_sound_and_timer_return_2026_10_01/verify_checkpoint.py
git diff --check
```

EXE SHA-256: `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`. `.text`: `c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`. Logs, fresh Ghidra analyses, plate-comment readbacks, and the audit script are retained under `matching2/build/experiments/panned_sound_and_timer_return_2026_10_01`.

DeathShrink, both wraps, and EaseStep remain assembly. Trigger activation's separately frozen 627-byte candidate retains six instruction-order differences and remains unpromoted. Five semantic rendering functions retain inline x87; their full 4,451-byte extents are excluded from the assembly-free count.
