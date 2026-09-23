# Stream interface array initializer `0x0044CE80`

Live Ghidra analysis of `th10.exe` identifies a 118-byte function at
`0x0044CE80`. Its displayed signature is `__stdcall` with two stack dwords,
but the decompiler also reports live-in `EAX`, `ESI`, and `EDI`; there are no
caller or xref records. The result is the initializer object in `EAX`, and the
body ends in `RET 8`.

The disassembly shows the roles of those live-ins: `EAX` points to the source
interface array, `ESI` is the object being initialized, and `EDI` is the entry
count. The routine stores the `0x004705D8` vtable, allocates and copies the
pointer array, stores its two stack arguments and count, calls streamer refill
`0x0044D110`, then invokes vtable slot `+0x34` for each interface before
clearing `[ESI+0x30]`. Ghidra lists `operator_new` and `0x0044D110` as direct
callees.

Keep the exact assembly row for now. The nominal stack signature cannot express
the three live-in registers, and the refill edge also uses a private register
convention. A readable translation needs the initializer and refill routine
recovered as one native-LTCG cluster.
