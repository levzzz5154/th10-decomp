# Sound stream factories 0x0044C8F0 and 0x0044CBF0 (2026-10-05)

Both factories are byte-exact from natural source:
`src/platform/sound_stream_create_file_0044c8f0.cpp` (702 bytes) and
`src/platform/sound_stream_create_memory_0044cbf0.cpp` (651 bytes), with their
generated cleanup funclets and EH handlers.

## What was wrong

The earlier models were `__declspec(dllexport) int __fastcall` free functions
that took the device owner as an ordinary argument, so that the observed
register convention (output slot in ECX, flags in EDX) was forced by the
declaration. That produced 692 instead of 702 bytes and a different register
assignment: retail loads the segment count at entry into EBP, keeps the zero
in ECX and reloads the notification event inside the position loop.

The factories are members of the device owner (`SoundDeviceOwner`, the
DirectX sample's `CSoundManager::CreateStreaming`). As plain non-exported
members with a direct caller in the cluster, the pass chooses the private
convention itself from the entry block, and the same body then compiles to the
retail bytes. No statement of the body had to change apart from

- an `int hr` that receives each COM result before the `< 0` test (this is
  what keeps the zero register across the SetNotificationPositions failure
  path: `xor ebp,ebp; cmp eax,ebp`);
- `device` / `&device` instead of `*owner` / `owner`.

The memory factory differs from the file one only by the inlined
`OpenMemory(pcm, pcm_bytes, record)` (the sample's `OpenFromMemory`), which is
not guarded by the allocation check.

## Cluster layout

- `sound_stream_create_file_0044c8f0`: factory now selected (anchor before);
  direct caller is the unselected launcher copy
  `src/platform/sound_music_launch_0043d690.cpp`.
- `sound_stream_create_memory_0044cbf0` (new): factory, its unwind funclet
  0x00465310 and handler 0x0046531B, and the stream constructor 0x0044D6A0 as
  an additional source. The old `sound_interfaces` cluster, whose context was
  the forced-fastcall factory, is gone.

## Tooling note

The scratch variant runner counted diff lines from a 4000-character
truncated diff, so every variant of a large function reported the same count.
Count from the full `diff ref.s cur.s` instead.
