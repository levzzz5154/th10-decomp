#include "th10/platform/memory_file.hpp"

// The retail resource routines use the path pointer itself in ECX. This ABI
// view gives those operations C++ types without dereferencing it as an object.
class ResourcePath {
public:
    BYTE* Load(int mode);
    DWORD GetFileSize();
};

// 0x00436400: replace this file's buffer with the resource selected by path.
// mode is ignored. Retail does not close the existing buffer before overwrite.
BYTE BufferFile::Open(const char* path, const char*) {
    ResourcePath* resource = (ResourcePath*)path;
    data_ = resource->Load(0);
    size_ = resource->GetFileSize();
    position_ = data_;
    return data_ != 0;
}
