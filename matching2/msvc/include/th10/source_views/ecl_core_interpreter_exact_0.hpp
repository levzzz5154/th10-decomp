#pragma once
#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"


// BLOCKED (D2102): no readable dispatcher candidate is retained.  Ghidra
// measures 0x1A1A (6682) bytes, 329 basic blocks, 697 edges, 252 conditional
// branches, 127 calls, and cyclomatic complexity 370; the maintained retail
// extent is 7020 bytes including the split tail/labels.  Opcode edges cover
// 60 switch successors at 0x0044E205 and shared exits 0x0044FB68/77/85/96/
// B0/B2.  The dispatcher calls SpawnChild at 0x0044E268/2A2 and StartChild
// at 0x0044E360, supplying the private EDI/EAX child ABI.
// residual_class=complete schema-2 opcode/state-machine translation;
// residual_bytes=7020 source bytes.  The exact assembly wrapper remains the
// only measured implementation; a 5-byte readable skeleton is forbidden.
// variants_tested=Ghidra decompile, opcode/state overlay, helper models, and
// native-LTCG child ABI probes; no complete readable candidate matched.
// next_lever=first recover the full opcode hook/state cluster and the actual
// dispatcher caller edges, then remeasure the complete body.
// 0x0044E1A0..0x0044E1D7: FUN_0044e1a0
// Naked body preserves the retail register/stack ABI.
