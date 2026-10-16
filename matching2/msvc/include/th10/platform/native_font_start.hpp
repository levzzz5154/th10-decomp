#pragma once
#include <stddef.h>
#include <string.h>
struct GdiSurface2;
struct FontBitmapV4 {
    unsigned long size;
    long width,height;
    unsigned short planes,bit_count;
    unsigned long compression,image_size;
    long x_pixels_per_meter,y_pixels_per_meter;
    unsigned long colors_used,colors_important;
    unsigned long red_mask,green_mask,blue_mask,alpha_mask;
    unsigned long remaining_v4[13];
};
struct FontFormatRecord { int kind,bits_per_pixel;unsigned int alpha_mask,red_mask,green_mask,blue_mask; };
struct FontRandomState {
    unsigned short seed,upper_word;
    unsigned int generations;
    unsigned short Next() {
        unsigned int value;memcpy(&value,this,sizeof(value));
        value^=0x9630;value-=0x6553;
        seed=(unsigned short)(((unsigned short)value>>14)+(value<<2));
        ++generations;return seed;
    }
};
typedef char FontRandomSize[(sizeof(FontRandomState)==8 && offsetof(FontRandomState,seed)==0 && offsetof(FontRandomState,upper_word)==2 && offsetof(FontRandomState,generations)==4)?1:-1];
typedef char FontBitmapSize[sizeof(FontBitmapV4)==108?1:-1];
extern "C" {
 extern FontFormatRecord g_font_formats[];
 extern GdiSurface2 g_font_atlas_surface;
 extern FontRandomState g_rng;

 extern void* g_font_height_60[15];
 extern const char str_ms_gothic[];
 extern void* (__stdcall* imp_CreateDIBSection)(void*,const FontBitmapV4*,unsigned int,void**,void*,unsigned int);
 extern void* (__stdcall* imp_CreateCompatibleDC)(void*);
 __declspec(dllimport) void* __stdcall CreateFontA(int,int,int,int,int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,const char*);
}
__declspec(noinline) bool __stdcall FontSurface_Create(GdiSurface2*,int,int,int);
bool __stdcall FontSurface_CreateWithFallback2(GdiSurface2*,int,int,int);
extern "C" __declspec(noinline) void __cdecl InitializeFontCache();
