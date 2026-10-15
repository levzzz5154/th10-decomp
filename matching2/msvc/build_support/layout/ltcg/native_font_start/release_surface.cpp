// 0x00436A30: release a GDI drawing surface's DC and DIB section.
extern "C" void* (__stdcall* imp_SelectObject)(void* dc, void* object);
extern "C" int (__stdcall* imp_DeleteDC)(void* dc);
extern "C" int (__stdcall* imp_DeleteObject)(void* object);

struct GdiSurface_00436a30 {
    unsigned char unknown_000[0x100];
    int font_index;
    int width;
    int height;
    unsigned int image_size;
    int stride;
    void* dc;
    void* previous_bitmap;
    void* bitmap;
    void* pixels;
};

#pragma code_seg(".text$a04release")
__declspec(noinline) bool __stdcall ReleaseSurface_00436a30(GdiSurface_00436a30* surface) {
    if (surface->dc) {
        imp_SelectObject(surface->dc, surface->previous_bitmap);
        imp_DeleteDC(surface->dc);
        imp_DeleteObject(surface->bitmap);
        surface->width = 0;
        surface->height = 0;
        surface->dc = 0;
        surface->bitmap = 0;
        surface->previous_bitmap = 0;
        surface->pixels = 0;
        surface->font_index = -1;
        return true;
    }
    return false;
}
#pragma code_seg()
