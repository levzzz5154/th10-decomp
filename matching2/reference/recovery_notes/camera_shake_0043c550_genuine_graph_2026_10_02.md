# Camera shake 0x0043C550: genuine graph, one scheduling residual

The complete 439-byte callback remains assembly. No maintained source, layout,
header, tool or manifest was changed. This bounded pass reaches a complete
ordinary C++ model with **439 bytes / 27 differences**, all confined to one
instruction-order window. It is not exact and must not be promoted.

The isolated project and evidence are under
`matching2/build/experiments/camera_shake_0043c550_2026_10_02/`.
`final_evidence.json`, `final_frozen_proof/report.json` and
`final_frozen_proof/measurement.json` record a fresh production-path build of
unchanged final candidate inputs. `freeze.py` verifies the precise residual,
whole contribution and unchanged dependency hashes.

## Genuine topology and data model

Fresh live Ghidra disassembly covers all 439 bytes and confirms the only xref:
selector case 1 loads callback address 0x0043C550 at 0x0043C9AE. The callback
receives the controller in ECX, returns a scheduler result in EAX, and uses
plain RET. The frozen candidate is an ordinary one-pointer fastcall entry;
for this callback its physical ABI equals the original thiscall boundary.
It uses the complete maintained `ScreenEffectController_0043c970` declaration,
including its actual embedded FrameTimer, rather than an incomplete owner view.

The native graph retains the callback through that complete genuine selector,
the real screen-effect factory and complete scheduler creation/registration
bodies. The old synthetic repeated-allocation context was omitted. The factory
itself supplies the public stdcall linker entry. Its complete contribution is
83 bytes in this graph, versus its separately maintained 77-byte private-entry
recovery. This nonexact unselected helper is not shortened or credited.

The RNG occupies eight physical bytes at 0x004918B0: low seed word, reserved
high word and generation counter at +4. Retail reads the 32-bit seed storage
and writes only its low 16 bits. A local union exposes those two views without
pointer type-punning; the seed recurrence uses unsigned arithmetic and preserves
the high word. Returning the computed low-word local, rather than rereading the
stored seed field after incrementing generation, removes the extra seed reload,
restores the original register allocation and both ECX=3 modulus loads. This is
a target-specific fixed-Windows/MSVC storage model; the shared RNG header is
unchanged. Each axis advances twice and duplicates the **second** generated word
into both halves of its packed value, exactly as the retail instructions prove.
Replacing this with the general API that packs two different words would be
semantically wrong.

## Exact remaining difference

Every instruction, register, address and byte outside 0x0043C606..0x0043C621
matches. The candidate emits the four-byte `FIDIV [ESP+8]` at 0x0043C606, before
the second seed's XOR/SUB/rotate instructions. Retail emits those same integer
instructions first, then the identical FIDIV at 0x0043C61E. The complete size,
branch addresses and following code remain identical. `freeze.py` proves that
moving this four-byte instruction is the sole residual; no such move was made
to the built output. The 27-byte difference count reflects this scheduling
window, not recovered byte coverage.

The fresh complete candidate body SHA-256 is
`95a21fde5b1af5b395b1e782fa43ec6d82214ca11a513a7d4ae4a5791e07ea18`.
The full retail body SHA-256 is
`ce3e4112ea53c56eb4532e630abe5ee26682aed39d2c09f018a7cb0a7a47240d`.

## Bounded controls and unselected contributions

The preserved native matrix contains the genuine baseline, per-axis destination
and RNG reference helper, per-axis returned value, two seed-storage return
models, four amplitude representations, complete real controller and inline
timer models, direct shared-struct local-return word helpers, and interleaved
amplitude/RNG stages. Complete valid 439-byte union/local-return models retain
27 differences; wider amplitude forms retain 31 or 38. The return-value axis
model emits 433 bytes. Direct typed-short seed local-return controls emit
415/430 bytes, and the double staged model emits 455. These failed extents and
any resulting layout-origin errors are retained as diagnostics, without selecting
padding or normalizing an oversized body into the requested 439 bytes.

In the final graph, the complete unselected selector (396), two registrations
(131 each) and two creators (43 each) match retail independently. The 83-byte
public factory differs from the separately maintained 77-byte retail reference.
Their complete sizes, hashes and comparisons are recorded in `final_evidence.json`.
They are context only, with zero recovery credit. The selected callback and new
graph contain no inline assembly, added barriers, volatile objects, fabricated
arguments or register-pressure callers. Production reports record zero changed
instruction bytes, zero masked bytes and no reference bytes used for building.
The oracle is opened only after native compilation and linkage.

Further work needs a new evidence-grounded reason for the FIDIV scheduling.
Repeating the measured helper, type, amplitude-stage or genuine-graph variants
is not justified. The effect-ring pair was excluded earlier in this pass because
both depend on the still-unexpressed FSINCOS leaf at 0x004458B0; their previous
receipts remain authoritative.

## Revisit of the proposed per-axis boundary

A later request specifically revisited the inline RNG/choice/destination helper.
Inspection confirms that exact boundary was already measured in
`axis_refs_with_local_rng_return_source.cpp`: `SetShakeComponent(float&,
ShakeRngStorage&, float)` encloses both advances, packing, modulo, choice and
destination assignment, and is called once per axis. Its entire 439-byte native
body is byte-for-byte identical to the frozen best model above. The generation
counter remains in ESI and the amplitude remains live on x87 through both
switches. Thus this boundary preserves the same sole FIDIV residual.

`axis_helper_duplicate_audit/audit.json` records the original native PE/MAP
hashes, original native input hashes, source-copy hash equality and a reconstructed
original layout whose hash equals the recorded compiler input. All other original
inputs remain hash-identical. The script `audit_axis_helper.py` independently
checks the complete MAP contribution, body identity, native selector callback
pointer and relevant ESI/x87 instructions. The prior shared-RNG destination
boundary gives 439/197; the return-value boundary gives 433 and fails the complete
extent. This duplicate lane is exhausted by concrete existing evidence. No new
compiler probe or maintained implementation change was made during the revisit.
