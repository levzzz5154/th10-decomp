# Replay-pool constructor structural probes, 2026-09-28

The complete allocator at `0x0042AA50` remains unrecovered. The preserved constructor model emits a complete 139-byte contribution with six differing bytes: it schedules the state-buffer address calculation before the input-cursor store. Neither of the two bounded structural initialization probes improves that result. No maintained input was changed, and no source is offered for promotion.

The experiment lives in `matching2/build/experiments/replay_pool_constructor_2026_09_28`. Fresh Ghidra decompilation and disassembly are retained as `fresh_decompile_function.txt` and `fresh_disassemble_function.txt`. They cover the complete original 139-byte function, including allocation failure, full `0x6284`-byte clear, cursor and intrusive-link initialization, stage-list traversal, insertion, and `RET 4`. Its actual ABI is stage in ESI, list owner on the stack, and embedded-link result in EAX.

| Probe | Whole emitted contribution | Normal original 139-byte gate | Whole diagnostic differing bytes, including length |
| --- | ---: | --- | ---: |
| Preserved constructor baseline | 139 bytes | NOT EXACT | 6 |
| 03: POD pool with inline `Initialize()` and explicit null guard | 135 bytes | Rejected: extent outside MAP CODE contribution | 69 |
| 04: same source plus instruction-free `_ReadWriteBarrier()` after the input-cursor store | 135 bytes | Rejected: extent outside MAP CODE contribution | 70 |

Probe 03 keeps the complete ordinary C++ initialization semantics but allows MSVC to use the already-zero allocation pointer directly on failure. It removes the retail success jump and failure `XOR EDX,EDX`, shortening the contribution by four bytes. Its initialization still places `LEA EAX,[EDX+0x5464]` before the cursor store. Probe 04 restores the retail cursor-store/LEA order, but swaps the zero-fill setup to `MOV ECX,0x18A1` before `XOR EAX,EAX`. It also retains the four-byte control-flow shortening. The initial allocation-result copy agrees with retail (`8B D0`) in both structural models. These are full compiler outputs; the byte counts are positional comparisons of each entire emitted contribution against the entire original function, not candidate proof.

The maintained whole-body gate remained configured for 139 bytes throughout. `attempt03.json` and `attempt04.json` therefore report no selected normalized body and are terminal failures. `measure_structural.py` independently reads each complete actual MAP contribution from its fresh PE and writes `structural_measurements.json`; it does not truncate, pad, mask, patch, or feed oracle bytes into a build. Complete disassemblies and artifact hashes are retained alongside the sources. The closest preserved constructor baseline was restored in the scratch project after the two probes.

Earlier `__stosd` attempts 01 and 02 are compiler capability failures, not measured allocator bodies. Both produce C4163, saying `__stosd` is unavailable as an intrinsic in MSVC 13.10.6030, and fail to link. Attempt 01 leaves unresolved `___stosd@12`; explicit cdecl attempt 02 leaves unresolved `___stosd`. Neither produces a usable linked allocator measurement. `_ReadWriteBarrier` is supported and emits no instruction in probe 04.

The next useful lever is genuine full replay caller context that changes the constructor's scheduling without deleting its allocation-failure convergence. Further POD spelling variations are not supported by these measurements. Existing replay caller work is independent of this bounded constructor experiment; this result is not an impossibility claim.
