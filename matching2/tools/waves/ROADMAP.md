# Remaining work and the wall in front of it

**2026-09-13 architecture update:** the caller/callee wall below has a measured
whole-program route. Schema-2 LTCG batches compile real callers and callees as
separate `/GL` inputs into one native `/LTCG` link, using a real entry instead
of a synthetic caller. The previously blocked `0044C130 -> 0044C150` pair is
exact (117 bytes), and the whole executable remains exact. `make ltcg-proof`
reproduces positive and negative compiler controls. See
[the experiment and pipeline](../../reference/whole_program_ltcg.md).
The counts below are historical; use `make progress` for current accounting.

**Further caller/callee recoveries (2026-09-13):** the archive loader now has
real script/checksum callers in a schema-2 batch (+302 bytes). The previously
unrecovered `0x0043DC90` sound queue and its projectile caller matched together
under schema 2; the cluster now also contains three ESI-entry bullet motion
routines under a rooted schema-1 context (+1,667 bytes total). See the
[queue proof](../../reference/recovery_notes/sound_queue_deceleration_0041d170_0043dc90.md),
[motion expansion](../../reference/recovery_notes/bullet_motion_sound_cluster_00407780_00407a30_00407be0.md),
and [allocator/initializer follow-up](../../reference/recovery_notes/animation_pool_initializer_followup_00401de0_00449950.md).
These recoveries leave 443 C++ regions / 24,757 bytes; `make progress` remains
the authoritative current count.

**Render cluster expansion (2026-09-13):** compiler-visible batch flushing now
unlocks the solid quad, color viewport, and viewport clear/present pair through
a real schema-2 batch. The gradient quad extends that batch under schema 1,
retaining only the two required public roots (+1,361 bytes / five regions).
[Source and ABI evidence](../../reference/recovery_notes/viewport_quad_cluster_0043bc40_0043c1a0.md).
The whole executable is exact at 448 C++ regions / 26,118 bytes.

**Render-state and primitive callers (2026-09-13):** the render batch now also
contains the EAX/EDI state synchronizer and EAX/EDX quad appender, together with
five real draw callers (+1,568 bytes / seven regions). Five of seven direct
synchronizer callers are recovered; the two 1,111-byte quad pipelines remain.
[Source-shape and ABI evidence](../../reference/recovery_notes/render_state_primitives_004425a0_004450e0.md).
The whole executable is exact at 455 C++ regions / 27,686 bytes.

**Camera application (2026-09-13):** the render batch also recovers the 330-byte
EDI camera apply routine, including view/projection construction and normalized
cross product. The default camera setup and blend/color helper retain measured
source-shape blockers. See [camera evidence](../../reference/recovery_notes/camera_apply_followup_00421480_004215a0.md)
and [color follow-up](../../reference/recovery_notes/blend_color_followup_004423e0.md).
The whole executable is exact at 456 C++ regions / 28,016 bytes.

**Archive resource callers (2026-09-13):** asset-buffer replacement, parameter
file relocation, and optional map loading now share the archive loader's native
compiler scope (+563 bytes / three regions). The parameter loader's float
projection value also reproduces its FSIN and exact aligned nested loops.
[Recovery evidence](../../reference/recovery_notes/archive_resource_callers_0040b480_00426520_0043e9d0.md).
The whole executable is exact at 459 C++ regions / 28,579 bytes, with 2,126
assembly regions / 360,403 bytes remaining.

Measured against the manifest at commit `22b5236` (whole-image build byte-exact).

```
ordinary C++      382 regions  16,518 bytes
inline assembly 2,204 regions 372,464 bytes
embedded data      25 regions   8,157 bytes
padding         1,817 regions  15,533 bytes
total .text                  412,672 bytes
```

## What lands regions, in order of cost

1. **Mechanical families** — `matching2/tools/waves/cluster_accessors.py` recovers
   the whole EAX-convention field-accessor family (98 regions) by pattern-matching
   the retail body, generating a native-LTCG cluster per region, probing, and
   rolling back anything that does not match. This closed 98 regions in one run
   with zero failures, after three agent waves had landed six. Prefer this route
   wherever a family is uniform; the 12 remaining repeated patterns among small
   regions cover only 27 regions, so the rest is per-region work.
2. **Agent waves** — `wave.py` + `briefs/` + `integrate.py`, for bodies that need
   real reasoning. Expect roughly a quarter of assigned regions to land, so assign
   several per agent and have them land incrementally.
3. **The cluster recipe** — `briefs/CLUSTER.md`, now with the four traps that
   previously cost whole builds. Required for any region whose entry convention is
   not the C++ ABI.

## Classes that C++ cannot express (measured, not assumed)

Each of these was attacked repeatedly by different agents with independent
experiments; record them here so nobody re-derives them.

| class | evidence | consequence |
|---|---|---|
| **Argument in EAX/EBX/ESI/EDI or a 64-bit EDX:EAX parameter** | MSVC 13.10 assigns a value parameter only to ECX/EDX or the stack; a 64-bit parameter always goes on the stack. Verified across `__cdecl`, `__stdcall`, `__fastcall`, member, struct-by-value and `__int64` forms. | Recoverable as a native-LTCG cluster — 265 regions are of this shape. |
| **Callee takes an argument in one of those registers** | The *call site* bytes live in the caller's unit, and no declaration can describe them. Earlier per-region probes left a fixed residual per call. | Recover both endpoints in one native LTCG scope. The worker pair now matches across separate `/GL` objects; one giant module is not required by that experiment. |
| **`fsincos`** | MSVC 7.1 emits `fsin`+`fcos` separately for every source spelling, in float and double, both orders. A native `/LTCG` build does not fuse them either, and every object in `libc.lib` contains zero `d9 fb` byte pairs. | 4 regions × 30 bytes. Unreachable from C++ in this toolchain. |
| **Provider of a `switch` table shared by two functions** | A data region named by two different heads cannot be owned by either. | Not observed in practice; the detector refuses such a region. |
| **Explicit `__thiscall`** | Error C4234, "reserved for future use". | Use a plain member function instead. |
| **Variadic member followed by caller cleanup** | A variadic member pushes `this`; a variadic free function declared `__fastcall` is ignored and mangled `YA`. | The variadic-member shape *is* reachable once both caller and callee share one `/GL` module — five such regions were recovered as clusters. |
| **Store-literal trampoline** | `mov eax,ecx; jmp rel32` (e.g. `0x42B9A0` → `0x42B6F0`). Earlier probes emitted `push ecx; call; ret`, or a bare `jmp` without the receiver move. | ~2 regions × 7 bytes. Still untested as a real caller/callee batch; the old per-region failure does not establish impossibility. |
| **Outlined CRT math** | A translation unit emits `call _sinf@4` / `call _cosf@4` rather than retail's 43-byte inline x87 sequence, so the call site cannot match. | Reachable through a cluster, where the CRT inlines; 0x00404DA0 was recovered this way. |
| **SEH frame whose scope table is its own region** | MSVC emits the scopetable and `__ehhandler` into `.text$x`/`.rdata` contributions that are not the region's extent, and the scopetable address (e.g. `0x0046556B`) is itself a manifest region a per-unit compile cannot place. | 14 regions. Needs a manifest-level handler binding, which `bind_relocations.py` cannot express (`__real@`/`__imp__`/`_data_` only). |
| **Two mutually exclusive retail properties in one straight-line tail** | `0x0042A3E0`: every shape yielding the mid-stream `mov eax,1` also gets an if-converted tail (23 differing bytes); every shape keeping the branch loses the materialisation (62–64 bytes vs 68). ~70 shapes tried. | Cluster candidate; possibly one of the permanently residual regions. |


## The pools of remaining assembly

Owned assembly regions (a region whose `owner` is itself) fall into three classes,
and only the first two can be converted with the current mechanism.

**1. Expressible now.** The region's own entry convention is one a C++ prototype
can declare, and every direct callee either is already recovered C++ or also uses
a declarable convention. ~90 plain regions (21 KB) plus ~406 that additionally
need a native LTCG cluster to reproduce their own entry register.

**2. Needs a native LTCG cluster.** Ordinary MSVC 13.10 compilation places an argument only in ECX or
EDX, or on the stack — never EAX, EBX, ESI or EDI, and a 64-bit argument always
goes on the stack even though the return comes back in EDX:EAX. A region whose
retail entry puts a parameter anywhere else (`__usercall`/`__userpurge` in the IDA
prototype) is reproduced by compiling it as a cluster: a `/GL` module whose
synthetic context caller forces the register, linked `/LTCG`, from which the outer
fixed-address link takes only the named function. `matching2/msvc/layout/ltcg/` and
`matching2/tools/matching/ltcg_cluster.py` are the machinery;
`layout/ltcg/rank_level.json` is a worked example.

**3. Needs whole-program LTCG — now supported in bounded batches.** At this
historical checkpoint, 359 regions, 105,724 bytes, had at
least one direct callee whose *own* entry convention MSVC only chooses during a
native `/LTCG` link, e.g. `int __usercall sub_449950@<eax>(int a1@<esi>)`.
That retail caller must supply the object in ESI. Ordinary per-unit compilation
chooses the call sequence from the callee's declaration, which cannot express
this convention.

Recovering the callee does not help: it makes the callee readable, but the caller
still has to emit a call site no declaration can describe. Recovering both
definitions in one schema-2 native link now addresses this boundary. The old
per-region mismatch evidence is in `matching2/build/waves/results5/L504/blocker.json`,
`results5/L509` and `results5/L508` — all three independently reproduced the
closest expressible call site and found a fixed residual difference of a few bytes
per call (e.g. twelve missing `mov eax,ecx` = 25 bytes).

**4. Already the vendor's own code — 327 regions, 54,411 bytes (14.6% of the
remaining assembly).** `matching2/tools/waves/match_crt.py` compares each
remaining region against every object in the toolkit's nine `.lib` files, masking
the object's own relocation fields. 327 regions are byte-identical to a library
section outside those fields, i.e. the linker only rewrote addresses:

| library | regions | bytes |
|---|---|---|
| libc.lib | 224 | 32,599 |
| libcmt.lib | 98 | 21,584 |
| libcp.lib | 5 | 228 |

These are CRT functions, not game code: `_input`, `memcpy`, `strlen`, `sprintf`
and friends. Their bytes are already correct in the shipped library, and the
game's own translation units never contain them. Two consequences:

- They cannot be recovered by reading disassembly the way game code is; the
  source is the CRT's, and the toolkit ships only headers (`include/`), not
  `crt/src/`. Rebuilding them from source needs the VC7.1 CRT source, which is
  not on this machine.
- Because the bytes come from the vendor's own object, the honest way to close
  them is to let the build take those regions from the library rather than to
  hand-write an imitation. That is a build-architecture decision, not a
  per-function task.

The remaining ~318 KB is game code, of which ~96 KB is class 3 above and the rest
is reachable cluster-by-cluster.

Historical highest-leverage callees, by callers blocked at the checkpoint
above. `0043DC90`, `00442F50`, `0044B360`, and `0044C150` are now recovered;
their remaining private call sites still need compiler-visible definitions
in the same native LTCG scope:

| callee | callers blocked |
|---|---|
| `0x00449950` | 36 |
| `0x0043DC90` | 33 |
| `0x00442F50` | 26 |
| `0x0044B360` | 23 |
| `0x004489D0` | 22 |
| `0x00448980` | 19 |
| `0x0043E710` | 18 |
| `0x0044C150` | 18 |

## Already solved, worth not re-deriving

- **Split functions.** Retail split some functions into parts separated by the
  compiler's own alignment padding. `matching2/tools/waves/merge_parts.py` merges
  the parts, emits the padding verbatim, and folds the absorbed regions.
- **Jump tables.** MSVC emits a `switch`'s table inside the function's own
  section, after the code and its alignment padding; the manifest inherited the
  table as a separate data region owned by a different translation unit, which
  made every such function fail the extent gate. `absorb_tables.py` grows each
  region to code + padding + table, folds the data regions in, keeps the bytes
  emitted by the region's own inline assembly, and re-probes. 47 regions, 3,242
  bytes of tables and padding.
- **`fsincos`.** MSVC 7.1 never emits it from `sinf`/`cosf` source; those bodies
  need another route.
- **Not expressible any other way:** `__thiscall` spelled explicitly (error
  C4234); variadic member (pushes `this`); a variadic non-member declared
  `__fastcall` (ignored, mangled `YA`).

## Tooling built for this

| tool | purpose |
|---|---|
| `tools/matching/probe.py` | the byte gate for one unit |
| `tools/waves/vdiff.py` | address-aligned retail vs compiled instruction diff, with a differing-byte count, for iterating on a body |
| `tools/waves/plan.py` | ranks regions by size, cluster need and callee blocking |
| `tools/waves/wave.py` | deals a wave and writes per-agent briefs |
| `tools/waves/register_cluster.py` | atomic manifest registration of a cluster (parallel-safe) |
| `tools/waves/carve_region.py` | moves one region into its own single-region unit |
| `tools/waves/absorb_tables.py` | folds compiler-emitted jump tables into their function region |
| `tools/waves/merge_parts.py` | merges split functions |
| `tools/waves/integrate.py` | verifies agent proposals and writes them into the manifest |
| `tools/waves/repair_units.py` | completes or reverts a unit an agent left half-converted |
| `tools/waves/match_crt.py` | finds remaining regions that are verbatim toolkit-library code |
| `tools/waves/cluster_accessors.py` | recovers the uniform EAX-convention accessor family as clusters |
| `tools/waves/bind_relocations.py` | binds `__real@`/`__imp__`/`_data_` names the probe reports unbound |
