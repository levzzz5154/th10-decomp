# 0x0040C3C0 stage animation reload (with 0x0040C3A0 and 0x0040B4F0)

Three regions recovered in cluster `stage_anm_reload_0040c3c0`:

- 0x0040C3C0 `Stage_0040c3c0::ReloadAnm` (126 bytes, stage in EBX): builds the
  file name in the scratch path with an inlined `strcat`, loads it into the
  stage's slot through 0x00447280, clears the reload flag and stops the
  loading sprite (the inlined body of 0x0040C440).
- 0x0040C3A0 (18 bytes): the worker thread entry, `__cdecl` with no argument,
  rooted so it keeps that frame.
- 0x0040B4F0 (11 bytes): a caller-less owner wrapper, owner in EAX; kept by a
  context compiled under `#pragma inline_depth(0)`.

The only source-level adjustment was reading `anm_name` into a local before
clearing the path's first byte, which is the order retail schedules them.
The handle stop at 0x00409E50 is the usual ABI anchor model.
