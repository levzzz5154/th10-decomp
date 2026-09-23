# Laser segment cut cluster recovery (0x0041D880–0x0041EFA0)

## Scope and result

The four entries were audited but remain in their retail assembly source.
Ordinary C++ can express their `__thiscall` entry ABI, and readable candidate
bodies were explored. Those candidates were not retained because they omitted
per-hit effects, animation registration, and later clear-segment creation,
which materially changes collision behavior. The Ghidra findings below
record the control flow and the dependencies needed for a complete recovery.

## Live Ghidra evidence

The open `th10.exe` program reports these original signatures:

| Address | Decompiled signature | Core test |
| --- | --- | --- |
| `0x0041D880` | `int __thiscall (this, float*, float*, int)` | Sample points against an axis-aligned box centered at the first vector, with half-size from the second vector. |
| `0x0041DD80` | `int __thiscall (this, float*, float, int)` | Sample points against a 2D point and radius. |
| `0x0041EB00` | `int __thiscall (this, float*, float*, int)` | Same box predicate, with the alternate leading-hit handling. |
| `0x0041EFA0` | `int __thiscall (this, float*, float, int)` | Same radius predicate, with the alternate leading-hit handling. |

All sample from the laser position at `this + 0x24`, use the angle at `this + 0x3c`, and read length at `this + 0x40`. The live data bytes identify `0x00470B0C` as `0.5f`, `0x00470CD8` as `12.0f`, `0x00470D1C` as `24.0f`, and `0x00470C0C` as `18.0f`. The vector helper at `0x0041F800` is already a semantic `PolarVector2_0041F800::SetPolar` definition in `src/math/vector.cpp`; the recovered bodies call it to make the initial six-unit sample offset.

The standard pair (`D880`, `DD80`) moves the primary object past leading hit samples, reduces its length, and retains the first clear run after that. Its state writes include the dead byte at `+0x50`, prior visible length at `+0x434`, and removed distance at `+0x4c`. The alternate pair (`EB00`, `EFA0`) instead sets the length at `+0x40` to zero when the first sampled span is hit, or keeps the initial clear run when sampling begins outside the collision area.

## Remaining behavior and dependency boundary

Each original body also performs behavior that a standalone replacement must
preserve:

- All four call `FUN_0041BB00` for conditional hit effects.
- The four bodies create or register hit animations through `FUN_00448DB0`, `FUN_00449950`, `FUN_0043E710`, and `FUN_004489D0`.
- They submit one child laser object for each later clear run through `FUN_0041C510`. Ghidra shows that routine reads its manager through `ESI` and the callers prepare a large temporary object image on the stack. Recreating that operation through an ordinary typed call requires an ABI bridge or recovered object API, neither of which belongs to these four bodies.

The sample-predicate and primary-span logic alone is insufficient for
promotion: it drops subsequent clear spans and collision-triggered
visuals/effects. The trigonometric helper may also differ in rounding from
retail's x87 sequence. The original 260-byte local hit mask follows the
observed stack allocation and 256-byte clear; game lengths are assumed to stay
within the normal sample range.

## Entry ABI for a future complete implementation

The Ghidra signatures are `__thiscall`: receiver in ECX, then three 32-bit
stack arguments, with an integer result in EAX. An `extern "C" int __fastcall`
shim with `(void* self, void* unused_edx, ...)` keeps the receiver in ECX,
ignores EDX, and leaves all three real arguments on the stack. The decorated
MSVC x86 linker names end in `@12`:

- `@LaserSegment_CutAgainstBox_0041D880@12` at `0x0041D880`
- `@LaserSegment_CutAgainstRadius_0041DD80@12` at `0x0041DD80`
- `@LaserSegment_CutAgainstBox_0041EB00@12` at `0x0041EB00`
- `@LaserSegment_CutAgainstRadius_0041EFA0@12` at `0x0041EFA0`

If complete semantic bodies are recovered, update the four `regions.json`
anchor symbols to those names and bind the corresponding linker aliases. No
caller changes are indicated because the ABI visible to existing thiscall
call sites remains the same.

No build, probe, or test was run, per task instruction.
