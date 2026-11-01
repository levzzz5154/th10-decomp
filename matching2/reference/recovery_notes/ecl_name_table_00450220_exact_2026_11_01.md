# Script name table loader 0x00450220: byte-exact (2026-11-01)

The 589-byte loader `ScriptFileLoader::Parse` (`src/script/sptlib/ecl_name_table.cpp`)
is now byte-exact C++. It ships as an ordinary translation unit: the plain
`/O2 /Gz` compile matches without `/GL` or an LTCG cluster. Its callees are the
plain cdecl CRT `malloc` (0x00452706, `_entry_malloc`) and `free` (0x00452422,
`_crt_free`), and the manifest's symbol table binds both. The equivalent layout
`build_support/layout/equivalent/ecl_name_table.json` is gone. Before this it had
194 of 198 instructions identical, 4 recorded differences and 23 differing bytes.
The naked-asm owner `build_support/exact/script/sptlib/ecl_name_table.cpp` is gone
too; no other region used it. The region record is
`semantic_ScriptFileLoader_Parse_00450220` (symbol `?Parse@ScriptFileLoader@@UAEHPAH@Z`),
and its `previous_record` keeps the asm record.

## What closed it

The search agent (`build/experiments/goal_2026_11_01/ecl_name_table/REPORT.md`)
reached 198 of 198 identical instructions and 0 differing bytes in the
equivalence rig with two changes.

1. **Count update through a reference.**
   `AddCount(name_count, files[file_count]->sub_count)` uses
   `static __forceinline void AddCount(int& count, int n) { count += n; }`.
   The store goes through a pointer, so Gopt no longer forwards the sum into
   `name_count * sizeof(ScriptSub)`. The size reads the stored count back as a
   single-use temporary, and the shift lowering (c2 0x1073FB90) keeps `shl`
   instead of `lea`. That was the open question of
   `ecl_name_table_00450220_shift_lea_2026_10_25.md`.

   The `shl` adds the Riscify `GetReg` call that moves the head's count into
   EDX as retail does: `mov edx,[ebx+8]` early, then `add edx,eax; mov eax,edx;
   shl eax,3`. A pointer helper `AddTo(&name_count, n)` gives the same bytes. A
   plain `+=`, or an inline member `void AddNames(int n) { name_count += n; }`,
   still forwards the sum (23 bytes).
2. **The free names both table locals.** The update removes the head's sum as a
   register candidate. That turned the ChoosePhysReg EBP contest (old table vs
   names cursor) into a tie, which the names cursor wins (485 bytes, frame 0xC).
   The free now reads

       if (previous) crt_free((old == previous) ? old : previous);

   It replaces the old `(sub == files[file_count]->sub_count) ? previous : previous`
   consistency hack, which is gone. `old` and `previous` are both loaded from
   `entries` (the original reason for two locals: c2 keeps retail's second
   `test ebp,ebp` only when the two tests read different variables). The select
   between them keeps the old table ahead. ChoosePhysReg trace: EBP goes to the
   old table at priority 72. With a plain `crt_free(previous)` it goes to the
   names cursor at 67.

Parse is now declared `virtual`. Retail calls it through slot 0 of the vtable at
0x0046D0F0, and `LoadChunks` is slot 1 (`call [edx+4]`). The codegen is
identical to the non-virtual member, and `__declspec(noinline)` was dropped.

## Readability sweep (what does not reach 0)

About 110 rig builds tried to replace the select and the duplicate local with a
natural spelling. None reached 0 bytes:

- **One `old` local with any free spelling: 480.** The second test folds. The
  spellings were a `SAFE_FREE` macro, `FreeTable(ScriptSub*)`, a nulling
  `SafeFree(ScriptSub*&)` or `SafeFree(ScriptSub**)`, and a copy-and-free
  `MoveTable(to, from, count)`. The by-reference forms also give `old` a stack
  home.
- **Plain free with two locals: 480 or 485.** All 16 assignments of old/previous
  to the head test, the memcpy source, the free test and the free argument were
  tried in both declaration orders. Testing one variable twice gives 480; using
  two variables loses EBP and gives 485.
- **Other free spellings:**
  - `if (previous && previous == old) crt_free(old)`: 480. So do the nested and
    `previous != 0 && old == previous` forms.
  - `if (previous == old && previous) ...`: 51.
  - An if/else free: 12.
  - `old ? old : previous`, `previous ? old : previous`,
    `old != 0 ? old : previous`: 485.
  - An unguarded `crt_free(previous ? previous : old)`: 354.
- **Exact spellings:** `(old == previous) ? old : previous` and its mirrors
  (`(previous == old) ? old : previous`, `(old != previous) ? previous : old`),
  `(old < previous) ? old : previous`, and
  `if ((old == previous) ? old : previous) crt_free(previous)`. The shipped
  source keeps the first, with comments.

## Validation

- Rig (`vtry.py`): final source DIFFBYTES 0, as both the virtual and the
  non-virtual member.
- `tools/matching/probe.py --source src/script/sptlib/ecl_name_table.cpp`: EXACT.
- Full `build_msvc.py` of the promoted tree: passes, and the linked `.text` is
  exact outside the equivalent regions. Ordinary C++ went from 2,313 to 2,314
  regions and equivalent regions from 9 to 8. Byte-exact C++ went from 90.9% to
  91.1% of bytes (293,510 of 322,064).
