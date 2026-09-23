# 0x00408030 activation leaf: live Ghidra recovery

## Decision

Keep the production body in [score_state_activate_from_result_retail_00408030.cpp](../../msvc/src/game/score_state_activate_from_result_retail_00408030.cpp)
unchanged for now. Its control flow is recoverable, but the current function
entry has a private register ABI that a normal MSVC C++ declaration cannot
express: callers supply the state pointer in ESI, while the function has no
Ghidra parameters. The earlier native candidate therefore did not match even
at its first byte. Converting this leaf alone would require retaining an
assembly entry shim, changing every caller, or measuring a larger caller and
callee cluster; the first option would leave inline assembly in the requested
result.

This audit used the connected Ghidra program `th10.exe` (32-bit x86, image
base `0x00400000`) and read-only calls for function metadata, decompilation,
disassembly, call xrefs, and variable/P-code views. No build, probe, or test was
run.

## Recovered behavior

Ghidra's entry is `undefined4 __stdcall FUN_00408030(void)`, body
`0x00408030..0x004080F6` (199 bytes). The signature omits the actual state
input: the first instruction saves ECX, and the body reads and writes the
object through ESI throughout. It returns a Boolean-like value in EAX and
restores ECX on every return path.

The recovered transition is:

1. Read the 16-bit state at `+0x446`. If it is neither 1 nor 2, return 0
   without changing the object.
2. Call `0x004086B0` on the position at `+0x3B4` with two `8.0f` extents. That
   helper uses ECX for the position, consumes two stack floats, and returns 0
   when the position is inside the axis-aligned bounds or 1 when it is outside.
3. Set the word at `+0x30C` to 1 and the phase at `+0x446` to 3.
4. If the bounds helper returned 1, OR bit 3 into the state flags at `+0` and
   return 1.
5. Otherwise, if the signed value at `+0x438` is nonnegative, call
   `0x00448DB0` to create/register the associated animation. The call supplies
   three stack values and uses EDI for the position record; the callee returns
   with `ret 0xC`.
6. On the in-bounds path, initialize the timer at `+0x3F8..+0x408` if its bit
   0 is clear: previous `0xFFF0BDC1`, current 0, elapsed 0, speed pointer
   `0x00476F78`, and set bit 0. Then set current and elapsed to 0 and previous
   to `-1`; return 1.

The paired entity sources support the phase interpretation: the projectile
spawn body writes phase 1 at `0x00406A83` and phase 2 at `0x00406C66` in
`enemy_projectile_spawn.cpp`; this leaf accepts either and moves it to 3.
Several callers walk 2000 records at `0x7F0`-byte strides.

## Caller and callee evidence

Ghidra's direct xrefs list eight call sites across five source bodies:

| Caller body | Call sites | Evidence for the state in ESI |
| --- | --- | --- |
| `0x00406D90` projectile command runtime | `0x004070E0`, `0x00407243` | Both sites first move the receiver from EBP to ESI. |
| `0x00408100` entity-range scan | `0x004081B2` | The loop holds the current `0x7F0`-stride record in ESI. |
| `0x00415B00` stage/runtime update | `0x00415D62` | The loop checks `[ESI+0x446]` and advances ESI by `0x7F0`. |
| `0x00425730` player/runtime update | `0x00425879`, `0x00425A59`, `0x00425D55` | Each loop checks and advances the ESI record. |
| `0x00408460` unassigned sweep fragment | `0x0040848D` | The fragment moves EAX to ESI, then scans records with the same stride. |

The fifth body is not present in Ghidra's function table: the live xref at
`0x0040848D` points into the manifest-owned
`src/unidentified/unassigned_00408460.cpp` fragment. It does not appear in
Ghidra's four-name `get_function_callers` result, so the xref list and caller
source were checked separately.

The two direct callees are `0x004086B0` and `0x00448DB0`. The first is a
small bounds helper with a representable ECX-plus-two-float shape. The second
is not a normal stack-only helper: its body at `0x00448DB0..0x00448E25` reads
the position from EDI, the resource from the stack and ECX, and other values
from its stack frame; it calls `0x00449950`, `0x0043E710`, and `0x004489D0`.
The animation loader uses EAX for the animation object, ECX for its resource,
and EBX for the index. The list-registration helper takes its manager in EDX
and entity/record values in EBX/EAX. These register contracts are also
documented by the adjacent
[`animation_manager_create_positioned_primary_00448d50.cpp`](../../msvc/src/render/animation_manager_create_positioned_primary_00448d50.cpp)
recovery source. `0x00448DB0` itself has 16 direct xrefs across 13 caller
functions, so it is a separate, wide recovery cluster.

## Why the existing candidate misses

The prior candidate made the object a typed C++ argument and represented the
bounds result and animation creation as ordinary helper parameters. The
recorded probe produced 174 bytes against the 199-byte retail body and first
differed at `0x00408030` (`0x66` versus retail `0x51`). A later cdecl helper
variant produced 219 bytes and also differed at entry. The current production
comment records that result as blocker D2701. Both are consistent with the
live entry: the original starts `push ecx; mov ax,[esi+0x446]`, with no
instruction to receive a C++ `this` pointer in ECX or a stack argument.

Changing only the call declaration cannot solve this. There are eight direct
call sites in five separately owned assembly fragments, and one caller is
still explicitly unassigned. The animation side then crosses the private
register ABIs at `0x00448DB0`, `0x00449950`, `0x0043E710`, and `0x004489D0`.
The smallest coherent next investigation is therefore a native-LTCG slice
that models all five current caller bodies, this state transition, and the
animation creation path with its real record layouts and helper contracts.
The previous `projectile_runtime_004067d0_00406d90.md` note already identifies
the 0x408030 / 0x4086B0 / 0x448DB0 relationship; this audit adds the omitted
0x408460 call site and the full live xref inventory. Until that cluster can
replace the ESI entry without an assembly shim, retain the byte-exact body.
