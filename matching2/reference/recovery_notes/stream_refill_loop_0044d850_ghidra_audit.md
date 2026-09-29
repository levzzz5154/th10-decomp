# Stream refill loop `0x0044D850` / `0x0044D9F0`

2026-09-26: the full function now has a typed candidate and differential
coverage with its actual restoration/refill/cursor dependencies and worker
caller. See [restart, service and worker recovery](sound_stream_restart_service_worker.md).
This supersedes the old behavioral sketches; both production rows still await
native helper ABI and byte gates.

Live Ghidra analysis of `th10.exe` identifies `FUN_0044D850` with a
`uint __stdcall` display signature and one recovered pointer parameter. Its
only caller is `FUN_0043E3A0`; the call at `0x0043E435` pushes the global stream
pointer from `EDX` and the current mode from `ESI`, then the callee returns
with `RET 8`. The manifest splits the body between `0x0044D850` (413 bytes)
and `0x0044D9F0` (221 bytes). Ghidra's decompiler warns that several blocks,
including the `0x0044D9F0` refill loop, are unreachable in its recovered CFG.

This has a conventional stack entry, but it is not an independent standard-ABI
translation candidate. Its refill path calls `0x0044D110` with the streamer in
`EAX` and stack arguments, archive seek `0x0044DD40` with the cursor in `ESI`
and mode in `AL`, and archive read `0x0044DE10` with the cursor in `EAX`, byte
count in `EDX`, and additional stack arguments. The routine also dispatches
through several DirectSound vtable slots. Existing recovery notes identify the
cursor and refill calls as custom-ABI dependencies.

Keep both manifest rows as exact assembly until the real caller and these
callee conventions can be modeled together. The readable conversion boundary
is the full stream-thread/refill/cursor cluster, not either split row alone.
