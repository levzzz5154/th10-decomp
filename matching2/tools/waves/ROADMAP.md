# Remaining work and the wall in front of it

Measured against the manifest at commit `c8b75cf` (whole-image build byte-exact).

```
ordinary C++      283 regions  16,049 bytes
inline assembly 2,303 regions 372,933 bytes
embedded data      25 regions   8,157 bytes
padding         1,817 regions  15,533 bytes
total .text                  412,672 bytes
```

## The three pools of remaining assembly

Owned assembly regions (a region whose `owner` is itself) fall into three classes,
and only the first two can be converted with the current mechanism.

**1. Expressible now.** The region's own entry convention is one a C++ prototype
can declare, and every direct callee either is already recovered C++ or also uses
a declarable convention. ~90 plain regions (21 KB) plus ~406 that additionally
need a native LTCG cluster to reproduce their own entry register.

**2. Needs a native LTCG cluster.** MCVS 13.10 places an argument only in ECX or
EDX, or on the stack — never EAX, EBX, ESI or EDI, and a 64-bit argument always
goes on the stack even though the return comes back in EDX:EAX. A region whose
retail entry puts a parameter anywhere else (`__usercall`/`__userpurge` in the IDA
prototype) is reproduced by compiling it as a cluster: a `/GL` module whose
synthetic context caller forces the register, linked `/LTCG`, from which the outer
fixed-address link takes only the named function. `matching2/msvc/layout/ltcg/` and
`matching2/tools/matching/ltcg_cluster.py` are the machinery;
`layout/ltcg/rank_level.json` is a worked example.

**3. Needs whole-program LTCG — the wall.** 359 regions, 105,724 bytes, have at
least one direct callee whose *own* entry convention MSVC only chooses during a
native `/LTCG` link, e.g. `int __usercall sub_449950@<eax>(int a1@<esi>)`:
the retail caller emits `mov eax,obj; call`, and the argument register is decided
by the *caller's* translation unit from the callee's declaration. No declaration
can put an argument in ESI, so the call site cannot be reproduced per unit.

Recovering the callee does not help: it makes the callee readable, but the caller
still has to emit a call site no declaration can describe. The measured evidence
is in `matching2/build/waves/results5/L504/blocker.json`,
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

Highest-leverage callees, by number of callers they block (each is itself still
assembly, so each is a cluster target first):

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
| `tools/waves/bind_relocations.py` | binds `__real@`/`__imp__`/`_data_` names the probe reports unbound |
