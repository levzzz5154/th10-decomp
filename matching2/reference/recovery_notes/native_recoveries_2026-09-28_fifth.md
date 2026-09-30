# C++ recovery checkpoint, 2026-09-28, fifth checkpoint

**The final combined executable and all current-input hash gates passed.**
The four complete routines below are integrated and pass their maintained normal
probes as readable C++ without inline assembly. They total **1,345 bytes**.
Across the preceding four checkpoints and these routines, **47 routines /
11,711 bytes** have been recovered. The separately corrected return contract at
0x00449450 adds no recovered bytes.

| Entry | Bytes | Recovered operation | Detail |
| --- | ---: | --- | --- |
| 0x004089C0 | 211 | Initialize player manager tasks and embedded timer | [Recovery note](player_manager_tasks_004089c0_native_2026-09-27.md) |
| 0x00420540 | 302 | Write screenshot BMP headers and pixels, then release buffers | [Recovery note](screenshot_writer_00420540_2026-09-27.md) |
| 0x0043A750 | 436 | Construct the observed multimedia timer-state prefix | [Recovery note](timer_constructor_0043a750_2026-09-27.md) |
| 0x0043C970 | 396 | Select nine screen effects and register update/draw tasks | [Recovery note](screen_effect_selector_0043c970_2026-09-28.md) |

The screenshot writer compiles through ordinary MSVC C++. The other three
routines are selected from native-LTCG units. Their public source declarations
and complete compiler contexts reproduce the observed native conventions:
player manager owner EBX with zero EAX/plain RET; timer constructor receiver ESI
with returned receiver EAX/plain RET; and screen controller ESI, draw priority
EBX, five stack arguments and RET20. The screenshot callback retains the genuine
`void __cdecl(void*)` thread-entry signature and ignores its argument.
Compiler contexts, dependency anchors and layout gaps remain unselected and
add no recovered bytes. Three new clusters bring the registered total to 686.

The screenshot recovery preserves all three writes and retail's repeated
close/unlock/depth-decrement branches when the shared handle remains stored
after a short write. It always releases both temporary buffers and clears the
thread handle. The timer type describes only the observed 0x2E4-byte prefix;
related MIDI code uses later fields, so this is not a full-allocation claim.
The player initializer preserves all three priorities, callback/context stores,
flag updates and lazy/reset timer writes. Its two complete 131-byte scheduler
registration anchors independently match.

The screen controller includes all 357 executable bytes, three alignment bytes,
and its nine-entry switch table. Full genuine scheduler creation and registration
models resolve retail's callback/priority ordering. The two 43-byte creation
anchors and two 131-byte registration anchors independently match. Its complete
genuine allocator caller emits 77 bytes against retail's 82 and remains
unselected; the maintained allocator is unchanged. Timer reset through a shared
three-word view preserves the observed order without assembly or barriers.

Fresh executor-caller evidence showed that `AnimationManager_00449450::ValidateHandle`
returns the object or null in EAX rather than void. The source, header, metadata,
and decorated symbol were corrected together while preserving the complete
already-semantic **21-byte body**. Independent review passed its exact scratch
probe and the full 73-byte Find anchor. The Find anchor and 46-byte synthetic
context remain unselected. The five correction files are integrated; its
maintained 21-byte probe and final combined image gate passed.

Independent source review passed all four newly selected routines and the
return-contract correction. The reviews cover ABI, offsets, complete operations,
ownership and retained compiler-input hashes, with no material issues. Reviewed
selected/dependency sources contain no inline assembly, naked bodies or encoded
instruction streams. These reviews do not replace the final executable gate.

Whole-executable verification **passed**. All **2,242 maintained build units**
completed without failure. The complete **487,936-byte executable equals the
stable retail oracle byte for byte**, with SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Its `.text` SHA-256 remains
`c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`.

The manifest and full hash gates passed. The audit compares all **3,921 current
project input files**, including the full added/deleted file set, with the build
report. It checks four new selected sources and the corrected helper for assembly,
and all four affected native units for zero masking, zero instruction changes,
zero address-operand changes and no oracle instructions used for building.
Ghidra plate comments were saved and read back for the player initializer,
screen controller and corrected helper. The screenshot writer and timer
constructor still have no Function heads; their complete bounded evidence is
retained and no Function objects were invented.

A separate preserved first-stage proof covers the first three routines
(**949 bytes**) and all 3,915 then-current inputs, before the screen controller
and return correction were added. It remains available alongside the final
four-routine proof.

Current integrated manifest totals are **1,654 semantic regions / 82,044 bytes**
and **1,124 assembly regions / 307,054 bytes**. The selected-body audit's six
partial semantic regions still contain **4,525 bytes**: two 1,111-byte sprite
submissions at 0x00442670/0x00442AD0 retain FRNDINT, two 591-byte rotated builders
at 0x004436C0/0x00443910 and the 1,047-byte projection builder at 0x00443B60 retain
FSINCOS, and the 74-byte callback allocator at 0x00449ED0 retains explicit
register assembly. Thus the integrated counts are **1,648 fully C++ semantic
regions / 77,519 bytes**, and **1,130 regions / 311,579 bytes** still containing
assembly across both classifications. The full decompilation goal remains active.

Seven substantive candidates remain unpromoted:

- **0x00449ED0, callback allocator:** full 74-byte C++ body differs in 22 bytes.
  Zero/flag register lifetimes and final publication schedule remain unresolved.
  [Residual note](scheduler_callback_create_00449ed0_native_2026-09-28.md).
- **0x0042AA50, replay pool append:** full 139-byte body differs in six bytes
  because two six-byte store/LEA operations are reversed. Its native ABI is
  established. [Residual note](replay_pool_append_0042aa50_2026-09-27.md).
- **0x004084A0, record sweep:** complete model emits 368 of 370 required bytes,
  with 246 overlap differences. x87 spills and precision remain unresolved;
  fresh retail confirms 2,000 entries. [Residual note](record_sweep_004084a0_2026-09-27.md).
- **0x00421FA0, name-history insertion:** complete model emits 317 of 316
  required bytes, with 102 overlap differences and the first 114 bytes exact.
  Copy scheduling and genuine caller ordering remain unresolved.
  [Residual note](name_entry_select_00421fa0_2026-09-27.md).
- **0x0040B9F0, emitter decision:** full 111-byte body differs in 48 bytes.
  Existing Tick and the unselected callback remain independently exact; a shared
  full tick type follow-up retained the same residual.
  [Residual note](emitter_decision_0040b9f0_native_residual_2026-09-27.md).
- **0x0041BB00, item allocator:** complete 827-byte model fails the 819-byte
  extent gate, with 754 overlap differences. Manager/position register agreement
  remains unresolved. Its full 203-byte LoadScript anchor is exact; other complete
  dependencies are unselected and nonmatching. The next lever is the genuine
  0x0041E260/0x0041F400 caller pair and polar-setter preservation contract.
  [Residual note](item_spawn_0041bb00_native_residual_2026-09-28.md).
- **0x0040BD80, ending/credits executor:** the complete model emits 1,500 of
  1,568 required bytes, with 1,300 diagnostic overlap differences, first 0040BD82.
  The normal probe rejects the original extent outside the actual MAP contribution.
  Independent review passed all 18 slots and side effects; 31 genuine full anchors
  remain unselected. The next lever is genuine diverse variadic MarkText callers
  00415E90/00419120/00433EF0 to preserve its three fixed stack arguments and
  text-loop register lifetimes. [Residual note](recovery_script_executor_0040bd80_native_residual_2026-09-28.md).

Unequal-extent overlap figures are diagnostics, not passed promotion gates.
Earlier measured residuals and prior verified checkpoints remain preserved.
No tiny exact wrapper or unselected helper substitutes for a complete target.

Proof and handoff artifacts are under `matching2/build/experiments/`:

- `native_recoveries_2026-09-28_fifth_reviews.json`
- `native_recoveries_2026-09-28_fifth_next_leads.json` and `.md`
- `native_recoveries_2026-09-28_fifth_stage1_verified.json`, full report snapshot,
  build log and partial-semantic audit (historical first-three proof)
- `native_recoveries_2026-09-28_fifth_verified.json`
- `native_recoveries_2026-09-28_fifth_port_report.json` (full report snapshot)
- `native_recoveries_2026-09-28_fifth_build.log` and `_audit.py`
- `native_recoveries_2026-09-28_fifth_partial_semantic_audit.json` and `.md`
- `native_recoveries_2026-09-28_fifth_ghidra_before.json`, `_annotate.py` and `_ghidra_verified.json`
- `native_recoveries_2026-09-28_fifth_integration.json`
