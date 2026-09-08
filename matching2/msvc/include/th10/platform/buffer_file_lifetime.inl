// Shared definitions: ResourceFile's destructor inlines this cleanup, whereas
// BufferFile's deleting-destructor entry calls its out-of-line destructor.
// The owning translation unit supplies the latter's noinline attribute.
#ifndef TH10_BUFFER_DESTRUCTOR_ATTRIBUTES
#define TH10_BUFFER_DESTRUCTOR_ATTRIBUTES
#endif

extern "C" void __cdecl entry_free_00452422(void*);

TH10_BUFFER_DESTRUCTOR_ATTRIBUTES inline BufferFile::~BufferFile() {
    Close();
}

inline void BufferFile::Close() {
    if (data_) {
        entry_free_00452422(data_);
        data_ = 0;
    }
    data_ = 0;
    size_ = 0;
    position_ = 0;
}

#undef TH10_BUFFER_DESTRUCTOR_ATTRIBUTES
