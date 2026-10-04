# Music launchers 0x0043D690 and 0x0043D950: recovered (2026-10-04)

Both are exact ordinary C++; `make -j2` and `make EXACT=1 -j2` pass.

| address | bytes | source | cluster |
|---|---|---|---|
| 0x0043D690 `WaveSoundManager::LaunchMusic` | 241 | `msvc/src/platform/sound_music_launch.cpp` | `title_assets_0041f990` |
| 0x0043D950 `WaveSoundManager::PlayCachedMusic` | 298 | `msvc/src/platform/sound_music_play_cached.cpp` | `sound_music_play_cached_0043d950` |

## The finding

The two stream factories (0x0044C8F0 file, 0x0044CBF0 memory) are not free
`__fastcall` functions. They are members of the object that owns the
DirectSound device, with the DirectX sample's `CreateStreaming` parameter
order (output slot, source, creation flags, 3D algorithm GUID, notify count,
notify size, notify event, plus the track record):

    owner->CreateFileStream(&stream, flags, name, guid, 16, bytes, event, record)
    owner->CreateMemoryStream(&stream, pcm, pcm_bytes, record, flags, guid, 16, bytes, event)

The whole-program pass passes the output slot in ECX, the flags in EDX and the
owner on the stack. Argument evaluation follows the declared order, so the
address of the output slot is computed before the owner is pushed. With an
`extern __fastcall (output, flags, owner, ...)` declaration the registers are
right but that order is not, which left 0x0043D690 with its ECX/EDX swap and
0x0043D950 with `lea ecx` on the wrong side of the last push.

## Cluster shape

- The factories have exception frames, so their real models cannot be compiled
  in a caller's cluster. Each cluster carries an EH-free stand-in at the retail
  address (`title_assets_dependencies/create_file.cpp`,
  `sound_music_play_cached_dependencies/create_memory.cpp`), never selected.
- The stand-in's own callees must be real bodies. With `MusicReadCursor::Open`
  (0x0044DBF0) as an extern the pass put `segment_count` in ECX; with the real
  body it picks the output slot and the flags, as retail does.
- 0x0043D950 tail-calls the real track selector 0x0043D790 (and its callee
  0x0044DCA0), included through one-line wrapper translation units because
  maintained sources of other clusters cannot be `additional_sources`.
- New `Supervisor` members: `music_mode` (+0x163), `flags` (+0x178).

## Follow-up

The factory models themselves (692 of 702 and 636 of 651 bytes as fastcall free
functions) have not been retried as members of the device owner.

### Factory retry as a member (same day, not promoted)

Changing the 0x0044C8F0 model from `__fastcall (output, flags, owner, ...)` to
`SoundDeviceOwner::CreateFileStream(output, flags, name, ...)` in a scratch copy
gives retail's size exactly (702 bytes, was 692) but the pass then passes
`flags` in ECX and `name` in EDX with the output slot on the stack; retail has
the output slot in ECX and the flags in EDX, keeps `this` in a stack local and
has one more local (frame 0x50 against 0x4C). 217 differing listing lines.

Why: c2's `MdmFlexParams` picks register parameters by walking the callee's
entry-block instructions and taking the parameters loaded into registers there
(see memory `msvc-c2-flex-params-entry-scan`). Retail's entry block reads the
output slot and the flags first. A `__forceinline` inner member wrapped by the
factory is not inlined (the body has an unwind state), so that shape is out.
Next step for whoever continues: trace the entry-block tuple order of the
member model at `MdmFlexParams` and find the source order that reads `output`
before `name` (for instance an early argument check), then recheck the frame.
The production cluster still uses the fastcall model; nothing was changed there.
