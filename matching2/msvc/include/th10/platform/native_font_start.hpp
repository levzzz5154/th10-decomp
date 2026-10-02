#pragma once
#include <stddef.h>
#include <string.h>
struct GdiSurface_00436a30;
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
 extern FontFormatRecord data_00474918[];
 extern GdiSurface_00436a30 data_00474cb0;
 extern FontRandomState data_004918b0;

 extern void* data_00491868[15];
 extern const char data_0046f36c[];
 extern void* (__stdcall* data_00466024)(void*,const FontBitmapV4*,unsigned int,void**,void*,unsigned int);
 extern void* (__stdcall* data_00466020)(void*);
 __declspec(dllimport) void* __stdcall CreateFontA(int,int,int,int,int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,const char*);
}
__declspec(noinline) bool __stdcall FontSurface_Create_00436af0(GdiSurface_00436a30*,int,int,int);
bool __stdcall FontSurface_CreateWithFallback_00436aa0(GdiSurface_00436a30*,int,int,int);
extern "C" __declspec(noinline) void __cdecl InitializeFontCache_00437a00();
