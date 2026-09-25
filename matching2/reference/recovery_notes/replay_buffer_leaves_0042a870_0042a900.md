# Replay buffer usage and byte append

Ghidra identifies two independent functions with no incoming xrefs. The
42-byte function at `0x0042A870` receives a replay buffer in ECX. It counts
complete six-byte records from the cursor at `+0x5460`, then adds the number
of bytes used in the buffer beginning at `+0x5464` and ending at the cursor
stored at `+0x6274`. The retail magic constant `0x2AAA9C9A` folds the
subtraction of `0x5464` into the division expression.

The 38-byte function at `0x0042A900` receives the buffer in EAX and a byte in
DL. It writes that byte at the cursor, advances the cursor, and returns true
when the byte-buffer count reaches `0x78` (120). The adjacent recovered
`0x0042A820`, `0x0042A830`, `0x0042A850`, and `0x0042A8A0` helpers establish
the same buffer layout and six-byte record stride.

The [C++ source](../semantic_candidates/replay_buffer_leaves_0042a870.cpp)
uses one typed layout for both functions. `GetCombinedReplayBytes_0042a870`
uses fastcall to preserve its ECX input. `AppendReplayByte_0042a900` uses typed
cdecl arguments in place of EAX/DL. The manifest retains both assembly records
in `previous_record`. Byte matching remains unverified, and no build or byte
comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
