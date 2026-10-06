# Complete player-state graph, 2026-10-06

The earlier 780-byte partial probe has been replaced by a complete ordinary
C++ reconstruction of the 3,112-byte `0x00425730` owner. The retained source
measures 3,024 bytes, including the full 20-byte switch table. There are 2,812
differing overlapping bytes and 136 instruction groups under address-only
diagnostic rebinding. The production owner remains assembly; zero new bytes
are selected or credited.

Candidate: [player_state_00425730](../semantic_candidates/player_state_00425730/).
Reference behavior comes from the saved Ghidra decompile at
`decompiled/ghidra_augmented/functions/00425730.c`, checked against the current
retail PE and complete maintained assembly. Ghidra MCP discovery confirms the
connected th10 project, with th10.exe and c2.dll open. No new live decompile
result is claimed.

## Complete behavior and storage

The source covers all five switch states and their shared tail. It preserves
state-0 entry motion and history, early collision sweeps, state-1 focus/power
drain and movement, state-4 contact/revive and its fallthrough to death, state-2
seven-item fan and game-over/respawn, and state-3 clearing. The common tail
updates all 32 indicators, invulnerability blink and animation, all four
rectangle sets, both embedded timers, the clamped hold counter, sequence
reset/update and the full effect owner before returning 1 with RET4.

The common 0x4478-byte player now embeds its actual 0x3ac-byte Entity at 0x14,
fixed-point position at 0x3cc/0x3d0, primary bounds/half-size from 0x404, full
size at 0x428, outer half-size at 0x434, previous position at 0x440 and direction
at 0x454. The familiar active word is at record+0x90. The 0x6c-byte indicator
describes its actual Motion at 0x18 and angular step at 0x0c. Compile-time
checks cover the new offsets alongside the existing complete shared layout.

The full 28-function graph contains no synthetic compiler caller. The first
implementation allowed two source conveniences to be outlined (bullet
retirement and power-display updates), causing unbound-symbol measurement
failure. Their actual loops/calls were spelled out at the real owner sites.
The retained native link has only the 28 declared complete function bodies;
there are no extra fabricated helper contributions.

The initial complete source swapped the early-revive timer targets: it set
invulnerability to 60 and the state timer to 200. Full tests found 15 failures
in that branch. Retail's calls at 0x425c28 and 0x425c38 establish state timer
60, then invulnerability 200. The corrected source passes all 947 owner cases.
The failed historical run is not passing evidence.

## Genuine private ABI and raw proof

Twenty-six bodies from the prior 27-function scheduled graph are unchanged
under diagnostic rebinding. The complete sequence updater changes from its
public-root ECX entry to retail's EAX entry naturally through the real outer
owner. All 174 diagnostic bytes now agree. The graph has 24 complete
diagnostic-exact functions, totaling 2,731 bytes.

An isolated staging project uses the unchanged normal
`matching2.tools.matching.probe` and native fixed-address cluster gate. It
selects only the complete 174-byte sequence updater for the experiment, places
the complete real player-state owner as unselected compiler context, and
retains the other 26 complete genuine functions as anchors. The updater is
raw-exact at 0x004281d0, including its private receiver and every relative call.
Its raw SHA-256 is
`d01d87b0ca6e43943e25ff6ba7107d5857b6ec7478a4093ad0a2efabe65d611c`.
Instruction and address operand changes, masked bytes and reference bytes used
for building are all zero. The probe uses no constant aliases.

Independent comparison of every complete fixed body finds 21 raw-exact bodies
out of 28. The remaining seven are explicitly recorded in
`evidence/fixed_sequence/probe/complete_raw_bodies.json`; they are not accepted
as raw exact or selected by the isolated probe.

Sequence Update was already production C++ in the frame_timer cluster. That
cluster still uses a synthetic context for several routines. The new proof
establishes a genuine context for this body but has not migrated production
ownership. Current production remains 59 actual assembly regions / 89,043
bytes and eight equivalent C++ owners; the existing exact EXE remains retail
identical. There is no new recovery credit.

## Bounded execution and compiler observation

The corrected graph passes 3,953 cases: pickup 1,965, effect 215, shared
sequences 328, spawn 186, sequence 312 and player owner 947. Full-owner cases
compare complete player, collision engine, bullet/front state, animation
manager/objects and relevant globals, external call values/order, returns,
register preservation, RET4 cleanup, x87 balance and control word. They cover
all state/frame thresholds, focus/power, death/respawn modes, indicator slots
and motion modes, precision/speed combinations, blink, configuration/hold
counter, history levels and repeated updates.

The full-owner fixture scripts collision and record activation, bullet
evaluation/reset/virtual retirement, movement, contact, familiar refresh,
initialization, power display, angle return, item creation, gauge, scene/input
mode and animation VM. The x87 angle result comes from a separate scripted
boundary implementation, leaving both instruction bodies intact. Private
external conventions are normalized explicitly by the fixture: for example,
retail movement takes EDI while the current external public member declaration
takes ECX. These tests do not establish those private ABIs or execute their
full implementations. The complete genuine timer/motion/indicator/sequence/
effect graph does execute with its natural native conventions.

The read-only player-owner register-allocation trace has 109 events. Generic
verification compares all 28 complete native bodies and all 9,216 emitted
code bytes. Code-section SHA-256:
`c188eeb3c3fa4985ab83790a415c14a196ce98eedfd1dbfb282d8c16638abd91`.
Hardware breakpoints only; compiler program/data writes and forced choices
are zero. This observation is not a raw-retail equality claim for the owner.

The next byte-matching work is to replace the owner's external public
declarations with complete genuine collaborators, beginning with collision
activation/check, movement, contact and familiar refresh, so their retail
private conventions follow from real bodies. The raw-exact sequence proof can
then support migration away from its synthetic production context. The entire
3,112-byte owner and any new assembly replacement still require the full raw
gate and both maintained build modes.
