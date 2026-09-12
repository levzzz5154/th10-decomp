# Animation variable/resource utility cluster — 0x0043EC70..0x00448D50

Date: 2026-09-12

## Scope and result

Attempted the five live manifest regions in the 614-byte animation utility
cluster:

| Address | Live extent | Live source | Result |
| --- | ---: | --- | --- |
| `0x0043EC70` | 144 | `src/render/animation_manager.cpp` | retained asm |
| `0x0043ED00` | 156 | `src/render/animation_object_resolve_float_variable_0043ed00.cpp` | retained asm |
| `0x0043EDA0` | 132 | `src/render/animation_object_resolve_integer_variable_0043eda0.cpp` | retained asm |
| `0x00447F70` | 87 | `src/render/animation_manager_clear_indexed_resources_00447f70.cpp` | retained asm |
| `0x00448D50` | 95 | `src/render/animation_manager_create_positioned_primary_00448d50.cpp` | retained asm |

No region was independently exact. Production semantic sources, LTCG layout/
context files, and proposal files were not retained; `regions.json` was not
modified. The disposable lab and its temporary artifacts were removed after
measurement.

## Recovered behavior and ABI evidence

`legacy_semantic/src/render/animation_manager.cpp`, its animation-manager
header, the live callers, and retail disassembly support the following
behavioral model:

* `0x0043EC70` reads animation integer variables with the object in `ECX` and
  the variable ID in `EAX`. IDs `10000..10003` read integer fields at `+0x30C`
  through `+0x318`; IDs `10004..10007` read float fields at `+0x31C` through
  `+0x328` and tail through retail `__ftol2` at `0x00463B2C`; IDs `10008..10009`
  read `+0x32C` and `+0x330`; other IDs return the ID. The retail extent also
  owns the jump table at `0x0043ECD8`.
* `0x0043ED00` resolves a float operand using `EDI` for the operand/fallback,
  `ESI` for the animation object, `CL` for the selector, and the mask at
  `[ESP+4]`, with `RET 4`. Encoded IDs `10004..10007` select script floats and
  `10013..10015` select the base-position floats at `+0x334..+0x33C`.
* `0x0043EDA0` resolves an integer operand using `EAX` for the operand,
  `EDX` for the animation object, `CL` for the selector, and the mask at
  `[ESP+8]` after the saved-register prologue, with `RET 4`. Encoded IDs
  `10000..10003` and `10008..10009` select the corresponding object fields;
  otherwise the original operand is returned. Its jump table at
  `0x0043EDFC` is inside the 132-byte extent.
* `0x00447F70` uses manager `EDI` and index `ESI`. It releases the indexed
  primary/secondary resources through each vtable's `+8` entry, releases the
  manager resource at `+0x3AD5E0` through retail `0x00452422`, zeros all three
  slots, preserves `EBX`, and returns plainly.
* `0x00448D50` consumes the positioned-resource/custom stack ABI, allocates via
  `0x00449950`, sets bucket/flag state, copies the three position words to
  `+0x340`, loads through `0x0043E710`, and registers the primary through
  `0x004489D0`. The retail body is a separate 95-byte ownership region with
  `RET 0x0C`.

The attempted semantic candidate used readable variable/object field names,
noinline member helpers, explicit field offsets, and a synthetic pointer-array
compiler context. It reused the known retail absolute bindings for `__ftol2`,
`free`, allocation, script loading, and primary registration. This was a
bounded compiler experiment only; the synthetic context was not game code.

## Exact probe measurements

The corrected native-LTCG build reached an image and map, but its fixed layout
could not validate because the generated contributions were shorter and moved
the later regions. The map measured these compiler contributions:

| Retail address | Retail extent | Native contribution start | Native extent | First compared mismatch |
| --- | ---: | --- | ---: | --- |
| `0x0043EC70` | 144 | `0x0043EC70` | 62 | `0x0043EC70` |
| `0x0043ED00` | 156 | `0x0043ECB0` | 64 | `0x0043ED00` |
| `0x0043EDA0` | 132 | `0x0043ED00` | 51 | `0x0043EDA0` |
| `0x00447F70` | 87 | `0x00447E80` | 79 | `0x00447F71` |
| `0x00448D50` | 95 | `0x00448C60` | 66 | `0x00448D50` |

The first candidate bytes versus retail were:

* `0x0043EC70`: native `3D 10 27 00 00 7C 07 ...` (`cmp eax, 10000`) versus
  retail `8D 90 F0 D8 FF FF 83 FA 09 77 5C ...` (the retail range dispatch and
  jump-table shape).
* `0x0043ED00`: native `F6 44 24 04 01 74 34 ...` versus retail
  `B8 01 00 00 00 D3 E0 0F B7 4C 24 04 ...`; the compiler folded the selector
  mask test instead of retaining the retail setup/table sequence.
* `0x0043EDA0`: native `F6 44 24 04 01 74 29 ...` versus retail
  `56 BE 01 00 00 00 D3 E6 0F B7 4C 24 08 ...`; the saved-register and selector
  lowering do not match the retail custom ABI.
* `0x00447F70`: the first byte coincided, then native `8B 8C B7 ...` differed
  from retail `8B 84 B7 ...` at `0x00447F71`; the native expression selected
  `ECX` where retail keeps the first resource in `EAX`, followed by different
  virtual-call lowering.
* `0x00448D50`: native `56 8B 35 10 1C 49 00 E8 ...` versus retail
  `53 55 8B 6C 24 10 56 8B 35 ...`; the native member/argument prologue and
  call sequence do not preserve the retail caller-shaped ABI.

These are ordinary C++/custom-ABI compiler mismatches, not proof that any
region is irreducible or exact-assembly-required.

## Next bounded dependencies

The variable helpers need a compiler-visible internal register model that keeps
the retail `ECX`/`EAX`, `EDI`/`ESI`/`CL`, and `EAX`/`EDX`/`CL` conventions while
retaining the x87 conversion tail and jump-table ownership. The clear helper
needs an explicit `EDI` manager/`ESI` index wrapper and a noinline virtual-call
shape that emits the retail `EAX`/`EDX` resource temporaries. The positioned
creator needs a caller-shaped custom-ABI context around the already known
allocation, loader, and primary-registration dependencies; its 95-byte body
must remain independently gated. Retry only with fresh measurements and keep
all non-exact regions as asm.
