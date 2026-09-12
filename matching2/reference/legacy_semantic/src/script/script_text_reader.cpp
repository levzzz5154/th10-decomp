#include "th10/script/script_text_reader.hpp"
#include "th10/game/player_motion.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


// 0x00419F40 - Pull the next meaningful line out of a script text buffer.
// The line buffer is zeroed, then lines are consumed one at a time: each
// line is copied (clamped to the buffer), trailing newline characters are
// skipped, anything after a '#' is stripped, and the post-processor runs.
// Blank results keep consuming; when no newline remains the tail of the
// text is copied and the remaining count drops to zero.
char* ScriptText_NextLine(char* line_buffer, unsigned int buffer_size,
                          char* cursor, unsigned int* remaining,
                          char* (*find_char)(char* text, char wanted),
                          void (*post_process)(void)) {
	for (unsigned int index = 0; index < buffer_size; ++index) {
		line_buffer[index] = 0;
	}
	if (line_buffer[0] != 0) return cursor;
	for (;;) {
		char* line_end = find_char(cursor, '\n');
		if (line_end == 0) line_end = find_char(cursor, '\r');
		if (line_end == 0) break;
		unsigned int line_length = (unsigned int)(line_end - cursor);
		if (line_length > buffer_size - 1) line_length = buffer_size - 1;
		std::memcpy(line_buffer, cursor, line_length);
		*remaining -= (unsigned int)(line_end - cursor);
		while (*line_end == '\n' || *line_end == '\r') {
			++line_end;
			*remaining -= 1;
		}
		char* comment = find_char(line_buffer, '#');
		if (comment != 0) {
			for (char* zero = comment; zero < line_buffer + buffer_size;
			     ++zero) {
				*zero = 0;
			}
		}
		post_process();
		cursor = line_end;
		if (line_buffer[0] != 0) return cursor;
	}
	unsigned int tail = *remaining;
	if (tail > buffer_size - 1) tail = buffer_size - 1;
	std::memcpy(line_buffer, cursor, tail);
	*remaining = 0;
	return cursor;
}
