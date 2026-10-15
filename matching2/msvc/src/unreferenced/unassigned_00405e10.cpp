// 0x00405E10: clear bit 0 of the +0x10 flags word and return the object.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is an
// ordinary translation unit; the returned object is what the caller keeps.
struct ObjectClearer_00405e10 {
    unsigned char pad_000[0x10];
    unsigned int flags;                       // +0x10
    __declspec(noinline) ObjectClearer_00405e10* Clear();
};

ObjectClearer_00405e10* ObjectClearer_00405e10::Clear() {
    flags &= ~1u;
    return this;
}
