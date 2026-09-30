# Native C++ recovery checkpoint, 2026-09-27 addendum

Nine additional routines, totaling **656 bytes**, were recovered and integrated
after the earlier 13-routine checkpoint: **22 routines / 2,550 bytes** across
the two checkpoints. Every new selected function is readable
C++ without inline assembly, naked bodies, or encoded instructions. Normal
probes compare the complete retail contribution at its original address.

| Entry | Bytes | Recovered operation |
| --- | ---: | --- |
| 0x0040D510 | 28 | Set bit 1 on the two owned objects |
| 0x00422200 | 28 | Matching flag-setter twin |
| 0x00439080 | 28 | Cleanup and optional object deletion |
| 0x00447940 | 143 | Copy position record and derive normalized coordinates/scales |
| 0x00447F70 | 87 | Release the indexed resource set |
| 0x004492F0 | 90 | Set object and child positions |
| 0x00449350 | 111 | Set positions with the 224/16 translation |
| 0x00449AA0 | 59 | Initialize two embedded resource lists |
| 0x00449E50 | 82 | Release queued resources under the scheduler lock |

The three twins reuse existing successful native models. The other functions
use fresh typed bodies and compiler contexts that reproduce their private
register conventions. The position setters include a complete, independently
exact 73-byte Find anchor; it remains excluded from recovered output.

The indexed release keeps the retail repeated clear with a zero-instruction
compiler barrier. The resource initializer uses barriers to preserve its two
store phases. The resource-release loop needs no barriers; a volatile pointer
field preserves the retail repeated stack-argument read.

Current manifest totals: **1,629 semantic regions / 72,883 bytes** and
**1,149 assembly regions / 316,215 bytes**. The semantic classification still
includes three previously recovered render functions containing inline assembly
(0x00442670, 0x00442AD0, and 0x00443B60). These also remain part of the goal.

Whole-executable verification **passed**: all 2,249 maintained build units
completed without failure, and the full **487,936-byte executable equals the
stable retail oracle byte for byte**. SHA-256:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

The manifest gate and full hash gate passed. The audit also checks every current
project input against the build report, checks all nine sources for assembly,
and checks all eight new native units for zero masking and zero instruction or
address-operand rewrites. Machine-readable proof is
`matching2/build/experiments/native_recoveries_2026-09-27_addendum_verified.json`.
The build log is `native_recoveries_2026-09-27_addendum_build.log` in that same
experiment directory.

An independent source review found no substantive issues. Recovery plate
comments were saved and read back for all seven available Ghidra Function
heads; 0x00422200 and 0x00439080 remain raw fragments with retained evidence.

The full goal remains active. New unmatched candidates were retained with
measured residuals rather than promoted:

- Back and front animation registrars: exact prefixes, but remaining allocator
  and zero-correction differences change the complete contributions.
- 0x00449A50: 32-byte candidate with scratch-register differences.
- 0x00449870: complete 217-byte candidate with constructor/assignment allocator
  differences; its full 194-byte preserving-loader anchor is exact.
- 0x00436570: process-launch candidate emits 204 bytes against the retail 201,
  with delayed argument loading and polling scratch-register differences.

Individual recovery notes and experiment reports retain the source shapes,
compiler-context details, Ghidra evidence, and residuals. The next substantive
ranking starts with 0x00421070/0x00421300 (queued cleanup and handle release),
0x00413A20 (score task setup), and 0x0044A4E0 (joystick polling), using their
now-recovered dependencies.
