struct InputStream { unsigned char* ptr; int count; };
extern "C" int __cdecl crt_filbuf(InputStream*);

extern "C" int __fastcall crt_libcmt_input_inc(int, InputStream* stream) {
    if (--stream->count >= 0) return static_cast<unsigned char>(*stream->ptr++);
    return crt_filbuf(stream);
}
