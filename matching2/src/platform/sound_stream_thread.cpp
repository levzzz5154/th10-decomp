#include "th10/platform/sound_stream_thread.hpp"
#include "th10/game/player_motion.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


// 0x0043D690 - Start the streaming-sound worker thread. The source name is
// copied into the stream's name buffer; without a device and format block
// the call fails. Otherwise the previous stream stops, the ring-buffer size
// is derived from the data size (quartered, clamped to 0x3FFFFFFF, rounded
// down to a whole block), the wake event and worker thread are created, and
// the stream is opened against that buffer. Returns 0 on success, -1 else.
int SoundStream_StartThread(
    const char* source_name, char* name_buffer, void* device,
    void* format_block, void (*stop_previous)(void), unsigned int data_size,
    unsigned int block_align, void* (*create_event)(void), void** event_slot,
    void* (*create_thread)(void* argument, unsigned int* thread_id_out),
    void* thread_argument, void** thread_slot, unsigned int* thread_id_slot,
    int (*open_stream)(unsigned int buffer_bytes, void* event_handle)) {
	std::strcpy(name_buffer, source_name);
	if (format_block == 0 || device == 0) return -1;
	stop_previous();
	unsigned int quarter = ((data_size * block_align) & 0x3FFFFFFFu) >> 2;
	unsigned int buffer_bytes = quarter - quarter % block_align;
	*event_slot = create_event();
	*thread_slot = create_thread(thread_argument, thread_id_slot);
	int result = open_stream(buffer_bytes, *event_slot);
	return result >= 0 ? 0 : -1;
}
