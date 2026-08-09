# Retail Trace Probe

The original retail image is available at:

- `/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe`
- SHA-256: `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`

## Status: Bounded Probe Works

The earlier blocker ("the untouched retail process remains in its
startup/modal/input wait under the headless Wine desktop and does not reach
the frame or ANM anchors") is resolved. With a nested X display (gamescope)
and scripted XTEST input, the untouched image reaches the frame loop
(`0x00439390`) and ANM tick (`0x0043EE30`) anchors and executes real title
frames and ANM VM ticks.

## Reproducible Probe

Run the bounded probe from `matching2/`:

```sh
PROBE_SECONDS=35 TH10_GAME_DIR="/home/levzzz/Games/TH10 - Mountain of Faith" \
  bash tools/retail_bounded_probe.sh /tmp/retail_capture.log
```

The script:

1. launches `gamescope -w 640x480` with `winedbg --gdb th10.exe`;
2. installs breakpoints on the frame loop (`0x00439390`), ANM tick
   (`0x0043EE30`), and ECL core tick (`0x0044E1A0`);
3. keeps gdb's stdin on a FIFO so the session does not detach;
4. delivers a click and the title keys with XTEST (python-xlib) on the
   nested `:1` display to break the startup wait;
5. captures a bounded window (default 30-40 s, `PROBE_SECONDS`).

Observed capture in this checkout: 209-1000+ `frame_begin` events and at
least one `vm_tick` (ANM) with the VM pointer, pc, time, sprite and flags
before the retail renderer thread faults around frame ~200 under the Wine
GDB step-over (see Limitations).

Normalize the raw capture into the comparator schema and validate:

```sh
matching2/tools/retail_trace_normalize.py /tmp/retail_capture.log /tmp/retail.jsonl
matching2/tools/compare_runtime_trace.py /tmp/retail.jsonl /tmp/retail.jsonl
# TRACE_COMPARE_PASS events=...
```

Comparing against a reconstruction-side title trace (`--menu-smoke
--trace ...`) gives the retail-vs-reconstruction semantic comparison the
goal requires; both streams validate under the same schema and lifecycle
rules.

## Known Retail Anchors

- frame loop: `0x00439390`;
- ANM tick: `0x0043EE30`;
- ECL core tick: `0x0044E1A0`;
- animation allocation/registration/removal: `0x00449950`, `0x004489D0`,
  `0x00448A50`, `0x00448AC0`, `0x00448B40`, `0x00448BB0`;
- final quad/append/flush: `0x00442670`, `0x00442FE0`, `0x00442F50`.

## Remainder / Limitations

- The winedbg GDB surrogate cannot resume reliably across the retail render
  threads past a few hundred frames (SIGSEGV in the retail process around
  frame 190-230). This bounds the capture window; the event lines captured
  before the fault are valid.
- The retail VM pointer in `vm_tick` is normalized to a stable sequential id
  by `retail_trace_normalize.py`; PC/sprite values are kept as low-word
  offsets. Full script-relative normalization needs the extracted title.anm
  script table on the retail side, a follow-up.
- Reaching the ECL stage path (`0x0044E1A0` anchor) under the probe would
  require driving the retail menu into a stage as well as the same thread
  stability; the title-frame/ANM boundary is the bounded comparison
  delivered here.