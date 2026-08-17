# Retail Trace Probe

The original retail image is available at:

- `/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe`
- SHA-256: `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`

## Status: Bounded Probe Reaches Stage 1; Per-Tick ECL State Captured

With a nested X display (gamescope) and scripted XTEST input, the untouched
image reaches the frame loop (`0x00439390`), the ECL core tick
(`0x0044E1A0`), StageContext_Enter (`0x00417870`), the stage script load
(`0x00403850`), and the ECL name-table registration (`0x00450220`), and
executes real frames and real stage ECL VM ticks. A longer Z sequence
(`Return Enter` + ten `Z` at `KEY_DELAY=1.4`) confirms Game Start ->
difficulty -> character; the probe then captures the stage window until the
bounded timeout.

The earlier "renderer SIGSEGV" limitation was misattributed: the tick
handler assigned `set $pc = $instr & 0xFFFF`, and gdb treats `$pc` as the
program counter register, so every tick stop resumed the inferior at
`ip & 0xFFFF` - an unmapped address (immediate fault) or a stray code
address (delayed fault ~250 frames later). The crash address matched
`ip & 0xFFFF` exactly across runs. The handler now assigns only
register-safe convenience names; with that fix, captures run the full
window with continuous per-tick ECL state (10,900 ticks in a 120s stage
run) and no fault.

## Reproducible Stage Probe

Run the bounded stage probe from `matching2/`:

```sh
PROBE_SECONDS=120 KEY_DELAY=1.4 TH10_GAME_DIR="/home/levzzz/Games/TH10 - Mountain of Faith" \
  bash tools/retail_bounded_probe.sh /tmp/retail_stage.log \
  "Return Enter Z Z Z Z Z Z Z Z Z Z"
```

The script waits for the nested `:1` display, feeds the GDB script, waits
for the first captured frame, delivers the keys, and captures a bounded
window. `DIAG=1` switches to stop-on-fault and dumps the fault site
(backtrace, registers, stack, interpreter dispatch tables). `NO_TICK=1`
and `TICK_MODE=count|break|hbreak` isolate the tick anchor.

Captured event vocabulary (`th10-recon-jsonl-v1`):

- `frame_begin` with the game-state words at `0x4776E4`/`0x4776E8`;
- `ecl_vm_tick` with vm, ip, pc low word, the VM float clock (vm+0x00),
  async_id, rank_mask, scratch_top;
- `stage_enter`, `stage_load`, `script_register` (ECX=table, arg0=script
  buffer, verified against the `sub_450220` caller that pushes the loaded
  buffer before `call`).

Normalize and compare against the reconstruction stage trace:

```sh
matching2/tools/retail_trace_normalize.py /tmp/retail_stage.log /tmp/retail.jsonl
matching2/tools/retail_vs_recon_stage.py /tmp/retail.jsonl /tmp/recon_stage.jsonl
```

The reconstruction stage trace is generated with
`run_all_pe32.sh --trace /tmp/recon_stage.jsonl --smoke --ecl 3600`
(249,449 events, deterministic). Two independent retail stage captures
produce identical flat tick sequences on the normalized comparison fields
(rank_mask, async_id, scratch_top, pc low word - 10,900/10,900); only the
frame-boundary attribution jitters under the uncapped loop.

The comparison timeline is each VM's float clock (vm+0x00), captured on both
sides at interpreter entry as raw bits: retail emits `clock`, and the
reconstruction emits a matching `time_before` field on each `ecl_vm_tick`.
The scheduler `stage_frame` is NOT the comparison key because it is monotonic
and cannot represent the wait/jump opcodes that move vm+0x00 backwards (the
retail root clock rewinds at tick ~181, e.g. 180 -> 161).

`retail_vs_recon_stage.py` aligns every VM (root, async children, spawned
enemies) by creation order and confirms the entry script-relative pc and
async_id at each position before comparing ticks. The default run reports
63/63 VMs identity-aligned and 10,900/10,900 per-tick full agreement across
the retail capture. The only remaining lifecycle gap is enemy despawn: retail
retires spawned-enemy VMs within the bounded window while the reconstruction
keeps them alive to the trace end (the 0x9808/0x6698 child families retire
identically).

The retail stage script runs from the `stage01.ecl` buffer captured by
`script_register` (arg0); per-tick script-relative pc resolves for
10,898/10,900 ticks (the two unresolved ticks have ip=0 at VM teardown).

## Reference Capture

A normalized reference capture of the untouched image (`th10-recon-jsonl-v1`,
frame loop + ECL core ticks with full VM state) is committed at
`matching2/tests/retail_probe_evidence/retail_ecl_reference.jsonl` and is
validated by `tests/runtime_trace_compare_test.py` on every `test.sh` run;
the test requires every `ecl_vm_tick` to carry the full field set, so a
field-less artifact cannot pass.

## Known Retail Anchors

- frame loop: `0x00439390`;
- ANM tick: `0x0043EE30`;
- ECL core tick: `0x0044E1A0`;
- stage entry: `0x00417870`; stage script load: `0x00403850`;
- ECL name-table registration: `0x00450220` (ECX=table, [esp+4]=script);
- animation allocation/registration/removal: `0x00449950`, `0x004489D0`,
  `0x00448A50`, `0x00448AC0`, `0x00448B40`, `0x00448BB0`;
- final quad/append/flush: `0x00442670`, `0x00442FE0`, `0x00442F50`.

## Limitations

- The retail boot under gamescope occasionally fails with a BadWindow X
  error (gamescope xwm/window-creation race, unrelated to the GDB script);
  the probe resets the wineserver before launching and the failure is a
  retry, not a result.
- The captured `delta` stack word is not the interpreter frame delta
  (observed 0.0); the VM float clock at vm+0x00 is the trusted time field.
- The retail VM pointer in `ecl_vm_tick` is normalized to a stable
  sequential id by `retail_trace_normalize.py`; the pc low word is
  captured, and script-relative pc is resolved from the `script_register`
  bases.
- The ANM tick anchor (0x0043EE30) is not used as a breakpoint: stepping it
  in the main loop destabilizes the probe; the frame/ECL pair keeps the
  session stable across the longest observed windows.
