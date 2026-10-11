# Joystick binding reader 0x0044A190: allocator findings (2026-10-11)

Still inline assembly. This note records what a day of rigs and compiler
traces established, so the next attempt does not start from the 49-group
candidate of 2026-10-06 again. Two models are saved next to that candidate in
`reference/semantic_candidates/joystick_binding_reader_0044a190/natural_models/`:

| model | shape | instructions differing from retail (of 282) |
| --- | --- | --- |
| `single_function_int_mask.cpp` | one `__fastcall(mask, unused, set, device)` function | 237 |
| `inline_helper_int_mask.cpp` | the same body as a `__forceinline` helper `(mask, binding, device)` called from that function | 181 |

Neither uses `volatile`, a value record or per-use device snapshots. Both
are plain `cl /O2 /Gz /MT /Gy /G6 /GF /GS /Zl` compiles. The counts come from
a line diff of the disassembly, so a register rename counts as a difference;
they are not comparable with the "49 groups" of the older candidate.

## What is settled

- **The mask arrives in ECX by declaration.** With a stack mask in an LTCG
  cluster (three plain parameters, or mask plus a by-value record) the
  allocator never gives the mask a callee-saved register: it loads it after
  the API call in each path, so the entry block has no mask load and the
  private convention never moves it to a register. Retail's `mov esi,ecx`
  needs a register parameter. `__fastcall(mask, unused, set, device)` gives
  ECX, two stack words and `ret 8`; the callers do not load EDX, which fits a
  dead second parameter.
- **The device index is an ordinary stack parameter.** Without `volatile`
  it is reloaded from `[ebp+0xc]` in each block as in retail, including the
  copy kept in a register across the Acquire retry loop. Those are
  live-range pieces of a candidate that lost its register, not aliasing.
- **The mask is 32 bits wide in the DirectInput path and the button tests are
  ternaries.** `(state.buttons[n] & 0x80) ? 2 : 0` on an `unsigned int` mask
  gives retail's `movzx eax,byte; shr eax,6; and eax,2; or esi,eax`, and
  `? 0x100 : 0` gives the `and eax,0x80; shl eax,1` of the fifth binding. A
  16-bit mask narrows them to `shr cl,6; and cl,2; movzx dx,cl`. Written as
  `if` statements they become branches.
- **The binding pointer and the mask are both defined by a copy at entry**
  (`mov ebx,eax`, `mov esi,ecx`). The inline-helper model reproduces that
  structure: the helper's parameters are copy-defined candidates. With the
  helper's parameters in the order mask, binding, device the binding gets EBX
  and the mask ESI; with binding first they swap.
- **`mov bx,[ebx+0x68]` follows from the binding being in EBX.** The last
  field read reuses the dying base register when that register can hold a
  16-bit value; a model with the binding in ESI shows `mov si,[esi+0x68]`.
- **Spellings of the binding address do nothing** (array index, pointer
  arithmetic, integer address, intermediate offset, assignment per branch,
  twin locals): the address is always computed directly in the binding's
  register unless the body is an inlined helper.

## What is still wrong

1. **X and Y axis terms.** Retail finishes the X pair, ORs it into the mask
   (`or esi,edi`), then computes the Y pair and returns `(up | down) | mask`.
   Every model with a 32-bit mask folds all four terms into one chain and
   ORs the mask last. A 16-bit boundary on the mask keeps them apart in a
   single function (`mask |= x; return (unsigned short)mask | y`) but not
   inside the inlined helper, and a 16-bit mask breaks the DirectInput path.
2. **Register pressure in the axis block.** With the four terms folded the
   block has 11 candidates; the two X limits are loaded once and used three
   times (priority 132 each), the bands and positions follow at 66, and the
   mask (46) loses its register and is stored at entry. Retail's second X sum
   reloads its limits (`mov ebx,[max]; add ebx,[min]`), which is what a load
   candidate that lost its register looks like, so retail met the same
   pressure with the mask winning. Item 1 probably decides this.
3. **Button word register.** Retail keeps `info.dwButtons` in EDX and builds
   each test in EAX; the models keep it in EAX.
4. **Entry temporary.** Retail computes the binding address in EAX and
   copies it; the helper model computes it directly in EBX.

## Compiler facts used

`ChoosePhysReg` (c2.dll 0x107AAB62, function created in the Ghidra project)
scores each available register: plus the preference counts of unallocated
conflicting candidates, plus `100 * f40` for every conflicting candidate
whose only remaining register it is, minus the candidate's own preferences.
The lowest score wins and ties follow the class order (ESI, then EDI, then
EBX among the callee-saved three). The `costs=` field printed by
`reference/compiler_traces/regalloc/trace_choose_physreg.py` is this score. A
candidate that still has two registers open repels nobody, which is why the
axis temporaries take ESI while the mask could still fall back to EBX.

The axis arithmetic was also checked in isolation: limits read through the
global array are shared inside one ternary and reloaded in the next, named
band locals are shared across both, and sums of register locals are merged
across ternaries.
