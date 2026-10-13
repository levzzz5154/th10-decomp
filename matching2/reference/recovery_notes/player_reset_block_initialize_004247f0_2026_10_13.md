# PlayerResetBlock::Initialize 0x004247F0 — equivalent recovery (2026-10-13)

Status: accepted.  Registered-check verdict below; the scratch-project
verification ran the full non-record path (hunk equality, budgets, gate).

## What was wrong with the 2026-10-12 attempt

1. **The model body was 187 bytes short** (1248 against the 1435-byte
   region), so the comparison window overran into `ParameterLoader::Load`.
2. The overread produced the misleading verdict "model references an unbound
   symbol at 0x401852": that address is a `jbe` inside `Load`, reached only
   because the window was too long.

## What closed the gap

All edits are in the model body,
`matching2/msvc/layout/ltcg/large_player_dependencies/runtime.cpp`:

* **The float bounds go through one 12-byte local** (`struct PlayerBounds3
  { float x,y,z; }`), exactly the retail shape: `sub esp,0xc` at entry, each
  bound computed into the local and copied member-wise to `[ebx+base]` /
  `[ebx+base+0xc]` through `lea`/`mov [esp+0xc..0x14]`.  The previous model
  assigned `Float(offset)` directly and skipped the whole staging.
* **The 33-entry indicator loop writes through a stepped pointer**
  (`indicator[0]/indicator[1]; indicator+=2`), giving retail's
  `lea eax,[ebx+0x436c] … add eax,0x8` form.
* **The entry name select is an if/else**, not a ternary: retail loads the
  else value first and branches with `je`.
* **`data_00474c68`/`data_00474c6c` are fields of one escaped struct**
  (`GameSelectionView`); the stub
  (`equivalent/game/player_reset_block_initialize_004247f0_stub.cpp`, kept
  alive by the layout's `roots` entry `_SelectionStateRef_00474c68@0`)
  defines a `noinline` function returning `&data_00474c68.shot_type`, so the
  address escapes and the compiler re-reads the index like retail.  As lone
  externs the compiler folded the three character-table index loads into one
  register-held index and the body lost the reloads retail has.  This mirrors
  the finding in `player_hud_update_00408d60_00409220_2026_10_04.md` for the
  same words.
* The three table stores are dword puns
  (`reinterpret_cast<const unsigned int&>` of the float table element), which
  is how the parameter words are laid out.

## Call-binding findings (tool behaviour worth remembering)

* A call to a symbol that only exists in the bindings object is **rebased
  twice** by the /LTCG code generator: the model link resolves the call to
  `absolute value + 0x400000`.  Layout entries of kind `relative_code` must
  never be *called*; a called external needs kind `code` (whose value the
  code generator rebases exactly once, giving the retail address) or a real
  context body plus a `bindings` entry (`?Load@ParameterLoader@@QAEHPBD@Z` →
  `0x426520` is bound this way; `Load` is a cluster anchor, not a binding).
* The two call targets in this region
  (`?Recovery_LoadCachedResource@@YIPAUCachedResource@@HPAXPBD@Z` and
  `_LargePlayerRefresh@4`) moved from `relative_code` to `code` in
  `absolute_symbols`; the two speculative `bindings` entries for them were
  removed again.

## Residual differences (recorded, 24 hunks / 29 of 314 instructions)

* `operand-order` ×10: x87 `fld`/`fmul`/`fadd` operand swaps in the four
  parameter conversions, the three `half` computations and the six `fadd`
  bounds sums (commutative, same results).
* `evaluation-order` ×12: the `fmul` const loads are pipelined one conversion
  ahead, `0x470b0c` is hoisted ahead of the timer stores, and the
  `mov esi,[ebx+0x45c]` hoist sits inside the conversion run.
* `register-choice` ×2: the `Configure` argument marshals through `eax`
  instead of `edx`.

## Registered-cluster maintenance

`runtime.cpp` is also the driver context of the registered `large_player`
cluster (Factory 0x425020 and the PlayerResetBlock constructor 0x4246C0).
The rewritten body compiles to 1415 bytes there (the escape helper lives in
the equivalence stub, so the cluster build keeps the folded index loads), so
`layout/ltcg/large_player.json` needed:

* anchor `Initialize`: `size` 1234 → 1415;
* gap `.text$a08gap`: address `0x424cc2` → `0x424d77`, size 862 → 681.

Probe after the change: both cluster regions still report EXACT.

## regions.json delta

Append to `equivalent_recoveries` (the region itself stays `asm`):

```json
{"region": "asm_FUN_004247f0_004247f0",
 "layout": "layout/equivalent/player_reset_block_initialize_004247f0.json"}
```

Verdict: `player_reset_block_initialize_004247f0: 1,435 of 1,435 bytes used,
285 of 314 instructions identical, 0 base/index swaps, 0 frame-offset,
29 instructions in 24 recorded differences`.
