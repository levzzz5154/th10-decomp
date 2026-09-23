# Text slice `0x00440000..0x00440FFF` audit

Audit date: 2026-09-23. No separate compact function in this interval is a
conversion candidate. Both the current region manifest and live Ghidra place
the entire interval inside the assembly implementation of the ANM VM tick at
`0x0043EE30`.

## Boundary evidence

The current `matching2/msvc/regions.json` has no region whose start address is
inside `0x00440000..0x00440FFF`. Its only region overlapping that interval is
`asm_FUN_0043ee30_0043ee30`, starting at `0x0043EE30`, source
`src/script/anm_vm_tick.cpp`, size 9,964 bytes. The region continues past this
interval through `0x0044151B`, where it includes the alignment and the ANM
opcode table.

Live Ghidra lookups at both `0x00440000` and `0x00440FF0` resolve to the same
function, `FUN_0043ee30`, whose entry is `0x0043EE30` and whose function body
ends at `0x004413A2`. The live function listing contains no separate entry
inside the assigned interval. Disassembly at `0x00440000` begins with a
conditional branch, then loads operands through `EBX`, calls
`0x0043EC70` with the animation object in `ECX`/`EBP`, and rejoins the common
dispatcher flow. These are interior instructions, not a callable leaf with an
independent C++ entry contract.

## Conversion blocker

The overlapping function is a monolithic interpreter/update path. Live
Ghidra control-flow analysis reports 532 basic blocks, 2,752 instructions,
473 cyclomatic complexity, 93 loops, and 203 call instructions. Its opcode
arms share script-PC, timing, interrupt, object-register, and frame-update
state; the slice contains no return boundary or function-local cut at which a
small ordinary C++ translation could replace the assembly safely. The
function's private helper call surfaces are documented in
`anm_vm_tick_0043ee30_dependency_audit.md`, including object-in-`ECX`,
register-carried operand/output pointers, and an x87 `ST(0)` input to the frame
conversion helper.

Disposition: retain the current assembly. A semantic conversion requires the
complete `0x0043EE30` dispatcher and its nonstandard helper surfaces, not a
partial edit to this interval. No source or manifest change was made. No
build, probe, or test was run.
