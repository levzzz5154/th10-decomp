# Scheduler callback allocation: native C++ residual, 2026-09-28

This is a measured **unpromoted** recovery. The maintained 74-byte SchedulerCallback_Create at 0x00449ED0 still contains inline assembly; its existing semantic classification does not satisfy the assembly-free goal.

Retail allocates a 0x24-byte callback task through the separately recovered global operator new at 0x00452493. On allocation success the constructor captures the old flag word, clears the three routine fields and priority, clears heap-owned bit 0, and self-links the task pointer while clearing next/previous. The outer routine then clears the register/remove callbacks again, publishes the requested callback, and sets heap-owned bit 0. The tail is unconditional even when allocation returns null; the candidate preserves that retail behavior. The public ABI is callback at [ESP+4], result EAX, RET 4.

Fresh Ghidra decompile and disassembly retained under `matching2/build/experiments/scheduler_callback_create_00449ed0_2026_09_27/native_variant/ghidra_*.txt` establish the complete 0x00449ED0..0x00449F19 body. Source uses a typed 36-byte node and the constructor pattern already independently proven in MessageHost_Init's 334-byte semantic recovery. A zero-instruction _ReadWriteBarrier keeps the captured constructor flags adjacent to their mask/store.

The isolated experiment separates the callback allocator into `src/game/scheduler_callback_create.cpp` and leaves all other bodies in `src/game/scheduler.cpp`. Native LTCG retains the real public stdcall ABI through a synthetic indirect caller and linker root; this 16-byte context is unselected. Operator new remains an opaque genuine cdecl dependency at its retail address. No shortened/fake allocator body is compiled.

The independent final standard probe emits all **74 bytes with 22 differences**. Constructor branch distances, call displacement and RET4 are correct. Retail assigns ECX to the long-lived zero and EDX to captured constructor flags; C++ assigns EDX to zero and ECX to captured flags. Retail's tail loads callback in EDX, clears register/remove fields, reads and sets flags in ECX, then publishes callback and flags. The candidate publishes callback earlier and schedules the two routine clears later. No instruction, address operand, comparison mask or reference-generated replacement changes these bytes.

Bounded alternatives were measured with the normal native comparison: MessageHost-style out-of-class inline constructor and uniform pointer fields (22 differences); barrier before callback publication (26); volatile final routine clears (23); separate inline SetCallback member (22); forceinline Reset(node, captured flags) helper inside the constructor (22); and the same helper called from explicit conditional operator-new allocation (22). Native LTCG alone does not resolve the ordinary O2 residual. Attempt01's guessed context extent was rejected before body comparison. Attempt06 had a generated local/member name collision and is explicitly invalid evidence; it was corrected for the measured attempt07.

The original typed constructor candidate is restored in `native_variant/msvc`. `final.json` is the fresh complete-body comparison; `measured_residual.json` records every differing byte and variant status. `scheduler_remaining.json` independently proves the two remaining owned scheduler.cpp bodies (308 + 268 bytes) remain exact after the scratch-only ownership split.

Source SHA256: `4517735fc143029c5e4fd3f38a6686fccaf8038bac54103425d1768102d80797`.

Native body SHA256: `b0518c6c4a81c258cd22a49938d3b54c10076d673c5037b75b664bb7d6194656`.

A future attempt should establish a concrete source/evaluation dependency that extends callback EDX through the two final clears while allowing the zero-to-final-flags ECX lifetime. Repeating the native backend switch or the tested inline constructor/helper topologies has no new evidential basis. No maintained project files were modified by this experiment.
