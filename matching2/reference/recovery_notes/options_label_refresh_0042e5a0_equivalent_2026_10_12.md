# Options label refresh 0x0042E5A0 — equivalent-model session 2026-10-12

Status: model and layout drafted, not yet registered.  The exact build is
unaffected (the asm region stays; the model files sit unregistered in the
tree until the blockers below are cleared).

## What the function does (fully mapped this session)

* Copies the music and sound volumes to 0x00497854 / 0x00497858 and the
  request queue call `RegisterResource(0x00492590, "bgm/th10_02.wav", 8, 0)`
  (custom ABI: EAX=this, EDX=name, stack resource+parameter, RET 8).
* Music DSP attenuation: `x = 1 - 0.01*music`; `-5000 - (int)((1-x^4)*-5000)`
  via `__ftol2`, or the constant -10000 while the music is off.
* Twelve digit labels (music 0x25/0x26/0x27 + 0x29/0x2A/0x2B, sound
  0x2D/0x2E/0x2F + 0x31/0x32/0x33) are each reconfigured with
  `ConfigureObject(obj, digit + 0x33 or 0x3D)` where digit = hundreds /
  (v/10)%10 / v%10.  ConfigureObject ABI: ECX=resource (obj+0x308),
  EAX=object, DX=index.
* Then two visibility trees (music, sound): below ten hides the hundreds and
  tens labels (&= ~2), one hundred shows all four (|= 2), in between shows
  the tens and hides the hundreds.  Walks use slot `animation_slots[1]`
  (room+0x2C8), script compare at +0x38A, fallback `Find(0)`.

The volume RMW in TitleOptions 0x0042D920 (its three call sites) is the
same goto-convergence shape that fixed the caller.

## Model files (unregistered)

* `msvc/equivalent/game/options_label_refresh_0042e5a0.cpp`
* `msvc/include/th10/game/options_label_refresh_0042e5a0.hpp`
* `msvc/layout/equivalent/options_label_refresh_0042e5a0.json`
  (context_cluster = the title cluster; entry = its compiler context)

## Blockers measured with tools/matching/equivalence.py

1. The model body is 3445 bytes — it FITS the 3999-byte region.  The tool
   rejects it anyway: `model_code` is derived from the first `ff /24` jump
   target inside `size + 0x400`, and TitleOptions' switch table (compiled
   into the same model link by the context) lands at +4388, past the region.
   A table-detection guard (a candidate table should be pointed at by a
   jump inside the compared window, or the window should stop at the
   function's own section) would let the comparison run.
2. c2 compiles the model's `ConfigureObject` calls as stack-thiscall
   (push sprite; push object) and reloads the manager global after every
   call, while retail uses the register form (EAX/EDX/ECX) with ESI live
   across it — +389 bytes if the two were merged, and ~24 recorded
   code-shape differences otherwise.  In-cluster callee compilation picks
   the register form only when c2's interprocedural pass sees the same
   caller shape as retail; the single-caller model link does not.

## Next levers

* Fix the table heuristic in tools/matching/equivalence.py, register the
  recovery, and record the configure-call differences (code-shape class
  explicitly covers "a read-modify-write folded or split" and shared-tail
  merges; a calling-convention difference needs the same class or a new
  listed one).
* Or make the title cluster compile the ConfigureObject body in-context
  (registrar.cpp-style anchor like pause_open_004231d0 does) so the real
  function can become a selected region and the ABI matches naturally.

## Session addendum (same day): extent probe fixed, deeper blocker found

The equivalence tool's table heuristic was fixed (a tail-zero region whose
retail bytes contain no `ff /24` jump-table instruction cannot gain one from
the model; foreign tables in the slack window are now ignored — commit
1ef091c3).  With that guard the comparison runs, and a worse blocker
surfaces:

* The model body is 3445 bytes — 554 SHORTER than the 3999-byte region.
  Retail spends the difference on per-block alignment pads, the merged
  child-walk thunks (`mov eax,[eax]; mov eax,[eax]; jmp`) and a denser
  schedule.  The equivalence machinery compares code against code at equal
  extent and a jump-table tail; a 554-byte structural shortfall cannot be
  recorded as instruction differences.
* Reproducing retail's extent requires c2 to make the same tail-merge and
  scheduling decisions, which reduces to the same register-ABI question as
  before (the ConfigureObject calls must use the ECX/EAX/DX form with ESI
  live across them).  c2 chooses that form only with the caller shape it saw
  in the retail build; the single-caller model link does not reproduce it.

Verdict: the region stays `asm`.  The model remains useful as the readable
documentation of the function's semantics.  A future lever would be a
schema-2 cluster that compiles this function together with a Configure-
Object body whose callers match retail's shapes closely enough for c2 to
pick the register convention, or an equivalence-tool extension that compares
an explicitly declared model extent against a same-length retail prefix
(the tail would then need per-byte justification).

## 2026-10-12: current state re-measured

The drafted model now compiles to 3,472 bytes against the 3,999-byte
region — 527 short (the earlier 3-byte overflow state came from a
different model revision). The equivalence tool compares the model body
across the full region extent, so a 527-byte shortfall cannot be recorded
as differences. The gap concentrates in the ConfigureFromResource caller
blocks (the model's include covers the callee, but the retail interleaves
its label-setup blocks with the volume walks differently). Next lever:
grow the model with the retail block order before re-measuring.

## Block-level finding (2026-10-12, second pass)

The 527-byte shortfall decomposes cleanly: retail inlines the child walk
of `FindLabel` (the `mov eax,[eax]; cmp word [edx+0x38A],cx` search by
script id, ~35 bytes) at **every one of the 15 label sites**, while c2
outlined that walk into a single shared 153-byte copy in the model build
and calls it. The per-site difference (~35 B × 15 − 153 ≈ 372 B) plus the
two-Find fallback shape accounts for the gap. The lever is forcing the
inliner to keep the walk per site — e.g. splitting `FindLabel` so the walk
loop is small enough for c2's inline budget, or matching retail's exact
two-Find structure (the fallback `Find(manager, {0})` after the loop).

## Third pass (2026-10-12): 3,904 of 3,999 bytes

Two real decode fixes landed: `FindLabel` returns the found child (the
retail walk's result feeds the per-label block), and the music show/hide
ids corrected (0x27 for the ones digit, not 0x29). The model is now 95
bytes short. The remainder is the case ordering: retail compares the
volume byte against 0x64 and the <100 path clears the hundreds label
through the `Find({0})` fallback, then walks 0x26/0x2A per case — the
model's if/else-if ladder orders these differently. The 32 label-touch
sites (2 readouts × ~5 labels × 3 cases, `cmp al,0x64` at 0x42EDB3) map
1:1; the block order between them is what remains.

## Fourth pass (2026-10-12): 3,904 bytes, 95 short

With the FindLabel result fix and the corrected music label ids, the model
compiles to 3,904 bytes. The remaining 95 bytes are block order, not
missing code: the branch at +0xB9 reaches +0x783 where retail reaches
+0x77D (a 6-byte block-order delta at one site), and the rest is the
ladder's if/else-if ordering against retail's `cmp al,0x64` dispatcher.
Removing the 0x27 show/hide sites shrank the model to 3,520 (wrong —
retail's ladder does touch three music labels), confirming the sites are
right and only their order differs. This is the c2 block-ordering class;
the lever is the same allocator/trace tooling used for StartChild.

## Fifth pass (2026-10-12): nesting experiment ruled out

Restructuring the flat else-if ladder into retail's nested
`if (<10) {...} else { if (>=100) {...} else {...} }` shape compiled to
3,632 bytes — worse than the flat 3,904. Removing the 0x27 sites from the
ladder also shrank the body (3,632), confirming those sites contribute
needed bytes even though the ladder-only walk sites in retail show three
music labels. The 3,904-byte flat form is the best source-level shape
found; the residual 95 bytes are c2 block ordering only reachable through
the allocator/trace tooling.

## Sixth pass (2026-10-13): accepted — 1,174 of 1,204 instructions identical

The draft was rebuilt around four decode corrections; after them the model
compiles to the full 3,999-byte extent and the recorded differences shrink to
30 instructions in 40 hunks (12 `alignment-padding`, 28 `code-shape`), with
`equivalence.py --layout` reporting an empty `not_equivalent`.

1. **The walk result feeds `Find` as an id.**  Retail's found-tails are the
   two-deref thunks (`mov eax,[eax]; mov eax,[eax]`): the walk takes the
   matching child's *own id* (`LabelAnimation_0042d920::id`, offset 0) and
   looks *that* up in the manager; the loop-exit path looks up id 0.  The
   earlier "returns the found child" reading was wrong.  Spelling the id as
   two separate branches (`if (match != 0) id = match->object->id; else
   id = 0;`, `match` assigned inside the loop) reproduces the out-of-line
   found-thunks and the hoisted `mov ecx,<script>` — +416 bytes over the
   shared-default shape.
2. **The ladder scripts are 0x25/0x26/0x29/0x2A (music) and
   0x2D/0x2E/0x31/0x32 (sound).**  0x27 never appears: the visibility tree
   hides/shows the hundreds and tens digits of *both* fonts, never the ones
   digits.  The fifth pass's 0x27 sites and the nesting experiment were
   chasing the wrong set; the flat `if (<10) else if (<100) else` ladder with
   the correct scripts matches retail's block order exactly.
3. **The custom-register leaves use the cluster's `YIX` spellings.**
   `SelectResourceSprite_0043e5a0` (`__fastcall`, resource in ECX, sprite in
   EDX) replaces the `__thiscall` ConfigureObject include, and
   `RegisterResource_0043e460_eax` (`__fastcall`, queue, name, resource,
   parameter) replaces the queue method call; the layout's bindings/absolute
   symbols were updated accordingly.  Retail's extra EAX state (the object,
   the queue) stays a recorded `code-shape` difference per site — but the
   walk registers (script in ECX, object in EDX, manager in ESI, room in EDI,
   zero in EBX) now match retail exactly.
4. **The flag update is spelled through a pointer variable**
   (`unsigned int* flags = &label->flags_35c; ...`).  A direct
   `label->flags_35c &= ~2u` folds into `and [mem],imm`; the pointer form
   reproduces retail's split `mov ecx,[eax+0x35c]; add eax,0x35c;
   and ecx,imm; mov [eax],ecx` at every ladder site, with the shared final
   store and the epilogue woven into the last one.

The manager lookup is hoisted to the function top and passed down (retail
keeps it in ESI; per-site re-reads made c2 reload it after every call).  The
remaining recorded differences are the private EDI receiver edges (the model
takes the room on the stack: `push edi`/`mov edi,[esp+0x14]`, `ret 0x4`
against retail's bare `ret`), the queue call's ECX/EAX edge, the resource
load scheduled before the digit magic at six of the twelve configure sites,
one redundant two-byte `jmp` at +0x209, and the window-end truncation of the
model's last shared thunk (the body is two bytes past the 3,999-byte extent,
so its final `jmp` is cut by the compared window; retail's completes).

Regions.json delta for the orchestrator: append to `equivalent_recoveries`:
`{"region": "asm_FUN_0042e5a0_0042e5a0", "layout":
"layout/equivalent/options_label_refresh_0042e5a0.json"}`.
