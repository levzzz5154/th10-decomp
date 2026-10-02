# Quad vertex buffer setup 0x004462F0

2026-10-02. The body was already modelled as an anchor of
`layout/ltcg/native_font_start_closure.json`, 70 bytes off. It is now a
selected function of that cluster (`src/render/quad_buffer_create_004462f0.cpp`)
and the whole EXE is exact.

The model listed the sixteen vertex stores one by one in retail's emission
order, which the compiler regroups by constant. Written as the chained
assignments the pairs suggest (`v[0].x = v[2].x = -128.0f`, ... and one
four-way chain for z), x and y first, then z, then u and v, the compiler
produces retail's grouping and order directly.

Worth repeating elsewhere: an anchor model written to mirror the disassembly
can sit a few bytes from exact for a reason the source's natural shape removes.

## Other near-exact anchor models (same day)

A scan of every cluster anchor that sits on a still-assembly region, compared
with retail: 0x004076A0 (8 bytes), 0x004078E0 (21), 0x0043E8B0 (22),
0x00436AF0 (33); everything else is 30% or more off.

0x004076A0 was tried and left as an anchor. Its model needs
`_ReadWriteBarrier()` to stop the compiler forwarding the normalised angle to
the `SetPolar` argument (retail re-reads the member); without it the frame
grows by 8 bytes. A double-returning helper, reference/pointer/accessor
helpers and a local copy do not block the forwarding. With the barrier the
only difference is `mov eax,[esi+0x3e4]` and `fmul [esi+0x690]` swapped.

0x00436AF0 (font surface create) was promoted the same way. Its model was 33
bytes off, all in the final nine member stores. Holding the `SelectObject`
result in a local and searching the store order by single moves found the one
exact order: pixels, previous_bitmap, stride, image_size, dc, bitmap, width,
height, font_index. With the call written directly into the first store the
search stalls 15 diff lines away.
