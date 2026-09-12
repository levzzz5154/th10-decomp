# Projectile runtime pair: `0x004067D0` and `0x00406D90`

## Result

Neither semantic candidate passed the independent exact extent-and-byte gate.
The exact assembly sources in `src/game/enemy_projectile_spawn.cpp` and
`src/game/projectile_command_runtime.cpp` remain unchanged, no proposal was
retained, and `regions.json` was not edited. The rejected candidate sources,
native-LTCG layout/context, and native build outputs were removed.

| Region | Live extent | Legacy extent | Native candidate | First mismatch |
| --- | ---: | ---: | ---: | --- |
| `0x004067D0` | 1472 | 1472 | 820 | `0x004067D0`: candidate `51`, retail `8B` |
| `0x00406D90` | 1454 | 1616 | 1356 | `0x00406D98`: candidate `28`, retail `10` |

For the spawn body, 51 of the candidate's 820 positions happened to equal
retail; the extent deficit was 652 bytes. For the command body, the first
eight bytes were exact (`55 8B EC 83 E4 F8 81 EC`) before the local-frame size
diverged (`0x228` candidate versus `0x210` retail); 105 of 1356 positions
equaled retail. The maintained-source focused probe is exact over both live
extents.

## Coupling and ABI evidence

`0x004073E0` calls the allocator at `0x00407458` with the spawn descriptor in
`EBX`, then pushes manager, column, row, and base angle. The allocator returns
with `RET 0x10`. Its entry first fetches the manager arguments from
`[ESP+4]`/`[ESP+8]`, then obtains the current pool record from manager `+0x10`.
An ordinary member candidate instead began `push ecx; push ebp; ...` and never
acquired the retail incoming-`EBX` shape.

The allocator calls `0x00406D90` with the newly initialized projectile in
`ECX` at `0x00406D10`. The other command caller, `0x00406240`, also loads its
projectile into `ECX` at `0x00406374`. The command body is therefore a normal
member-shaped callee, but opcode `0x400000` constructs a descriptor on its
aligned stack and calls `0x004073E0`, creating a recursion-capable
allocator/command cluster. That nested call uses retail register state not
represented by the archived vector/event abstraction.

The fresh native `/GL` pair produced `.text$01spawn = 0x334` bytes and
`.text$02commands = 0x54C` bytes at the requested addresses. It also emitted
an empty default `.text` contribution; the strict native-map validator rejects
that undeclared code-section marker. More importantly, both complete compiler
contributions already fail the required retail extents and bytes, so bypassing
the map check would not make either region promotable.

## Recovered behavior

The allocator scans at most 2000 projectile records of stride `0x7F0`, wraps
to manager `+0x60` when a record state at `+0xC36` is 5, and returns failure
when no record with active word `+0x446 == 0` is found. It derives speed from
descriptor fields `+0x18/+0x1C` and row count `+0x1F6`. Layout modes 0 through
8 generate paired fan, ring, half-step ring, and randomized angle/speed
patterns using fields `+0x10/+0x14`, columns at `+0x1F4`, and layout at
`+0x1F8`.

It initializes the chosen record's position, normalized angle, velocity,
animation/type tables, movement state, flags, and two embedded scheduler-like
objects; copies `0x1B0` bytes of commands from descriptor `+0x20` to projectile
`+0x464`; initializes command index from descriptor `+0x208`; executes the
initial command stream; publishes the entity; and advances the manager cursor
with the state-5 wrap rule.

The command executor processes at most 18 records of stride `0x18`, with
arguments at projectile `+0x464` and opcode at `+0x474`. Opcode zero stops;
`0x80000000` skips; a zero gate field at record `+0x14` stops once projectile
flags at `+0x43C` are active. The remaining opcodes initialize velocity,
acceleration, angular, scale, sound/effect, position, index-jump, and spawn
states. Opcode `0x400000` builds a `0x210`-byte spawn descriptor from current
position and command data, copies the command block, advances the command
cursor around the nested spawn, and optionally triggers the follow-up effect.

## Next dependency

The next useful attempt must compile a caller-faithful semantic slice of
`0x004073E0` together with the pair so native LTCG can prove the descriptor-in-
`EBX` allocator entry. It also needs exact semantic/custom-ABI definitions for
random float `0x0044BB20`, angle normalization `0x0044BC10`, velocity setup
`0x00408750`, publish/list insertion `0x00404F30`, post-spawn setup
`0x0043EE30`, scheduler reset `0x00405410`, angle-from-point `0x00426660`, and
the `0x00408030`/`0x0043DC90`/`0x0043DD10` effects. For `0x00406D90`, model
the nested descriptor as its real typed aggregate (including constructor/copy
semantics) so MSVC emits the retail `0x210` aligned frame without the
candidate's security-cookie expansion. The stale 1616-byte legacy command
extent must not be used; the authoritative live boundary is 1454 bytes ending
at the plain `RET` at `0x0040733D`.

## Focused caller/leaf follow-up

A second bounded native-LTCG probe added caller `0x004073E0` and semantic
forms of leaves `0x00404F30`, `0x00408030`, `0x00408750`, `0x0043DC90`, and
`0x0043DD10`. Existing exact semantic implementations at `0x0044BB20`,
`0x0044BC10`, `0x00405410`, and `0x00426660` were read-only bindings. No owned
candidate reached its independent exact gate:

| Region | Retail | Best native | First mismatch |
| --- | ---: | ---: | --- |
| `0x00404F30` bullet-slot construction | 202 | 103 | `0x00404F30`: `8B` vs retail `83` |
| `0x00406D90` command execution | 1454 | 926 | `0x00406D98`: `1C` vs retail `10` |
| `0x004073E0` grid emission | 194 | 162 | `0x004073E1`: `A1` vs retail `53` |
| `0x00408030` activation | 199 | 174 | `0x00408030`: `66` vs retail `51` |
| `0x00408750` polar vector | 30 | 28 | `0x00408750`: `D9` vs retail `51` |
| `0x0043DC90` resource queue | 123 | 108 | `0x0043DC94`: candidate SIB `F5` vs retail `FD` |
| `0x0043DD10` sound queue | 149 | 126 | `0x0043DD11`: candidate `05` vs retail `44` |

The final typed nested descriptor is exactly `0x210` bytes and contains no
byte array. This eliminated the earlier security-cookie references. It did
not reproduce the retail frame: native LTCG allocated `0x21C`, while retail
allocates `0x210`; both bodies first differ at that immediate. The remaining
12 bytes are compiler temporaries caused by source-level initialization and
the nested member call. The contribution remains 528 bytes short.

The caller context did not force the descriptor into retail `EAX` at
`0x004073E0` or preserve it in `EBX`. Retail starts
`push ecx; push ebx; mov ebx,eax`; native omitted the `EBX` save and loaded the
player global immediately. Thus its call of the read-only allocator could not
establish the allocator's descriptor-in-`EBX` convention. The queue leaves
also exposed missing caller allocation: `0x0043DC90` indexed its table with a
different register, and `0x0043DD10` loaded the scale global before the stack
argument rather than preserving sound id in `EBX` and manager in `ESI`.

Ordinary `cos`/`sin` source emitted separate `FCOS` and `FSIN` sequences for
`0x00408750`. Retail spills `ECX`, reloads the destination through `EAX`, and
uses one `FSINCOS`. The bullet constructor and activation leaf similarly need
their real inlined aggregate/timer types and caller register allocation;
abstract offset stores compile substantially smaller.

The fresh link retained an empty default `.text` marker, which the strict
native-map validator rejects. All contributions already failed extent or
bytes independently, so this was not the deciding rejection. All candidate,
layout, context, and native outputs were removed; the seven exact assembly
sources stayed unchanged, with no proposal or manifest edit.

The next dependency is a source-level caller chain that naturally keeps the
grid descriptor in `EAX` then `EBX`, plus the real typed projectile command
record and nested-pattern constructor whose initialization consumes no stack
beyond the `0x210` object. Queue recovery needs caller slices that naturally
hold resource id in `EDI`, or sound id/manager in `EBX`/`ESI`. For
`0x00404F30`, include semantic `0x00401DE0` and `0x0043E710` with their real
entity/timer aggregate constructors; for `0x00408030`, include `0x004086B0`
and `0x00448DB0` with the observed `ESI` state and transient `EDI` result
pointer. Until those shapes are proven, exact assembly remains production.
