# Player pickup sweep recovery note: 0x00428630

Historical experiments below are superseded by the complete genuine graph in
[the 2026-10-06 follow-up](player_hit_pickup_genuine_2026_10_06.md).
The corrected record/clock offsets are reflected here; the old temporary
compiler attempts below remain historical. Both target regions remain ASM.

Status: the production region remains the exact 1170-byte retail assembly
body in `msvc/src/game/player_pickup_sweep.cpp`.  A readable semantic
candidate and one task-local native-LTCG/custom-ABI cluster were probed and
reverted because neither was byte-exact.  No task-specific LTCG layout,
compiler-context source, proposal, or dependency promotion is retained for
this region.

## Proven contract and behavior

The live manifest and augmented Ghidra listing define the function as
`0x00428630..0x00428AC1` (1170 bytes), with a `__thiscall`-shaped entry:

- `ECX` is an optional result word.  It is cleared after the generation-equality
  early-out and before scanning slots; it is not touched by that early-out.
- The three stack arguments are the pickup manager, player center, and player
  size.  The player caller at `ida/th10.exe.c:21978` passes `0`, the global
  manager at `0x00477834`, and player fields at `+0x2c` and `+0xb0`.
- Equal manager generation words at `+0x474` and `+0x478` return zero.

The manager layout needed by this routine is:

```text
+0x0010  animation resource
+0x049c  128 pickup records, stride 0x5c; each starts with its own frame pair
+0x04e0  first record's handle column, not the beginning of the records
+0x350c  32 score/collision regions, stride 0x6c
```

Each slot uses position at `+0x14/+0x18`, transition scale at `+0x1c`,
velocity scale at `+0x2c`, state at `+0x40`, animation handle at `+0x44`,
collected at `+0x50`, initialized at `+0x54`, and descriptor at `+0x58`.
Descriptors use signed value at `+0x02`, width/height at `+0x0c/+0x10`,
type at `+0x1d`, collected script at `+0x20`, and a filter callback at
`+0x30`.

The slot sweep rejects state `0` and state `2`, then tests the pickup box
against the player box.  Type 3 uses the player's lower edge for the zero
playfield boundary; all other types use the pickup's upper edge.  There is no
descriptor-null guard after the state test in the retail body.  An optional
descriptor filter is called with the manager in `ECX`, the current pickup's
clock/record address (`manager + 0x49c + index*0x5c`) in `EDX`, and the player center on the stack; a
nonzero result rejects the pickup.

Accepted pickups are marked collected.  The first accepted, uninitialized
slot stops its current animation and marks itself initialized.  Type 3 adds
its signed descriptor value only when that pickup's own counter is at
interval 4.  Other types add the value, retire the current animation, create
`collected_script + 5` on layer 15, preserve the old animation field at
record `+0x2c`, set animation flag bit `0x4`, set transition scale to `0.1`,
set state to `2`, and multiply velocity scale by `0.125`.  Type 2 additionally
allocates an indicator with size `32.0`, speed `1.4`, style `13`, and
`value / 3` count.

After the 128 slots, the routine adds the result of the custom-ABI player
hit-test.  It then scans the 32 regions.  Bit 0 enables a region; a region is
skipped when its frame changed and the current frame is divisible by its
interval.  Bit 1 selects circular distance-squared testing.  Otherwise an
angle of zero selects an axis-aligned box, and any other angle rotates the
player-relative point by `-angle` before the box test.  An overlap adds the
region value, accumulates it, and clears the value once the limit is reached.

When the total is nonzero, the global score at `0x00474c44` increases by
`(total / 10 + 10) / 10` and is capped at `999999999` when it reaches one
billion.  The raw total is returned.

## Candidate and exactness result

The archived semantic source supplies the high-level behavior; IDA/Ghidra and
the caller establish the exact fields and custom call arguments above.  The
archived public structs were not used verbatim:
the live disassembly shows the first pickup/clock at `+0x49c`, its handle at `+0x4e0`,
and the region records at `+0x350c`; the older 1520-byte coverage record is
stale relative to the live 1170-byte manifest region.

A temporary readable candidate used padded behavioral structs, a named member
method, and bounded inline call shims for the observed custom conventions.
It emitted 1156 bytes rather than the required 1170.  The first bytes were:

```text
retail:   83 ec 40 55 8b 6c 24 48 8b 85 78 04 00 00 3b 85
candidate:55 8b ec 83 ec 38 53 56 57 8b 7d 08 8b 87 78 04
```

The shims force a conventional EBP frame (`push ebp; mov ebp,esp`) and do
not reproduce the retail frame/stack-slot reuse.  The candidate was rejected
by the focused probe and is not present in the production source or manifest.

## Native-LTCG context attempt

A second bounded attempt used temporary task-local layout/context files and
the owned source as a native `/GL` translation unit.  The source modeled the
observed caller-side setup explicitly: `0x0040c480` received `EAX = &slot +
0x44`; `0x00449450` and `0x00449630` received `ESI = &slot + 0x44`;
`0x00448d00` received its scratch result in `EDI` with resource/script/layer
on the stack; and `0x004059f0` received the player center in `EAX` and the
global player object in `ECX`.  The synthetic context repeatedly invoked the
named member through the same manager/center/size shape.

The fresh native image was rejected before production integration.  Its map
placed `.text$01pickup` at `0x00428630` with contribution length `0x453`
(1107 bytes), while the required focused extent is `0x492` (1170 bytes).
The context contribution landed at `0x00428bd0` with length `0x8b`, rather
than the temporary requested context address `0x00428c00`; the image also
contained an empty default `.text` marker from the inline-assembly helpers,
which the native map gate rejects.  Directly reading the fresh body gives:

```text
retail:  83 ec 40 55 8b 6c 24 48 8b 85 78 04 00 00 3b 85
native:  55 8b ec 83 ec 28 53 56 8b 75 0c 8b 86 78 04 00
first difference: 0x00428630
different prefix bytes: 1068 of 1107
extent deficit: 63 bytes
```

The closest native shape therefore remains a normal EBP-framed member
(`push ebp; mov ebp,esp; sub esp,28h`), not the retail frameless
`sub esp,40h; push ebp; mov ebp,[esp+48h]` entry.  The temporary cluster,
context, proposal, and any generated native image were deleted; the
production source hash was restored to the archived exact body, and the
target manifest entry was not changed.

## Next dependency

The next useful dependency is a compiler route that owns the sweep caller and
the custom-ABI edges in one whole-program/native-LTCG context, while allowing
the call sites themselves to preserve `EAX`, `ESI`, and `EDI` conventions and
the retail stack-slot reuse.  Promoting `0x0040c480`, `0x00449450`,
`0x00449630`, `0x00448d00`, or `0x004059f0` alone cannot repair a standalone
translation unit's call sites.  A future conversion must first make that
multi-source ABI capability reproduce the frameless entry, then pass the
focused 1170-byte extent-and-bytes gate before changing the manifest entry;
until then the exact assembly is the only accepted production representation.
