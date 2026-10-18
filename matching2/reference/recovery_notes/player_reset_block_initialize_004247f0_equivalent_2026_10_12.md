# PlayerResetBlock::Initialize 0x004247F0 — equivalent attempt (2026-10-12)

Status: attempted and parked.  The region stays `asm`.

## What exists

A complete readable body already lives in the `large_player` cluster
(`layout/ltcg/large_player_dependencies/runtime.cpp`,
`PlayerResetBlock::Initialize`) as the anchored context of the recovered
Factory/Reset functions.  The equivalent-model attempt
(`layout/equivalent/player_reset_block_initialize_004247f0.json`,
unregistered) wired the model link with the cluster's context and symbol
coverage.

## Blocker: the model body is 187 bytes shorter

The model's `Initialize` compiles to 1248 bytes against the 1435-byte
region.  The equivalence machinery compares code at equal extent
(`retail[:code_bytes]` against `body[:model_code]`), so a shorter body
cannot be compared: the overread into the next function's code produces
unbound references and instruction garbage.

The shortfall is the same scheduling class as the label refresh 0x42E5A0:
the model's stack-frame layout, evaluation order and register homes differ
(the entry block alone shows the middle position dword kept in EDX and
never stored, versus retail reloading it through ECX into [esp+0x4c]).

## Notes for future attempts

* Bindings for this context must distinguish three address spaces: the
  model image addresses of context-defined callees (e.g. TextLog::Append at
  model 0x401c10) are NOT retail addresses — binding a model address as if
  it were retail silently corrupts every call.  `bindings` values must be
  retail addresses; the tool maps model→retail through the link map.
* The cluster's `absolute_symbols` (LargePlayerTick/Draw/Refresh/Cleanup,
  ParameterFile and scheduler externals) are all needed by the model link.
* The cluster anchors' bodies are context-defined and must NOT be bound
  absolutely (duplicate definition).
* A future lever: match the retail extent by recovering the scheduling
  (the same lever as every blocked region), or extend the equivalence tool
  to compare a declared shorter model extent against a retail prefix with
  the remainder justified — a large tool change.

## 2026-10-17: multiply operand order canonicalized; parked

The ten x87 operand-order hunks (`fld [esi+0xN]; fmul [0x470b44]` in retail
versus the hoisted `fld [0x470b44]` plus `fmul [esi+0xN]` in the model, the
four `(int)(field*flt_100)` bound words) do not move when the multiplies are
spelled `flt_100*field`: the compiler canonicalizes the memory-operand
product either way, exactly the `msvc-c2-oper-order-mechanism` rule (the
swap moves codegen only register-register). Retail's per-statement global
reload is the CSE decision, not the source operand order.

Region stays equivalent (217 differing bytes). The scheduling lever named in
the note above remains the route.


## 2026-10-18: 217 -> 4 differing bytes; one evaluation-order hunk recorded

Campaign run in /tmp/campaign/player_reset.  The model now compiles 313/314
instructions byte-identical (4 differing bytes, tail 0); the equivalence gate
passes with one recorded difference (class `evaluation-order`).

### Levers that closed bytes (in order)

1. **S2/S3 statement split to retail IL order** (load the table value, store
   `Float(0x430)=5`, then multiply, then the two half stores) - retail's IL is
   `fVar1 = data[..]; [0x430]=5; fVar1 = fVar1*0.5f;` per Ghidra.  217 -> 173.
2. **Named reference locals pin the commutative-operand sort**
   (`msvc-c2-operand-order-mechanism`): `float& base_x=Float(0x3c0);` at the x
   adds, `float& base_y=Float(0x3c4);` at the y adds, `float& h428/h420/h434`
   bound at their fsub and re-used at the matching add (a *multi-use* reference
   becomes a real pointer local whose number enters OptCmpHashVal; single-use
   refs collapse to the same address temp and do nothing).  Tuning these
   five references closed 12 of the 13 operand-order hunks.  173 -> 9.
3. **Pooled-constant literals** (`th10-codex-candidate-graphs-recovery-levers`:
   "extern float constants should be literals; operand order of x87 multiplies
   follows"): 0x470B0C/0x470B44 are retail .rdata *pool constants* (0.5f and
   100.0f, read from the oracle image).  Spelling `0.5f`/`100.0f` and binding
   `__real@3f000000` -> 0x470b0c and `__real@42c80000` -> 0x470b44 in the
   layout (`bindings`, like item_update/anm_vm_tick) turned every x87
   `fld [glob]; fmul [field]` into retail's `fld [field]; fmul [glob]`.
   165 -> 42.
4. **Typed leading members + the stored struct argument**: `word_0c`/`word_10`
   (now `ConfigureResource_00404f30 resource_handle`) as real members let the
   compiler prove the nearby stores cannot alias the handle load, so the load
   hoists above the store; passing the stored struct itself (`blk->resource_handle`,
   the `msvc-store-then-pointer-read-keeps-register-copy` / Codex "by-value
   handle" shape) puts the value in EDX (the expression-temp rotation) instead
   of EAX - which also removes the `push eax`-to-`xor eax,eax` anti-edge.
5. **Argument/operand statement order**: the resource load before the
   `word_0c` store; the `parameters` load before the four dword stores; the
   S1/S2/S3 store interleavings as retail emits them.

### Residual (recorded): push/lea order at 0x004248AB

Retail `lea esi,[ebx+0x14] / push edx`, model `push edx / lea esi,[ebx+0x14]`
(4 bytes).  The scheduler trace (compiler_traces/scheduler) shows the two nodes
tie exactly (priority 44032, path 42, one successor each) so the pick falls to
the original sequence number: the model's call lowering creates the stack-arg
push node before the receiver's lea node, retail the other way round.  Ruled
out (each measured, some with hunk-level swaps elsewhere): the callee's
declared parameter order permutation ((int,resource) <-> (resource,int); it
changes only the mangled name), named/pointer/multi-use receiver locals,
receiver as `&slot`/`&blk->slot`/inline helper, argument as expression /
named local / stored struct / pointer-helper read / constructed temporary,
`&slot`-based address folding in earlier statements, comma-operator use lists,
task-block reshapes that keep the byte stream (rotation nudges), and the
slot-forwarder member call.  The priority model says the model's `push` wins
only via the sequence tie-break, so the lever is the callee-lowering order of
this-vs-stack-arg setup - none of the documented rules moves it.

### Missing-store audit

Ghidra decompile of 0x004247F0 compared statement-by-statement with the model:
every retail write is present in the model (the MISSING-STORE family does not
apply to this region).

## 2026-10-18: the last hunk closed by the callee-param-order lever (4 -> 0 bytes)

The push/lea residual at 0x004248AB is gone: the region is byte-identical
(314/314 instructions, 0 differing code bytes, 0 tail bytes).  `variant.py`
final line `final  314/314  0  0  0  0 *EXACT*`; `equivalence.py --layout`
reports `"differences": [], "not_equivalent": [], base_index_order: 0,
frame_offset: 0`.  The layout's `differences` is now empty.

### The lever: the receiver declared last in the callee's parameter order

The two setup nodes (the receiver's `lea esi,[ebx+0x14]` and the resource
`push`) tie exactly in the list scheduler (prio 44032, path 42, one successor
each), so the pick falls to the IL sequence number -- the call-lowering
creation order of the two nodes.  That order follows the CALLEE'S DECLARED
PARAMETER ORDER (`msvc-ltcg-callee-param-order-sets-caller-load-order`; the
same lever closed front_script_tick's 0x4492F0 call, where the trailing
position argument's `lea` is created before the id push).  The shared member
declaration `ItemConfiguredEntity_00404f30::Configure(int, ConfigureResource)`
always declares the receiver first (`this` is implicit leftmost), so no
permutation of its explicit parameters can move the receiver's setup after the
push -- which is why the earlier `(int,resource) <-> (resource,int)` retest
moved only the mangled name and left the hunk.

The fix is the callee's declared parameter order itself: the receiver becomes
an EXPLICIT LAST parameter.  configure.cpp's model of 0x00404F30 is now
`ConfigureItemEntity_00404f30(int index, ConfigureResource_00404f30 resource,
ItemConfiguredEntity_00404f30* entity)` -- the same body, spelled as the ABI
anchor at .text$a01body it has always been, with the receiver trailing so the
caller's lea is created before the push (the front_script_tick
SetAnimationPosition recipe).  The visible body still bakes the retail private
convention (receiver ESI, index EAX, resource on the stack) from the modelled
caller's call; only the setup order flips to retail's `lea / push / xor /
call`.  The cluster's Configure anchor now names the stand-in symbol, the
layout's `bindings` maps it to 0x404f30, and the old member
`ItemConfiguredEntity_00404f30::Configure` is gone (clean cutover: it had no
other caller).  All three receiver-last permutations --
(index,resource,entity), (resource,entity,index), (resource,index,entity) --
measured 0 differing bytes; the three receiver-first ones stayed at 4.  The
call site spells the receiver as the trailing argument.

### Ruled out this session (each measured with variant.py)

- Statement placement of the receiver's address computation: a named
  `ItemConfiguredEntity_00404f30* slot` local defined one or two statements
  before the call, at the call statement, scoped around the call, or with its
  range ended before the call block -- all 4 bytes unchanged (the lea node is
  created at call lowering wherever the named local's first mention sits).
- Named argument locals for the pushed resource (early or at the call): 29
  differing bytes -- the local's stack home replaces the register push.
- Constant-true re-read shapes (receiver base or slot pointer re-read in a
  folded `?:` compare, kept as a copy-block candidate): 4 bytes unchanged.

Campaign file map: `base_runtime.cpp` (final model source, probe base),
`v_a.py` (placement sweep), `v_d.py` (callee-permutation sweep),
`vfinal.py` (final one-variant check).  Design pitfall recorded for the next
caller-order lever: an ABI anchor whose modelled caller stops calling it loses
the convention source and recompiles to a different extent (Configure went
204 -> 210 bytes with a thiscall default), breaking the cluster layout -- the
anchor's own symbol must move to the stand-in, not be rooted beside it.
