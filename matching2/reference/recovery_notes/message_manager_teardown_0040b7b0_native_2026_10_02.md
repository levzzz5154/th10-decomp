# Message manager teardown 0x0040B7B0 — complete native recovery

The complete 362-byte teardown is recovered as readable C++ with no inline assembly. The focused normal probe matches every byte without masking or rewriting an operand. Only this previously-assembly region receives new recovery credit.

## Behavior and genuine topology

The manager receives its state as one stack argument and returns with `RET 4`. It removes the update/draw tasks at +0x08/+0x0C under the scheduler lock, clears indexed render resource 0, destroys and frees the animation owner at +0x18, releases/frees animation banks 29..32, frees the script allocation at +0x14, and clears published manager/state globals.

The compiler entry is the actual complete 128-byte `Recovery_ReleaseGlobalStates` body at 0x004203F0. It retains its existing selected owner in `recovery_leaves.cpp`; this new link uses it solely as an unselected genuine caller. There is no synthetic loop, pressure caller, fake argument, volatile access, scheduling barrier, byte patch, or compiler-operand rewrite.

The ordinary inline bank-release helper keeps a reference to the actual bank slot while its resource is released. It then rereads the slot for CRT free and clears it. The bank reference yields retail's ESI slot address and EDI resource without adding an artificial operation. The scheduler body is the complete existing removal algorithm, with its real ECX task/EDX scheduler convention derived by native LTCG.

The old 2026-09-12 teardown investigation attempted the unrelated SEH-bearing item-manager destructor first and stopped after its missing EH prologue. This message-manager body has no SEH prologue. Genuine complete callee visibility is sufficient here; no additional residual or source sweep was needed.

## Independently checked full contributions

Every complete declared native body matches retail in this visibility context:

| Body | Bytes | Different bytes | Exported by this cluster |
| --- | ---: | ---: | --- |
| MessageState release 0x0040B7B0 | 362 | 0 | yes |
| Actual global-state caller 0x004203F0 | 128 | 0 | no |
| Bullet animation owner destroy 0x0040B3A0 | 192 | 0 | no |
| Animation resource release 0x00447810 | 242 | 0 | no |
| Indexed render resource clear 0x00447F70 | 87 | 0 | no |
| Resource removal marker 0x004493E0 | 92 | 0 | no |
| Scheduler removal 0x00449F60 | 114 | 0 | no |
| Worker stop 0x0044C150 | 101 | 0 | no |

Existing selected caller/helper owners and shared headers are unchanged. The layout-local dependency source copies the complete existing semantics and consistently casts the shared animation manager to each genuine typed view. The header does not fabricate data or change the ABI.

## Evidence

Experiment directory: `matching2/build/experiments/message_teardown_2026_10_02`.

- `base.json`: initial complete focused probe, exact.
- `final_packaged.json`: fresh probe of final reviewable source/layout/header files, exact.
- `complete_measurements.json`: independent native PE comparisons of all eight complete bodies above.
- `landing/proposal.json`: sole region classification/symbol change and new cluster entry.

Selected worker SHA-256: `4c0bed7e867f4b9d79e7b8fd6babef5c7ea5ccc6c3a6ec2cc81887e34c786e7a`.

The root owns manifest integration and final incremental whole-image verification.

## Integrated whole-executable gate

Root integrated the maintained ownership metadata. The incremental build
passed with zero failures: 1,604 unchanged units reused, six compiled, and
150 toolkit library members extracted. All 487,936 output bytes match retail;
zero bytes are masked. Whole-executable SHA-256 is
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

The three new recoveries replace 1,158 assembly bytes. Linked body/source/layout
hashes and package evidence are saved in
`matching2/build/experiments/quad_teardown_archive_2026_10_02_verification.json`.
The full inline-assembly-removal goal remains incomplete.
