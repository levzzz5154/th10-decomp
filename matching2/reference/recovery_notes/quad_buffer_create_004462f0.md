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
