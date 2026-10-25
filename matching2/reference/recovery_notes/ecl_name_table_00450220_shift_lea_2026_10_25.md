# Name table 0x00450220: the last 4 instructions are a shl/lea decision (2026-10-25)

Status: equivalent, 194/198. Retail keeps `name_count` in EDX in the head
block (`mov edx,[ebx+8]` early, `add edx,eax`, `mov eax,edx`, store); the
model uses ECX.

## Mechanism (traced, c2.dll 13.10.6030)

The head block `name_count += sub_count; size = name_count * 8;` reaches
Riscify as `add [ebx+8],eax; mov eax,[ebx+8]; lea eax,[eax*8]; push eax; call;
add esp; cmp ebp,0`. Riscify walks backwards and calls `GetReg` for every
opcode whose flag word (table 0x1086B580) has bit 0x400: push, inc/dec and the
arithmetic/shift group 0x23..0x34 (shl is 0x2A), but not mov, lea or movzx.
Round robin from the start of the block: cmp -> ECX (EAX is live out),
add esp -> EDX, push -> ESI, then the split `add [ebx+8]` wraps to ECX.
Retail has one more call in between: a `shl` instead of the `lea`
(shl -> ECX, then the add gets EDX).

Forcing the decision with gdb (`build/experiments/goal_2026_10_25/ent/riscify/force_shl.py`,
jump from 0x1073FBE9 to 0x10735446 for that instruction) gives 198/198, so
this is the only difference.

The lowering of the IL shift (op 0x27A) at 0x1073FB90 keeps `shl` only when
the destination is a temporary with a defining instruction (symbol +0x14) and
the source is not a register symbol or is also such a temporary, or when the
source and destination are the same symbol. Otherwise it emits `lea`. In the
model the source is the Gopt value `s1a4` of `name_count + sub_count`
(store-to-load forwarding of the reload; no defining instruction), so it is
always `lea`.

## Spellings that do not change it (all 194/198 or worse)

Size spellings (`<< 3`, `* 8u`, `int`, `sizeof` first, `size <<= 3`,
`size *= 8`, `(name_count += n) * 8`, `(name_count = name_count + n) * 8`,
comma, scale variable, `__int64`, pointer arithmetic), type-punned stores and
reads (`unsigned&`, `long*`, `char*` offset), statement orders, reusing `size`
for the memcpy. Computing the size before the update (`(name_count + n) * 8`)
moves the load to EDX but makes the sum a shared value (179/198).
`_ReadWriteBarrier` between update and size stops the forwarding but moves
the frame (116/198); a volatile read too (116/198).

What is needed: a source form where the shifted value is a plain expression
temporary or a memory operand at lowering time while the stored value is
still forwarded by Riscify. Tracers: `reference/compiler_traces/regalloc/trace_riscify.py`
(block lists at Riscify entry/exit and every GetReg), and in the experiment
folder `trace_shiftlea.py` (IR at the shift decision), `trace_rmw.py`
(IR at RMW formation, 0x10735E96), `watch_op.py` (writes to one IR field).

## Address-taken locals (same day)

Taking the address of `names`, `old` or `previous` (`Touch(&x)`, an empty
`__forceinline` template) when its store sits between the two
`files[file_count]->sub_count` reads gives 191/198: the add's `sub_count` is
reloaded (the store to an address-taken local kills load availability), the
stored sum is then not forwarded, the reload becomes a copy and the shift
stays `shl` (retail's head order and EDX are back), but `sub_count` is loaded
twice where retail loads it once. Every order that keeps one `sub_count` load
(touch before `data`, after the update, a touched `count` local, `previous`
assigned after the update) is forwarded again (194). `(void)&x` folds away.
Address-taking `names` or `previous` through real helper calls
(`TakeName(&names)`, `FreeTable(&previous)`) moves the frame and EBP
(96..119/198). Sweeps: `ent/v16.py`..`ent/v24.py`; `eqdis.py` prints a
variant's instruction diff against retail.

## Why the index is a Gopt value (traced later the same day)

The `lea` comes from the address-mode folder `FUN_1079987C` (c2.dll), which
runs on the multiply-by-8 after its expansion at `FUN_107881F2` (the expansion
inserts `s251 = s1a4; s250 = s251 * 8` because `s1a4` has no defining
instruction). The folder walks back through defining instructions of type 4
(`+0xA & 0xFFF == 4`): copies (0x263), adds (0x278/0x279) and scales (0x27A,
0x27C). It absorbs the copy and stops at `s1a4` because `s1a4` has no
definition, then dispatches form 0x255 (index*scale) through the table at
0x10799D10 to 0x1073FB90. That emitter keeps `shl` only when the index
operand is not kind 1, its symbol has a defining instruction, or it is the
destination symbol. So retail's index was a plain expression temporary: most
likely the reload of `name_count` as a load that Gopt did not see as
redundant (the copy would then stop the walk at the load, and Riscify's own
store-to-load forwarding gives retail's `mov eax,edx`).

In the model the reload is redundant with the store: Gopt makes it a value
`s1a3`, and the value propagation `FUN_1074D21E` (called per operand from
`FUN_1074D2EE`) replaces it with the stored sum `s1a4`. The gate that allows
it (0x1076C5EB..0x10774DCA) is: phase flag `DAT_10884020` set, the operand is
a kind-3 symbol, its `+0x36 & 0x81` is clear and bit 2 of `+7` equals the
value's. With a user variable (kind 4/5) instead, the propagation stops for
anything but a compare, but the folder then stops at the variable, which has
no definition either, so it is still `lea`.

A store to an address-taken local between the update and the size does not
make the reload non-redundant (`previous` touched after the update: 194; a
touched `names` moves the frame: 109). `ent/v25.py` has those. Tools:
`ent/riscify/trace_step.py` (instruction-level path of one c2 call),
`ent/riscify/dump_at.py` (registers and memory at one breakpoint hit).

Still open: a source form whose reload of `name_count` Gopt cannot forward
(a kill between the store and the reload that emits no code), with one
`sub_count` load.
