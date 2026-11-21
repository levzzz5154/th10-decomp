struct Stream { char* ptr; int count; char* base; int flags; };
extern "C" void __cdecl crt_free(void*);

extern "C" void __cdecl crt_freebuf(Stream* stream) {
    if ((stream->flags & 0x83) && (stream->flags & 8)) {
        crt_free(stream->base);
        *reinterpret_cast<unsigned short*>(&stream->flags) &= 0xfbf7;
        stream->ptr = 0;
        stream->base = 0;
        stream->count = 0;
    }
}
