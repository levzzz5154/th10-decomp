# Laser initialise 0x0041E5C0

2026-10-02. Ordinary C++ selected in the existing
`layout/ltcg/entity_start_script_00404f30.json` cluster, next to the script
start it calls twice; the whole EXE is exact.

* It is a virtual method (vtable slot at file offset 0x6CA14), rooted in the
  cluster; laser in ECX, parameters on the stack, RET 4.
* Retail writes the first flag change of each animation through the pointer it
  passed to the two calls (ESI) and the second through the laser. A local
  `Entity* animation` for the calls and the first change, and the member for
  the stop frame and the second change, reproduces both.
* The last five assignments are scheduled by the compiler, not emitted in
  source order. Only one of the 120 orders is exact: `unknown_40c`, `length`,
  `unknown_44`, `width`, `angle`.
