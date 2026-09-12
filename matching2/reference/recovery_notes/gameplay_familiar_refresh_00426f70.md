# Gameplay familiar refresh: `0x00426F70`

## Result

The 2,520-byte region remains the exact naked-assembly implementation in
`src/game/gameplay_final_runtime.cpp`. The complete semantic candidate did not
pass the required extent/byte gate, so no production semantic source, task
layout, context, or integration proposal was retained. `regions.json` was not
edited.

The maintained-source focused probe is exact for address `0x00426F70`, extent
2,520. Retail receives the player runtime as one stack argument, allocates a
`0x38`-byte local frame, saves `EBX/EBP/ESI/EDI`, and returns with `ret 4`.
The final 24 bytes after the return are the six-entry switch table and belong
to this contribution; they are not an adjacent function.

## Recovered behavior

The function refreshes the player's four familiar/orbit records from the
signed power gauge at `0x00474C48`.

- It first sweeps the four attached-effect handles at player `+0x330C`, stride
  `0x98`, resolving each handle through both animation-manager intrusive
  lists. At power 100 or above it marks the resolved animation and its child
  chain with removal flag `0x04000000`, clears the handle, and recreates the
  shot/difficulty-specific front sprite (`0x14`, `0x15`, or `0x16`) on layer
  `0x0F`. Below 100 it instead writes stop state `1` at animation `+0x304`.
- The desired familiar count is signed `power / 20`, capped at four. An
  unchanged count exits after the effect-handle sweep.
- For each desired record at player `+0x32A0`, stride `0x98`, it copies the
  player position, retires the previous animation handle at record `+0x68`,
  stores the orbit index, generates the four random offset words, and selects
  normal/focused coordinates according to difficulty and shot type.
- It allocates and initializes script `0x11`, `0x12`, or `0x13`, forces layer
  `0x0F` and animation flag `0x40000000`, registers the animation in the
  manager, and stores the returned handle. Difficulty-one shot paths also
  install the callbacks at `0x00427950` or `0x00427AD0`; focused shot 2 asks
  the manager to set the stop frame from the new handle.
- Surplus records are disabled and their animations/child chains receive stop
  state `1`. Finally the function stores the new count at player `+0x3500`
  and marks all four record dirty flags at `+0x332C`, `+0x33C4`, `+0x345C`,
  and `+0x34F4`.

This behavior is grounded in the complete augmented Ghidra control flow,
retail disassembly, callers at `0x00425730` and the initialization/factory
paths, and the archived legacy semantic runtime model.

## Rejected compiler candidate

A disposable complete-control-flow translation was compiled with the required
MSVC 13.10.6030 profile. Its ordinary optimized contribution was 1,876 bytes,
644 bytes shorter than retail. The relocation-aware overlap comparison had a
two-byte matching prefix and first diverged at `0x00426F72`:

```text
retail:    83 EC 38 66 8B 0D 48 4C 47 00 0F BF D1 B8 67 66 ...
candidate: 83 EC 0C 66 A1 .. .. .. .. 66 3D 64 00 8B 15 .. .. ...
```

Thus the first mismatch is the local-frame topology (`0x38` versus `0x0C`),
followed immediately by different power-load/division scheduling. Across the
1,876-byte overlap, 1,538 non-relocation bytes differ. A `/GL` compile was
also made, but it was not promoted into a fixed-address layout: the source
still represented the animation pipeline with ordinary external returns, so
linking it as a synthetic one-function LTCG context would not model the retail
register edges and could not constitute an exact proof.

Ghidra's `extraout_ECX` and uninitialized output locals identify the missing
source contracts. Retail carries allocator/configuration results through the
calls at `0x00449950`, `0x00449870`, and `0x004489D0`, then exposes the new
handle in a caller-visible register/local arrangement; `0x00448E30` and
`0x00449470` participate in the same convention. Random generation at
`0x00463B2C` likewise has a nonstandard caller-visible return shape. All six
dependencies remain assembly regions, and the existing animation-manager
cluster recovery independently records incompatible candidate extents and
entry conventions.

## Next dependency cluster

Before retrying this region, recover one exact caller-faithful native-LTCG
pipeline containing `0x00449950` (allocate), `0x00449870` (script initialize),
`0x004489D0` (register primary-back), and one real caller that stores the
returned handle. Then prove the `0x00448E30` create wrapper and
`0x00449470` stop-frame helper against that ABI, plus a typed exact return
contract for `0x00463B2C`. Only after those leaves preserve their retail
register outputs can this caller reproduce its `0x38` spill frame, call
scheduling, and in-contribution switch table.

The rejected source, candidate objects, compiler outputs, and probe artifacts
were removed. No shared tooling or unrelated/concurrent files were changed.
