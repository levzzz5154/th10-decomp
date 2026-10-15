// 0x00420670..0x00420868: capture the back buffer for a screenshot.
//
// Waits for a pending screenshot to finish, fetches the back buffer and fills
// in the bitmap file header and the file name. For a 32-bit back buffer
// (D3DFMT_X8R8G8B8) it allocates the info header and a 640x480 24-bit pixel
// buffer, copies the rows bottom-up and starts the writer thread (0x00420540).
// A 16-bit back buffer (D3DFMT_R5G6B5) only logs that screenshots are not
// available.
//
// The application object arrives in ESI and the name in EAX.
#include "th10/app/screenshot_capture_00420670.hpp"
#include <string.h>

#pragma code_seg(".text$00cshot")
int GameApp_00420670::CaptureScreenshot(const char* name) {
    while (screenshot_thread != 0)
        Sleep(10);

    Direct3DSurface_00420670* back_buffer = 0;
    device->methods->GetBackBuffer(device, 0, 0, 0, &back_buffer);

    memset(&file_header, 0, sizeof(file_header));
    file_header.type = 0x4D42;      // "BM"
    file_header.offset = 0x36;
    file_header.size = 0x36;
    strcpy(filename, name);

    switch (back_buffer_format) {
    case 0x16: {
        info_header = (BitmapInfoHeader_00420670*)asm_malloc_00452706(sizeof(BitmapInfoHeader_00420670));
        if (info_header == 0) {
            g_log.Append(data_0046def0);
            goto done;
        }
        memset(info_header, 0, sizeof(BitmapInfoHeader_00420670));
        pixels = (unsigned char*)asm_malloc_00452706(640 * 480 * 3);
        if (pixels == 0) {
            g_log.Append(data_0046def0);
            goto done;
        }
        file_header.size += 640 * 480 * 3;
        info_header->bit_count = 24;
        info_header->size = 40;
        info_header->width = 640;
        info_header->height = 480;
        info_header->planes = 1;
        info_header->compression = 0;

        LockedRect_00420670 locked;
        back_buffer->methods->LockRect(back_buffer, &locked, 0, 0);
        int row = 479;
        int offset = 0;
        do {
            unsigned char* out = pixels + offset;
            unsigned char* in = locked.bits + locked.pitch * row;
            for (int column = 0; column < 640; ++column) {
                *(unsigned short*)out = *(unsigned short*)in;
                out[2] = in[2];
                in += 4;
                out += 3;
            }
            --row;
            offset += 640 * 3;
        } while (row > -1);
        back_buffer->methods->UnlockRect(back_buffer);

        g_application.screenshot_thread = asm_beginthread_00452eec(ScreenshotWriter, 0, 0);
        break;
    }
    case 0x17:
        g_log.Append(data_0046df38);
        break;
    default:
        g_log.Append(data_0046deb0);
        return 1;
    }

done:
    if (back_buffer != 0)
        back_buffer->methods->Release(back_buffer);
    return 0;
}
#pragma code_seg()
