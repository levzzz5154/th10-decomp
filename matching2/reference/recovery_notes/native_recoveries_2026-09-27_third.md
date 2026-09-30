# C++ recovery checkpoint, 2026-09-27, third checkpoint

Nine more routines, totaling **1,918 bytes**, are integrated as readable C++
without inline assembly, naked bodies, or encoded instructions. Across the
[first checkpoint](native_recoveries_2026-09-27.md),
[addendum](native_recoveries_2026-09-27_addendum.md), and this checkpoint,
**31 routines / 4,468 bytes** have been recovered. Each new routine passes a
normal probe over its complete retail contribution at the original address.

| Entry | Bytes | Recovered operation | Detail |
| --- | ---: | --- | --- |
| 0x00407560 | 305 | Update effect acceleration and timer | [Recovery note](effect_accel_00407560_exact_2026-09-27.md) |
| 0x0040B1B0 | 147 | Create animation with callbacks | [Recovery note](animation_public_callers_0040b1b0_0041fdd0_native_2026-09-27.md) |
| 0x00413A20 | 289 | Set up score task resources and clock | [Recovery note](score_task_setup_00413a20_native_ltcg_2026-09-27.md) |
| 0x00420EA0 | 118 | Replace the UI worker under its critical section | [Recovery note](game_ui_thread_spawn_00420ea0.md) |
| 0x00421070 | 268 | Mark queued animations for cleanup | [Recovery note](queued_animation_cleanup_00421070_00421300_exact_2026-09-27.md) |
| 0x00421300 | 269 | Mark queued animations for release | [Recovery note](queued_animation_cleanup_00421070_00421300_exact_2026-09-27.md) |
| 0x00421B90 | 77 | Compute a staged three-vector cross product | [Recovery note](vector_cross_00421b90_exact_2026-09-27.md) |
| 0x00427B50 | 181 | Allocate and initialize an indicator pool slot | [Recovery note](public_leaf_pair_00427b50_0042c920_2026-09-27.md) |
| 0x0044A4E0 | 264 | Poll WinMM or DirectInput joystick buttons | [Recovery note](joystick_poll_0044a4e0_exact_2026-09-27.md) |

Two routines compile directly as ordinary MSVC C++. The other seven are
selected from six native-LTCG units. Score setup and UI thread creation extend
existing registered clusters; all their previously selected functions remain
exact. The compiler contexts and ABI anchors are excluded from recovered
output. Complete allocator, initialization, Find, positioned-creation, and
logger anchors were also checked where available.

Joystick polling uses the ordinary fastcall ABI: pad index in ECX, shared
128-byte output buffer returned in EAX. Its WinMM and DirectInput records are
distinct, and the DirectInput state is intentionally not preinitialized.
The WinMM import alias is explicitly retained in the maintained manifest.

The cross product uses conventional C++ formal `left x right`. Its actual
compiler convention places **formal left in EDX**, **formal right in ECX**,
and destination in EAX, returning that pointer in EAX. Independent execution
of the original retail bytes, including aliasing cases, and disassembly of
the compiler context confirm these operand roles. Ghidra's earlier reverse
cross interpretation used ECX-first labels and was correct for those labels.

Whole-executable verification **passed**: all **2,246 maintained build units**
completed without failure, and the full **487,936-byte executable equals the
stable retail oracle byte for byte**. SHA-256:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

The manifest and full hash gates passed. The audit checks all **3,882 current
project input files** against the build report, all nine selected sources for
assembly, and all six affected native units for zero masking and zero
instruction or address-operand rewrites. The retail executable supplies no
build instructions. Proof artifacts are under
`matching2/build/experiments/`:

- `native_recoveries_2026-09-27_third_build.log`
- `native_recoveries_2026-09-27_third_audit.py`
- `native_recoveries_2026-09-27_third_verified.json`
- `native_recoveries_2026-09-27_third_ghidra_before.json`
- `native_recoveries_2026-09-27_third_ghidra_verified.json`

An independent source review found no material issues in the sources, layouts,
ABIs, offsets, or comments. Recovery plate comments were saved and read back
for all eight available Ghidra Function heads. 0x0040B1B0 remains a raw
fragment with retained evidence; no function object was invented for it.

Current manifest totals are **1,638 semantic regions / 74,801 bytes** and
**1,140 assembly regions / 314,297 bytes**. The semantic classification still
includes three earlier render functions containing inline assembly:
0x00442670, 0x00442AD0, and 0x00443B60. These remain part of the full goal.

The full goal remains active. Three additional candidates retain measured
residuals in scratch and remain assembly in the maintained manifest:

- **0x00441950, integer interpolator:** the natural model emits 367 of the
  required 370 bytes. The limit spill and Hermite term scheduling remain
  different; a volatile experiment emits 371 bytes without correcting them.
  Its genuine 576-byte easing anchor is independently exact.
  [Recovery note](integer_interpolator_00441950_2026-09-27.md).
- **0x0042C920, progress-storage constructor:** the complete 204-byte candidate
  has displaced ESI/EDI saves. Removing saves for diagnostic alignment does
  not constitute a passing probe.
  [Recovery note](public_leaf_pair_00427b50_0042c920_2026-09-27.md).
- **0x0041FDD0, title effects:** the closest candidate emits 219 of 220 bytes,
  with a different choice of owner versus cached field-pointer register.
  [Recovery note](animation_public_callers_0040b1b0_0041fdd0_native_2026-09-27.md).

Earlier measured residuals also remain unresolved; this checkpoint does not
claim completion of the executable's C++ decompilation.
