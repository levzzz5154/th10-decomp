struct Stream {
    char* ptr;
    int count;
    char* base;
    int flags;
    unsigned int file;
    char charbuf[4];
    int buffer_size;
};
extern "C" unsigned int data_00477614;
extern "C" void* __cdecl asm_malloc_00452706(unsigned int);

extern "C" void __cdecl asm_getbuf_00459f39(Stream* stream) {
    ++data_00477614;
    stream->base = static_cast<char*>(asm_malloc_00452706(0x1000));
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
