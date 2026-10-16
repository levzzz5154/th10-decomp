// 0x004356D0..0x004356E3: the file name part of the path, i.e. everything
// after the last forward slash.
extern "C" char* __cdecl strrchr2(const char* text, int character);

struct Path2 {
    __declspec(noinline) const char* BaseName() const;
};

#pragma code_seg(".text$01accessor")
const char* Path2::BaseName() const {
    const char* separator = strrchr2((const char*)this, '/');
    if (separator != 0) {
        return separator + 1;
    }
    return (const char*)this;
}
#pragma code_seg()
