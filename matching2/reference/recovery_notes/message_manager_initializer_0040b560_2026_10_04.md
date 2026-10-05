# Message manager allocation cleanup 0x004657B0: EXACT

Recovered from the natural C++ new expression in the complete message-manager
initializer model, with the complete ending-text constructor compiled alongside
it. Production selects only the generated unwind (11 bytes at 0x4657B0) and
handler (10 bytes at 0x4657BB). The complete 36-byte unwind map/FuncInfo at
0x471790 also matches exactly. Independent unmasked SHA-256 comparisons agree
for every span; evidence is in `matching2/build/experiments/message_manager_initializer_2026_10_04`.

The handler previously labeled a library xlocale `_Mpunct::_Init` handler was
misattributed: its FuncInfo belongs to this application initializer's allocation
cleanup. Its former record is retained in `previous_record`.

## Compiler context

The 584-byte initializer candidate and 605-byte ending-text layout constructor are
complete unselected anchors. The actual 584-byte retail initializer and 648-byte
retail ending-text constructor remain assembly-owned. The new expression now
passes both constructor arguments on the stack with RET8, matching retail;
compiling against an imported constructor declaration instead uses public thiscall
and is insufficient.

`TH10_ENDING_TEXT_LAYOUT_ONLY` removes the worker destructor from the unselected
caller model. The actual worker ownership and cleanup remain compiled and selected
by `ending_text_0040ba90.json`. Without this switch, both EH groups become adjacent
in the compiler's `.text$x`, whereas retail places them at separate addresses.
The default constructor model and its existing selected cleanup are preserved.
Configurable code sections keep the empty worker contribution from aligning a
middle layout gap and shifting all following anchors.

The additional source contains complete animation, scheduler, archive loader and
text log implementations. Their extents are validated, including the 359-byte
archive loader in this context; none is truncated to its retail extent.

## Bounded exploration and remaining initializer differences

Fifteen scratch probes plus two production probes are archived. C-linkage opaque
construction suppresses EH under /EHsc; C++ linkage restores it. RAII allocation
guards outline a destructor and emit an eight-byte cleanup calling that destructor,
even with forceinline or an active flag. Natural new emits the correct eleven-byte
direct allocation cleanup.

Compiling the full ending constructor first produces a 574-byte initializer and
641-byte constructor. Independent background-address computation, a byte pointer
for unlock state, and capturing the filename before clearing the destination give
a 584-byte initializer. Its first remaining instruction differences are the
post-background result load (ECX versus EAX), ending-index arithmetic register
choices, comparison/store scheduling, and unlock-index address reuse. Volatile
index probes alter these choices but do not match; production uses ordinary
readable accesses, not the casts from those probes.

Next useful work is the remaining initializer register allocation and scheduling,
or another complete remaining assembly owner. Do not repeat the imported-ctor or
RAII-guard probes. Do not claim recovery of the initializer merely from equal size.

Validation: production cluster probe EXACT; full default build exact outside the
three existing equivalent C++ regions. `make EXACT=1` reports Whole EXE exact: 487,936 bytes; independent `cmp`
against the retail th10.exe exits successfully.

Additional bounded probes: volatile mode global leaves the baseline instruction
scheduling unchanged; volatile flags splits the retail memory OR into load/OR/store
and increases the body. Neither is promoted (probes 16–17 archived).

## Resolved 2026-10-05

`MessageManager::Initialize` is byte-exact (584 bytes) and selected in the
`message_manager_0040b560` cluster; `make` and `make EXACT=1` pass.

Source changes that closed the remaining differences:

- The game counters at `0x00474C44` are one struct whose address escapes in
  the cluster context, which orders the `ending_index` store against the
  `continued`/`difficulty` compares.
- Flags are raised through `RaiseFlag(unsigned int&, unsigned int)`, which
  gives retail's `or dword ptr [ebp+20h]` forms without reloading.
- The animation resource is read through `MessageThread::Resource()`, which
  rotates the scratch registers of the creator call by one.
- The update and draw tasks are two locals (`update`, `draw`) instead of one
  reused `task`. This was the last residual: the unlock byte address
  `[index + unlocks + 0x1D882]` had base and index exchanged.

Mechanism of the last residual, read from `c2.dll`: the sum is sorted by
`OptCmpHashVal` (unsigned compare of node hashes, larger first; the first
operand becomes the base register). Late in the pipeline the manager pointer
is a temporary and the index load hashes as `8 + ((id & 3) << 14)`, against
the global pointer leaf `(sym id << 5)`. All temporaries are freed in
ascending order before that phase, so the late temporaries are handed out
downwards from the function's temporary total: the manager pointer got
`total - 5`. With one reused task local the total was 333 (id 328, class 0,
index sorts last); two task locals change the total and the index sorts
first as in retail. Spelling of the indexed expression itself (pointer
arithmetic, accessors, casts, local copies) never matters.
