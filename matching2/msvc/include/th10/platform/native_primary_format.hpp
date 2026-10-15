#pragma once
#include <stddef.h>

struct WaveSecondaryBuffer;
struct WaveDirectSoundDevice;
struct SoundStream;
struct MusicReadCursor;
struct WaveNotification;

#pragma pack(push, 2)
struct WaveFormatImage {
    unsigned short tag;
    unsigned short channels;
    unsigned int sample_rate;
    unsigned int average_bytes_per_second;
    unsigned short block_alignment;
    unsigned short bits_per_sample;
    unsigned short extra_bytes;
};
#pragma pack(pop)

struct WaveBufferDescription {
    unsigned int size;
    unsigned int flags;
    unsigned int bytes;
    unsigned int reserved;
    const WaveFormatImage* format;
    unsigned char algorithm[16];
};

struct WaveBufferMethods {
    int (__stdcall* query_interface)(WaveSecondaryBuffer*, const void* iid, WaveNotification** output);
    void* add_reference;
    unsigned int (__stdcall* release)(WaveSecondaryBuffer*);
    void* get_caps;
    int (__stdcall* get_position)(WaveSecondaryBuffer*, unsigned int* play, unsigned int* write);
    void* before_status[4];
    int (__stdcall* get_status)(WaveSecondaryBuffer*, unsigned int* status);
    void* initialize;
    int (__stdcall* lock)(WaveSecondaryBuffer*, unsigned int offset,
        unsigned int bytes, unsigned char** first, unsigned int* first_bytes,
        unsigned char** second, unsigned int* second_bytes, unsigned int flags);
    int (__stdcall* play)(WaveSecondaryBuffer*, unsigned int reserved,
        unsigned int priority, unsigned int flags);
    int (__stdcall* set_position)(WaveSecondaryBuffer*, unsigned int position);
    int (__stdcall* set_format)(WaveSecondaryBuffer*, const WaveFormatImage*);
    int (__stdcall* set_volume)(WaveSecondaryBuffer*, int volume);
    int (__stdcall* set_pan)(WaveSecondaryBuffer*, int pan);
    void* set_frequency;
    int (__stdcall* stop)(WaveSecondaryBuffer*);
    int (__stdcall* unlock)(WaveSecondaryBuffer*, unsigned char* first,
        unsigned int first_bytes, unsigned char* second, unsigned int second_bytes);
    int (__stdcall* restore)(WaveSecondaryBuffer*);
};

struct WaveSecondaryBuffer {
    WaveBufferMethods* methods;
    int RestoreIfLost(unsigned int* restored);       // maintained 0x0044D300
};
struct WaveNotificationPosition {
    unsigned int offset;
    void* event;
};
struct WaveNotificationMethods {
    void* query_interface;
    void* add_reference;
    unsigned int (__stdcall* release)(WaveNotification*);
    int (__stdcall* set_positions)(WaveNotification*, unsigned int count, const WaveNotificationPosition*);
};
struct WaveNotification { WaveNotificationMethods* methods; };
struct WaveDeviceMethods {
    void* query_interface;
    void* add_reference;
    unsigned int (__stdcall* release)(WaveDirectSoundDevice*);
    int (__stdcall* create_buffer)(WaveDirectSoundDevice*,
        const WaveBufferDescription*, WaveSecondaryBuffer** output, void* outer);
    void* get_caps;
    int (__stdcall* duplicate_buffer)(WaveDirectSoundDevice*, WaveSecondaryBuffer*, WaveSecondaryBuffer**);
    int (__stdcall* set_cooperative_level)(WaveDirectSoundDevice*, void* window, unsigned int level);
};
struct WaveDirectSoundDevice { WaveDeviceMethods* methods; };


struct NativeDeviceOwner {
    WaveDirectSoundDevice* device;
    // Window/level/bits are original stack inputs; channels and sample rate
    // are genuine private BX/EDI inputs of the complete original method.
    __declspec(noinline) int Configure(void* window, unsigned int level,
        unsigned short bits, unsigned short channels, unsigned int rate);
};
typedef char NativeWaveFormatSize[sizeof(WaveFormatImage)==18?1:-1];
typedef char NativeWaveDescriptionSize[sizeof(WaveBufferDescription)==36?1:-1];
typedef char NativeWaveSetFormatSlot[offsetof(WaveBufferMethods,set_format)==0x38?1:-1];
extern "C" {
int __stdcall Ordinal_11_00452170(const void*,WaveDirectSoundDevice**,void*);
__declspec(noinline) int __fastcall Sound_SetPrimaryFormat(
    unsigned short,unsigned short,unsigned int,WaveDirectSoundDevice**);
}
