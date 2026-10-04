# FPS display factory at 0x00413350 (2026-10-04)

The complete 151-byte function in `src/game/stats_task.cpp` is now readable,
inline-asm-free C++ and passes the exact-byte probe. The previous standalone
104-byte candidate lacked the scheduler callee's private conventions.

Live Ghidra decompilation confirms this sequence:

1. Allocate an 0x8C-byte display, zero it, set flag 2, and publish it at
   `0x00477708` inside its constructor.
2. Allocate an 0x24-byte scheduler task. Clear its callbacks and priority,
   clear the ownership bit while preserving the other flag bits, and initialize
   its embedded link to refer back to the task.
3. Set callback `0x00413690`, context to the display, and flag bits 0/1.
4. Register the task in the secondary scheduler at priority 47, store it at
   display offset 0xC, and return the display.

The compiler context links the recovered secondary-registration body from
`layout/ltcg/scheduler_anchor_00402230.cpp` at `0x00449B70`. Native LTCG then
keeps the display in EBX, the task in ESI, and the priority in EDI, reproducing
the entire retail sequence. The context and scheduler anchor are unselected;
only the real factory enters the final image.

The first complete candidate was already 151 bytes and differed only in the
order of the ownership-mask instruction among the callback initialization
stores. A separate inline `InitializeTaskLink` helper restores retail's order.
The existing `scheduler.hpp` remains unchanged. No memory barriers, inline
assembly, instruction rewriting, or comparison exceptions are needed.

The constructor preserves retail's allocation-failure behavior: publication
occurs only after successful display allocation, and task setup is performed
without adding a new failure branch.

Validation:

```sh
python3 matching2/tools/matching/probe.py --source src/game/stats_task.cpp
make EXACT=1
make
```
