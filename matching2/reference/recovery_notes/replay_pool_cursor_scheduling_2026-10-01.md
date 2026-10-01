# Replay pool allocator: cursor scheduling follow-up

The complete C++ allocator at `0x0042AA50` still emits 139 bytes against the 139-byte retail function, with six differing bytes. This follow-up does not promote the allocator; its maintained region remains assembly.

Fresh Ghidra confirms allocation of a `0x6284`-byte replay pool, whole-object clearing, initialization of input and state cursors at offsets `0x5460` and `0x6274`, and append of its intrusive link at `0x6278` to the requested stage list. The native compiler scope derives the genuine stage-in-ESI argument and stack list pointer, returning the link in EAX with RET 4.

Five complete native builds compare the baseline, a volatile input-cursor field, a volatile state-cursor field, a volatile input-cursor store, and a volatile state-cursor store. All produce the same 139-byte body. The only mismatch remains the scheduling of `mov [edx+0x5460],edx` and `lea eax,[edx+0x5464]`: retail stores the input cursor first; the compiler calculates the state-record address first. Differences are at offsets `0x1F`, `0x20`, `0x21`, `0x25`, `0x26`, and `0x27`. Volatile access alone does not constrain this independent address computation.

The prior constructor barrier and complete snapshot-caller investigations already measured other source and compiler-scope approaches. This result removes volatile cursor access as a useful next scheduling lever; it does not establish impossibility of a complete C++ match.

All scratch sources, manifests, layouts, native PE files, compiler reports, source hashes, and fresh Ghidra output are retained under `matching2/build/experiments/replay_pool_cursor_followup_2026_10_01`. Its `results.json` links the five complete-function measurements and records their proof hashes. No retail bytes enter compilation, no opcode or address-operand edits are applied, and no bytes are masked. Main sources and the last verified full executable are unchanged by these experiments.
