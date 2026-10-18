# Animation script-change C++ equivalence recovery, 2026-10-05

The complete 287-byte routine at `0x0043E8B0` is now covered by
`layout/equivalent/animation_change_script_0043e8b0.json`. The default build
uses the ordinary C++ model in `equivalent/render/`; the exact build retains
the original assembly. The existing exact handle wrapper and lookup retain
their ownership. Their source is included in this compiler context to derive
the changer's private entry: resource EDX, object EAX, index ECX, plain RET.
The existing `RunChangeScriptVm` call binds to `0x0043EE30`.

The model uses ordinary scalar/float source without a volatile scale read.
The 2026-10-06 refinement uses the known -1.0f literal instead of reading its
global alias. The full comparison reports 66 instructions, 51 identical,
and nine explicitly recorded register-choice hunks, with 22 differing bytes
instead of the preceding 32. There are no frame-offset,
base/index, or unproven branch-target allowances.

All nine hunks are one consistent ESI/EDI allocation change:

| Value and lifetime | Retail | C++ |
| --- | --- | --- |
| incoming index, through the 16-bit ScriptIndex store | EDI/DI | ESI/SI |
| script pointer, from lookup through both +0x38C/+0x390 stores | ESI | EDI |
| flags after the index dies | EDI | ESI |
| previous-frame reset constant after the flags die | EDI | ESI |

The null-script compare follows the script-pointer register, the flag test
and mutations follow the flags register, and all consumers follow the same
mapping. Both callee-saved registers are saved before their first overwrite
and restored on every exit. The C++ moves its index copy and table-pointer
load before the second push; neither operation uses ESP or changes the
original EDI being saved. The read order, resource/loading check, and object
stores otherwise agree. The flags word and script pointer have distinct live
ranges/registers in both bodies, with no value lost across a use or call.

The literal now emits retail's exact `fld object.scale_x` followed by
`fmul [0x00470B60]`, including its position around the intervening flag
operations. The pooled compiler literal `__real@bf800000` binds to that
existing float address. Its value is -1.0f; this remains an x87 multiply,
rather than a sign-change instruction. The former operand-order allowance
has been removed. The two smaller hunks at `+0x42` and `+0x4B` cover only
the register operands in the OR and XOR/store instructions.

The full gate follows every branch, checks the entry and return instructions,
verifies all other instructions and addresses, and rejects any difference
outside these exact nine hunks. No compiler flag, verifier rule, assembly
instruction, or region extent was changed to admit the candidate.

The exact handle caller's compiler context uses the same ordinary literal
source, replacing its old volatile read. Its layout positions and verifies
the compiler's actual four-byte constant at `0x00470B60`; the added `.rdata`
gap remains unselected layout data. The caller's complete 36 bytes and the
lookup anchor's 73 bytes remain exact. The changer remains equivalent,
with exact-build ownership still in its original assembly region.

Sources, six logical-parameter-order controls, native PE/MAP files and
strict maintained probe/equivalence reports are preserved under
`build/experiments/script_change_exact_2026_10_06/`. Parameter permutations
did not change the ESI/EDI mismatch; the prior candidate-priority trace still
describes that unresolved allocation.

## 2026-10-18: the residual is a two-point register contest, not flag-statement placement

Semantic audit and raw-byte audit both pass: the model's `(flags | 8) & ~0x200u`
is the same value as retail's `(flags | 8) ^ 0x200` under the `flags & 0x200`
guard. The retail site (raw runs from `diff_dump.py --raw`, cross-checked with
Ghidra's listing of 0x0043E8B0) is exactly

```
0x003f  fld   [eax+0x3c]           ; 3 bytes
0x0042  or    edi,0x8              ; 3 bytes
0x0045  fmul  [0x00470b60]         ; 6 bytes
0x004b  xor   edi,0x200            ; 6 bytes
0x0051  mov   [eax+0x35c],edi
```

ONE `fmul` and ONE `or edi,0x8`; the "second fmul / second `or edi,0x8`" in the
diff-dump neighbourhood listing are the *model* side rendered at its own
offsets. Any `(flags | 8) ^ 0x200` spelling (split around the float, inline
store, temp chain, memory RMW) emits this exact `or`/`fmul`/`xor` sequence and
schedules it exactly as retail; the only differing bytes are the ESI/EDI
register nibbles and the entry's index/param-copy placement that follows the
same allocation.

The allocation is decided by `Spillcosts` priority order (`ChoosePhysReg` picks
descending priority, class-order ties ESI first). Verified formula (per block,
refs x K x weight; -K per block lived through, K = candidates referenced or
flagged):

- flags = 4*K(B6) + 8*K(B7)
- script = 4*K(B4) - (K(B5) + K(B6) + K(B7)) + 4*K(B8)

With the shared 0x200 immediate (test + xor, same 32-bit type) K(B6)=5 and
K(B7)=3: flags 44, script 38 -> flags takes ESI (wrong). The shipped and-form
unshares the 0x200 (0xfffffdff is a different constant): K 4/2, script 40 >
flags 32 -> every register matches. Retail keeps the shared 0x200 (the encoding
forces value 0x200 in 32-bit ops at both sites) and still wins, so retail's IR
carries ~2 more points of script or less of flags than any form found here.

New progress this session: the **member-function form** (`void
Entity::ChangeScript(ScriptChangeResource*, int)`, the retail "phantom incoming
EAX" object re-expressed as `this`) lifts script 38 -> 42: the `this`
copy-definition counts as a real reference in the entry block (K(B4) 4 -> 5),
while ordinary parameters are copy-defs with zero refs. flags stays 44, so the
form is exactly two points short and does not change any byte on its own.

Ruled out this session (~110 measured shapes; register-contest levers traced
with `trace_spillcosts.py` and confirmed bit-identical Spillcosts state):

- every update spelling and placement: `(flags|8)^0x200` split around the float
  statement, inline store, two statements (`|=` then `^=`), named temps for the
  chain, memory RMW split (keeps a second store -> dead), reversed
  `(flags^0x200)|8` (emits xor-first, 34 bytes), statement-order swaps;
- typed constants: int vs unsigned on either side, two distinct enums, const
  variables, `(unsigned short)`, `0x200ULL`/512LL on either side (0x43B110's
  value-and-type split only survives narrow-width stores; all 32-bit spellings
  pool to one constant);
- volatile on the flag storage and on the float constant (each access is single
  so no reload appears; no candidate change);
- doubled statements (mask written twice, slot load written twice/into two
  locals, id load doubled, duplicate stores): dead-store/CSE folded away before
  Spillcosts, traced identical;
- named locals for the id word, the mask input, the chain temps: propagated;
- copy-chains (`fv` used in the test then copied into multi-assignment
  `flags`): propagated, traced identical;
- `__forceinline` helpers (pair stores, slot load, test mask, whole update),
  both parameter orders, free and `this->`/`resource->` member forms;
- field-address pointers with one or two assignments (stores stay forwarded);
- the VM call declared as the observed three-argument `__fastcall` edge
  (0 -> ECX, flags_06C -> EDX, object on stack): the argument setup
  re-materializes the zero (`xor ecx,ecx`) and the tail shifts (41-49 bytes).

Closing the last 14 bytes needs a source that adds two K points in the entry or
stores block (or removes one flags reference event in the update block) without
adding instructions; every shape in the documented lever families normalizes
away before the register allocator sees it.

## 2026-10-18 (later): closed — the doubled slot read in the guard, 0 differing bytes

The 14 bytes are gone. `variant.py` reports `final_exact 66/66 0 0 0 0 *EXACT*`
and `equivalence.py` reports `"differences": []`, `"not_equivalent": []`,
`base_index_order 0`, `frame_offset 0`.

The closing lever is the "expression written twice and merged late" candidate
rule (`msvc-c2-what-adds-a-register-candidate`) applied to the script slot
read: the guard reads the slot a second time,

```cpp
void* script = resource->scripts[index];
if (!script || !resource->scripts[index] || resource->loading) return;
```

The two reads load-merge into the one register read, so the instruction stream
is untouched, but the late merge leaves a temporary plus the variable in the
entry block — one more K point exactly where script has its references
(K(B4) 4 -> 5). Combined with the retail flag spelling
`object->AnimationFlags() = (flags | 8) ^ 0x200u` (its `or`/`fmul`/`xor`
schedule already matched), the priorities become script 46 vs flags 44:
script takes ESI at the ChoosePhysReg decision and every register, opcode and
schedule position matches retail.

The member-function form from the earlier 2026-10-18 section (the `this`
copy-def adding the same one K point, script 38 -> 42) is an independent lever
of the same family and is not needed in the final model; the free-function
form closes with the doubled read alone (also exact as `f2_two_locals`: two
slot locals used by the guard and the two pair stores).

Ruled out in the same session, for the record: every update spelling and
placement (the note section above), typed constant splits, volatile flag
storage and float constants, doubled mask/id statements (fold dead before
Spillcosts), named locals, copy chains, `__forceinline` helper parameters,
field pointers with one or two assignments, and the three-argument `__fastcall`
VM edge. The distinguishing property of the closing shape is that the doubled
expression survives as a temporary plus the variable (a real candidate), which
adjacent same-expression rewrites, constant-copied locals and helper
parameters all fail to do.
