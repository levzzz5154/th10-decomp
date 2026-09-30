#pragma once

extern "C" void __cdecl SoundBuffer_Free(void* pointer);

namespace {
// Both stream factories have one unwind obligation: release the raw outer
// stream allocation, including NULL, until publication is complete.
class PendingSoundStream {
public:
    explicit PendingSoundStream(void* allocation) : allocation_(allocation), pending_(true) {}
    ~PendingSoundStream() { if (pending_) SoundBuffer_Free(allocation_); }
    void Publish() { pending_ = false; }
private:
    PendingSoundStream(const PendingSoundStream&);
    PendingSoundStream& operator=(const PendingSoundStream&);
    void* allocation_;
    bool pending_;
};
}
