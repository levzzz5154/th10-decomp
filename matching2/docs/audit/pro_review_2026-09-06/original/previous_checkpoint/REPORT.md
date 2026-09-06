# TH10 reconstruction audit — resumable checkpoint

**Status: partial semantic audit; partial cleanup. This is not a full-repository clearance.**

Repository: `levzzz5154/th10-decomp`  
Branch: `audit/recovery-calibration-2026-09-06`  
Requested access check: `AUDIT_START_HERE.md` at `e4315d2`, successfully read; blob `17ac0b9dce3d1f33a4f0eee193a83fc92cbb30b0`.  
Reviewed snapshot: `04a840d9228378bc793a709af493f49bffe53d74`.  
Frozen production baseline named by the handoff: `895c4202387d1c6099cf0cec2e8798bdae6a1754`.  
Applied documentation-only cleanup: `09835addae52e8eda47fc8c387a518ca7a0b4294`.

## Executive result

This checkpoint establishes **six independent source/adapter contract defects**, with explicit activation and input-domain limits. It also preserves **two conditional floating-point concerns**, five narrowly supported observations, and five other unresolved rows. The highest-priority integration issue is the bullet ANM provider's loss of per-VM/per-variable state. The most thoroughly exercised arithmetic issue is the four-step RNG's reversed return-word order: **all 65,536 seeds differ from the instruction-derived return oracle**, under both GCC and Clang, while the final seed and generation agree.

No production implementation was changed. The only repository modification distinguishes the optional five-packet calibration heading from the full-repository audit and preserves its old link fragment. No reference exports, historical evidence, tests, assets or code were deleted.

This work does **not** establish full-game equivalence. It does not complete the 722-address implementation inventory, 551-file queue, 1,717 indexed reference starts, full opcode tables, or reference-boundary reconciliation. These scopes remain explicitly unresolved. Reading a dispatcher or inventory does not certify its contents.

The machine-readable `ledger.json` contains 18 detailed findings, exact source blob hashes, dependency/reference hashes, inspected source ranges or original instruction addresses, input domains, assumptions, production reachability, counterexamples, positive controls, corrections and regression requests. The full scope sets are incorporated by immutable path and blob hash, not expanded into a fabricated per-item completion ledger.

## 1. Priority findings

### ANM-001 — bullet VM variable slots alias across variables and instances

**Verdict:** confirmed provider-contract mismatch; high priority if activated by the loaded scripts.

`matching2/standalone/host_stage.cpp:883–896` implements `BulletVmIntSlot` and `BulletVmFloatSlot` with a single function-static fallback per type. Both ignore the VM and variable ID. By contrast, the original integer and float slot resolvers at `0x0043EDA0` and `0x0043ED00` return distinct offsets inside the particular VM. Examples include integer variables at `VM+0x30C` and `VM+0x310`, and float variables at `VM+0x31C` and `VM+0x320`.

A minimal isolated probe writes integer variable 10000 of VM A to 7, then variable 10000 of VM B to 9. Reading A's slot now gives **9**, not **7**. Different integer IDs in the same VM alias too, as do float slots. Both compilers reproduce this. These are separate callback bodies but **one independent storage-design defect**, not four defects.

This is not merely an unused test provider: `g_bullet_vm_hooks` binds these callbacks at lines 948–966; `HostBulletPoolTick` invokes `AnmVm_Tick` with that table; `HostInitBulletPoolRuntime` installs the bullet update callback. That establishes static production wiring. It does **not** establish which variable instructions are activated by the actual `bullet.anm` assets. The comment claiming a restricted opcode slice is not evidence of unreachability.

**Correction:** provide instance-owned slots for the original supported IDs, with faithful fallback and mask semantics. **Regression:** use two VMs and at least two IDs of each type, then exercise the actual dispatcher rather than only calling the provider. Confirm activation against the supported assets and trace lifetime/draw effects.

### ANM-002 — integer variable reads return encoded IDs as literals

**Verdict:** confirmed provider-contract mismatch; high priority if activated.

`BulletVmReadInt`, `host_stage.cpp:865–873`, ignores `is_variable` and the VM and simply copies the argument bits. A masked variable argument encoding **10000**, whose VM value is **7**, therefore returns **10000**, not **7**. The original reader at `0x0043EC70` reads the VM field for that ID. Literal integer 7 is a positive control: both behaviors return 7 when no variable resolution is requested.

The same production table and activation limitations apply as for ANM-001. The literal-only float callback is suspicious too, but its complete special-ID contract is retained as **unresolved**, not counted as another established defect.

**Correction:** honor variable-reference masks and the original integer-ID map. **Regression:** compare the same operand bits with the variable flag clear/set, then cover each supported ID and unknown-ID fallback. Storage isolation and operand resolution must be tested separately so one fix cannot hide the other defect.

### RNG-001 — four-step RNG returns its first two words in reverse order

**Verdict:** confirmed mismatch; medium priority pending production reachability.

`matching2/src/math/rng.cpp:49–57` advances four times and returns `(first << 16) | second`. At original `0x0044BA80`, instruction `0x0044BAAD` stores the first word at `[ESP]`, `0x0044BACC` stores the second at `[ESP+2]`, and `0x0044BB07` loads that dword into EAX. The required result is therefore **`first | (second << 16)`**. The raw and saved Ghidra exports corroborate the ordering with their concatenation expression; they are distinct snapshots, not independent function-discovery proofs.

For seed 0 and generation 0:

| Quantity | Source | Original instruction-derived expectation |
|---|---:|---:|
| Return | `0xC374BFC7` | `0xBFC7C374` |
| Final seed | `0x7D40` | `0x7D40` |
| Final generation | 4 | 4 |

Both GCC 14.2 and Clang 17 reproduce **65,536/65,536 wrong returns**, with **zero final-state mismatches**. This exhausts the seed domain at generation 0. It does not prove caller reachability or the global ordering of RNG calls. In particular, the source comment stating that no retail caller remains was not independently proven.

**Correction:** change only the packed return ordering while preserving four advances and counter semantics. Correct the inaccurate “two calls, keep first” comment. **Regression:** retain exhaustive seed coverage with a stack-word oracle and independently check state/counter, rather than deriving expected values from the reconstruction itself.

### TIMER-001 — decrement helper drops the original count argument

**Verdict:** confirmed general-contract mismatch; medium priority, adapter restrictions unproved.

The original `0x00428DD0` receives a count in EAX, negates/converts it and delegates to the advance helper. `FrameTimer_Decrement`, `timer.cpp:38–42`, has no count parameter and always advances by `-1.0f`.

With current/elapsed 10 and unit speed, original count **0** leaves current **10**; the source produces **9**. Count **2** should produce **8**, while the source again produces **9**. Count **1** is the representative positive control and agrees.

A deliberately restricted unit-decrement helper can be useful, but it must not silently stand in for the general credited original function without a verified adapter invariant. Complete call-site/ABI closure was not obtained.

**Correction:** restore the count contract, or separate and explicitly constrain the unit helper. **Regression:** test count 0, 1, 2 and bounded negative counts through the PE32 calling convention, including previous/current/elapsed and stack behavior.

### TIMER-002 — owner-timer reset invents target/speed behavior

**Verdict:** confirmed general-contract mismatch; medium priority, consumer restrictions unproved.

`GameState_SetTimerTarget`, `timer.cpp:44–59`, writes `target - 1` at owner offset `0x2B0` and accepts a supplied speed pointer. The original `0x0042C620` unconditionally resets that field to **-1** and installs the shared global speed pointer on first initialization.

With initialized flags and source target **1**, the source stores **0** where the original stores **-1**. Target **0** is a positive control. Owner-value publication and the zeroed timer fields do not repair the differing previous value.

The native probe deliberately uses the initialized path. It does not exercise a 32-bit pointer store at the original offset under a 64-bit ABI. Production might restrict arguments to target 0/shared speed, but that restriction was not established.

**Correction:** implement the original reset contract or document and prove the restricted adapter at every consumer. **Regression:** test initialized and uninitialized PE32 objects, retained initialized speed pointers, exact shared-global selection, flags, surrounding canaries and all relevant field writes.

### RNG-002 — signed counter increments do not define original wrapping behavior

**Verdict:** confirmed language-domain mismatch; low priority until overflow reachability is measured.

`RngState::generation` is signed, while `rng.cpp:41,55` performs `+=2` and `+=4`. Original dword ADD instructions wrap. With generation **2,147,483,646** for the two-step call or **2,147,483,644** for the four-step call, both source probes terminate with an explicit UBSan signed-overflow diagnostic. The original counter result has bits `0x80000000`.

This is **one independent arithmetic-domain defect**, inherited by both float wrappers. It is not four newly observed gameplay bugs. Generation 0 gives the expected increments; ordinary play reaching the overflow boundary remains unmeasured.

**Correction:** define unsigned 32-bit wrapping arithmetic and preserve documented layout/representation at consumers. **Regression:** test wrap boundaries and subsequent calls without changing seed/output order; verify ABI layout and the absence of sanitizer overflow.

## 2. Conditional floating-point findings — not unconditional bugs

### FP-001: `FrameTimer_Tick`, original `0x00404ED0`

The non-normal-speed path stores elapsed with **FST without popping ST0**, then converts the retained value. Source code can instead convert the already rounded binary32 field. For `elapsed=0.9f`, `speed=0.1f`, the native source stores 1 and sets current **1**. The instruction-derived x87 microprobe also stores 1 but gives current **0** at 53- or 64-bit precision; at 24-bit precision it gives **1**, agreeing with the source.

### FP-002: `FrameTimer_Advance`, original `0x0044BF40`

This original function **does store and reload before integer conversion**; do not conflate it with Tick. Its retained multiply/add product can still change stored elapsed. With `elapsed=-0.01f`, `speed=0.1f`, `delta=0.1f`, source elapsed bits are **`0x30800000`**, versus modeled **`0x300F5C29`** at 53/64-bit precision. Both current values are zero. The 24-bit model agrees with source.

These native x87 microprobes explicitly select precision and use FISTTP to model valid, in-range truncation. They are **not executions of the retail process or the original complete conversion helper**. Original global bytes, live control words, exception state and rebuilt PE32 machine code still need verification. No unconditional production failure or unconditional floating-point fix is claimed.

## 3. What is supported, and only within which limits

`Rng_NextU32` agrees on output and state for every seed at generation 0. The final **stored binary32** outputs of both float wrappers agree for every seed with the documented host-test constants. That does not establish equivalence of unspilled ST0 return values; the original float functions lack a final binary32 store, and the counter-wrap defect remains.

`GameState_DisableTimerWithOwner` has matching inspected stores under the PE32/shared-global mapping; its initialized-state host control agrees. Its uninitialized raw pointer path was not run. `EmbeddedTimer_Reset` has matching reset/flag stores only as an adapter receiving the owner+0x30 timer and the original shared speed. Its actual production mapping and register ABI remain open.

No complete source file is marked semantically cleared. Adjacent `Timer_Set`/`Timer_Reset`, the ANM special-value reader, full dispatcher coverage, fixed RNG providers and no-op child/ring operations remain explicit work items. A source read or a passing literal control does not settle these contracts.

## 4. Execution record and reproducibility

The package contains four exact source/header files. Their Git blob hashes were recomputed over the canonical Git blob framing and matched the connector's hashes before compilation. `source_subset_manifest.json` also records SHA-256 and byte length. Production sources were compiled unchanged; custom code appears only in independent harnesses.

Run from this extracted package directory:

```bash
python3 run_probes.py
python3 run_host_probe.py
python3 check_environment.py
```

The captured environment is Linux x86-64 with GCC **14.2.0**, Clang **17.0.0**, and Python **3.13.5**. Exact commands, flags, compiler versions, inputs, outputs and exit statuses are in `probe_results.json`, `host_contract_probe_results.json`, and `environment_checks.json`. Both C++ compilers used C++17, `-O2 -Wall -Wextra -Werror`. Counter probes additionally used UBSan with recovery disabled.

The host-callback probe compiles four verbatim callback excerpts with an opaque stand-in VM; it does **not** compile the complete host translation unit or run `AnmVm_Tick`. This distinction is recorded in its results. An observation probe's success means the described behavior—including defects—was reproduced; it is not an acceptance pass.

**Not run here:** full `test.sh`, the complete PE32 build, Wine/retail gameplay, fresh graphics/sound/collision traces, or full reference/audit integrity checks. Wine, a PE32 compiler and qemu-i386 were not found. A minimal assembled ELF32 executable could be linked but failed to execute with `Exec format error`. No complete local checkout was available; connector-only metadata downloads into the local environment also failed DNS resolution. No inaccessible or missing evidence was replaced with an inferred pass.

The repository's existing baseline reports successful host/build/smoke runs, but those are **historical**, not rerun results. The smoke reports zero title sprite draws. Its strict all-VM comparison exits 1, with unmatched/incompletely paired evidence. Differently bounded traces do not identify a particular lifetime defect, and matching paired fields does not cover omitted behavior.

## 5. Independence and comparison with prior audits

The initial RNG/timer assessment preceded reading the existing Codex calibration. The initial host-provider assessment was unresolved and was subsequently narrowed using the original variable resolvers and actual binding. This package is a **consolidated checkpoint**, not a separately timestamped blind-review submission.

All six confirmed issues here are additional to the calibration's six implementation rows. The retained-sum FP mechanism is structurally consistent with the calibration's trajectory concern, but neither establishes the live retail control word.

The calibration's easing, trajectory, score-popup, version-marker and FPS rows were read as prior claims, not accepted merely because a previous model reported them. They are listed individually as **not independently revalidated in this batch** in `ledger.json`. No such prior verdict has been overwritten. The older sparse and 57-address historical reviews likewise remain historical rather than current clearance. Thus the requested independent cross-comparison is still partial.

Rejected inferences are explicit: semantic annotations are not proof; a successful link is not behavioral equivalence; no-op comments do not prove unreachability; zero-draw smoke is not visual validation; matching paired ECL events does not settle missing events. No unsupported claim that the previous calibration itself is wrong is made.

## 6. Cleanup performed and retained material

Commit `09835addae52e8eda47fc8c387a518ca7a0b4294` changes only `matching2/docs/audit/README.md`:

```diff
-## Start the independent Pro review
+<a id="start-the-independent-pro-review"></a>
+
+## Optional five-packet calibration
```

The original fragment is preserved, and all existing links, reproduction commands, historical verdicts and hashes remain unchanged. Connector comparison against the reviewed snapshot confirms **one file, +3/-1**. Old blob: `99424d29ffa98f206c2db7d8d67e97995efab510`; new blob: `aa9eab5c33739af55d0870a9ab072cdf758ac47b`. The supplied `cleanup.patch` documents an **already applied** change; do not reapply it blindly.

`cleanup_manifest.json` records 12 candidate groups, their exact paths, keep/consolidate/unresolved decisions, dependency checks, validation and execution status. All three Ghidra corpora are retained because their analysis state, coverage and historical consumers differ. Original IDA material and provenance, packets, baseline artifacts, inventories, historical audit material and already-archived narratives are retained. Legacy hybrid scripts are **unresolved removal candidates**, not deleted as supposedly unused code. Complete consumer, dynamic registration and generator checks are still needed before deleting anything.

Full-tree cleanup is **not complete**. Neither the reference-integrity gate nor the audit-integrity gate was run locally; the applied edit was validated by its bounded diff, preserved anchor and unchanged links, not by a claimed full gate pass. No gate was weakened.

Navigation remains: root `AUDIT_START_HERE.md` → `FULL_REPO_PRO_PROMPT.md` for scope; `matching2/src`, `include/th10`, `standalone` for implementation; `docs/audit/README.md` for baseline/optional calibration; `ida/` and all three Ghidra snapshots for original references; explicitly historical docs for earlier narratives.

## 7. Exact continuation and missing evidence

First close the RNG/timer batch's actual register/typed adapters, caller restrictions and live FP environment. Preserve all counterexamples before changing code. Then take the required ECL dispatch/scheduling batch: enumerate every original arm and default, operand type, callback provider, failure branch and lifetime consequence. Do not use a source switch or a prefix-only trace as a completeness certificate.

For the ANM findings, obtain the supported `bullet.anm` opcode/variable-ID census and execute minimal variable scripts through the production dispatcher. Audit constant RNG and child/ring providers against original callees, then compare observable creation, lifetime, positions and drawing—not only ECL PC/clock/rank.

The remaining enemy/player/collision/bullets/draw/input/replay/save/archive/audio/menu/ending/shutdown batches, unannotated helpers, missing functions and ambiguous boundaries are still open. Original IDA collapsed/undecompiled bodies need an expanded export; augmented Ghidra coverage must not be described as an independent IDA result. Global/initialized analysis-memory dumps are not runtime captures.

On a complete, asset-equipped checkout, run the reference and audit integrity commands before and after any follow-up edits:

```bash
python3 tools/audit_reference_corpus.py --check
bash matching2/audit_check.sh
bash matching2/test.sh
```

Use the documented PE32 toolchain, original executable/assets and Wine for build/runtime work. Capture controlled equal-duration gameplay windows and preserve all missing/unpaired events. Return one disposition per actual scope item before claiming full completion; keep cleanup completion separate from semantic completion.

## Evidence navigation

All repository evidence is pinned to the reviewed SHA above; artifact IDs in `ledger.json` resolve to exact paths, Git blob hashes and canonical URLs without credentials. Original instruction addresses are stronger locators than decompiler-generated line offsets. Key original exports are `decompiled/ghidra_augmented/functions/0044BA80.asm`, `00428DD0.asm`, `0042C620.asm`, `00404ED0.asm`, `0044BF40.asm`, `0043EDA0.asm`, `0043ED00.asm`, and `0043EC70.asm`.

Local result files distinguish actual host execution from static comparisons and modeled expectations. `SHA256SUMS.txt` authenticates the packaged files relative to the delivered checksum list; it is not a signed attestation of completeness or historical independence.
