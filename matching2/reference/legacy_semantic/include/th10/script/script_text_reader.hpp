#pragma once

// Script text line reader (retail 0x00419F40).

// --- 0x00419F40 --------------------------------------------------------------
char* ScriptText_NextLine(char* line_buffer, unsigned int buffer_size,
                          char* cursor, unsigned int* remaining,
                          char* (*find_char)(char* text, char wanted),
                          void (*post_process)(void));
