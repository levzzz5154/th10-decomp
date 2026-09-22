struct Stream { char* ptr; int count; char* base; int flags; };
extern "C" void __cdecl asm_free_00452422(void*);

extern "C" void __cdecl asm_freebuf_00462225(Stream* stream) {
    if ((stream->flags & 0x83) && (stream->flags & 8)) {
        asm_free_00452422(stream->base);
        *reinterpret_cast<unsigned short*>(&stream->flags) &= 0xfbf7;
        stream->ptr = 0;
        stream->base = 0;
        stream->count = 0;
    }
}
