#include "th10/game/ascii_overlay_callbacks.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x00447AE0 - Format a shadowed ASCII overlay string. The text is printed
// into the overlay's line buffer, the draw position is centered using the
// glyph column width (default 0x11 when the override byte is zero), and the
// overlay is submitted with its shadow bit before the dirty flag is set.
void AsciiOverlay_FormatShadowed(
    char* text_buffer, unsigned int buffer_capacity, Byte column_byte,
    void* font_page, Word shadow_flag, Word* dirty_flags,
    Word color,
    void (*submit)(void* font_page, int centered_offset, Word color,
                   Word shadow_flag),
    const char* format, ...) {
	unsigned int columns = column_byte != 0 ? column_byte : 0x11u;
	va_list arguments;
	va_start(arguments, format);
	std::vsnprintf(text_buffer, buffer_capacity, format, arguments);
	va_end(arguments);
	unsigned int length = (unsigned int)std::strlen(text_buffer);
	int centered_offset = (int)(((columns - 1) * length) >> 1);
	submit(font_page, centered_offset, color, shadow_flag & 1u);
	*dirty_flags |= 1u;
}

// 0x0043C410 - ASCII manager draw callback: draw every registered overlay
// group and report success to the scheduler.
int AsciiManager_OnDraw(void (*draw_all)(void)) {
	draw_all();
	return 1;
}

// 0x0043C2C0 - text draw-state reset callback.
int Ascii_OnResetDevice(void (*reset_text_state)(void)) {
	reset_text_state();
	return 1;
}
