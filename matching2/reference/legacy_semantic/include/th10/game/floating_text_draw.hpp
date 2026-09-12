#pragma once

// Reverse-order floating text record draw (retail 0x0042B780).
// Retail function 0x0042B780.
struct FloatingTextRecord{unsigned char text[12];float x,y;unsigned color;int mode;float divisor;unsigned char active,count;};struct FloatingGlyphDraw{float x,y;unsigned color;unsigned char alpha;int glyph_index;};struct FloatingTextEnv{unsigned view_flags;int*alpha_blend_state;float player_position[2];void(*disable_alpha_blend)();void(*draw_glyph)(const FloatingGlyphDraw*);};int TextBatch_DrawReverseGlyphs(const FloatingTextRecord[723],const FloatingTextEnv*);
