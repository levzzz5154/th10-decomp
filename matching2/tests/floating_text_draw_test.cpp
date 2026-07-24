#include "th10/game/floating_text_draw.hpp"
#include <cstdio>
#include <cstring>
static int b,n;static FloatingGlyphDraw g[4];static void B(){b++;}static void G(const FloatingGlyphDraw*x){g[n++]=*x;}int main(){static FloatingTextRecord r[723];r[0].active=1;r[0].count=2;r[0].text[0]=1;r[0].text[1]=2;r[0].mode=8;int blend=1;FloatingTextEnv e={0,&blend,{0,0},B,G};if(TextBatch_DrawReverseGlyphs(r,&e)!=1||b!=1||blend||n!=2||g[0].glyph_index!=198||g[1].glyph_index!=197)return 1;std::puts("recovery_batch40_test passed");}
