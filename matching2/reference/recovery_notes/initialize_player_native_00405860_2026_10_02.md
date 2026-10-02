# Player initialization `0x00405860`: native recovery

2026-10-02. Maintained promotion verified.

The complete 397-byte routine is readable, inline-assembly-free C++ in
`matching2/msvc/src/game/initialize_player_00405860.cpp`. The maintained native
probe reports zero differing bytes, with selected-body SHA-256
`97a3b63c03fa748e56bc93fda09e8c5b5fbab97b5e3819fd198aa0a811005852`.
The public entry takes one actual state pointer on the stack, returns a status
in EAX, and uses RET4. The earlier ABI audit records both actual callers
passing that pointer with `push esi`.

The source rejects an already initialized state, resets its timer with
`Reset(-1)`, sets its dimensions and position, selects and creates the primary
animation, queues panned sound, updates the power digits, clears expired
flags, clamps the global value, and sets the pending animation flag. The
timer argument describes the previous frame; current frame and elapsed time
reset to zero. The final maintained timer name and argument were reprobed
before whole-image verification.

The genuine schema-2 cluster selects InitializePlayer397 and the existing
SetPowerDigits79, connected by the actual call at `0x00405975`. It replaces
the old digits cluster registration and its synthetic context. The digits
source, fixed-address region, owner, and existing recovery credit remain
unchanged; its source SHA-256 is
`14a4ea07427f804490868e13d62916388d7b99b2c861497ccf2680c1c1e299fd`.
Only InitializePlayer397 receives new credit.

Complete ordinary C++ dependencies implement Entity_Init273, Allocate161,
Configure356, LoadScript197, primary registration117, positioned creation116,
flag expiry176, and QueuePan149. Their complete emitted extents are recorded
in `final_receipt.json`; all remain unselected and receive zero new credit.
Entity_Init has one real `Entity*` argument. Native LTCG derives the private
register/stack contracts of the selected calls from this full graph, including
position EDI for creation, ESI/EBX for panned sound, owner ESI for digits, and
EAX for flag expiry. No unused parameter is introduced to force a register.

Flag expiry uses an ordinary pointer loop over the eight actual entity
subobjects, skipping slot two, after the 60-frame threshold. This complete
176-byte helper naturally clobbers EAX and retains retail ESI state in the
caller; it is not a recovery of the retail 81-byte helper. The positioned
creator also implements its full behavior without scheduling stores marked
volatile. No synthetic caller, register barrier, assembly bridge, byte mask,
or instruction/address rewrite is used.

Evidence is retained in
`matching2/build/experiments/player_initialize_real_graph_20261002`:
`maintained_probe.json`, its native cluster report, `final_receipt.json`,
`preserved_digits_probe.json`, `whole-exe.log`, and `whole_verification.json`.
The agent's earlier isolated receipt predates the maintained timer rename;
the maintained probe and whole-image receipt pin the final source hashes.
The incremental whole gate reused 1,605 units and compiled four with zero
failures. Its 487,936-byte EXE matches retail literally, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

At this receipt's verification point, the combined Bounce410 and
InitializePlayer397 gain is 807 bytes. The direct-source audit records 2,104
asm-free selected regions / 137,196 bytes, with assembly remaining in 216
selected regions / 185,935 bytes. Six older mixed semantic bodies account
for 4,525 bytes excluded from asm-free credit. The overall goal remains open.
