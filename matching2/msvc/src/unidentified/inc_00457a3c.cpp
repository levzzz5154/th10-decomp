struct InputStream { unsigned char* ptr; int count; };
extern "C" int __cdecl asm_filbuf_0045e123(InputStream*);

extern "C" int __fastcall asm_inc_00457a3c(int, InputStream* stream) {
    if (--stream->count >= 0) return static_cast<unsigned char>(*stream->ptr++);
    return asm_filbuf_0045e123(stream);
}
