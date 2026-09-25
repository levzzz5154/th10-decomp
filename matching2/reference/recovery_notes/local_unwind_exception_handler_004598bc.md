# Local unwind exception handler at 0x004598BC

Live Ghidra disassembly and decompilation identify a standalone 34-byte cdecl
SEH handler at `0x004598BC..0x004598DD`. Its four arguments are the exception
record, establisher frame, context record, and dispatcher context pointer.
It reads `ExceptionFlags` at record offset 4. When either unwind flag bit
(`0x02` or `0x04`) is set, it stores the establisher frame into the dispatcher
context and returns `ExceptionCollidedUnwind` (3). Otherwise it returns
`ExceptionContinueSearch` (1). Ghidra's function and typed prototype were
saved with this interpretation.

The maintained [C++ source](../semantic_candidates/local_unwind_exception_handler_004598bc.cpp)
implements that behavior without inline assembly. The manifest preserves the
original assembly record in `previous_record`. A prior byte matching attempt
recorded in `0045xxxx_0046xxxx_wave18.md` emitted 32 bytes against the retail
34-byte body. No build or byte comparison was run for this semantic promotion;
exact retail matching remains unresolved.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
