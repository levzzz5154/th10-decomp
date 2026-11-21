struct Stream {
    char* ptr;
    int count;
    char* base;
    int flags;
    unsigned int file;
    char charbuf[4];
    int buffer_size;
};
extern "C" unsigned int g_crt_stdio_bufsize;
extern "C" void* __cdecl crt_malloc(unsigned int);

extern "C" void __cdecl crt_getbuf(Stream* stream) {
    ++g_crt_stdio_bufsize;
    stream->base = static_cast<char*>(crt_malloc(0x1000));
    if (stream->base) {
        stream->flags |= 8;
        stream->buffer_size = 0x1000;
    } else {
        stream->flags |= 4;
        stream->base = stream->charbuf;
        stream->buffer_size = 2;
    }
    stream->count = 0;
    stream->ptr = stream->base;
}
