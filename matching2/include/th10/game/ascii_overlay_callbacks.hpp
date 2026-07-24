#pragma once

// ASCII overlay shadowed formatting, draw callback, and device-reset callback (retail 0x00447AE0, 0x0043C410, 0x0043C2C0).
#include "th10/util/scalars.hpp"

// --- 0x00447AE0 --------------------------------------------------------------
void AsciiOverlay_FormatShadowed(
    char* text_buffer, unsigned int buffer_capacity, Byte column_byte,
    void* font_page, Word shadow_flag, Word* dirty_flags,
    Word color,
    void (*submit)(void* font_page, int centered_offset, Word color,
                   Word shadow_flag),
    const char* format, ...);

// --- 0x0043C410 --------------------------------------------------------------
int AsciiManager_OnDraw(void (*draw_all)(void));

int Ascii_OnResetDevice(void (*reset_text_state)(void));
