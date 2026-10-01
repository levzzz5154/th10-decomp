# Float operand resolution and the entity forwarding caller

2026-09-30. Three more complete game functions are C++ without inline assembly:

| Entry | Bytes | Function | Machine calling convention |
| --- | ---: | --- | --- |
| `0x00412AA0` | 26 | `ForwardEclFloat` | Entity in EAX; selector and float on stack; RET 8 |
| `0x0044FE40` | 183 | `EclFloatVm::ResolveFloatOperand` | VM in EAX; selector in ECX; plain RET |
| `0x0044FF80` | 171 | `EclFloatVm::ResolveFloatValue` | VM in EAX; selector's low bits in CL; float on stack; RET 4 |

Together they retire 380 bytes of assembly. The float operand is an independent
native-LTCG cluster; the real forwarder and float-value resolver share a batch
with separate maintained translation units. Complete compiler-generated
functions are selected without instruction rewriting or masked bytes.

## Recovered behavior

Live Ghidra MCP decompilation and the retail instruction listings confirm the
indirect operand bitmap at table +8, float slots at +0x10, byte-addressed VM
stack at +8, cursor at +0x1008, frame base at +0x100C, external context at
+0x1014, and the context's float-value virtual at vtable +0x0C. The preserved
constants at `0x00470B04` and `0x00470B60` are exactly 0.0f and -1.0f.

Immediate operands return their literal value. Non-negative indirect operands
encode a byte displacement into the current frame. A displacement of -1 pops
a raw value word, then a type-tag word; an integer tag converts the word to
float. Other negative displacements are truncated to an integer selector and
resolved through the external context. Both paths preserve the native x87
comparisons and truncation helper at `0x00463B2C`.

The operand resolver returns an integer-tagged scratch value directly through
x87. The supplied-value resolver first rounds that conversion to float in its
original stack argument, then reloads the argument for its return. The C++
models preserve this distinction. They also preserve retail's underflow paths:
the supplied-value resolver returns its input when no value can be popped;
the operand resolver leaves its local result slot unwritten. Initializing that
local with the selector emits 187 bytes instead of 183, so that attempted
behavior change was rejected.

## Source shape and the caller/callee batch

The successful operand model tests the bitmap before fetching the indirect
slot, binds its displacement by reference, and expresses the two scratch pops
as separate cursor-field decrements. This is the same useful source shape as
the previously recovered integer operand resolver.

The float-value model uses an integer selector: its machine code only reads
CL, but the forwarding caller loads the selector as a complete word. A byte
formal reproduced the callee alone and produced the wrong byte-load instruction
in the caller. Both formal types reproduce the 171-byte callee; the integer
formal also permits the exact caller.

A compound `vm->current->interpreter` call produced a 26-byte forwarder with
nine differing bytes. Naming only the first pointer (`EclFloatOperandSlot*
slot = vm->current`) yields the retail schedule: copy the float word into ECX,
chase both pointers through EAX, push ECX, load the selector into ECX, call the
actual value resolver, and RET 8. No ABI stand-in replaces the real callee in
this batch. Member/free forms, reordered parameters, raw-word forwarding, and
a fully resolved pointer local were measured before selecting the slot local.
The raw-word variants shortened the caller to 22 bytes and were rejected.

The shared `th10/script/ecl_float_values.hpp` exposes the table, tagged stack,
external context, interpreter, and entity-slot views. Its compile-time size
checks require the 32-bit stack and interpreter layouts. Synthetic loop drivers
retain the private entry-register conventions; their code and layout gaps are
not recovered game code. Existing assembly and other native-LTCG callers keep
their fixed-address aliases and were checked with the real implementations.

## Verification and remaining work

The final focused probe checks 11 complete regions: these three functions,
the integer operand/value and shared dispatcher unit, the two destination
resolvers, and the three ECL operand thunks. The whole-image build then checks
all .text bytes and compares the entire 487,936-byte executable with the
independent reference. Source fingerprints, compiler provenance, native
function records, and comparison results are in the companion evidence JSON.

Reproduction:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/game/ecl_forward_float_00412aa0.cpp \
  --source src/script/ecl_resolve_float_operand_0044fe40.cpp \
  --source src/script/ecl_core_interpreter.cpp \
  --source src/script/ecl_resolve_variable_value_00450030.cpp \
  --source src/unidentified/FUN_0040c650_0040c650.cpp
make MSVC_ARGS='--jobs 32 --verify matching2/build/oracle/th10.exe'
```

Scratch variants are in `matching2/build/experiments/ecl_float_resolvers_2026_09_30/`
and `matching2/build/experiments/ecl_float_forward_2026_09_30/`. This closes the
four-resolver historical ABI audit; the interpreter state machines remain
assembly. Manifest accounting is 1,840 semantic regions / 96,307 bytes and
459 assembly regions / 226,590 bytes. The rendering sources still contain
inline x87 blocks despite their semantic classification. The full
no-inline-assembly objective remains incomplete.
