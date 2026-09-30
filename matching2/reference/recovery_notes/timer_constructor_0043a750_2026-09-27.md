# Complete timer-state constructor at 0043A750

> Integration status (2026-09-28): the exact routine or return correction described here is integrated and passes its maintained normal probe. The combined 487,936-byte executable matches retail byte for byte. See [the fifth checkpoint](native_recoveries_2026-09-28_fifth.md) for current proof. Scratch-only status and parent handoff instructions below describe the original investigation; unmatched and unselected context bodies add no recovered bytes.


The complete 436-byte retail body is recovered as readable, assembly-free C++ in an isolated native-LTCG scratch project. It passed its first normal probe and two independent final probes. The parent must integrate and run the combined image gate before calling this a maintained recovery.

## Current evidence

Fresh live Ghidra MCP reads for program `th10.exe`, socket `/run/user/1000/ghidra-mcp/ghidra-2136235.sock`, are retained in `matching2/build/experiments/timer_constructor_0043a750_2026_09_27/`:

- `ghidra_raw.json`: all 436 bytes at `0043A750..0043A903`.
- `ghidra_disassembly.json`: all 92 instructions, 436 bytes, no truncation.
- `ghidra_decompile.txt`: no Function exists at this head.
- `ghidra_xrefs.json`: no references exist in the current Ghidra listing.

No Function, prototype, caller, allocation size, or inheritance relationship was invented. A read-only helper scanned executable `.text` for E8/E9 direct targets to this head and found none. The source uses an explicitly synthetic placement-construction loop to establish the observed private receiver ABI.

## Semantics and ABI

The constructor receives its object pointer in ESI, returns it in EAX, and ends with plain RET. It sets the base dispatch table to `0046F810`, queries `timeGetDevCaps(self + 8, 8)` through import slot `00466290`, then installs derived dispatch table `0046F80C`. It clears the timer ID; six scattered 32-bit fields; one byte at `+2C4`; seven words at `+2C8..+2E0`; the 32-word array at `+98..+114`; the 32-word array at `+14..+90`; and the separate word at `+94`. It finally stores `-1` at `+10`.

Typed inline loops over the two arrays naturally produce the retail unrolled ECX and EDX zero-store runs. Each observed initialization is retained, with no volatile declarations, barriers, encoded registers, or opaque helper bodies.

`DerivedTimerState` models only the observed 0x2E4-byte prefix. It does not claim a full allocation size. Related MIDI sequencer code accesses fields beyond this prefix, including `+2E4/+2E8`; MIDI event code uses words through `+2FC`. Reserved ranges are untouched by this constructor.

## Native proof and promotion

The definitive normal report is `probe_final_documented.json`; the generated `proposal.json` contains the sole selected 436-byte region. The compiler context is 41 bytes and remains unselected. There are no dependency anchors.

The selected native body SHA-256 is `0931f4b92d0480f588d33ae50b288db1cf579d39c2007c868ecc3d87b353d656`, equal to all 436 fresh Ghidra bytes. The normal report states exact, zero differing bytes, no failures, zero instruction-byte changes, zero address-operand changes, zero masked bytes, and `reference_bytes_used_for_build: false`.

Only these four files are proposed for promotion from scratch `msvc/`:

| File | SHA-256 |
| --- | --- |
| `src/unidentified/unassigned_0043a750.cpp` | `ebd8dc7152c4b43321b62b1f2dec460c1724e3e346675c3231fe7d69602a9ac5` |
| `include/th10/platform/derived_timer_state_0043a750.hpp` | `2540a6f2afff69cb653cbab0c9ff2778a45cce00de2a00ff7ce9e054d619d166` |
| `layout/ltcg/timer_constructor_0043a750.json` | `8e5067cbd775986eec3319dc054324a227c656fd4424a9af4bb3916c68ec277e` |
| `layout/ltcg/timer_constructor_0043a750_context.cpp` | `4e219bc9db0db8c18c2212cdc5cc6b7fd3fe59845c7d5be3af1514507f1c95bb` |

The existing `include/th10/platform/win32_timer.hpp` is reused unchanged for the eight-byte capability structure. Do not copy the entire scratch manifest or project. Copy these four files, register `layout/ltcg/timer_constructor_0043a750.json`, run a fresh maintained normal probe, and then verify the complete executable with the shared gate.
