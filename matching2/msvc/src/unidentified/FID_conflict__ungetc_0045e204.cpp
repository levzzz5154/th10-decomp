// The FILE prefix accessed by the retail ungetc implementation. The remainder
// of the CRT stream object is intentionally opaque here.
struct UngetcStream_0045e204 {
    char* ptr;              // +0x00
    int count;              // +0x04
    char* base;             // +0x08
    int flags;              // +0x0C
};

extern "C" void __cdecl asm_getbuf_00459f39(UngetcStream_0045e204* stream);

// 0x0045E204..0x0045E26F: CRT ungetc worker. Ghidra identifies this body as
// a conflict between __ungetc_lk and _ungetc library matches.
extern "C" int __cdecl asm_FID_conflict__ungetc_0045e204(
    int ch, UngetcStream_0045e204* stream) {
    if (ch == -1)
        return -1;

    const unsigned int entry_flags = static_cast<unsigned int>(stream->flags);
    if ((entry_flags & 1u) == 0u &&
        ((entry_flags & 0x80u) == 0u || (entry_flags & 2u) != 0u)) {
        return -1;
    }

    if (stream->base == 0)
        asm_getbuf_00459f39(stream);

    if (stream->ptr == stream->base) {
        if (stream->count != 0)
            return -1;
        ++stream->ptr;
    }

    --stream->ptr;
    if ((static_cast<unsigned int>(stream->flags) & 0x40u) != 0u) {
        if (*stream->ptr != static_cast<char>(ch)) {
            ++stream->ptr;
            return -1;
        }
    } else {
        *stream->ptr = static_cast<char>(ch);
    }

    ++stream->count;
    stream->flags = (stream->flags & ~0x10) | 1;
    return ch & 0xff;
}
