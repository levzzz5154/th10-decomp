# Mechanical native-LTCG families — 2026-09-18

Twenty-one assembly regions, 830 bytes in total, were replaced by ordinary
C++ and verified byte-exact both with focused probes and the complete image
build.  The resulting executable remains exact across 487,936 bytes.

The recovered families are:

- eight fixed-size structure copies at `0x00412D60`, `0x00412D70`,
  `0x00412D80`, `0x00412D90`, `0x00413220`, `0x0041AC20`, `0x0041AC30`,
  and `0x004421A0`;
- six ESI-entry destroy-and-free wrappers at `0x004148E0`, `0x00418150`,
  `0x0041AFB0`, `0x00425090`, `0x0042B6D0`, and `0x0042CDB0`;
- timer resets at `0x004050D0` and `0x00412DB0`;
- owned-pointer-array cleanup at `0x00409EB0` and `0x0042BAD0`;
- the `0x0042B6F0` effect-pool update and its real `0x0042B9A0` tail
  wrapper in one schema-2 batch; and
- the 205-byte version matcher at `0x00420DD0`.

The version matcher exposed a distinct source-visibility requirement.  Retail
compiled its six-byte literal comparison to `repe cmpsb`; declaring the bytes
as absolute extern arrays hid their contents and changed instruction
selection.  The cluster schema now supports validated `data_aliases`, allowing
compiler-visible pooled literals to be rebound to their retail addresses.
Parser and binding checks reject malformed bytes, conflicting overlaps,
undeclared duplicate definitions, unbound aliases, and aliases unused by every
selected body.  The focused LTCG test suite has 20 passing tests.

After these promotions `make progress` reports 507 ordinary-C++ regions /
34,172 bytes and 2,078 assembly regions / 354,856 bytes.  `make verify`
compiled all 2,358 maintained sources without failure and reported the whole
executable exact.
