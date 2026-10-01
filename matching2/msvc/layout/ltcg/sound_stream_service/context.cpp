#include "../../../src/platform/sound_stream_service.cpp"
#include "fill.cpp"
#include "restore.cpp"
#include "rewind.cpp"
#include "read.cpp"

#pragma code_seg(".text$11context")
extern "C" __declspec(noinline) int __stdcall StreamServiceContext(SoundStreamState** streams, unsigned int* repeats, int count) {
    int result = 0;
    while (count--) result |= SoundStream_Service_0044d850(*streams++, *repeats++);
    return result;
}
#pragma code_seg()
