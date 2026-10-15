#include "th10/source_views/font_cache_init_d7bc6e_0.hpp"
extern "C" void __cdecl InitializeFontCache_00437a00() {
    if (!FontSurface_Create_00436af0(&g_font_atlas_surface,0x400,0x40,0x1a))
        FontSurface_Create_00436af0(&g_font_atlas_surface,0x400,0x40,0x15);
    unsigned char* bytes=(unsigned char*)&g_font_atlas_surface;
    for (unsigned int index=0;index<256;++index) {
        unsigned short next=g_rng.Next();
        bytes[index]=(unsigned char)(next>>9);
    }
    g_font_height_60[14]=CreateFontA(32,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[13]=CreateFontA(34,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[12]=CreateFontA(36,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[11]=CreateFontA(38,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[10]=CreateFontA(40,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[9]=CreateFontA(42,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[8]=CreateFontA(44,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[7]=CreateFontA(46,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[6]=CreateFontA(48,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[5]=CreateFontA(50,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[4]=CreateFontA(52,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[3]=CreateFontA(54,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[2]=CreateFontA(56,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[1]=CreateFontA(58,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
    g_font_height_60[0]=CreateFontA(60,0,0,0,400,0,0,0,0x80,0,0,4,0x11,str_ms_gothic);
}
