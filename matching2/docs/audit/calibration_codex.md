# Codex static calibration review

Baseline: `895c4202387d1c6099cf0cec2e8798bdae6a1754`. This is **six implementation rows across five retail addresses**, with four rows containing confirmed semantic mismatches and two showing valid-state semantic agreement. One mismatch row propagates another row's dependency defect; these counts are not independent bug counts. This is a bounded calibration, not a full repository audit.

The matching C++ bodies, declarations, direct source callers/bindings, complete IDA function bodies and assembly, and raw Ghidra references were inspected. Assembly resolves hidden register arguments and floating spills that pseudocode obscures. Existing audit verdicts were not used as evidence. No retail executable was run. All 22 baseline source/reference files used for this review were byte-compared with the commit; their SHA-256 hashes and structured findings are in [calibration_codex.json](calibration_codex.json).

| Address | Implementation | Result | Integration evidence and limits |
|---|---|---|---|
| `0x0044C350` | `Easing_Evaluate` | Valid-state mathematical agreement; precision unproved | Called by `src/math/param_block_interp.cpp:135`; no production `ParamBlockInterp_Tick` caller found. |
| `0x0044C350` | `Trajectory_EaseFraction` | Confirmed wrong formulas in modes 11 and 12 | Bound in `src/game/bullet.cpp:242`; used by the transform path called from `standalone/host_stage.cpp:1315`. Script activation untested. |
| `0x00412AC0` | `Trajectory_Evaluate2D` | Confirmed dependency mismatch; conditional timer rounding discrepancy | Four raw-record calls in `src/game/bullet.cpp:246,252,258,264`. Native 64-bit probe uses typed records, not the retail-layout bridge. |
| `0x0042B9C0` | `ScorePopup_Enqueue` | Valid-state semantic agreement as an adapter | No production call found; raw layout and return ABI differ from retail. |
| `0x00420100` | `VersionMarker_Load` | Confirmed wrong probe filename | No production call or callback provider found. Archive-open side effects remain unverified. |
| `0x004135D0` | `FpsCounter_Render` | Confirmed stale FPS snapshot; incomplete print interface | No production call or callback provider found. No claim of observed on-screen failure. |

## Findings and positive controls

**Easing:** IDA C at `ida/th10.exe.c:67761`, assembly at `ida/th10.exe.asm:112590`, and `decompiled/ghidra_raw/0044C350_FUN_0044c350.c` agree on the complete mode table. Constants are defined at assembly lines 163280–163284. `src/math/easing.cpp:6` implements the same mathematical expressions. Its `double` intermediates and `float` return still do not preserve the retail x87 ST0 contract; dyadic checks do not prove bitwise equivalence for general input.

`src/game/trajectory_evaluate.cpp:130` gives mode 11 a cubic expression centered on `2t-1`; assembly `loc_44C49F` at line 112728 instead uses quartic ease-in/out. Mode 12 at source line 135 shares the cubic mode-13 expression, while assembly `loc_44C404` at line 112669 uses a quadratic. The executable probe reproduces these exact, precision-independent counterexamples:

| Mode | Elapsed / duration | Baseline trajectory result | Assembly-derived mathematical result |
|---|---|---|---|
| 11 | 2.5 / 10 | 0.9375 | 0.03125 |
| 11 | 7.5 / 10 | 0.9375 | 0.96875 |
| 12 | 2.5 / 10 | 0.4375 | 0.375 |
| 12 | 7.5 / 10 | 0.5625 | 0.625 |

The probe also checks modes -1 through 18 at ratios 0, 1/4, 1/2, 3/4 and 1: **100** mathematical controls for `Easing_Evaluate` and **90** for the trajectory helper excluding modes 11/12. All pass. Passing this small grid establishes only those examples plus the inspected mathematical structure.

**2D trajectory:** Complete references are IDA C lines 22408–22576, assembly lines 25301–25541, and `decompiled/ghidra_raw/00412AC0_FUN_00412ac0.c`. Timer updates, completion snap, lazy initialization, modes 7/17, Hermite basis, and generic blend agree structurally for finite inputs with valid pointers and no output/state aliasing. Four probe controls exercise integration, completion, Hermite, and acceleration ordering. Binding the actual production easing helper with mode 12, duration 10, elapsed 1.5 before a unit tick, start X=0 and target X=16 produces **7**, while the assembly-derived formula gives **6**.

There is also a numeric conversion boundary: assembly lines 25339–25344 perform `fadd`, `fst` into the elapsed field, then `__ftol2` on the retained x87 value. The C++ converts the rounded elapsed field. With elapsed `nextafter(1.0f,0.0f)`, speed `2^-25`, current 0 and duration 10, the native probe stores elapsed 1 and sets current **1**; truncating the unrounded extended sum gives **0**. This discrepancy is conditional on x87 precision above binary32 and nearest rounding. The retail control word was not established or exercised. General spill-order differences in Hermite/blending, exceptional values, aliasing, and actual script reachability remain open. `Trajectory2D` is 60 bytes only with 32-bit pointers; the native probe does not validate the raw casts in the production caller.

**Score popup:** IDA C at line 42030, assembly at line 61502, and `decompiled/ghidra_raw/0042B9C0_FUN_0042b9c0.c` agree on least-significant digit first, any negative value becoming the single glyph 10, zero, wrap at 720, active/count/color/position writes, and lazy timer publication. The probe exercises these and preservation of an already initialized speed pointer. Agreement assumes a nonnegative ring index and nonaliasing position. Negative-index normalization is an added defensive behavior. The return pointer is an adapter API: retail EAX retains position Y's bits. The C++ record has active at +48 and stride 52 on 32-bit, whereas retail has active at +56 and stride 64; its queue header differs too. No raw-layout equivalence or connected production queue is claimed.

**Version marker:** `src/app/version_marker.cpp:10` passes **`th10.ver`**. Assembly line **45173** explicitly loads **`th10.dat`** into EAX before `sub_434C30`, with ECX pointing to `dword_497990`. IDA C line 33115 confirms the name; raw Ghidra omits that hidden filename register and cannot establish it independently. The probe captures the baseline wrong string. Generated `th10_0100a.ver`, return values, and pointer/size publication are positively checked for probe failure, load success and load failure. This assumes the loader writes its size output; the C++ initializes the local size where retail does not. The callback interface must also account for opening/populating the archive, not merely existence. Existing `tests/game_mode_transitions_test.cpp:14` asserts the incorrect `th10.ver` literal, so its passing result is not evidence that the literal matches retail.

**FPS render:** Assembly calls the update at line 26487 and subsequently loads `[edi+34h]` at line 26491. The C++ `fps` value was already copied before its callback runs. The probe changes FPS from 20 to 60 inside the update and captures **red**, while the retail order with thresholds 30 and 40 selects **white**. Assembly lines 26512–26525 also pass the FPS as a double and position `(590,470,0)` to the printer; the C++ callback accepts only the format. A global-reading adapter might supply missing printer data, but none was found and it would not repair the stale color input. Threshold constants are at assembly lines 163349/163361. Controls verify the finite threshold boundaries, white restoration, shutdown/null-thread suppression, update invocation, return 1 and frame accumulation. NaN behavior, integer overflow, arbitrary thresholds/skip counts and callbacks mutating other globals are outside those controls. Raw Ghidra drops print arguments; assembly is necessary here.

## Reproduction

Run from the repository root. This is an **observation probe**, intentionally separate from the ordinary acceptance tests: exit 0 means the documented baseline behavior, including defects, was reproduced. A subsequent correct fix should make these baseline assertions fail and require replacing them with retail-derived acceptance tests.

```sh
g++ -std=c++17 -O2 -Wall -Wextra -Werror \
  -D__fastcall= -D__stdcall= -D__cdecl= -D__thiscall= '-D__declspec(x)=' \
  -Imatching2/include matching2/tests/audit_calibration_probe.cpp \
  matching2/src/math/easing.cpp matching2/src/game/trajectory_evaluate.cpp \
  matching2/src/game/score_popup.cpp matching2/src/app/version_marker.cpp \
  matching2/src/app/fps_counter.cpp -o /tmp/th10-audit-calibration-probe
/tmp/th10-audit-calibration-probe
```

Verified with GCC 16.2.1 (`20260810`) on native Linux x86-64, at `-O0` and `-O2`, exit 0. Final output: `BASELINE OBSERVATIONS REPRODUCED (not retail equivalence)`. The long-double/power expressions are mathematical models at dyadic inputs and a retained-sum model; they are not an x87 emulator. No production files were changed by this review.
