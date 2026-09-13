# Effect particle advance at 0x00445620: reconnaissance

2026-09-13. `0x00445620` (598 bytes) is the last large region in the render
family whose own ABI is a standard one (`int __thiscall sub_445620(int this)`,
plain `RET`) and whose three callees are all expressible, so it needs no LTCG
cluster. The disassembly fixes its shape as follows (all offsets are from the
entity in ECX unless marked `state`):

- `state = this->resource` (`[this+0x358]`) is a 0x4A8-byte block.
- `state[0..2]` receives `base_position + position` (`[this+0x340] +
  [this+0x334]`, `+0x344 + +0x338`, `+0x348 + +0x33C`).
- Two guarded blocks, each: `delta = state->rate + state->accumulator`; the sum
  is stored back and compared against the pooled float at `0x470B04` (zero);
  only when it is nonzero does a loop run. Both loops are the same shape —
  eleven iterations with a `0x54` stride over records based at `state+0x30`,
  and each iteration adds the pooled `1.0f` at `0x470AFC` to the three floats
  at `+0x14`, `+0x30` and `+0x4C` of that record. The second block's fields are
  the same three with `+4` (its guard reads `state+0x18`, the loop body adds to
  `+0x18`, `+0x34`, `+0x50`). So the two blocks are *duplicated* in the source,
  not a shared helper.
- The main loop runs `0x1F` times over records based at `state+0x1C` with a
  `0x1C` stride, with a parallel float array at `state+0x3A0` advancing by four
  bytes per iteration. Per iteration: the same eleven-record guard loop keyed
  off `record+0x14`, `record[0x10] = this->color` (`[this+0x2FC]`),
  `record[0x13] = 0`, then `sub_4458B0(record, running_value, delta)` as a
  `__thiscall` with two float stack arguments, and finally the placement is
  re-added to the record's three floats.
- The running value starts at `0xC0490FDB` (a float local) and advances by the
  pooled float at `0x470B6C` each iteration.
- The tail copies seven dwords (one 0x1C record) from the first record over the
  slot after the last one (`rep movsd` with `ESI` = `state+0x1C`), then returns
  0.

Two things to settle when attempting it: the field layout of the 0x54-stride
records (`record[0x14]`, `record[0x30]`, `record[0x4C]` are the three floats)
and the three pooled float constants (`0x470AFC` = 1.0f, `0x470B04` = 0.0f,
`0x470B6C`), which a plain region binds through the manifest symbol map rather
than a cluster `constants` entry. The callee `0x004458B0` is a `__thiscall`
taking two floats on the stack, so it stays an ordinary declaration.
