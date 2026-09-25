# Pause-menu/state initializer `0x00422AB0`

The 382-byte region (`0x00422AB0..0x00422C2D`) now has an inline-assembly-free
C++ semantic model in
[`matching2/msvc/src/game/fun_00422ab0_00422ab0.cpp`](../semantic_candidates/fun_00422ab0_00422ab0.cpp).
The manifest marks the row semantic and binds its recovered stdcall symbol;
`asm_symbols.hpp` declares the one-pointer `__stdcall` entry.

## Behavior and state offsets

The routine sets `state+0x04` to 1. If bit 0 of `state+0x20` is clear, it
initializes `+0x14` to 0, `+0x10` to `0xFFF0BDC1`, `+0x18` to 0, and `+0x1C`
to the address `0x00476F78`, then sets that flag bit. It then unconditionally
resets `+0x14` and `+0x18` to 0 and `+0x10` to `0xFFFFFFFF`. The code does not
establish the semantic names of those fields, so the C++ keeps them as offsets.

It sets bit `0x10` in the dword at the object pointed to by `0x00477810`, offset
`+0x58`. It creates two animation objects from the pool reached through
`0x00491C10`, initializes them from resource pointers at
`[*0x004776E0+0x8998]` and `[*0x0047770C+0x9EC8]`, and registers them in the
secondary animation list with script indexes 0 and `0x79`. Before each script
load it stores `0x0F` at object `+0x20` and ORs `0x40000000` into `+0x35C`.
The resulting handles go to state `+0x1D8` and `+0x1D4`, respectively. Those
fields are treated as handles/IDs based on subsequent calls; their higher-level
names remain unverified.

The first handle and `(0x20, 0x10, 0x180, 0x1C0)` update the descriptor at the
animation manager. The source expands this work directly into ordinary C++:
it resolves the first handle, reads the animation resource, converts floats at
resource offsets `+0x30`, `+0x34`, `+0x0C`, and `+0x08` in that order, then
checks the signed dword at manager `+0x04`. If that dword is negative, it
stores the pointed handle at manager `+0x04`, the four inputs at `+0x08..+0x14`,
the converted values at `+0x18..+0x24` in retail order, and zero at `+0x28`.
The second handle is stopped at frame 3. The initializer then queues sound
`0x20` with request 0 and registers resource `"Pause"` with values 6 and 0. If
`[*0x00477810+0x5C]` is nonzero, it searches the first handle's children for
script index `0x75`, sets the animation flag for a match, and clears the
temporary result. At the end, state `+0x2C0` receives the current bits at
`0x00476F78`, and that global is set to `1.0f`.

## Entry ABI and call graph

Ghidra reports `void __stdcall FUN_00422ab0(int param_1)`: one pointer at
`[ESP+4]`, no private register input at entry, and `RET 4`. The binary preserves
EBX, EBP, ESI, and EDI. Its only direct caller is `FUN_004223F0`, which pushes
ESI and calls it at `0x0042243B`. The return value is not consumed by the caller.

The direct callees, in retail order, are:

| Address | Observed role and retail inputs |
| --- | --- |
| `0x00449950` | Allocate an animation object; manager in ESI, result in EAX. |
| `0x00449870` | Initialize/load an object; resource receiver in ECX, object and script index on the stack, `RET 8`. |
| `0x00448AC0` | Register the secondary-list object; output pointer in EAX, manager in EDX, object in EBX. It writes the assigned handle to the object and output slot. |
| `0x00424480` | Update the descriptor for the first handle; private receiver in ESI, then handle and `0x20, 0x10, 0x180, 0x1C0` on the stack, `RET 0x14`. It calls `0x004491C0` and `0x00463B2C`. |
| `0x0040C4D0` | Stop the second handle and unflagged descendants at frame 3; handle address in EAX, with manager context loaded into EDX by the helper. It calls `0x004491C0`. |
| `0x0043DC90` | Queue sound; queue object at `0x00492590` in ECX, sound ID `0x20` in EDI, request 0 on the stack. |
| `0x0043E460` | Register `"Pause"`; manager/base in EAX, string in EDX, values 6 and 0 on the stack, `RET 8`. |
| `0x004497D0` | Find child script index `0x75`; root-handle pointer in ESI, index in EBX, output pointer in EDI. |
| `0x004492A0` | Set the matching animation flag; manager context in EDX, ID on the stack, `RET 4`. The instructions do not read ECX. |

The source expands `0x00448AC0`, `0x0043E460`, and `0x004497D0` into readable
offset-based operations because their register-only input tuples do not have
ordinary C++ call signatures. It also expands the descriptor operations
inline; there is no C++ call through retail `0x00424480` and no reference to a
source-only helper symbol. The layout contains the maintained semantic
`Entity_Init` body through its small compiler-context file, so the allocator's
heap fallback sees that existing body without adding a synthetic caller.

## Exactness and integration limits

This source is a semantic model, not a byte-match claim. Live Ghidra disassembly
confirms that the stdcall entry has only its stack pointer argument, while the
two allocator calls use an internal ESI receiver:

* The caller `0x004223F0` pushes ESI at `0x0042243A` and calls this routine at
  `0x0042243B`; the initializer ends with `RET 4`.
* At the first allocation, `0x00422AFD` loads `0x00491C10` into ESI and
  `0x00422B09` calls `0x00449950` without another receiver setup.
* At the second allocation, `0x00422B33` reloads `0x00491C10` into ESI;
  `0x00422B74` calls `0x00449950`. The intervening register-list and
  descriptor calls preserve ESI.
* `0x00449950` starts by reading `[ESI+0x3AD068]` and uses ESI for the pool
  base throughout. Ghidra identifies no stack parameters for this function.

The edge is expressible from ordinary C++ in a native-LTCG caller context. The
measured context in
[`animation_pool_visibility_boundary_00449950.md`](animation_pool_visibility_boundary_00449950.md)
uses the same `pool->Allocate()` member-call form with the allocator definition
visible. LTCG selected ESI for the manager and emitted the allocator's
non-heap path byte-for-byte. That proves the source model need not add inline
assembly to represent this edge. The candidate
[`pause_menu_animation_pool_00422ab0.json`](../../layout/ltcg/pause_menu_animation_pool_00422ab0.json)
uses the actual typed initializer as the schema-2 entry and records the two
Ghidra allocator callsites and the allocator's two real initializer callsites;
it does not introduce a synthetic caller. `Entity_Init` has a maintained
semantic owner at `src/game/entity_initialize_00401de0.cpp` and a stable
`__fastcall` ABI: the entity is in EDX, ECX is not read or written, and the
function uses plain `RET`. Its fixed target extent is 273 bytes. The layout's
context file only places that existing body in the candidate's compiler view.
All extents and addresses in the layout are retail target measurements; native
context sizes and lowering are unmeasured.

The allocator's heap path has a known LTCG visibility boundary. The recovery
measurements in
[`00449950_wave10.md`](00449950_wave10.md) found 153 bytes with the `Entity_Init`
body visible, because LTCG keeps the returned object in EDX when it knows that
the callee preserves EDX; declaration-only compilation produced 163 bytes and
materialized the dead ECX fastcall slot. Retail is 161 bytes: it omits ECX setup
but keeps the object in EDI across `Entity_Init`. A single all-`/GL` source
cluster cannot express that mixed visibility/clobber boundary. The current
context includes the real semantic body, so heap-path behavior is available to
LTCG, but it does not claim the 161-byte allocator result. The absolute
bindings for `Queue`, `StopAtFrame3`, and `SetFlag` are address evidence, not
proof that their call conventions compose correctly in this combined link.
This static-only follow-up does not verify either allocator call enters with
ESI in this full initializer context.

The descriptor evidence from live Ghidra is precise: callsite `0x00422B5D`
passes the first handle and four dwords to `0x00424480`; ESI is the descriptor
receiver, while lookup reloads manager global `0x00491C10` and calls
`0x004491C0`. Four calls to `0x00463B2C` convert the resource floats before the
signed availability guard. The semantic C++ keeps that lookup, conversion, and
store order. `static_cast<int>(float)` expresses the normal conversion but does
not claim identical exceptional behavior for NaN or out-of-range values.
Retail `0x00424480` remains a private-ESI/`RET 0x14` entry for its other callers;
this initializer model no longer calls it.

The concrete next integration step is a linker visibility control that lets the
allocator know the initializer's ECX slot is dead without letting LTCG assume
EDX survives the call, followed by a native layout check of both real
`Allocate` callsites for ESI equal to `0x00491C10`, the initializer's one-pointer
stdcall entry, and unchanged semantic effects. No synthetic caller or assembly
thunk is needed to state the current source candidate, but its full-context
lowering remains unverified.

Other private edges remain separate integration limits: retail `0x00424480`
still requires ESI and `RET 0x14` for its other callers; `0x00448AC0` takes EAX/EDX/EBX,
`0x0043E460` takes EAX/EDX and stack values, and `0x004497D0` takes ESI/EBX/EDI.
`0x0043E460` and `0x004497D0` retain dedicated blocker evidence in their source
files. The sound queue, handle stop, and flag setter already have C++ semantic
models, but their production call-site conventions still need cluster-level
integration.

The recovered function symbol is `_asm_FUN_00422ab0_00422ab0@4`. Its sole
caller remains inline assembly and pushes the state pointer before calling the
entry. The source uses typed `AnimationPool::Allocate` member calls and expands
the descriptor effects as C++ operations. The 161-byte heap fallback and the
ESI choice in this full caller remain unverified. No build, probe, or test was
run.

Ghidra now names the function `InitializePauseMenuState` and records the
one-pointer `__stdcall` prototype. Its plate comment captures the observed
state changes and the helper-call register caveats.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
