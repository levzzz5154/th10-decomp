# `ConstructGameState` (`0x00402160`) Ghidra audit

Audit source: connected Ghidra program `th10.exe` in project `th10`.

## Verified entry and call contract

- Ghidra's function boundary is `0x00402160..0x0040221B` (188 bytes,
  inclusive), named `ConstructGameState`.
- Ghidra recovers `uint * __stdcall ConstructGameState(uint *param_1)`.
- Its only code caller is `CreateGameState` at `0x00402640`; the call xref is
  at `0x00402675`. The caller pushes the allocated object pointer, calls this
  function, and uses the returned `EAX` pointer. The callee ends in `ret 4`,
  matching the one-argument stdcall stack contract.
- The only direct callee is `_eh_vector_constructor_iterator` at
  `0x0045252D`. Ghidra identifies it as a five-argument `__stdcall` helper:
  destination, element size, count, constructor callback, destructor callback.
  Its body advances by the element size, calls the constructor with the
  current element in `ECX`, and returns with `ret 0x14`. It has an internal
  exception cleanup path through `0x00452577`, which invokes array unwind with
  the destructor callback.

## Recovered successful-path operations

Ghidra's decompilation and the instruction listing agree on these operations:

1. Clear bit 0 at object byte offsets `0x34`, `0x48`, `0x90`, `0xDC`, and
   `0x168`.
2. Construct eight `0x3AC`-byte elements at object offset `0x180`, passing
   constructor `0x00402050` and destructor `0x00401FF0` to the vector helper.
3. Construct three more elements of the same size at offset `0x1F08`, with the
   same callbacks.
4. Clear bit 0 at offset `0x2A2C`, zero `0xAD9` dwords (`0x2B64` bytes) from
   the object base, set bit 1 at offset zero, and return the original pointer.

The entry also installs an FS-based SEH frame using handler thunk `0x0046556B`.
It sets a frame state word to zero at `0x004021E2`, immediately before the
second vector construction. These are part of the runtime's exception contract;
the successful-path decompilation by itself does not express that state
machine. The constructor `0x00402050` and destructor `0x00401FF0` are
separately identified by Ghidra as ECX-receiver functions, consistent with
the vector helper's callback convention.

## Decision

Keep the existing naked body. Ghidra gives a clear ordinary-path description
and the public entry ABI is known, but the body participates in compiler
generated SEH cleanup across both vector constructions. The helper also has a
five-argument stdcall ABI while the current shared declaration in
`asm_symbols.hpp` is an untyped cdecl assembly alias. A source rewrite would
need to preserve both the helper callback conventions and the outer
partial-construction cleanup path. The prior readable candidate did not
compile under the current declarations (MSVC C2733/C2664), and there is no
verified replacement here that preserves the exception behavior or retail
bytes. No source body or shared declaration was changed in this audit.
