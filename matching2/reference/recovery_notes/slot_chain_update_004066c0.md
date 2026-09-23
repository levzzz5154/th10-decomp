# Six slot-chain update at `0x004066C0`

Ghidra confirms a 25-byte routine that loops over slot indices 0 through 5,
calls the per-slot worker at `0x004066E0`, and returns 1. The owner arrives in
EDI under a private convention. Ghidra reports no direct callers or xrefs, so
the owner type and meaning of the slot chains remain uncertain.

The per-slot body at `0x004066E0` walks the head at `owner + 0x14 + slot * 4`
and follows links at node offset `+0x44C`. It copies a point from `+0x3B4`
and `+0x3B8` to `+0x33C` and `+0x340` after adding `(224,16)`, copies the
word at `+0x3BC` to `+0x344`, conditionally normalizes an angle from `+0x3E4`
when bit `0x08000000` at `+0x364` is set, sets bit 2, and dispatches the node
through `0x004451C0`.

The maintained source now models the six-iteration driver and helper as
readable C++ with offset-based field names. `layout/ltcg/slot_chain_update_004066c0.json`
uses the per-slot method as an ABI anchor and a synthetic array caller to
attempt to select the private EDI receiver. The anchor/context extents and EDI
selection are unverified; no build or probe was run.
