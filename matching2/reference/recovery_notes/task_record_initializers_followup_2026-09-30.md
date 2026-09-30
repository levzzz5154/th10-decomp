# Record initializer scheduling follow-up, 0x00449A50 / 0x00449A70

Both 32-byte records remain assembly. Tested readable Reset and Initialize(void* value) methods in an isolated native-LTCG cluster. Synthetic array caller successfully reproduces EAX receiver, ECX initializer input, and EDX flags temporary without needing unrelated unwind callers. The compiler-only context is 50 bytes; neither it nor its chosen address is recovered code.

Retail loads flags at +4, clears fields at +8/+12/+16/+0, then ANDs flags with ~1, writes +4, stores self at +20 and clears +24/+28. Initialize uses the incoming value instead of zero at +8. The ordinary candidates are both exactly 32 bytes but hoist the AND ahead of the stores. First differences: Reset 0x00449A55; Initialize 0x00449A78.

Measured 16 volatile-access masks over initial flags read, state write, three pointer writes and flags write. No exact candidate. Closest ordering variant (mask 6) retains retail entry registers and delays the AND past two stores, but still computes it before the +16/+0 writes (first differences 0x00449A5B /0x00449A7B). Volatile flags reads change register allocation rather than solve this. Checked eight additional pragma optimize controls (g/y/a/t off) on plain and mask-6 forms: none passes; g/t forms fail contribution validation, a/y forms retain the mismatch. Do not credit a matching byte extent as recovery.

Scratch structured receipts: /home/levzzz/.hermes/cache/scratch/task_record_variant_results.json. These temporary files will expire; the ordering result is preserved here. Production sources, manifest and executable were not changed by this experiment. Verified production baseline remains 1835 C++ regions /95146 bytes and 469 assembly regions /227904 bytes, whole executable exact 487936 bytes from the preceding build.

Next useful lever: genuinely different compiler/context instruction scheduling, not repeating volatile mask sweeps. No need for user input; this is a target-specific code-generation blocker, not overall campaign exhaustion.
