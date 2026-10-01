#include "th10/platform/memory_file.hpp"
#pragma code_seg(".text$13buffer")
__declspec(noinline) BYTE BufferFile::Open(const char* path, const char*) {
    const ResourcePath* resource = (const ResourcePath*)path;
    data_ = ResourceLoadRetail(path, 0);
    size_ = resource->GetFileSize();
    position_ = data_;
    return data_ != 0;
}
#pragma code_seg()
