# Stage STD consumer and cursor evidence

This checkpoint records only behavior visible in the checked-in raw Ghidra
output. It is not a complete STD format specification.

- `0x00403850` relocates header `+0x08` into the stage context at `+0x1C`.
- `0x00404450` initializes the instruction cursor at context `+0x4C` from
  context `+0x1C`.
- `0x00403C80` reads an instruction's due frame at `+0x00`, opcode at `+0x04`,
  and a signed stride at `+0x06` (`movsx` in the common advance path).
- Opcode 0 leaves the dispatch loop without taking the common advance path.
- Opcode 1 reads a relative cursor destination at `+0x08` and a time value at
  `+0x0C`, then sets the cursor to context `+0x1C + destination`.

Minimum bytes visibly accessed by `0x00403C80` are:

`0=8, 1=16, 2=20, 3=28, 4=20, 5=28, 6=20, 7=12, 8=20, 9=28,
10=52, 11=52, 12=9, 13=12, 14=16`.

The reconstruction bounds the stream conservatively by the containing STD
buffer because a narrower terminal region has not yet been proven. This bound
is named `container_end_bound` and must not be interpreted as a recovered
timeline end.
