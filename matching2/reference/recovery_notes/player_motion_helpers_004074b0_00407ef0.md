# Player motion helper models at 0x004074B0–0x00407EF0

Live `th10.exe` inspection confirms that the six region entries are leaf state
updates reached directly from `FUN_00406240`. Its call sites load the player
object into ESI before calling `0x004074B0`, `0x00407560`, `0x004076A0`, and
`0x00407EF0`; they load it into EBX before calling `0x00407DA0` and
`0x00407E40`. The caller ignores every helper's return value. These are
therefore modeled as ordinary `void` member operations on offset-backed player
state, but the retail ESI/EBX call edges still need a whole-cluster/LTCG
rewrite before the candidates can replace the current private-register entry
points.

The six typed C++ method candidates are preserved under
`matching2/reference/semantic_candidates`. The mapped files under
`matching2/msvc/src` retain the retail assembly entries because their callers
supply the state in ESI or EBX. The manifest rows remain `asm`; these models
were not built, probed, or tested.

| Address | Direct call in `FUN_00406240` | Recovered state operation |
| --- | --- | --- |
| `0x004074B0` | `0x0040638F`, ESI = player | For animation timer `+0x614`, emit the trail polar vector at `+0x3C0` while current frame `+0x618` is at most 16; otherwise toggle player bit 0. Copy current to previous, then advance elapsed/current from the pointed frame scale. |
| `0x00407560` | `0x0040639F`, ESI = player | While timer `+0x648` is below deadline `+0x670`, integrate scalar `+0x3D8` and velocity `+0x3C0..+0x3C8` from fields `+0x65C` and `+0x664..+0x66C`; refresh heading `+0x3E4` when either planar velocity component exceeds the `0x00470C58` threshold. Otherwise clear flag `0x10`. Then advance the embedded timer. |
| `0x004076A0` | `0x004063AF`, ESI = player | Before deadline `+0x6A4`, normalize heading `+0x3E4` by the scaled rate at `+0x694`, advance scalar `+0x3D8` by the scaled rate at `+0x690`, and set the polar vector at `+0x3C0`. At the deadline clear flag `0x20`. Then advance the timer at `+0x67C`. |
| `0x00407DA0` | `0x00406533`, EBX = player | Check position `+0x3B4` against the bounds object at `+0x39C`; if outside, wrap its x coordinate using bounds field `+0x34` and playfield limits `0x00470B40`/`0x00470B3C`. A wrap advances the timer at `+0x74C` by -1 and queues the resource in `+0x458` when nonnegative. If the timer count is nonpositive, toggle flag `0x100000`. |
| `0x00407E40` | `0x00406546`, EBX = player | The vertical counterpart checks position `+0x3B8`, wraps using bounds field `+0x30` and limits `0x00470B70`/`0x00470B38`, advances timer `+0x780` by -1, queues the same resource, and toggles flag `0x200000` when the timer count is nonpositive. |
| `0x00407EF0` | `0x00406408`, ESI = player | Before deadline `+0x7DC`, aim from player position `+0x3B4/+0x3B8` toward the pointed target's `+0x3C0/+0x3C4`, limit the angle step with fields `+0x7CC` and `+0x7C8`, normalize the heading, and update the polar vector. At the deadline clear flag `0x04000000`. Then advance timer `+0x7B4`. |

## Callee contracts at the call edges

- `0x00408750` (`PolarVector2_00408750::SetPolar`) is already a semantic
  two-float member operation. Its retail call uses ECX for the vector and two
  stack floats (`RET 8`).
- `0x0044BC10` and `0x00408660` are semantic angle helpers with float arguments
  and x87 `ST(0)` results. `0x004076A0` and `0x00407EF0` call these through the
  source-level angle APIs.
- `0x004061D0` is the semantic inclusive playfield check: ECX is the point,
  two float extents are on the stack, and EAX is nonzero when wrapping is
  requested. Both wrap candidates use that method instead of carrying its
  volatile ECX/EDX values across a call.
- `0x0044BF40` is the semantic `FrameTimer::Advance(float)` operation. The
  current retail body receives its timer object in ESI, so the source-level
  call still depends on cluster selection of the private receiver register.
- `0x0043DC90` is the semantic queue operation. The wrap callers use ECX for
  the queue object, EDI for the resource id, and one stack request value; the
  source candidates express it as `SoundQueue::Queue(id, request)` for the
  later cluster rewrite.
- `0x00463B2C` is a private conversion helper with its input in x87 `ST(0)` and
  integer result in EAX (EDX:EAX is also produced). The timer candidates use
  ordinary float-to-int conversion at the point where the current count is
  recomputed, leaving the exact conversion lowering to the integration pass.

The prior D3704, D3605, D3601, and D3702 source attempts, and the restored
vertical-wrap D3706 candidate, document earlier code-generation mismatches.
Those measurements do not measure these new source candidates. The horizontal
and vertical models retain offset-only names for the bounds and timer fields
whose higher-level ownership remains unconfirmed.
