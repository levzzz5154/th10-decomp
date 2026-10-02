# 0x00442300 alpha fade start (130 bytes) - parked

Semantics are settled: with the animation in EAX and the duration in ECX it
fills the integer interpolation at +0x108 (duration +0x12C, mode +0x130,
initial +0x108, two zeroed controls, final +0x10C) and restarts its timer at
+0x118. Mode, initial and final are read as bytes from three stack slots;
`RET 0xC`. Both callers are in the animation interpreter.

Closest model (8 diff lines): a member `StartAlphaFade(int duration, int mode,
int from, int to)` storing `static_cast<unsigned char>` of each, in a dedicated
cluster with a synthetic caller. The convention matches; the one difference is
that the mode byte is loaded into EDX ahead of the duration store, where
retail stores the duration first and then reuses ECX for every byte.

Tried without getting closer: `unsigned char`/`bool` mode (promoted to DL in
every member, fastcall, stdcall and cdecl form), a one-byte struct by value,
`mode & 0xFF` (swaps which argument gets ECX), every statement order, a
pointer to the interpolation, locals, an inline `Start` helper, and different
call-site arguments.
