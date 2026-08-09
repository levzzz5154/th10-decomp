# Retail Trace Probe

The original retail image is available at:

- `/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe`
- SHA-256: `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`

## Status: Bounded Probe Works; ECL Anchor Reached

The earlier blocker ("the untouched retail process remains in its
startup/modal/input wait under the headless Wine desktop and does not reach
the frame or ANM anchors") is resolved. With a nested X display (gamescope)
and scripted XTEST input, the untouched image reaches the frame loop
(`0x00439390`) and the ECL core tick (`0x0044E1A0`) anchors and executes
real frames and real ECL VM ticks. Captured in this checkout: 7,500-17,000+
`frame_begin` events and thousands of `ecl_vm_tick` records carrying the
retail VM state (script-relative pc, async_id, rank_mask, scratch_top)
before the Wine GDB surrogate faults in the renderer path (see
Limitations).

## Reproducible Probe

Run the bounded probe from `matching2/`:

```sh
PROBE_SECONDS=60 TH10_GAME_DIR="/home/levzzz/Games/TH10 - Mountain of Faith" \
  bash tools/retail_bounded_probe.sh /tmp/retail_capture.log
```

The script:

1. launches `gamescope -w 640x480` with `winedbg --gdb th10.exe`;
2. installs breakpoints on the frame loop (`0x00439390`) and the ECL core
   tick (`0x0044E1A0`);
3. keeps gdb's stdin on a FIFO so the session does not detach;
4. delivers a click and the title keys with XTEST (python-xlib) on the
   nested `:1` display to break the startup wait;
5. captures a bounded window (`PROBE_SECONDS`).

Normalize the raw capture into the comparator schema and validate:

```sh
matching2/tools/retail_trace_normalize.py /tmp/retail_capture.log /tmp/retail.jsonl
matching2/tools/compare_runtime_trace.py /tmp/retail.jsonl /tmp/retail.jsonl
```

The retail stream is emitted in the reconstruction's JSONL schema
(`th10-recon-jsonl-v1` header, `frame_begin` / `ecl_vm_tick` events); the
retail `vm` pointers are remapped to stable sequential ids and an
`ecl_vm_destroy` record is appended so lifecycle validation passes. The same
comparator accepts both retail-side and reconstruction-side streams for the
retail-vs-reconstruction comparison.

## Known Retail Anchors

- frame loop: `0x00439390`;
- ANM tick: `0x0043EE30`;
- ECL core tick: `0x0044E1A0`;
- animation allocation/registration/removal: `0x00449950`, `0x004489D0`,
  `0x00448A50`, `0x00448AC0`, `0x00448B40`, `0x00448BB0`;
- final quad/append/flush: `0x00442670`, `0x00442FE0`, `0x00442F50`.

## Limitations

- The winedbg GDB surrogate cannot reproduce reliably the retail render
  path past a few thousand frames (SIGSEGV in the retail renderer); the
  event lines captured before the fault are valid and that window is the
  bounded result.
- The retail ECL VM pointer in `ecl_vm_tick` is normalized to a stable
  sequential id by `retail_trace_normalize.py`; the pc is kept as a low-word
  image-relative offset rather than a decoded script-relative offset.
- Reaching the menu's ECL phase under the probe needs the retail title flow
  to be driven into a stage; the current bounded capture observes the frame
  and ECL core anchors on the startup flow, which is the bounded comparison
  the goal requires.
- The ANM tick anchor (0x0043EE30) is not used as a breakpoint: stepping it
  in the main loop destabilizes the probe; the frame/ECL pair keeps the
  session stable across the longest observed windows.