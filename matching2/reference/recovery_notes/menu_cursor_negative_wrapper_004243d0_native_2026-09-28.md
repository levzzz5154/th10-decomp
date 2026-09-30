# `0x004243D0` negative menu-cursor adapter: exact native C++ candidate

The complete 15-byte retail fragment at `0x004243D0` is reproduced by ordinary
C++ under native MSVC 7.1 `/GL` + `/LTCG`. This is a standalone candidate in
`matching2/build/experiments/menu_cursor_negative_wrapper_2026_09_28/`; it is
not a maintained-tree promotion or whole-executable result yet.

Retail executes `neg eax; push eax; mov eax,[esp+8]; call 0x0044BEA0; ret 4`.
The entry value in EAX is a signed delta, the stack word is the `MenuCursor*`,
and `MenuCursor::Advance` consumes the negated delta. The recovered source is:

```cpp
extern "C" __declspec(noinline) int __stdcall
ReverseAdvance_004243d0(int delta, MenuCursor* cursor) {
    return cursor->Advance(-delta);
}
```

Native LTCG privately passes `delta` in EAX and keeps only `cursor` at
`[ESP+4]`, so the compiler emits `RET 4` despite the source declaration's two
parameters. The call destination is the original `0x0044BEA0`; it is a
complete 128-byte C++ body copied from the maintained
`matching2/msvc/src/game/menu.cpp` into a scratch-only anchor translation unit.
The wrapper and anchor compile together, and the linker supplies their original
addresses through zero-filled layout gaps. Neither instruction bytes nor
addresses are rewritten, and the exported 15-byte COFF body has no relocation.

The full normal-project gate (`matching2/tools/matching/probe.py` with the
scratch project, the new source, and `matching2/build/oracle/th10.exe`) reports
`EXACT`: all 15 bytes at `0x004243D0` match with zero differences. The native
PE independently matches all 128 bytes at `0x0044BEA0`. The selected body SHA is
`3b6891d7e8770c1ccc3aae7b37632cb502e92535393356286301d358a117fc79`;
the anchor body SHA is
`88fb7c4b6160b6a62813effb64653e1673704b0b17fb55a7a9e3179ef8992c4e`.
The current gate is reproducible with:

```sh
PYTHONPATH=. python3 matching2/build/experiments/menu_cursor_negative_wrapper_2026_09_28/verify_candidate.py
```

Its `original_address_gate.json` records both complete extents, hashes, the
fresh native report, zero masks, zero instruction changes, and the retail-byte
comparison. `promotion_handoff.json` records every closure file and hash. The
cluster's synthetic caller is explicitly unselected: Ghidra has no Function
head or xrefs at `0x004243D0`, and a raw retail-PE scan found no `CALL/JMP
rel32` or absolute pointer encoding to it. This is evidence about current
references, not a claim that the code is unreachable. No Ghidra Function head
was created.

For integration, copy the four new source/layout files listed in the handoff,
replace only the manifest region at `0x004243D0` with the semantic source and
symbol, exchange its translation unit, and add the new native cluster. Keep the
existing `menu_cursor` cluster and original assembly source unchanged. Then
run the maintained normal probe and full executable byte gate before counting
this as recovered code.
