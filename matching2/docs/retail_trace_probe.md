# Retail Trace Probe

The original retail image is available at:

- `/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe`
- SHA-256: `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`

## Reproducible Launch

From the retail game directory, launch the untouched image through Wine's GDB
proxy:

```sh
cd "/home/levzzz/Games/TH10 - Mountain of Faith"
WINEDEBUG=-all winedbg --gdb th10.exe
```

The following commands establish the known retail anchors without relying on
symbols:

```gdb
set pagination off
set confirm off
break *0x00438AD0
break *0x00439390
break *0x0043EE30
break *0x0044E1A0
continue
```

A bounded probe in this checkout reaches `0x00438AD0` (`WinMain`). The untouched
retail process remains in its startup/modal/input wait under the current headless
Wine desktop and does not reach the frame or ANM anchors before the bounded
probe timeout. No retail trace file is emitted by the image itself.

## Required Probe Output

A usable injector/debugger script must break at the frame loop, ANM tick, ECL
tick, animation allocation/removal, and final quad submission anchors, then write
the same JSONL schema as the reconstruction:

- `resource`: archive name, byte size, stable content hash;
- `input`: held and pressed retail masks;
- `vm_create`/`vm_destroy`: monotonic probe IDs, script/resource IDs;
- `vm_tick`: script-relative PC offsets and VM state;
- `draw`: sprite/resource metadata and stable object handles;
- `ecl_opcode`/`ecl_vm_tick`: script-relative PCs, async IDs, rank masks;
- `present`: canonical RGB checksum before `Present`.

The probe must normalize the module base to script-relative offsets and must not
serialize pointers, absolute code addresses, or wall-clock timestamps. The
reconstruction-side comparator is
`matching2/tools/compare_runtime_trace.py`; it compares semantic event fields
and ignores only stream sequence bookkeeping.

The known retail anchors are:

- frame loop: `0x00439390`;
- ANM tick: `0x0043EE30`;
- ECL core tick: `0x0044E1A0`;
- animation allocation/registration/removal: `0x00449950`, `0x004489D0`,
  `0x00448A50`, `0x00448AC0`, `0x00448B40`, `0x00448BB0`;
- final quad/append/flush: `0x00442670`, `0x00442FE0`, `0x00442F50`.

Until the startup/input barrier is automated or an injector is supplied, a true
retail-vs-reconstruction trace comparison is blocked. The deterministic
reconstruction traces and schema tests remain valid independently.
