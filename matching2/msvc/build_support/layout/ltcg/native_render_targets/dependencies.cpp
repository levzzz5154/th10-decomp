#include "th10/platform/text_log.hpp"
extern "C" TextLog_0044b810 g_log;
#include "logger.cpp"
#pragma code_seg(".text$a00screenshot")
int ScreenshotState::CaptureScreenshot(const char* name) {
    while (thread!=0) imp_Sleep(10);
    RenderSurface* back=0;
    device->methods->GetBackBuffer(device,0,0,0,&back);
    memset(&file_image,0,sizeof(file_image));
    file_image.type=0x4d42;
    file_image.offset=0x36;
    file_image.size=0x36;
    char* destination=filename;
    do { *destination++=*name; } while (*name++);
    if (format==0x16) {
        info=(BitmapInfoImage*)retail_malloc_00452706(0x2c);
        if (!info) goto allocation_failed;
        memset(info,0,0x2c);
        pixels=(unsigned char*)retail_malloc_00452706(0xe1000);
        if (!pixels) goto allocation_failed;
        file_image.size+=0xe1000;
        info->bits=24;
        info->size=40;
        info->width=640;
        info->height=480;
        info->planes=1;
        info->compression=0;
        RenderLock locked;
        back->methods->Lock(back,&locked,0,0);
        unsigned int offset=0;
        for (int row=479;row>=0;--row) {
            unsigned char* out=pixels+offset;
            unsigned char* in=locked.bits+locked.pitch*row;
            for (int col=0;col<640;++col) {
                memcpy(out,in,2);
                out[2]=in[2];
                in+=4;out+=3;
            }
            offset+=0x780;
        }
        back->methods->Unlock(back);
        data_00492134=retail_beginthread_00452eec(&ScreenshotWriter,0,0);
    } else if (format==0x17) g_log.Append(data_0046df38);
    else { g_log.Append(data_0046deb0);return 1; }
    if (back) back->methods->Release(back);
    return 0;
allocation_failed:
    g_log.Append(data_0046def0);
    if (back) back->methods->Release(back);
    return 0;
}
#pragma code_seg()
#pragma code_seg(".text$a02release")
void SprtCtrlTargetsView::ReleaseTargets() {
    for (int index=0;index<32;++index) {
        if (primary[index]) {
            primary[index]->methods->Release(primary[index]);
            primary[index]=0;
        }
    }
}
#pragma code_seg()
#pragma code_seg(".text$a10flush")
int SprtCtrlTargetsView::Flush() {
    int result=quad_count;
    if (result) {
        g_d3d_device->methods->Stage(g_d3d_device,0,6,0);
        g_d3d_device->methods->Stage(g_d3d_device,0,3,0);
        g_d3d_device->methods->SetFVF(g_d3d_device,0x144);
        const void* start=batch_start;
        g_d3d_device->methods->Draw(g_d3d_device,4,(unsigned int)(quad_count<<1),start,0x1c);
        batch_start=cursor;
        quad_count=0;
        result=++draw_calls;
    }
    return result;
}
#pragma code_seg()
