// 0x0044CF00..0x0044D710: SoundBufferBase_DeletingDestructor, SoundBufferBase_Release, SoundBuffer_DeletingDestructor
#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
#include "th10/source_views/recovery_leaves_f39a06_3.hpp"
#include "th10/source_views/recovery_leaves_f39a06_4.hpp"
#include "th10/source_views/recovery_leaves_f39a06_5.hpp"
#include "th10/source_views/recovery_leaves_f39a06_6.hpp"
void* __fastcall SoundBufferBase_DeletingDestructor(SoundBufferBase* owner,
                                                       unsigned int unused, unsigned int flags) {
    SoundBufferBase_Release(owner);
    if (flags & 1)
        operator delete(owner);
    return owner;
}


#include "../../../include/th10/source_views/recovery_leaves_f39a06_7.hpp"
#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
#include "th10/source_views/recovery_leaves_f39a06_3.hpp"
#include "th10/source_views/recovery_leaves_f39a06_4.hpp"
#include "th10/source_views/recovery_leaves_f39a06_5.hpp"
#include "th10/source_views/recovery_leaves_f39a06_6.hpp"
#include "th10/source_views/recovery_leaves_f39a06_7.hpp"
void __fastcall SoundBufferBase_Release(SoundBufferBase* owner) {
    SoundBufferBaseFields* fields = (SoundBufferBaseFields*)owner;
    fields->vtable = (void*)0x004705D8;
    for (unsigned int index = 0; index < fields->element_count; ++index) {
        if (fields->elements[index]) {
            fields->elements[index]->Release();
            fields->elements[index] = 0;
        }
    }
    if (fields->elements) {
        operator delete(fields->elements);
        fields->elements = 0;
    }
    MusicReadCursor* device = fields->device;
    if (device) {
        if (device->state == 1) {
            CloseHandle(device->handle);
            device->handle = (HANDLE)-1;
        }
        operator delete(device);
        fields->device = 0;
    }
}


#include "../../../include/th10/source_views/recovery_leaves_f39a06_8.hpp"
#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
#include "th10/source_views/recovery_leaves_f39a06_3.hpp"
#include "th10/source_views/recovery_leaves_f39a06_4.hpp"
#include "th10/source_views/recovery_leaves_f39a06_5.hpp"
#include "th10/source_views/recovery_leaves_f39a06_6.hpp"
#include "th10/source_views/recovery_leaves_f39a06_7.hpp"
#include "th10/source_views/recovery_leaves_f39a06_8.hpp"
void* __fastcall SoundBuffer_DeletingDestructor(SoundBuffer* sound_buffer, unsigned int unused,
                                                unsigned int flags) {
    SoundBuffer_DestructBase(sound_buffer);
    if (flags & 1)
        operator delete(sound_buffer);
    return sound_buffer;
}

