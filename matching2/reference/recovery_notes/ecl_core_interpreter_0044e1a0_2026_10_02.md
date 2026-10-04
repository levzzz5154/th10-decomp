# Core ECL interpreter at 0x0044E1A0: equivalent recovery, not byte-exact

The 7,020-byte region (6,692 bytes of code plus jump tables) is registered
under `equivalent_recoveries`: readable C++ that compiles to the same
instructions as retail apart from compiler tie-breaks. The default build
compiles it into the executable after `tools/matching/equivalence.py` has
checked it against the exact bytes. The inline assembly in
`msvc/src/script/ecl_core_interpreter.cpp` is kept for the exact link that
check compares against and for `make EXACT=1`. This note records the model, the accepted
differences, and why they were not closed.

## Files

- `msvc/equivalent/script/ecl_core_interpreter_0044e1a0.cpp`: `EclVm::Run(float delta)`.
- `msvc/equivalent/script/ecl_core_interpreter_0044e1a0.hpp`: the VM, stack,
  and owner types, with the three force-inlined typed pops.
- `msvc/equivalent/script/ecl_core_interpreter_0044e1a0_context.cpp`: models of
  the helpers and the caller, needed only so the checking `/GL` + `/LTCG` link
  derives the same private register conventions. Only `Run` is compared.
- `msvc/layout/equivalent/ecl_core_interpreter_0044e1a0.json`: symbol bindings
  and the recorded differences.

## How close it is

Compiled with the project flags plus `/GL`, linked with `/LTCG`, and compared
against the built region by instruction, with branch targets and jump-table
entries followed through the alignment and callee and data symbols bound to
their retail addresses:

| Instructions | Count |
| --- | --- |
| Total | 1,790 |
| Identical | 1,679 (93.8%) |
| Base/index order only | 96 |
| Recorded differences | 15, in 12 places |

Frame size (0x108), prologue, register roles, case order, jump tables, every
call target, and every opcode's structure match. What differs:

1. **Base/index order in the inlined pops** (96 instructions).
   `mov ecx,[eax+esi+8]` versus `mov ecx,[esi+eax+8]`: the same address with
   the two registers encoded in the other order.
2. **Stack slots in opcodes 50 and 52** (12 instructions, class
   `stack-slot-order`). Opcode 50's second operand and result are at 0x20 and
   0x28 in retail and at 0x24 and 0x2c in the model; opcode 52 is the reverse.
   The locals are scoped to their case, so this is a renaming.
3. **Opcode 30 type lookup** (3 instructions, class `operand-order`). Retail
   adds the argument offset to the instruction's first word and then indexes
   from the instruction pointer; the model adds the pointer first. Same address.

All three are different encodings or orderings of the same computation. No
runtime test was performed; the equivalence claim rests on the instruction
comparison alone.

## What the source had to look like

- `PopRaw` returns whether it took a value, and `PopInt` / `PopFloat` consume
  the tag word only on success. Forms that repeat the `sp - 4 >= 0` test, or
  nest a raw pop inside a second test, give `sub eax,4` where retail has
  `add eax,-4`, or put the value and tag loads out of phase.
- Opcode 10 takes the first raw pop through a local `EclStack*` and the second
  through the member. Retail orders the two loads differently and no single
  spelling reproduces that.
- `IntValue` pops into its own `value` parameter, which is what makes the
  parameter a stack argument in the LTCG convention (matches 0x0044FF00).
- `FloatValue` is static: `(int selector, EclVm* vm, float value)`.
- The polar temporary in opcode 81 is three floats, giving the 0x108 frame.
- Opcode 30 uses one argument counter incremented in both arms, and calls an
  empty variadic log function. The empty call is what keeps the `'%'` compare.
- Opcode 87 computes `y = atan2(y, x)` into the existing local.

## Why exactness was not reached

The cause was read out of the compiler backend. Microsoft's public symbol
server holds the PDB for this exact `c2.dll` (`c2.pdb`, GUID
`5360F7BD-AFB5-4288-A53F-1FBE04D63911`, age 2). It is stripped to public
names and the DLL is block-reordered, so addresses have to go through the
PDB's OMAP streams, but about 3,400 backend functions get their names.

- `FactCanonSort` merge-sorts the operands of a commutative node with
  `OptCmpHashVal`, an unsigned compare of each operand's hash value.
- For a symbol leaf, `OptHashNode` derives that hash from the symbol record's
  sequence number: `id << 6` truncated to 16 bits for a temporary, and
  `(id & 0x7ff) << 5` for a local or parameter. The value wraps every 1,024
  temporaries and every 2,048 locals.
- `SymAlloc` takes records from LIFO free lists (`SymTmpFreeList`,
  `SymLocalFreeList`) and a recycled record keeps its old sequence number.
  Numbering appears to restart per function: helper functions in the same
  link see small numbers again.

Each inlined pop adds `this + sp`, where `this` is the inlined helper's
parameter symbol and `sp` is a temporary. Which of the two becomes the base
register is therefore decided by two sequence numbers, and those depend on
every symbol the function allocated and freed before that point: locals,
call arguments, expression temporaries, earlier inline instances. Code that
compiles to nothing still moves them.

A gdb breakpoint on `OptCmpHashVal` (through `winedbg --gdb`, on `link.exe`
during the `/LTCG` link) logs both operands of every comparison. With the
numbers from that trace, the hash rule predicts the model's operand order for
every pop.

Retail's pattern is reproduced exactly by shifting three sequences by
constants relative to the model:

| Sequence | Shift needed |
| --- | --- |
| Helper `this` symbols | +377 to +380 (mod 2048) |
| Value-load temporaries | +507 to +526 (mod 1024) |
| Tag-load temporaries | +484 to +502 (mod 1024) |

These figures are for the model as saved; other pop-helper layerings need
different constants but the same shape, with the value shift 5 to 42 above
the tag shift. A constant shift fitting all 63 remaining pops means the
difference sits before the first pop or in function-wide totals, not in the
per-pop code.

Dead statements can supply the first two shifts. A function-scope
`int u = 0;` moves all three sequences by one; `DebugLog("z")` moves the two
temporary sequences by one half each. That is why about 500 dead statements
reached 1769 of 1789 strict matches (counted without the trailing alignment instruction). No construct tried moves the value and
tag sequences apart by the 5 to 42 required, which is the one tag load that
never matched. The stack-slot pair and the opcode 30 ordering have not been
traced; opcode 30's is a three-operand sort through the same comparison.

So the missing information is the original function's exact sequence of
symbol allocations, which the binary does not record beyond these three
residues. An exact build could be engineered with filler once a construct
for the third shift is found, but that would be fitted, not recovered. The
earlier guess that the original contained compiled-out debug output is one
possible source of the shift and nothing more.

## If this is picked up again

- Fetch the PDB from
  `https://msdl.microsoft.com/download/symbols/c2.pdb/5360F7BDAFB54288A53F1FBE04D639112/c2.pdb`
  and map names through the OMAP-from-source stream. `OptCmpHashVal` is at
  0x10795BC5 in the loaded DLL (preferred base 0x10700000); operands arrive in
  ECX and EDX, hash at `+0x10`, symbol at `+0x18`, sequence number at
  `symbol+0x1c`, kind at `symbol+4` (3 temporary, 4 local, 5 parameter).
- Measure, do not sweep: trace a variant, read the three sequence numbers at
  the first pops, and compare with the shifts above. A trace takes about 25
  seconds.
- Opcode 10's first raw pop goes through a local `EclStack*` in the model
  because retail's base symbol there has a small hash. With the mechanism
  known, that spelling is a fit to one data point and may not be the original.
- The extended ECL opcode handler at 0x0040E770 very likely inlines the same
  pops and will depend on the same numbering; that has not been checked. Any
  function whose only mismatch is commutative operand order is the same
  problem.
