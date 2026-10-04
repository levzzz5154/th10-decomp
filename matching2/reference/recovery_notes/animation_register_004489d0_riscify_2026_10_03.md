# Animation registrars 0x004489D0 family: why the id register differs (2026-10-03)

Status: **not recovered**. 0x004489D0 / 0x00448A50 / 0x00448AC0 / 0x00448B40
stay assembly. This note replaces guesswork in the earlier wave notes with what
c2.dll actually does, traced with the PDB names.

## The residual

Best barrier-free model ("P" in `004489d0_wave12.md`) emits retail's
instruction sequence with the incremented id in EDI where retail has ESI:

    retail                                model P
    mov [edx+72dad8],ecx                  mov edi,[edx+732454]
    mov esi,[edx+732454]                  inc edi
    inc esi                               mov [edx+72dad8],ecx
    mov ecx,esi                           mov ecx,edi
    test ecx,ecx                          test ecx,ecx
    mov [edx+732454],esi                  mov [edx+732454],edi

## Mechanism (c2.dll 13.10.6030)

Three different allocators hand out registers; only the third matters here.

1. `ChoosePhysReg` colours global pseudo-registers (variables live across
   blocks) in priority order, register order EAX ECX EDX ESI EDI EBX EBP.
   In the registrar: node->ECX, manager->EDX, tail->ESI, the `tail->next`
   value->EDI, entity->EBX, out->EAX.
2. `RegAssign` gives expression temporaries a register from a per-type
   rotating position (`NextIntPos`).
3. `Riscify` runs after both. It walks each block **backwards** and splits
   memory-operand instructions (`inc [mem]`, `cmp [mem],imm`) into
   load / op / store, asking `GetReg` for a scratch register. `GetReg` is
   round-robin: it starts after `PrevRegUsed` (reset to "before EAX" at each
   block), prefers registers the function already uses, and skips live ones.
   It is called for every compare, even `test reg,reg`, where the result is
   thrown away but still advances the rotation.

So in the join block:

- Model P's instructions before Riscify are
  `inc [c]; mov ecx,[c]; test ecx,ecx; jne` (the id lives in ECX across the
  branch). Backwards: the `test` asks first and gets ESI (ECX is live), then
  `inc [c]` gets the next one, EDI.
- Retail's must have been `inc [c]; cmp [c],0; jne`. Backwards: the `cmp`
  gets ECX (free), then `inc [c]` gets ESI. A later pass forwards the store
  to the reload (`mov ecx,esi`).

For the zero arm retail has `inc ecx; mov [c],ecx`. With the id not in a
global register, that can only be `inc [c]` split by Riscify with the load
forwarded from the previous block.

**Target instruction list before Riscify:**
`inc [c]; cmp [c],0; jne L; inc [c]; L:` with no value kept in a register.

## Why ordinary source does not give it

- `++c; if (c == 0) ++c;` (any spelling: postfix, `+=`, `!`, `||`, ternary,
  typed member or raw pointer): the compare is merged into the flags of the
  increment and the arm is folded to `mov [c],1`.
- `int id = ++c; if (id == 0) c = id + 1;` (model P): id becomes a global
  register, giving the EDI result above.
- `volatile` counter: every access is an explicit load and store through
  `RegAssign` temporaries, all ECX, and nothing is forwarded.
- `_ReadWriteBarrier()` in the arm produces the retail join block and
  `inc [c]` in the arm (34 of 36 instructions), but the barrier also stops
  the load forwarding in the arm. It is a diagnostic, not a candidate.

- Reading the counter into a by-value copy for the test
  (`AnmId t = next_id; if (t.v == 0) ++next_id.v;`, or
  `if ((++next_id).v == 0) ++next_id;` with a by-value `operator++`) makes the
  optimiser reuse the copy inside the arm, which is model P again.
- Making only the test volatile gives `inc [c]` left unsplit: Riscify undoes
  the split when the reload cannot be forwarded. So retail's accesses are all
  non-volatile.

What is missing is a source form in which the optimiser forgets the counter's
value twice (after the increment and inside the arm) without emitting code.
Not found yet.

## Trace recipe

`winedbg --gdb --no-start link.exe @cluster.rsp`, attach gdb, break on
LoadLibraryA until c2.dll is loaded, then (addresses for the loaded DLL):

| what | address | read |
| --- | --- | --- |
| `ChoosePhysReg` selection done | 0x107AAC16 | `[esp+0x10]` chosen reg, `[esp+0x20]` globreg (`+0` sym, `+0x0c` priority, `+0x1c` id) |
| `RegAssign` entry / assignment | 0x1079C134 / 0x1079C23B | at assignment ESI = register |
| `GetReg` entry / result | 0x107AD33B / 0x107AD44E | `PrevRegUsed` at 0x108B2238, live set `[esp+4]`, result index in ESI |
| `Riscify` entry / exit | 0x107AD4FE / 0x107AD5FB | `[esp+4]` function; blocks at `[[fn+8]]`, next at `+0`, first/last instruction at `+0x1c`/`+0x20` |
| current function | 0x108AB128 | name at `[[[fn]+4]]` |

Instruction: `+0` next, `+4` opcode (1 mov, 0x12 lea, 0x21 inc, 0x2f
cmp/test, 0x26d barrier), `+0x28` source operands, `+0x2c` destination
operands. Operand: `+0` next, `+8` kind (1 register, 6 memory), `+0x1c`
symbol (register number at symbol `+0x1c`: 1 EAX 2 ECX 3 EDX 4 EBX 6 EBP
7 ESI 8 EDI), `+0x30` displacement, `+0x34` base operand.

## 2026-10-04 counter-storage and optimization controls

A new isolated primary-back cluster tests whether union views prevent the early
counter value propagation identified above. Both unsigned/signed views and
unsigned/opaque-pointer views still emit 117 bytes instead of retail's 118.
Changing the zero guard to a `do { ++counter; } while (counter == 0)` nonzero-ID
loop emits 101 bytes. Function-local `#pragma optimize("g", off)` emits 229 bytes;
it does not isolate the counter transformation from the rest of the function.
None passes the complete-function gate, and none was promoted.

The source uses unsigned counter arithmetic to preserve 32-bit wrapping. It
links an array-walking compiler context with ordinary manager/out/entity
arguments. The observed context is 68 bytes for the union and loop models;
the global-optimization control emits 64. Layout extent failures are kept as
failures, rather than padding or truncating a model to fit the retail region.

Inputs, native PE/MAP files and SHA-256 evidence are preserved under
`matching2/build/experiments/registration_counter_2026_10_04/`. The counter's
alternate storage type alone does not prevent simplification. Disabling global
optimization changes too much of the function to provide a matching recovery.
The four authoritative assembly implementations remain unchanged.
