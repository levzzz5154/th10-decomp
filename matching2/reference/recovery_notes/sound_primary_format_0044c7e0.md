# DirectSound primary-format setup

2026-09-26. The 260-byte routine at `0x0044C7E0`, historically named
`Input_SetJoystickPropertyRetail`, is a **DirectSound primary-buffer format
setter**. Its saved instructions and sound-initializer caller establish this
role. `semantic_candidates/sound_primary_format.cpp` now passes **436 retail
comparisons, including 51 matching faults**.

## Interface and behavior

Retail receives bits per sample in CX, channels in BX, sample rate in EDI,
and a device-owner cell on the stack, returning with RET 4. The candidate
exposes ordinary stdcall arguments `(bits, channels, rate, owner)` and RET 16
for behavioral validation. Both count fields use their low sixteen bits.

The owner cell is dereferenced without a null-cell check. A null device inside
a valid cell returns `0x800401F0` immediately. Otherwise, CreateSoundBuffer
receives a zeroed 36-byte description with size 36, flags 1, zero byte count,
null format and zero algorithm GUID. Its output pointer initially contains
null. A negative Create result returns unchanged, without releasing any buffer
the call placed in that pointer.

On success the routine constructs an 18-byte PCM format. Block alignment is
`uint16((bits >> 3) * channels)`. Average bytes per second is that truncated
alignment multiplied by the full sample rate, modulo 32 bits. The sample rate,
original low-sixteen-bit channel/bit counts, tag 1 and extra-size zero are copied
into their respective fields. There is no validation of conventional audio
parameter ranges.

SetFormat receives the created primary buffer and that format. A negative
result returns unchanged **without releasing the buffer**. After a nonnegative
result, the output pointer is reloaded; if nonnull, Release is called on that
current pointer. The function then returns zero, ignoring Release's value.
Tests use the output-cell address retained from CreateSoundBuffer to replace
or clear it during SetFormat and verify the later release target.

## Validation and integration

```sh
python3 matching2/tests/sound_primary_format_differential.py
python3 matching2/tests/sound_device_init_differential.py
```

The first test runs fresh native-Clang x86 Windows C++ against the verified
retail body under Unicorn. Cases cover null owner/device/output, HRESULT signs,
full and truncated input-register values, zero and overflowing format products,
escaped-output changes and seeded random parameters. They compare all format
and description bytes, COM calls, results, faults, object state, normal stack
cleanup and preserved registers. Independent arithmetic assertions verify each
format field; ownership assertions distinguish Create failure, SetFormat
failure and successful release. Fifty fault cases vary other inputs with a
null owner, and one covers a null successful Create output.

The second test executes this candidate with the recovered initializer, WAVE
loader and maintained chunk walker. It confirms startup continues after both
primary Create and SetFormat failures, matching the caller's ignored result.
See [sound initialization](sound_device_init_0043cd30.md) for integrated scope.

The Clang module is 234 bytes. Production remains assembly pending recovery of
the private register convention, native MSVC stack-cookie/frame matching and
the whole-executable byte gate. No real audio device or exception dispatch is
exercised. The old joystick-related blocker commentary is historical and is
not evidence for this function's actual role or receiver.
