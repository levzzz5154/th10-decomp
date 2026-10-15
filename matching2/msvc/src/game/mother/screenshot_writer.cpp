// 0x00420540: asynchronous BMP writer launched by the screenshot capture.
// The capture allocates the DIB header and bottom-up 640x480 BGR pixels.
// This entry writes the three BMP segments through the shared file handle,
// then frees both temporary buffers and clears the thread handle.
// The _beginthread caller passes a null argument. The ignored stack argument
// remains caller-cleaned under the public cdecl callback convention.
// Write failures preserve the retail close-and-unlock sequence: the shared
// handle is not changed here, so subsequent checks still see its stored value.
extern "C" int __stdcall File_OpenSharedWrite_0044b620(const char* path);
extern "C" void __cdecl crt_free(void* memory);
extern "C" __declspec(dllimport) int __stdcall WriteFile(
    void* file, const void* bytes, unsigned long length,
    unsigned long* written, void* overlapped);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void* handle);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* section);
extern "C" void* g_file_probe_handle;
extern "C" unsigned char g_file_critical_section;
extern "C" unsigned char g_file_critical_depth;
extern "C" unsigned char screenshot_bitmap_header_00492138[14];
extern "C" void* screenshot_dib_header_00492148;
extern "C" void* screenshot_pixels_0049214c;
extern "C" char screenshot_path_00492150[];
extern "C" unsigned long screenshot_thread_00492134;

extern "C" void __cdecl ScreenshotWriter(void*) {
    unsigned long written;
    File_OpenSharedWrite_0044b620(screenshot_path_00492150);
    if (g_file_probe_handle != (void*)-1) {
        WriteFile(g_file_probe_handle, screenshot_bitmap_header_00492138, 14, &written, 0);
        if (written != 14) {
            CloseHandle(g_file_probe_handle);
            LeaveCriticalSection(&g_file_critical_section);
            --g_file_critical_depth;
        }
        if (g_file_probe_handle != (void*)-1) {
            WriteFile(g_file_probe_handle, screenshot_dib_header_00492148, 40, &written, 0);
            if (written != 40) {
                CloseHandle(g_file_probe_handle);
                LeaveCriticalSection(&g_file_critical_section);
                --g_file_critical_depth;
            }
        }
        if (g_file_probe_handle != (void*)-1) {
            WriteFile(g_file_probe_handle, screenshot_pixels_0049214c, 0xe1000, &written, 0);
            if (written != 0xe1000) {
                CloseHandle(g_file_probe_handle);
                LeaveCriticalSection(&g_file_critical_section);
                --g_file_critical_depth;
            }
        }
        if (g_file_probe_handle != (void*)-1) {
            CloseHandle(g_file_probe_handle);
            LeaveCriticalSection(&g_file_critical_section);
            --g_file_critical_depth;
        }
    }
    if (screenshot_dib_header_00492148 != 0) {
        crt_free(screenshot_dib_header_00492148);
        screenshot_dib_header_00492148 = 0;
    }
    if (screenshot_pixels_0049214c != 0) {
        crt_free(screenshot_pixels_0049214c);
        screenshot_pixels_0049214c = 0;
    }
    screenshot_thread_00492134 = 0;
}
