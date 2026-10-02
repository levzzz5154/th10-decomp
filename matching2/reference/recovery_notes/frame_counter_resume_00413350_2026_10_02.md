# Frame-rate counter factory: retained exact baseline

The unfinished C++ replacement of `0x00413350` was tested through the normal
incremental build on 2026-10-02. Its complete native compiler contribution is
151 bytes, matching the retail extent. It still differs in nine bytes, so the
maintained owner remains the exact assembly in `src/game/stats_task.cpp`.
The attempted promotion and its extra compiler-context loop were removed.
This factory receives no assembly-free recovery credit.

The best readable candidate is retained in
`matching2/reference/semantic_candidates/frame_rate_counter_create_00413350.cpp`.
It clears and publishes the 0x8C-byte counter, allocates a 36-byte callback
task, registers it on the secondary scheduler at priority 0x2F, and retains
the task on the counter. The draw callback has a named declaration bound to
its full address, `0x00413690`. Ghidra confirms the genuine zero-argument
worker-start call at `0x00420207`.

Reordering the context assignment before the enabled-bit assignment makes
the entire registration tail exact. The sole remaining difference is that
MSVC emits the constructor's flag-mask AND immediately after the flag-word
load. Retail places it after the callback and priority clears. All registers,
branches, allocation calls, other stores and return instructions match.
The first differing byte is `0x00413394`.

A captured whole flag word and `_ReadWriteBarrier` reproduces the instruction
order, but exchanges the long-lived zero and counter registers (EBX/EBP),
leaving 18 differing bytes. It is an unselected diagnostic. The best retained
candidate contains no assembly, barrier, volatile control or supplied code
bytes. It was rooted directly as the real no-argument factory; no additional
synthetic caller loop was needed.

Measurements and input hashes are retained under
`matching2/build/experiments/frame_counter_resume_2026_10_02/`, including
`natural.cpp`, `candidate_layout.json`, `candidate_region.json`,
`candidate_hashes.json` and `natural_incremental.log`.

After restoring the exact factory baseline and integrating the independently
recovered pause-menu update and callback, the normal incremental whole-image
gate passed: 487,936 bytes, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
