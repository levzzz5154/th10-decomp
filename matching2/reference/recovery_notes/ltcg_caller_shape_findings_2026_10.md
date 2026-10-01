# Native-LTCG source-shape findings (October 2026)

Collected while converting small private-ABI wrappers to ordinary C++. Each
item was confirmed by an EXACT probe of the named region.

## Parameter order decides evaluation order, not just the ABI

Under LTCG the callee's registers come from its body, so the declared order of
its parameters is free -- but the *caller* still evaluates arguments right to
left in declared order, and that fixes which operand is loaded first.

* `0x0041BE40` (`Item_0041b8e0::EnterState2`) only matched after
  `Entity_StartScript_00404f30` was declared `(entity, resource, script)`:
  the script expression is then evaluated first and takes EAX, so the stage
  pointer has to go to ECX as in retail.
* `0x00449EB0` (`D3DResourceManager_00449eb0::ReleaseResources`) needs the
  list release declared `(owner, list)` so `lea eax,[edi+24h]` is formed
  before `push edi`.

When a body matches except for "register A and B swapped" or "load placed
before/after a push", permute the callee's parameter list before anything else.

## `this` is loaded before other stack parameters

`0x0043D640` stores `owner->pending[index]`. As a free function
`(filename, owner, index)` the compiler loads `index` first (ECX) and the owner
second (EDX); as a member `owner->LoadPendingSlot(filename, index)` it loads
the owner first, which is retail's order. The stack layout is identical.

## Receiver registers come from the synthetic caller

* A context that walks an array and calls a member gives ESI or EDI receivers
  when the callee itself calls something (`0x0043DA80`, `0x00449EB0`).
* A rooted `__fastcall` wrapper keeps public ECX and hands the callee its
  private register (`0x00427AD0` -> EDI receiver of `0x00427AE0`).

## Stand-in anchors must not leak register preservation

A tiny stand-in callee tells the link that EAX/ECX/EDX survive the call, and
the caller then keeps values in them (`0x0040D730` kept the object in EAX).
Have the stand-in call an external (absolute) symbol so it clobbers the
volatile registers like the real routine does.

## Return-block layout

`0x0043DA80`: `if (!a || f() < 0) return -1;` puts the failure return last;
two separate `if (...) return -1;` statements put it in the middle, as retail.

## Layout mechanics

* When a context function grows, later gaps move: read the new size from
  `cluster.map` and shift the following gap.
* Unreferenced `extern` functions from an included driver are discarded
  (zero-length contribution); do not list them as anchors.
* If a cluster has `.rdata` placed after `.text`, the `.text` gaps must still
  tile up to the original end of `.text`.
* A side-by-side disassembly diff of zero lines is not proof; always finish
  with `probe.py` reporting EXACT.

## A store written before a read-modify-write lands inside it

`x->a = 15; x->flags |= M;` compiles to `load flags; or; store a; store flags`
(the constant store is scheduled just before the last store of its block), so
retail's "split OR with an unrelated store in the middle" means the unrelated
store comes *first* in the source (`0x0042C670`).

## Small counted loops are unrolled

`0x00405500` clears a bit in seven of eight array elements. Seven separate
statements let the scheduler pair the preceding `pending_state = 0` store with
the last of them; `for (i = 0; i < 8; ++i) if (i != 2) e[i].flags &= ~2u;`
is unrolled by the compiler and reproduces retail, including the register
roles.

## Existing anchors can already be the answer

Several clusters carry a C++ "anchor" for a region that is still assembly.
`0x0040B9F0` and `0x0042C670` were one statement away from exact; compare
anchor bytes with retail before writing anything new.

## Still unresolved

* `0x00420B10` (`Music_Play`): final store wants the global base loaded before
  the stack index; every source shape tried loads the index first.
* `0x00449870`: retail keeps `this` in ECX through two vector resets and splits
  the flag OR into load/or/store; no source shape found.
* `0x0042A3E0`: all instructions match, but failing branches target the other
  `ret`.

## 0x00442300 (channel +0x108 starter) — parked

`StartChannel208` (0x00441F50) is exact as a member taking
`(int end_time, unsigned char mode, unsigned char initial, unsigned char goal)`:
object EAX, duration ECX, mode DL, RET 8.  The sibling at 0x00442300 keeps
mode, initial and goal all on the stack (RET 12) and loads each with
`movzx ecx, byte [esp+N]` immediately before its store.

Tried without success:
- the same signature: mode is enregistered in DL (RET 8), whatever the
  parameter order and whatever the callers pass (constant 0, byte load,
  truncated int);
- `int mode` or a one-byte struct by value: mode stays on the stack, but its
  load is hoisted above the `end_time` store into EDX (4-line diff);
- an extra unused parameter: removed entirely by LTCG.

Open question: what keeps a plain byte parameter out of DL in retail while
its load stays in source order.

## 0x00449A50 / 0x00449A70 (scheduler task reset) — parked

Both are unreferenced in retail (Ghidra: no xrefs) and reset a
`SchedulerTask` in EAX: `on_tick` (0, or ECX), `on_register`, `on_remove`,
`priority`, clear `heap_owned`, `link = {this, 0, 0}`.  Retail loads the flag
word first, performs the four stores, and only then masks and stores it.
Every source order tried (bitfield, explicit mask, shared inline helper,
explicit early read) places `and edx, ~1` directly after `xor ecx, ecx`, or
folds it into `and dword [eax+4], ~1`.

## 0x0040C9A0 (enemy drop release) — parked

`if (drops->main_item > 0) { item_manager->Spawn(position, main_item, -1,
-pi/2, 2.2f); drops->ScatterExtras(); main_item = 0; }` compiled in the
cluster that carries the real `ItemSpawnManager::Spawn` anchor produces the
right statements, but LTCG takes `position` in ECX (forwarding it to Spawn
untouched) and the drop record in ESI.  Retail takes `position` in EAX, copies
it to ESI, and takes the drop record in EDI.  Member vs free function,
parameter order and a retail-like dispatch-loop caller made no difference.

## 0x00442050 / 0x00442220 (colour interpolation starters) — exact

Shape that reproduces retail: store `end_time`, assign both control triples
from `AnimationColorComponents(0, 0, 0)` (member-initialiser order gives the
three ascending `xor`s), store `mode`, then build two *named locals* from the
byte pointers with a constructor that assigns blue, green, red (last component
first) and copy them to `initial` and `goal`.  Temporaries passed to an inline
setter, or a constructor in ascending order, scramble the six byte loads.

Follow-up on 0x00442300: with every byte parameter typed `int` and truncated
in the body, all three stay on the stack (RET 12) as in retail, but the mode
load is still hoisted into EDX above the `end_time` store.

## 0x0040B070 / 0x0040B110 (effect spawners) — parked, 0x0040B110 two lines off

Both are unreferenced in retail.  They index the 16-byte table at 0x00474430
(`short script; initialize; on_tick; on_draw`), allocate an animation object,
put it in render bucket 15 with flag 0x40000000, run the script, register it
at the back of the primary list, look it up again (zeroing the handle when it
is gone), call the optional initializer and copy the two callbacks to
+0x398/+0x39C.  Findings:

- The handle is **returned by value through a hidden pointer** (a class type
  with a constructor): retail loads the pointer into EAX last and returns it.
  An explicit `out` parameter makes the compiler use EDX and load it earlier.
- The shared stand-in for 0x004489D0 must clobber EDX (re-read the id counter
  instead of caching it); otherwise the caller keeps the manager in EDX across
  the call where retail reloads it into ESI.  That makes the stand-in 114
  bytes instead of 103 in the three clusters that carry it (not applied).
- 0x0040B110 then differs only in `shl eax, 4` being placed before
  `push esi` / the manager load instead of after it.
- 0x0040B070 takes its owner on the stack in retail (owner, hidden return,
  argument; RET 12); LTCG here always moves the owner to ECX, as a member
  (thiscall or stdcall) or as a free function.

Attempt saved in the session scratch as `parked_40b070/`.

## 0x00446C70 (ANM texture upload) — exact; three rules for LTCG argument homes

1. **A parameter the callee assigns to keeps its stack home; a read-only
   parameter is eligible for a register.**  With `format = 5` written to the
   parameter, `format` stayed on the stack.  Copying it to a local
   (`int stored_format = format;`) and narrowing the local put `format` in
   EAX with a separate frame slot, as in retail.
2. **An unused scalar parameter is deleted outright (caller stops passing
   it), `this` included, but an unused class-type by-value parameter keeps
   its stack slot.**  Retail's never-read first stack argument (RET 8) is
   reproduced by a four-byte struct passed by value; `int`, `float`, a dead
   local initialised from it, a dead store to it and an unused `this` are all
   removed.
3. **Repeating an inline accessor instead of naming the pointer changes the
   address computation.**  `entry->Thtx()->field` at every use gives
   `mov ecx,[esi+0x30]; lea eax,[ecx+esi]`; a named `thtx` local gives
   `mov eax,[esi+0x30]; add eax,esi` however the sum is spelled.

Rule 1 is worth retrying on parked functions whose register arguments came
out on the stack or vice versa (0x0040B070's owner slot is overwritten with
the resource, i.e. the parameter itself is reassigned).

## 0x00446B70 (ANM texture load from archive file) — exact; /GS shadow copies reveal pointer parameters

- Shares the `anm_texture_upload_00446c70` cluster as an additional source. A
  stand-in `Archive_LoadFile` took a wholly private convention (ESI/EBX/EAX)
  and stole the callee-saved registers; including the real
  `native_archive_read` closure (read/find/decrypt/load at their retail
  addresses) gives the retail contract (name in EAX, two stack arguments).
- Retail copies the first stack argument into a local directly after storing
  the security cookie and passes the *local's* address to the loader. An `int`
  parameter with `&param` uses the parameter slot itself; an explicit
  `int local = param;` copies too late and in ECX. Declaring the parameter as
  a pointer (`void*`) reproduces it: in a function with a /GS buffer the
  compiler shadow-copies pointer parameters below the buffer in the prologue.
  So "param copied to a local right after the cookie store" = pointer-typed
  parameter, even when it is only used as an integer.
- The format index is read-only in source (`int stored_format = format;`), as
  in 0x00446C70, which keeps it in ECX.

## 0x00446D70 (ANM texture upload at a row offset) — exact

- Same cluster as 0x00446B70/0x00446C70; the synthetic context moved to
  0x00447000 because this function occupies its old address.
- As a member the texture landed in the *first* stack slot; retail has it in
  the second, after the unread class-type tag. A free function
  `(tag, texture, format, data, top, size, has_thtx)` matches. Stack order
  therefore distinguishes member (`this` first) from free function.
- Parameter order `data, top` versus `top, data` swapped ECX/EDI; retail has
  top in ECX and data in EDI with `data` declared first.
- The surface pointer living in the dead `size` argument slot is the
  compiler's own reuse and needs nothing in source.

## 0x00446EB0 (ANM texture create from held file) — exact

- Member in the same cluster (texture ESI, format EAX). The register argument
  in EDX is the *height*; width is on the stack. Read the D3DX push order
  backwards carefully: the value pushed first of the pair is the later
  argument. Declared order `(tag, format, color_key, width, height)` gives
  stack `(tag, color_key, width)` and height in EDX.
- The earlier "BLOCKED: needs the real caller 0x00447511" verdict was wrong; a
  synthetic caller in the shared cluster suffices.

## 0x00446F40 (ANM texture create + THTX upload) — exact

- Member in the shared ANM texture cluster (context now at 0x00448000).
  Declared `(thtx, format, width, height)`: with `(format, thtx, ...)` the two
  register arguments came out swapped (format ECX, thtx EAX). Third case where
  declaration order of the register-eligible parameters decides EAX/ECX.
- The "release surface if non-null" on both exits is written as two explicit
  `if (surface) surface->Release();`; `surface = 0` precedes the format test.

## 0x004472E0 / 0x004470C0 (ANM file load + per-entry image preload) — exact

- Both live in the ANM texture cluster with the real archive closure and the
  shared `resource_surface_loading_log.cpp` TextLog anchor (log in EDI).
- 0x004472E0 matched as `__fastcall (index, file, entry)` *and* as
  `__stdcall (file, entry, index)` — LTCG gives ECX=index, EDX=file either
  way. Only the second makes the caller 0x004470C0 match: arguments are
  evaluated right to left in declared order, and retail sets ECX (index), then
  pushes the entry, then sets EDX (file). When a callee matches but its caller
  has register-setup order swapped, permute the callee's declared parameters.
- 0x004470C0: manager pointer is /GS shadow-copied (pointer parameter rule);
  `entry`/`entries` declared before `sprites`/`scripts` fixed the position of
  the sprite spill; loop shape `for(;;){ if (preload<0) return 0; next; ++index;
  if (!next) break; header += next; } return file;` gives the retail tail.

## 0x00447470 / 0x004473C0 / 0x00447080 (ANM entry load, next-entry step, load-now) — exact

- All in the ANM texture cluster; 0x00447050 and 0x00447940 are included as
  real anchors (their sources gained an overridable section macro, and the
  position-record structs moved to
  `include/th10/render/animation_position_record_00447940.hpp`).
- Call-site argument order decides member vs free function: 0x00446EB0 and
  0x00446F40 match either way in isolation, but 0x00447470 only matches when
  they are free functions with an explicit texture parameter (the texture is
  evaluated right-to-left in its declared position, not first as `this`).
- An inline accessor (`entry->Thtx()`) and the same expression written out at
  the call schedule differently; the written-out form matched.
- `(float)unsigned` uses the `__real@4f800000` literal; bound to 0x00470B98
  with `constant_aliases`.
- The scale factors are stored straight into the record's `width`/`height`
  fields and the texture size is written last from locals — that is what keeps
  both values on the FPU stack across the four products.
- Loop increments in the `for` header (`++i, ++offset`) versus in the body
  move the `add` relative to the counter `inc`.
- `AnmFile::cursor` is `volatile` (every use re-reads it; `cursor = 1;
  while (cursor)` is not folded). Incrementing through a named local
  (`int next = cursor + 1; cursor = next;`) uses EAX; `++cursor` uses EDX.
- 0x004473C0: five zero-initialised locals; only one of the 120 declaration
  orders (`position, script_base, sprite_base, index, loaded`) reproduces the
  retail `xor` order and which zero register seeds the stack-homed counter.
  Brute-forcing declaration order (`$S/ne_brute.py`) is a valid last step when
  everything but the init block matches.

## 0x00447700 (ANM pending-load service step) — exact

- Added to the `animation_manager_mark_resource_for_removal_004493e0` cluster
  (it owns the real 0x00447810 release body with the file in EDI) as a rooted
  `extern "C" __stdcall` function; 0x004473C0 is a plain-stack callee, so it
  is just an absolute symbol there.
- The slot clear is an inlined 0x004477D0 *without* its null test; with the
  test the compiler does not fold it against the caller's own check.

## 0x00447FD0 (image surface -> back buffer) — exact; inline accessor for the device

- Own cluster `animation_manager_copy_to_back_buffer_00447fd0` (manager EBX,
  index EAX, unreferenced in retail).
- `data_00491c30->Method(args)` loads the vtable *after* the arguments and
  routes arguments through EDX. Retail loads device (EAX) and vtable (EDX)
  first and routes every argument through ECX. Calling through a trivial
  inline accessor `static inline Device() { return data_00491c30; }`
  reproduces it exactly. Try this on every remaining function with COM calls
  whose only residue is "vtable loaded early / argument register differs".
