#include "th10/game/music_room.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


// 0x00426520 - Load the music-room track list file. The header's base
// extents (+0x10/+0x14) are pre-scaled by the given sine into +0x18/+0x1C,
// then every entry in the 8-byte-stride table at +0x110 has its payload
// offset relocated into a pointer and each 0x34-byte track record's four
// accent indices resolved through the color/parameter lookup tables.
int MusicRoom_LoadTrackList(Byte** slot,
                            Byte* (*load_file)(unsigned int* size_out,
                                                     int bank),
                            float sine_value,
                            const Word* accent_table_a,
                            const Word* accent_table_b,
                            const Word* accent_table_c,
                            const Word* accent_table_d) {
	unsigned int size = 0;
	Byte* data = load_file(&size, 0);
	*slot = data;
	if (data == 0) return -1;
	*(float*)(data + 0x18) = sine_value * *(float*)(data + 0x10);
	*(float*)(data + 0x1C) = sine_value * *(float*)(data + 0x14);
	int entry_count = *(Half*)(data + 2);
	for (int entry = 0; entry < entry_count; ++entry) {
		// Each 8-byte table entry holds a file offset that is relocated in
		// place into a payload pointer.
		Byte** payload_slot = (Byte**)(data + 0x110 + entry * 8);
		unsigned int payload_offset = *(Word*)payload_slot;
		*payload_slot = data + payload_offset;
		char* record = (char*)*payload_slot;
		while (*record >= 0) {
			*(Word*)(record + 0x24) =
			    accent_table_a[*(int*)(record + 0x24)];
			*(Word*)(record + 0x28) =
			    accent_table_b[*(int*)(record + 0x28)];
			*(Word*)(record + 0x2C) =
			    accent_table_c[*(int*)(record + 0x2C)];
			*(Word*)(record + 0x30) =
			    accent_table_d[*(int*)(record + 0x30)];
			record += 0x34;
		}
	}
	return 0;
}
