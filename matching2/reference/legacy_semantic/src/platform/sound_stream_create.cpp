#include "th10/platform/sound_stream_create.hpp"

#include <new>

namespace {

const unsigned int kClassNotInitialized = 0x800401F0u;
const unsigned int kFailure = 0x80004005u;
const unsigned int kOutOfMemory = 0x8007000Eu;
const unsigned int kStreamingBufferFlags = 0x18188u;
const unsigned int kFileHeaderBytes = 0x20;

}  // namespace

// 0x0044C8F0 - Create a segmented streaming buffer, register one notification
// at the end of each segment, and publish the initialized stream record.
unsigned int SoundStream_CreateSegmented(const StreamBufferDesc* description,
                                         StreamRecord** output,
                                         const StreamCreateEnv* env) {
    *output = 0;
    if (env->device == 0) {
        return kClassNotInitialized;
    }

    if (env->open(description->file_size + kFileHeaderBytes)) {
        return kFailure;
    }

    void* buffer = env->create_buffer(
        description->flags | kStreamingBufferFlags,
        description->segment_count * description->segment_size,
        description->format);
    if (buffer == 0) {
        return kFailure;
    }

    void* notify = env->query_notify(buffer);
    if (notify == 0) {
        return kFailure;
    }

    StreamNotice* notices =
        new (std::nothrow) StreamNotice[description->segment_count];
    if (notices == 0) {
        env->release(notify);
        return kOutOfMemory;
    }

    for (unsigned int index = 0;
         index < description->segment_count; ++index) {
        notices[index].position =
            description->segment_size - 1 +
            index * description->segment_size;
        notices[index].event = description->event;
    }

    const int notice_result = env->set_notices(
        notify, notices, description->segment_count);
    env->release(notify);
    delete[] notices;
    if (notice_result) {
        return kFailure;
    }

    StreamRecord* stream = env->allocate_stream();
    if (stream == 0) {
        return kFailure;
    }

    stream->desc = *description;
    stream->buffer = buffer;
    stream->owner = env->owner;
    stream->event = description->event;
    stream->cursor = 0;
    *output = stream;
    return 0;
}
