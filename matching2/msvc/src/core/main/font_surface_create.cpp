// 0x00436AF0: give a font surface a fresh top-down DIB of the requested size
// and pixel format, selected into a new memory DC.
//
// The last nine assignments are scheduled by the compiler; this is the one
// source order that reproduces retail's.
#include "th10/platform/native_font_start.hpp"
#pragma code_seg(".text$a06surface")
bool __stdcall FontSurface_Create_00436af0(GdiSurface_00436a30* surface,int width,int height,int format) {
    ReleaseSurface_00436a30(surface);
    FontBitmapV4 bitmap;
    memset(&bitmap,0,sizeof(bitmap));
    unsigned int index=0;
    while (data_00474918[index].kind!=-1 && data_00474918[index].kind!=format) ++index;
    // Preserve the original sentinel and native-address guard, including an unknown format.
    FontFormatRecord* entry=0;
    if (format!=-1) entry=(FontFormatRecord*)((unsigned int)data_00474918+index*sizeof(FontFormatRecord));
    if (!entry) return false;
    int stride=((entry->bits_per_pixel*width)/8+3)/4*4;
    bitmap.height=-1-height;
    bitmap.bit_count=(unsigned short)entry->bits_per_pixel;
    bitmap.size=sizeof(bitmap);bitmap.width=width;bitmap.planes=1;
    bitmap.image_size=stride*height;
    if (format!=0x18 && format!=0x16) {
        bitmap.compression=3;
        bitmap.red_mask=entry->red_mask;bitmap.green_mask=entry->green_mask;
        bitmap.blue_mask=entry->blue_mask;bitmap.alpha_mask=entry->alpha_mask;
    }
    void* pixels;
    void* dib=imp_CreateDIBSection(0,&bitmap,0,&pixels,0,0);
    if (!dib) return false;
    memset(pixels,0,bitmap.image_size);
    void* dc=imp_CreateCompatibleDC(0);
    void* previous=imp_SelectObject(dc,dib);
    surface->pixels=pixels;
    surface->previous_bitmap=previous;
    surface->stride=stride;
    surface->image_size=bitmap.image_size;
    surface->dc=dc;
    surface->bitmap=dib;
    surface->width=width;
    surface->height=height;
    surface->font_index=format;
    return true;
}
#pragma code_seg()
